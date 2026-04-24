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
    ~Graph();

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

    void save(const std::string&) const;
    void load(const std::string&);

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

// Queue implementation

template<typename T>
Graph<T>::Queue::Queue(size_t capacity) : head(0), tail(0), capacity(capacity + 1) {
    this->data = new size_t[capacity];
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
