// common/data_structures/uptree_test.cc
#include <gtest/gtest.h>
#include "uptree.h"

TEST(UptreeTest, BasicUnionFindOperations) {
    Uptree u(10);
    EXPECT_EQ(u.size(), 10);

    // Initially, no elements are connected except to themselves
    EXPECT_TRUE(u.connected(0, 0));
    EXPECT_FALSE(u.connected(1, 2));

    // Union and find
    u.unite(1, 2);
    EXPECT_TRUE(u.connected(1, 2));
    EXPECT_EQ(u.find(1), u.find(2));

    // More unions
    u.unite(2, 3);
    EXPECT_TRUE(u.connected(1, 3));

    // Uniting already connected elements is a no-op
    u.unite(1, 3);
    EXPECT_TRUE(u.connected(2, 3));
}

TEST(UptreeTest, PathCompressionAndRank) {
    Uptree u(5);
    u.unite(0, 1);
    u.unite(1, 2);
    u.unite(3, 4);

    int root_before = u.find(2);
    // After find, path compression should keep nodes pointing to root
    int root_after = u.find(2);
    EXPECT_EQ(root_before, root_after);

    EXPECT_FALSE(u.connected(0, 3));
    u.unite(2, 3);
    EXPECT_TRUE(u.connected(0, 4));
}

TEST(UptreeTest, InvalidIndexThrows) {
    Uptree u(3);
    EXPECT_THROW(u.find(-1), std::out_of_range);
    EXPECT_THROW(u.find(3), std::out_of_range);
    EXPECT_THROW(u.unite(0, 10), std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
