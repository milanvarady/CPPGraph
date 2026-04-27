#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "playground.h"

static const char* GREEN = "\033[32;1m";
static const char* RED = "\033[31m";
static const char* RESET = "\033[0m";

Playground::Playground() {
    // Add 4 nodes
    for (size_t i = 0; i < 4; i++) {
        this->graph.addNode(PInt(i));
    }
}

Playground::~Playground() {
    std::remove(Playground::SAVE_FILE_NAME);
}

void Playground::main() {
    std::cout << "CPPGraph Interactive mode" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;

    std::string line;
    while (true) {
        std::cout << GREEN << "> " << RESET;

        // Handle Ctrl+D
        if (!std::getline(std::cin, line))
            break;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "exit") {
            break;
        } else if (cmd == "help") {
            this->help();
        } else if (cmd == "print") {
            this->print();
        } else if (cmd == "connect") {
            size_t u, v;
            if (ss >> u >> v) {
                this->connect(u, v);
            } else {
                std::cout << RED << "Error: connect requires two node IDs." << RESET << std::endl;
            }
        } else if (cmd == "disconnect") {
            size_t u, v;
            if (ss >> u >> v) {
                this->disconnect(u, v);
            } else {
                std::cout << RED << "Error: disconnect requires two node IDs." << RESET << std::endl;
            }
        } else if (cmd == "connected") {
            std::cout << (this->graph.isConnected() ? "true" : "false") << std::endl;
        } else if (cmd == "save") {
            this->save();
        } else if (cmd == "load") {
            this->load();
        } else {
            std::cout << RED << "Unknown command: " << cmd << ". Type 'help' for info." << RESET << std::endl;
        }
    }
}

void Playground::help() const {
    std::cout << R"(
Available commands:
- print                   : prints the graph
- connect {u} {v}         : adds an edge between node1 and node2
- disconnect {u} {v}      : removes edge between node1 and node2
- connected               : checks if the graph is connected
- save                    : saves the current graph state
- load                    : loads previously saved graph state
- exit                    : exits interactive mode
)" << std::endl;
}

void Playground::print() const {
    char output[5][5 + 1];

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            output[i][j] = ' ';
        }
        output[i][5] = '\0';
    }

    output[0][0] = '0';
    output[0][4] = '1';
    output[4][0] = '2';
    output[4][4] = '3';

    // Top left - top right
    if (this->graph.hasEdge(0, 1))
        for (size_t i = 1; i < 4; i++)
            output[0][i] = '-';

    // Top left - bottom left
    if (this->graph.hasEdge(0, 2))
        for (size_t i = 1; i < 4; i++)
            output[i][0] = '|';

    // Top right - bottom right
    if (this->graph.hasEdge(1, 3))
        for (size_t i = 1; i < 4; i++)
            output[i][4] = '|';

    // Bottom left - bottom right
    if (this->graph.hasEdge(2, 3))
        for (size_t i = 1; i < 4; i++)
            output[4][i] = '-';

    // Top left - bottom right
    if (this->graph.hasEdge(0, 3))
        for (size_t i = 1; i < 4; i++)
            output[i][i] = '\\';

    // Top right - bottom left
    if (this->graph.hasEdge(1, 2))
        for (size_t i = 1; i < 4; i++)
            output[i][4 - i] = '/';

    // Middle cross
    if (this->graph.hasEdge(0, 3) && this->graph.hasEdge(1, 2))
        output[2][2] = 'X';

    // Print output
    for (size_t i = 0; i < 5; i++) {
        std::cout << output[i] << std::endl;
    }
}

void Playground::connect(size_t u, size_t v) {
    try {
        this->graph.addEdge(u, v);
    } catch (const std::exception& e) {
        std::cout << RED << e.what() << RESET << std::endl;
    }
}

void Playground::disconnect(size_t u, size_t v) {
    try {
        this->graph.removeEdge(u, v);
    } catch (const std::exception& e) {
        std::cout << RED << e.what() << RESET << std::endl;
    }
}

void Playground::save() const {
    this->graph.save(Playground::SAVE_FILE_NAME);
}

void Playground::load() {
    this->graph.load(Playground::SAVE_FILE_NAME);
}
