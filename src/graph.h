#pragma once

#include "array.h"
#include "node.h"

#include <cstddef>
#include <ostream>
#include <string>

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
        Queue(size_t);
        ~Queue();

        void enqueue(size_t idx);
        size_t dequeue();
        bool isEmpty() const;
    };
};
