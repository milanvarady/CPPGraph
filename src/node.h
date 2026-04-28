#pragma once

#include <iostream>
#include <ostream>

/// Wraps a single piece of data for use in `Graph`.
/// @tparam T The data type stored by the node.
template<typename T>
class Node {
    T data;

public:
    Node();
    Node(const T&);
    Node& operator=(const Node&);
    bool operator==(const Node<T>&) const;
    const T& getData() const;
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
