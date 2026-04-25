#pragma once

#include "../src/graph.h"
#include "../lib/gtest_lite.h"

inline void graph_tests() {
    // Constructor
    TEST(Graph, EmptyGraph) {
        Graph<int> g;
        EXPECT_EQ((size_t)0, g.getNodeCount());
        EXPECT_EQ((size_t)0, g.getEdgeCount());
    }
    ENDM

    // addNode
    TEST(Graph, AddNode) {
        Graph<int> g;
        g.addNode(10);
        g.addNode(20);
        g.addNode(30);
        EXPECT_EQ((size_t)3, g.getNodeCount());
        EXPECT_EQ(10, g.getNode(0).getData());
        EXPECT_EQ(20, g.getNode(1).getData());
        EXPECT_EQ(30, g.getNode(2).getData());
    }
    ENDM

    // getNode
    TEST(Graph, GetNodeOutOfBounds) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.getNode(1), std::out_of_range);
    }
    ENDM

    // addEdge and hasEdge
    TEST(Graph, AddEdge) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        EXPECT_TRUE(g.hasEdge(0, 1));
        EXPECT_TRUE(g.hasEdge(1, 0));
        EXPECT_EQ((size_t)1, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, AddEdgeDuplicateIsNoop) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        g.addEdge(0, 1);
        EXPECT_EQ((size_t)1, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, AddEdgeSelfLoopThrows) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.addEdge(0, 0), GraphError::SelfLoopNotAllowed);
    }
    ENDM

    TEST(Graph, AddEdgeOutOfBounds) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.addEdge(0, 1), std::out_of_range);
    }
    ENDM

    // hasEdge
    TEST(Graph, HasEdgeNoEdge) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        EXPECT_FALSE(g.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, HasEdgeOutOfBounds) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.hasEdge(0, 1), std::out_of_range);
    }
    ENDM

    // removeEdge
    TEST(Graph, RemoveEdge) {
        Graph<int> g;
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
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.removeEdge(0, 1);
        EXPECT_EQ((size_t)0, g.getEdgeCount());
    }
    ENDM

    TEST(Graph, RemoveEdgeOutOfBounds) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.removeEdge(0, 1), std::out_of_range);
    }
    ENDM

    // removeNode
    TEST(Graph, RemoveNode) {
        Graph<int> g;
        g.addNode(10);
        g.addNode(20);
        g.addNode(30);
        g.removeNode(1);
        EXPECT_EQ((size_t)2, g.getNodeCount());
        EXPECT_EQ(10, g.getNode(0).getData());
        EXPECT_EQ(30, g.getNode(1).getData());
    }
    ENDM

    TEST(Graph, RemoveNodeUpdatesEdgeCount) {
        Graph<int> g;
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
        Graph<int> g;
        g.addNode(1);
        EXPECT_THROW(g.removeNode(1), std::out_of_range);
    }
    ENDM

    // Copy constructor
    TEST(Graph, CopyConstructor) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<int> g2(g);
        EXPECT_EQ(g.getNodeCount(), g2.getNodeCount());
        EXPECT_EQ(g.getEdgeCount(), g2.getEdgeCount());
        EXPECT_TRUE(g2.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, CopyIsDeep) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<int> g2(g);
        g2.removeEdge(0, 1);
        EXPECT_TRUE(g.hasEdge(0, 1));
        EXPECT_FALSE(g2.hasEdge(0, 1));
    }
    ENDM

    // Assignment operator
    TEST(Graph, AssignmentOperator) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<int> g2;
        g2 = g;
        EXPECT_EQ(g.getNodeCount(), g2.getNodeCount());
        EXPECT_EQ(g.getEdgeCount(), g2.getEdgeCount());
        EXPECT_TRUE(g2.hasEdge(0, 1));
    }
    ENDM

    TEST(Graph, AssignmentIsDeep) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        Graph<int> g2;
        g2 = g;
        g2.addNode(3);
        EXPECT_EQ((size_t)2, g.getNodeCount());
        EXPECT_EQ((size_t)3, g2.getNodeCount());
    }
    ENDM

    // isConnected
    TEST(Graph, IsConnectedEmptyGraph) {
        Graph<int> g;
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedSingleNode) {
        Graph<int> g;
        g.addNode(1);
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedTwoNodesConnected) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        g.addEdge(0, 1);
        EXPECT_TRUE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedTwoNodesDisconnected) {
        Graph<int> g;
        g.addNode(1);
        g.addNode(2);
        EXPECT_FALSE(g.isConnected());
    }
    ENDM

    TEST(Graph, IsConnectedChain) {
        Graph<int> g;
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
        Graph<int> g;
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
        Graph<int> g;
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
}
