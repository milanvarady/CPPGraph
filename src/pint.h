#pragma once

#include "persistable.h"

class PInt : public Persistable {
    int value;

public:
    PInt() : value(0) {}
    PInt(int v) : value(v) {}
    PInt(const std::string& s) : value(std::stoi(s)) {}
    std::string encode() const {
        return std::to_string(value);
    }
    int get() const {
        return value;
    }
    bool operator==(const PInt& other) const {
        return value == other.value;
    }
};
