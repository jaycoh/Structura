#include <gtest/gtest.h>
#include "stack.h"

TEST(Stack, Constructor) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
}

TEST(Stack, PushPop) {
    Stack<int> s;
    s.push(42);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.pop(), 42);
    EXPECT_TRUE(s.empty());
}

TEST(Stack, Top) {
    Stack<int> s;
    s.push(42);
    EXPECT_EQ(s.top(), 42);
    EXPECT_FALSE(s.empty());  // top doesn't remove
}

TEST(Stack, EmptyPop) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}