#pragma once

#include <iostream>
#include <ostream>

/// Wraps a single piece of data for use in `Graph`.
/// @tparam T The data type stored by the node.
template<typename T>
class Node {
    T data;

public:
    /// Default constructor.
    Node();
    /// Constructs a node with the given data.
    Node(const T&);
    /// Deep copy assignment.
    Node& operator=(const Node&);
    /// Equality comparison based on stored data.
    bool operator==(const Node<T>&) const;
    /// Returns a const reference to the stored data.
    const T& getData() const;
    /// Replaces the stored data.
    void setData(const T&);
};

template<typename T>
Node<T>::Node() {}

template<typename T>
Node<T>::Node(const T& data) : data(data) {}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& other) {
    this->data = other.data;

    return *this;
}

template<typename T>
bool Node<T>::operator==(const Node<T>& other) const {
    return this->data == other.data;
}

template<typename T>
const T& Node<T>::getData() const {
    return this->data;
}

template<typename T>
void Node<T>::setData(const T& data) {
    this->data = data;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
    os << node.getData();
    return os;
}
