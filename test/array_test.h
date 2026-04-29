#pragma once

#include "array.h"
#include "gtest_lite.h"

inline void array_tests() {
    // Constructor
    TEST(Array, DefaultConstructor) {
        Array<int> a;
        EXPECT_EQ((size_t)0, a.getSize());
    }
    ENDM

    TEST(Array, CustomCapacityConstructor) {
        Array<int> a(100);
        EXPECT_EQ((size_t)0, a.getSize());
    }
    ENDM

    // pushBack and operator[]
    TEST(Array, PushBackAndAccess) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        a.pushBack(30);
        EXPECT_EQ((size_t)3, a.getSize());
        EXPECT_EQ(10, a[0]);
        EXPECT_EQ(20, a[1]);
        EXPECT_EQ(30, a[2]);
    }
    ENDM

    TEST(Array, PushBackBeyondCapacity) {
        Array<int> a(2);
        a.pushBack(1);
        a.pushBack(2);
        a.pushBack(3);
        EXPECT_EQ((size_t)3, a.getSize());
        EXPECT_EQ(1, a[0]);
        EXPECT_EQ(2, a[1]);
        EXPECT_EQ(3, a[2]);
    }
    ENDM

    // operator[] bounds check
    TEST(Array, OutOfBoundsThrows) {
        Array<int> a;
        a.pushBack(1);
        EXPECT_THROW(a[1], std::out_of_range);
        EXPECT_THROW(a[100], std::out_of_range);
    }
    ENDM

    TEST(Array, EmptyArrayAccessThrows) {
        Array<int> a;
        EXPECT_THROW(a[0], std::out_of_range);
    }
    ENDM

    // removeAt
    TEST(Array, RemoveAtMiddle) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        a.pushBack(30);
        a.removeAt(1);
        EXPECT_EQ((size_t)2, a.getSize());
        EXPECT_EQ(10, a[0]);
        EXPECT_EQ(30, a[1]);
    }
    ENDM

    TEST(Array, RemoveAtFirst) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        a.removeAt(0);
        EXPECT_EQ((size_t)1, a.getSize());
        EXPECT_EQ(20, a[0]);
    }
    ENDM

    TEST(Array, RemoveAtLast) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        a.removeAt(1);
        EXPECT_EQ((size_t)1, a.getSize());
        EXPECT_EQ(10, a[0]);
    }
    ENDM

    TEST(Array, RemoveAtOutOfBoundsThrows) {
        Array<int> a;
        a.pushBack(1);
        EXPECT_THROW(a.removeAt(1), std::out_of_range);
        EXPECT_THROW(a.removeAt(100), std::out_of_range);
    }
    ENDM

    // Copy constructor
    TEST(Array, CopyConstructor) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        Array<int> b(a);
        EXPECT_EQ(a.getSize(), b.getSize());
        EXPECT_EQ(a[0], b[0]);
        EXPECT_EQ(a[1], b[1]);
    }
    ENDM

    TEST(Array, CopyIsDeep) {
        Array<int> a;
        a.pushBack(10);
        Array<int> b(a);
        b.pushBack(20);
        EXPECT_EQ((size_t)1, a.getSize());
        EXPECT_EQ((size_t)2, b.getSize());
    }
    ENDM

    // Assignment operator
    TEST(Array, AssignmentOperator) {
        Array<int> a;
        a.pushBack(10);
        a.pushBack(20);
        Array<int> b;
        b = a;
        EXPECT_EQ(a.getSize(), b.getSize());
        EXPECT_EQ(a[0], b[0]);
        EXPECT_EQ(a[1], b[1]);
    }
    ENDM

    TEST(Array, SelfAssignment) {
        Array<int> a;
        a.pushBack(42);
        Array<int>& ref = a;
        a = ref;
        EXPECT_EQ((size_t)1, a.getSize());
        EXPECT_EQ(42, a[0]);
    }
    ENDM

    TEST(Array, AssignmentIsDeep) {
        Array<int> a;
        a.pushBack(10);
        Array<int> b;
        b = a;
        b.pushBack(20);
        EXPECT_EQ((size_t)1, a.getSize());
        EXPECT_EQ((size_t)2, b.getSize());
    }
    ENDM
}
