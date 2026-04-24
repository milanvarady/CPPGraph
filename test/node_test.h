#pragma once

#include "../src/node.h"
#include "../lib/gtest_lite.h"

#include <sstream>
#include <string>

inline void node_tests() {
    // Constructor and getData
    TEST(Node, Constructor) {
        Node<int> n(42);
        EXPECT_EQ(42, n.getData());
    }
    ENDM

    TEST(Node, ConstructorString) {
        Node<std::string> n("hello");
        EXPECT_STREQ("hello", n.getData().c_str());
    }
    ENDM

    // setData
    TEST(Node, SetData) {
        Node<int> n(1);
        n.setData(99);
        EXPECT_EQ(99, n.getData());
    }
    ENDM

    // operator==
    TEST(Node, EqualityTrue) {
        Node<int> a(10);
        Node<int> b(10);
        EXPECT_TRUE(a == b);
    }
    ENDM

    TEST(Node, EqualityFalse) {
        Node<int> a(10);
        Node<int> b(20);
        EXPECT_FALSE(a == b);
    }
    ENDM

    // operator=
    TEST(Node, AssignmentOperator) {
        Node<int> a(10);
        Node<int> b(20);
        b = a;
        EXPECT_EQ(10, b.getData());
    }
    ENDM

    // operator<<
    TEST(Node, StreamOutput) {
        Node<int> n(42);
        std::ostringstream os;
        os << n;
        EXPECT_STREQ("42", os.str().c_str());
    }
    ENDM

    TEST(Node, StreamOutputString) {
        Node<std::string> n("test");
        std::ostringstream os;
        os << n;
        EXPECT_STREQ("test", os.str().c_str());
    }
    ENDM
}
