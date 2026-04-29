#include <iostream>

#include "memtrace.h"
#include "gtest_lite.h"

#include "array_test.h"
#include "node_test.h"
#include "graph_test.h"

int main() {
    GTINIT(std::cin);
    array_tests();
    node_tests();
    graph_tests();
    GTEND(std::cout);
    return 0;
}
