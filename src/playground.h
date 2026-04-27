#pragma once

#include "graph.h"
#include "pint.h"

class Playground {
    static constexpr const char* SAVE_FILE_NAME = "graph.txt";
    Graph<PInt> graph;

public:
    Playground();
    ~Playground();
    void main();
    void help() const;
    void print() const;
    void connect(size_t u, size_t v);
    void disconnect(size_t u, size_t v);
    void save() const;
    void load();
};
