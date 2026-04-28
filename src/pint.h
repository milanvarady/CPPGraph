#pragma once

#include "persistable.h"

/// Persistable integer wrapper. Used by the playground and tests.
class PInt : public Persistable {
    int value;

public:
    /// Default constructor. Initializes value to 0.
    PInt() : value(0) {}
    /// Constructs from an integer.
    PInt(int v) : value(v) {}
    /// Deserializes from a string.
    PInt(const std::string& s) : value(std::stoi(s)) {}
    /// Serializes the value to a string.
    std::string encode() const {
        return std::to_string(value);
    }
    /// Returns the underlying integer value.
    int get() const {
        return value;
    }
    /// Equality comparison.
    bool operator==(const PInt& other) const {
        return value == other.value;
    }
};
