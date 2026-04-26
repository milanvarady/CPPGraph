#pragma once

#include <string>

class Persistable {
public:
    virtual std::string encode() const = 0;
    virtual ~Persistable() {}
};
