#include "../lib/memtrace.h"

#include "array_test.h"
#include "node_test.h"
#include "graph_test.h"

int main() {
    array_tests();
    node_tests();
    graph_tests();
    return 0;
}
