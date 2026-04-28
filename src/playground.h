#pragma once

#include "graph.h"
#include "pint.h"

/// Interactive console for experimenting with a `Graph<PInt>`.
/// Pre-loads 4 nodes (0-3). Save file is cleaned up on destruction.
class Playground {
    static constexpr const char* SAVE_FILE_NAME = "graph.txt";
    Graph<PInt> graph;

public:
    /// Initializes the graph with 4 nodes.
    Playground();

    /// Cleans up the save file.
    ~Playground();

    /// Runs the interactive command loop.
    void main();

    /// Prints available commands.
    void help() const;

    /// Prints the graph as a 5x5 ASCII diagram.
    void print() const;

    /// Adds an edge between two nodes.
    void connect(size_t u, size_t v);
    /// Removes an edge between two nodes.
    void disconnect(size_t u, size_t v);
    /// Saves the graph to a temporary file.
    void save() const;
    /// Loads the graph from the temporary file.
    void load();
};
