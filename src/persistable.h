#pragma once

#include <string>

/// Abstract base class for types that can be serialized to/from text.
/// Types used with `Graph` must derive from this and implement `encode()`.
/// They must also provide a constructor taking `const std::string&` for deserialization.
class Persistable {
public:
    /// Serializes the object to a string representation.
    virtual std::string encode() const = 0;
    virtual ~Persistable() {}
};
