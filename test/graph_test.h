#pragma once

#include <string>

#include "gtest_lite.h"
#include "graph.h"
#include "pint.h"

inline std::ostream& operator<<(std::ostream& os, const PInt& p) {
    os << p.get();
    return os;
}

inline void graph_tests() {
    // Constructor
    TEST(Graph, EmptyGraph) {
        Graph<PInt> g;
        EXPECT_EQ((size_t)0, g.getNodeCount());
        EXPECT_EQ((size_t)0, g.getEdgeCount());
    }
    ENDM

    // addNode
    TEST(Graph, AddNode) {
        Graph<PInt> g;
        g.addNode(10);
        g.addNode(20);
        g.addNode(30);
        EXPECT_EQ((size_t)3, g.getNodeCount());
        EXPECT_EQ(PInt(10), g.getNode(0).getData());
        EXPECT_EQ(PInt(20), g.getNode(1).getData());
        EXPECT_EQ(PInt(30), g.getNode(2).getData());
    }
    ENDM

    // getNode
    TEST(Graph, GetNodeOutOfBounds) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.getNode(1), std::out_of_range);
    }
    ENDM

    // addEdge and hasEdge
    TEST(Graph, AddEdge) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        EXPECT_TRUE(g.hasEdge(0, 1));
        EXPECT_TRUE(g.hasEdge(1, 0));
        EXPECT_EQ((size_t)1, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, AddEdgeDuplicateIsNoop) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        g.addEdge(0, 1);
        EXPECT_EQ((size_t)1, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, AddEdgeSelfLoopThrows) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.addEdge(0, 0), GraphError::SelfLoopNotAllowed);
    }
    ENDM

    TEST(Graph, AddEdgeOutOfBounds) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.addEdge(0, 1), std::out_of_range);
    }
    ENDM

    // hasEdge
    TEST(Graph, HasEdgeNoEdge) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        EXPECT_FALSE(g.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, HasEdgeOutOfBounds) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.hasEdge(0, 1), std::out_of_range);
    }
    ENDM

    // removeEdge
    TEST(Graph, RemoveEdge) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        g.removeEdge(0, 1);
        EXPECT_FALSE(g.hasEdge(0, 1));
        EXPECT_FALSE(g.hasEdge(1, 0));
        EXPECT_EQ((size_t)0, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, RemoveEdgeNonexistentIsNoop) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.removeEdge(0, 1);
        EXPECT_EQ((size_t)0, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, RemoveEdgeOutOfBounds) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.removeEdge(0, 1), std::out_of_range);
    }
    ENDM

    // removeNode
    TEST(Graph, RemoveNode) {
        Graph<PInt> g;
        g.addNode(10);
        g.addNode(20);
        g.addNode(30);
        g.removeNode(1);
        EXPECT_EQ((size_t)2, g.getNodeCount());
        EXPECT_EQ(PInt(10), g.getNode(0).getData());
        EXPECT_EQ(PInt(30), g.getNode(1).getData());
    }
    ENDM

    TEST(Graph, RemoveNodeUpdatesEdgeCount) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addNode(3);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        EXPECT_EQ((size_t)3, g.getEdgeCount());
        g.removeNode(0);
        EXPECT_EQ((size_t)1, g.getEdgeCount());
        EXPECT_TRUE(g.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, RemoveNodeOutOfBounds) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_THROW(g.removeNode(1), std::out_of_range);
    }
    ENDM

    // Copy constructor
    TEST(Graph, CopyConstructor) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<PInt> g2(g);
        EXPECT_EQ(g.getNodeCount(), g2.getNodeCount());
        EXPECT_EQ(g.getEdgeCount(), g2.getEdgeCount());
        EXPECT_TRUE(g2.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, CopyIsDeep) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<PInt> g2(g);
        g2.removeEdge(0, 1);
        EXPECT_TRUE(g.hasEdge(0, 1));
        EXPECT_FALSE(g2.hasEdge(0, 1));
    }
    ENDM

    // Assignment operator
    TEST(Graph, AssignmentOperator) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<PInt> g2;
        g2 = g;
        EXPECT_EQ(g.getNodeCount(), g2.getNodeCount());
        EXPECT_EQ(g.getEdgeCount(), g2.getEdgeCount());
        EXPECT_TRUE(g2.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, AssignmentIsDeep) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<PInt> g2;
        g2 = g;
        g2.addNode(3);
        EXPECT_EQ((size_t)2, g.getNodeCount());
        EXPECT_EQ((size_t)3, g2.getNodeCount());
    }
    ENDM

    // isConnected
    TEST(Graph, IsConnectedEmptyGraph) {
        Graph<PInt> g;
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedSingleNode) {
        Graph<PInt> g;
        g.addNode(1);
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedTwoNodesConnected) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedTwoNodesDisconnected) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        EXPECT_FALSE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedChain) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addNode(3);
        g.addNode(4);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedDisjointComponents) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addNode(3);
        g.addNode(4);
        g.addEdge(0, 1);
        g.addEdge(2, 3);
        EXPECT_FALSE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedAfterRemoveEdge) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addNode(3);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        EXPECT_TRUE(g.isConnected());
        g.removeEdge(1, 2);
        EXPECT_FALSE(g.isConnected());
    }
    ENDM

    // save and load
    TEST(Graph, SaveAndLoad) {
        Graph<PInt> g;
        g.addNode(10);
        g.addNode(20);
        g.addNode(30);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.save("/tmp/cppgraph_test.txt");

        Graph<PInt> g2;
        g2.load("/tmp/cppgraph_test.txt");
        EXPECT_EQ(g.getNodeCount(), g2.getNodeCount());
        EXPECT_EQ(g.getEdgeCount(), g2.getEdgeCount());
        EXPECT_EQ(PInt(10), g2.getNode(0).getData());
        EXPECT_EQ(PInt(20), g2.getNode(1).getData());
        EXPECT_EQ(PInt(30), g2.getNode(2).getData());
        EXPECT_TRUE(g2.hasEdge(0, 1));
        EXPECT_TRUE(g2.hasEdge(1, 2));
        EXPECT_FALSE(g2.hasEdge(0, 2));
    }
    ENDM

    TEST(Graph, LoadReplacesExistingState) {
        Graph<PInt> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        g.save("/tmp/cppgraph_test2.txt");

        Graph<PInt> g2;
        g2.addNode(99);
        g2.addNode(98);
        g2.addNode(97);
        g2.load("/tmp/cppgraph_test2.txt");
        EXPECT_EQ((size_t)2, g2.getNodeCount());
        EXPECT_EQ((size_t)1, g2.getEdgeCount());
        EXPECT_EQ(PInt(1), g2.getNode(0).getData());
    }
    ENDM

    TEST(Graph, SaveAndLoadEmptyGraph) {
        Graph<PInt> g;
        g.save("/tmp/cppgraph_test3.txt");

        Graph<PInt> g2;
        g2.load("/tmp/cppgraph_test3.txt");
        EXPECT_EQ((size_t)0, g2.getNodeCount());
        EXPECT_EQ((size_t)0, g2.getEdgeCount());
    }
    ENDM

    TEST(Graph, LoadInvalidFileThrows) {
        EXPECT_THROW(Graph<PInt>().load("/tmp/nonexistent_file_cppgraph.txt"), std::runtime_error);
    }
    ENDM
}
