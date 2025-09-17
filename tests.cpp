#include <gtest/gtest.h>
#include "circular-buffer.hpp"

using namespace std;

TEST(CircularDequeTest, Initially) {
    CircularDeque deq(3, false);
    EXPECT_TRUE(deq.empty());
    EXPECT_FALSE(deq.full());
    EXPECT_EQ(deq.size(), 0);
}

TEST(CircularDequeTest, PushBack) {
    CircularDeque deq(3, false);
    deq.push_back(3);
    deq.push_back(2);
    deq.push_back(1);

    EXPECT_TRUE(deq.full());
    EXPECT_EQ(deq.size(), 3);
    EXPECT_EQ(deq.front(), 3);
    EXPECT_EQ(deq.back(), 1);
}

TEST(CircularDequeTest, PushFront) {
    CircularDeque deq(3, false);
    deq.push_front(3);
    deq.push_front(2);
    deq.push_front(1);

    EXPECT_TRUE(deq.full());
    EXPECT_EQ(deq.size(), 3);
    EXPECT_EQ(deq.front(), 1);
    EXPECT_EQ(deq.back(), 3);
}

TEST(CircularDequeTest, PushBackOverflow) {
    CircularDeque dq(2, false);
    dq.push_back(1);
    dq.push_back(2);
    EXPECT_THROW(dq.push_back(3), std::overflow_error);
}

TEST(CircularDequeTest, PushForce) {
    CircularDeque dq(3, true);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    dq.push_back(4);
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq.back(), 4);
    EXPECT_EQ(dq.size(), 3);

    dq.push_front(5);
    EXPECT_EQ(dq.front(), 5);
    EXPECT_EQ(dq.back(), 3);
}

TEST(CircularDequeTest, ResizeUp) {
    CircularDeque dq(2, false);
    dq.push_back(1);
    dq.push_back(2);

    dq.resize(4);
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 1);
    dq.push_back(3);
    dq.push_back(4);
    EXPECT_EQ(dq.back(), 4);
    EXPECT_TRUE(dq.full());
}

TEST(CircularDequeTest, ResizeDown) {
    CircularDeque dq(5, false);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);

    dq.resize(3);
    EXPECT_EQ(dq.size(), 3);
    EXPECT_EQ(dq.front(), 1);
    EXPECT_EQ(dq.back(), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
