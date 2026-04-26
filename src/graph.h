#pragma once

#include "array.h"
#include "node.h"
#include "persistable.h"

#include <cstddef>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>

template<typename T>
class Graph {
    static_assert(std::is_base_of<Persistable, T>::value, "T must derive from Persistable");

    Array<Node<T>> nodes;
    Array<Array<bool>> matrix;
    size_t edgeCount;

public:
    Graph();
    Graph(const Graph&);

    Graph& operator=(const Graph&);

    void addNode(const T&);
    void removeNode(size_t idx);
    void addEdge(size_t from_idx, size_t to_idx);
    void removeEdge(size_t from_idx, size_t to_idx);

    bool hasEdge(size_t from_idx, size_t to_idx) const;
    size_t getNodeCount() const;
    size_t getEdgeCount() const;
    bool isConnected() const;
    const Node<T>& getNode(size_t idx) const;

    void print(std::ostream&) const;

    void save(const std::string& path) const;
    void load(const std::string& path);

private:
    class Queue {
        size_t* data;
        size_t head;
        size_t tail;
        size_t capacity;

    public:
        Queue(size_t capacity);
        ~Queue();

        void enqueue(size_t idx);
        size_t dequeue();
        bool isEmpty() const;
    };
};

// Graph exceptions

namespace GraphError {
class SelfLoopNotAllowed : public std::logic_error {
public:
    SelfLoopNotAllowed() : std::logic_error("Self-loop not allowed") {}
};
} // namespace GraphError

// Queue implementation

template<typename T>
Graph<T>::Queue::Queue(size_t capacity) : head(0), tail(0), capacity(capacity + 1) {
    this->data = new size_t[this->capacity];
}

template<typename T>
Graph<T>::Queue::~Queue() {
    delete[] this->data;
}

template<typename T>
void Graph<T>::Queue::enqueue(size_t idx) {
    this->data[this->tail] = idx;
    this->tail = (this->tail + 1) % this->capacity;
}

template<typename T>
size_t Graph<T>::Queue::dequeue() {
    if (this->isEmpty())
        throw std::out_of_range("Queue is empty");

    size_t head_data = this->data[head];
    this->head = (this->head + 1) % this->capacity;

    return head_data;
}

template<typename T>
bool Graph<T>::Queue::isEmpty() const {
    return this->head == this->tail;
}

// Graph implementation

template<typename T>
Graph<T>::Graph() : edgeCount(0) {}

template<typename T>
Graph<T>::Graph(const Graph& other) {
    this->nodes = other.nodes;
    this->matrix = other.matrix;
    this->edgeCount = other.edgeCount;
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph& other) {
    if (this == &other)
        return *this;

    this->nodes = other.nodes;
    this->matrix = other.matrix;
    this->edgeCount = other.edgeCount;

    return *this;
}

template<typename T>
void Graph<T>::addNode(const T& node) {
    size_t original_node_count = this->getNodeCount();

    // Add new node
    this->nodes.pushBack(node);

    // Extend existing matrix rows
    for (size_t i = 0; i < original_node_count; i++) {
        this->matrix[i].pushBack(false);
    }

    // Add new row filled with 0s
    const Array<bool> new_row = Array<bool>((original_node_count + 1), false);
    this->matrix.pushBack(new_row);
}

template<typename T>
void Graph<T>::removeNode(size_t idx) {
    if (idx >= this->getNodeCount())
        throw std::out_of_range("Graph removeNode out of range");

    // Count edges to remove
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        if (this->matrix[idx][i])
            this->edgeCount--;
    }

    // Remove node
    this->nodes.removeAt(idx);

    // Remove column from each row
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        this->matrix[i].removeAt(idx);
    }

    // Remove the row
    this->matrix.removeAt(idx);
}

template<typename T>
void Graph<T>::addEdge(size_t from_idx, size_t to_idx) {
    if (from_idx >= this->getNodeCount() || to_idx >= this->getNodeCount())
        throw std::out_of_range("Graph addEdge out of range");

    // Check loop
    if (from_idx == to_idx)
        throw GraphError::SelfLoopNotAllowed();

    // No-op if already exists
    if (this->matrix[from_idx][to_idx])
        return;

    this->matrix[from_idx][to_idx] = true;
    this->matrix[to_idx][from_idx] = true;

    this->edgeCount++;
}

