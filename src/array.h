#pragma once

#include <cstddef>
#include <stdexcept>

/// Dynamic array with automatic capacity management.
/// @tparam T Element type. Must be default-constructible and copy-assignable.
template<typename T>
class Array {
    T* data;
    size_t size;
    size_t capacity;

public:
    /// Creates an empty array with given initial capacity.
    /// @param capacity Initial capacity (default 10, minimum 1).
    Array(size_t capacity = 10);

    /// Creates an array of given size, filled with a default value.
    Array(size_t size, T default_value);

    /// Copy constructor. Deep copies all elements.
    Array(const Array&);
    /// Destructor. Frees the underlying buffer.
    ~Array();
    /// Deep copy assignment.
    Array& operator=(const Array&);

    /// Element access with bounds checking.
    /// @throw `std::out_of_range` if `idx` >= `size`.
    T& operator[](size_t);
    const T& operator[](size_t) const;

    /// Returns reference to the first element.
    /// @throw `std::out_of_range` if the array is empty.
    T& first();

    /// Returns the current number of elements.
    size_t getSize() const;

    /// Appends an element. Doubles capacity if full.
    void pushBack(const T&);

    /// Removes element at index, shifts remaining elements down.
    /// @throw `std::out_of_range` if `idx` >= `size`.
    void removeAt(size_t);

    /// Removes all elements. Keeps allocated capacity.
    void clear();
};

template<typename T>
Array<T>::Array(size_t capacity) : size(0), capacity(capacity > 0 ? capacity : 1) {
    this->data = new T[this->capacity];
}

template<typename T>
Array<T>::Array(size_t size, T default_value) : size(size), capacity(size > 0 ? size : 1) {
    this->data = new T[this->capacity];

    for (size_t i = 0; i < this->size; i++) {
        this->data[i] = default_value;
    }
}

template<typename T>
Array<T>::Array(const Array& other) {
    this->size = other.size;
    this->capacity = other.capacity;
    this->data = new T[this->capacity];

    for (size_t i = 0; i < this->size; i++) {
        this->data[i] = other[i];
    }
}

template<typename T>
Array<T>::~Array() {
    delete[] this->data;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this == &other)
        return *this;

    delete[] this->data;
    this->size = other.size;
    this->capacity = other.capacity;
    this->data = new T[this->capacity];

    for (size_t i = 0; i < this->size; i++) {
        this->data[i] = other[i];
    }

    return *this;
}

template<typename T>
T& Array<T>::operator[](size_t idx) {
    if (idx >= this->size)
        throw std::out_of_range("Array [] operator out of bounds");

    return this->data[idx];
}

template<typename T>
const T& Array<T>::operator[](size_t idx) const {
    if (idx >= this->size)
        throw std::out_of_range("Array [] operator out of bounds");

    return this->data[idx];
}

template<typename T>
T& Array<T>::first() {
    if (this->size < 1)
        throw std::out_of_range("Array first: array is empty");

    return this->data[0];
}

template<typename T>
size_t Array<T>::getSize() const {
    return this->size;
}

template<typename T>
void Array<T>::pushBack(const T& item) {
    // Expand capacity if needed
    if (this->size >= this->capacity) {
        this->capacity *= 2;
        T* tmp = new T[this->capacity];

        for (size_t i = 0; i < this->size; i++) {
            tmp[i] = this->data[i];
        }

        delete[] this->data;
        this->data = tmp;
    }

    // Add item
    this->data[size++] = item;
}

template<typename T>
void Array<T>::removeAt(size_t idx) {
    if (idx >= this->size)
        throw std::out_of_range("Array removeAt out of bounds");

    for (size_t i = idx; i < (this->size - 1); i++) {
        this->data[i] = this->data[i + 1];
    }

    size--;
}

template<typename T>
void Array<T>::clear() {
    delete[] this->data;
    this->size = 0;
    this->data = new T[this->capacity];
}
