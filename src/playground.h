#pragma once

#include "graph.h"
#include "pint.h"

/// @brief Interactive console for experimenting with a Graph<PInt>.
/// Pre-loads 4 nodes (0-3). Save file is cleaned up on destruction.
class Playground {
    static constexpr const char* SAVE_FILE_NAME = "graph.txt";
    Graph<PInt> graph;

public:
    /// @brief Initializes the graph with 4 nodes.
    Playground();

    /// @brief Cleans up the save file.
    ~Playground();

    /// @brief Runs the interactive command loop.
    void main();

    void help() const;

    /// @brief Prints the graph as a 5x5 ASCII diagram.
    void print() const;

    void connect(size_t u, size_t v);
    void disconnect(size_t u, size_t v);
    void save() const;
    void load();
};
