#include <gtest/gtest.h>
#include "sorted_binary_tree.h"

class SortedBinaryTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Optional: Setup code if needed
    }

    void TearDown() override {
        // Optional: Cleanup if needed
    }
};

TEST_F(SortedBinaryTreeTest, ConstructAndGetData) {
    SortedBinaryTree<int> tree(10);
    EXPECT_EQ(tree.getData(), 10);
}

TEST_F(SortedBinaryTreeTest, SearchSingleNode) {
    SortedBinaryTree<int> tree(10);
    EXPECT_TRUE(tree.search(10));
    EXPECT_FALSE(tree.search(5));
    EXPECT_FALSE(tree.search(15));
}

TEST_F(SortedBinaryTreeTest, InsertAndSearch) {
    SortedBinaryTree<int> tree(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(15));
    EXPECT_TRUE(tree.search(3));
    EXPECT_TRUE(tree.search(7));
    EXPECT_FALSE(tree.search(4));
    EXPECT_FALSE(tree.search(12));
}

TEST_F(SortedBinaryTreeTest, SetLeftValid) {
    SortedBinaryTree<int> tree(10);
    SortedBinaryTree<int>* left = new SortedBinaryTree<int>(5);
    left->insert(3);
    tree.setLeft(left);
    
    EXPECT_EQ(tree.getLeft()->getData(), 5);
    EXPECT_EQ(tree.getLeft()->getLeft()->getData(), 3);
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(3));
}

TEST_F(SortedBinaryTreeTest, SetRightValid) {
    SortedBinaryTree<int> tree(10);
    SortedBinaryTree<int>* right = new SortedBinaryTree<int>(15);
    right->insert(20);
    tree.setRight(right);
    
    EXPECT_EQ(tree.getRight()->getData(), 15);
    EXPECT_EQ(tree.getRight()->getRight()->getData(), 20);
    EXPECT_TRUE(tree.search(15));
    EXPECT_TRUE(tree.search(20));
}

TEST_F(SortedBinaryTreeTest, SetLeftInvalidThrows) {
    SortedBinaryTree<int> tree(10);
    SortedBinaryTree<int>* left = new SortedBinaryTree<int>(15);  // 15 > 10
    EXPECT_THROW(tree.setLeft(left), std::invalid_argument);
    delete left;
}

TEST_F(SortedBinaryTreeTest, SetRightInvalidThrows) {
    SortedBinaryTree<int> tree(10);
    SortedBinaryTree<int>* right = new SortedBinaryTree<int>(5);  // 5 < 10
    EXPECT_THROW(tree.setRight(right), std::invalid_argument);
    delete right;  // Clean up
}

TEST_F(SortedBinaryTreeTest, MaintainsBSTProperty) {
    SortedBinaryTree<int> tree(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    EXPECT_EQ(tree.getLeft()->getData(), 5);
    EXPECT_EQ(tree.getLeft()->getLeft()->getData(), 3);
    EXPECT_EQ(tree.getLeft()->getRight()->getData(), 7);
    EXPECT_EQ(tree.getRight()->getData(), 15);
    EXPECT_EQ(tree.getRight()->getLeft()->getData(), 12);
    EXPECT_EQ(tree.getRight()->getRight()->getData(), 20);
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}