template<typename T>
void Graph<T>::removeEdge(size_t from_idx, size_t to_idx) {
    if (from_idx >= this->getNodeCount() || to_idx >= this->getNodeCount())
        throw std::out_of_range("Graph removeEdge out of range");

    // No-op if nothing to remove
    if (!this->matrix[from_idx][to_idx])
        return;

    this->matrix[from_idx][to_idx] = false;
    this->matrix[to_idx][from_idx] = false;

    this->edgeCount--;
}

template<typename T>
bool Graph<T>::hasEdge(size_t from_idx, size_t to_idx) const {
    if (from_idx >= this->getNodeCount() || to_idx >= this->getNodeCount())
        throw std::out_of_range("Graph hasEdge out of range");

    return this->matrix[from_idx][to_idx];
}

template<typename T>
size_t Graph<T>::getNodeCount() const {
    return this->nodes.getSize();
}

template<typename T>
size_t Graph<T>::getEdgeCount() const {
    return this->edgeCount;
}

template<typename T>
bool Graph<T>::isConnected() const {
    // Special cases
    if (this->getNodeCount() == 0 || this->getNodeCount() == 1)
        return true;

    // Stores nodes that need to be explored
    Queue queue = Queue(this->getNodeCount());

    // Keep track of explored nodes
    Array<bool> explored = Array<bool>(this->getNodeCount(), false);

    // Label first node as explored
    explored.first() = true;

    // Enqueue root
    queue.enqueue(0);

    // By keeping track of the number of explored nodes
    // we don't have to check the explored array at the end
    // to check if all nodes were explored
    size_t exploredNodeCount = 1;

    // Traverse graph
    while (!queue.isEmpty()) {
        size_t node_idx = queue.dequeue();

        for (size_t i = 0; i < this->getNodeCount(); i++) {
            if (this->matrix[node_idx][i]) {
                if (!explored[i]) {
                    explored[i] = true;
                    exploredNodeCount++;
                    queue.enqueue(i);
                }
            }
        }
    }

    return exploredNodeCount == this->getNodeCount();
}

template<typename T>
const Node<T>& Graph<T>::getNode(size_t idx) const {
    if (idx >= this->getNodeCount())
        throw std::out_of_range("Graph getNode out of range");

    return this->nodes[idx];
}

template<typename T>
void Graph<T>::print(std::ostream& os) const {
    os << "Node count: " << this->getNodeCount() << std::endl;
    os << "Edge count: " << this->getEdgeCount() << std::endl;
    os << std::endl;

    // Print nodes
    os << "Nodes: ";
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        os << this->nodes[i];

        if (i != (this->getNodeCount() - 1))
            os << ", ";
    }

    os << std::endl;
    os << "Matrix: " << std::endl;
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        for (size_t j = 0; j < this->getNodeCount(); j++) {
            os << this->matrix[i][j] << ' ';
        }
        os << std::endl;
    }
}

template<typename T>
void Graph<T>::save(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + path);

    file << "CPPGraph v1.0" << std::endl;
    file << this->getNodeCount() << std::endl;
    file << this->getEdgeCount() << std::endl;

    // Print nodes
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        file << this->nodes[i].getData().encode() << std::endl;
    }

    // Print adjacency matrix
    for (size_t i = 0; i < this->getNodeCount(); i++) {
        for (size_t j = 0; j < this->getNodeCount(); j++) {
            if (j > 0)
                file << ' ';
            file << (this->matrix[i][j] ? '1' : '0');
        }
        file << std::endl;
    }
}

template<typename T>
void Graph<T>::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + path);

    // Parse header
    std::string header;
    file >> header;

    if (header != "CPPGraph")
        throw std::runtime_error("Invalid file format");

    // Parse version
    std::string version;
    file >> version;

    // Consume leftover newline char
    file.ignore();

    // Clear current data
    this->nodes.clear();
    this->matrix.clear();

    // Parse node and edge count
    size_t nodeCount;
    file >> nodeCount;
    file.ignore();
    file >> this->edgeCount;
    file.ignore();

    // Load node array
    for (size_t i = 0; i < nodeCount; i++) {
        std::string encoded;
        std::getline(file, encoded);
        this->nodes.pushBack(Node<T>(T(encoded)));
    }

    // Load matrix
    for (size_t i = 0; i < nodeCount; i++) {
        matrix.pushBack(Array<bool>());
        for (size_t j = 0; j < nodeCount; j++) {
            int cell;
            file >> cell;
            matrix[i].pushBack(cell != 0);
        }
    }
}
