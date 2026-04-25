#pragma once

#include "array.h"
#include "node.h"

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>

template<typename T>
class Graph {
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

    void save(const std::string& filename) const;
    void load(const std::string& filename);

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

    this->nodes.removeAt(idx);

    for (size_t i = 0; i < this->getNodeCount(); i++) {
        // Decrement edge count if needed
        if (this->matrix[i][idx])
            this->edgeCount--;

        this->matrix[i].removeAt(idx);
    }

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
    // TODO: implement
    return false;
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
void Graph<T>::save(const std::string& filename) const {
    // TODO: implement
}

template<typename T>
void Graph<T>::load(const std::string& filename) {
    // TODO: implement
}
