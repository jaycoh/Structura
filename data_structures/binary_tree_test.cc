#include <gtest/gtest.h>
#include "binary_tree.h"

// Helper struct with no default constructor
struct NoDefault {
    int val;
    NoDefault(int x) : val(x) {}
    bool operator==(const NoDefault& other) const { return val == other.val; }
};

// Test basic constructor and getters
TEST(BinaryTree, Constructor) {
    BinaryTree<int> tree(42);
    EXPECT_EQ(tree.getData(), 42);
    EXPECT_EQ(tree.getLeft(), nullptr);
    EXPECT_EQ(tree.getRight(), nullptr);
}

// Test setting and getting data
TEST(BinaryTree, SetData) {
    BinaryTree<int> tree(10);
    tree.setData(20);
    EXPECT_EQ(tree.getData(), 20);
    EXPECT_EQ(tree.getLeft(), nullptr);  // Shouldn’t affect structure
    EXPECT_EQ(tree.getRight(), nullptr);
}

// Test setting left child
TEST(BinaryTree, SetLeft) {
    BinaryTree<int> root(1);
    BinaryTree<int>* left = new BinaryTree<int>(2);
    root.setLeft(left);
    EXPECT_EQ(root.getLeft()->getData(), 2);
    EXPECT_EQ(root.getRight(), nullptr);
    EXPECT_EQ(root.getData(), 1);  // Root data unchanged
}

// Test setting right child
TEST(BinaryTree, SetRight) {
    BinaryTree<int> root(1);
    BinaryTree<int>* right = new BinaryTree<int>(3);
    root.setRight(right);
    EXPECT_EQ(root.getRight()->getData(), 3);
    EXPECT_EQ(root.getLeft(), nullptr);
    EXPECT_EQ(root.getData(), 1);
}

// Test replacing left child (checks memory management)
TEST(BinaryTree, ReplaceLeft) {
    BinaryTree<int> root(1);
    BinaryTree<int>* left1 = new BinaryTree<int>(2);
    BinaryTree<int>* left2 = new BinaryTree<int>(3);
    root.setLeft(left1);
    root.setLeft(left2);  // Should delete left1
    EXPECT_EQ(root.getLeft()->getData(), 3);
    EXPECT_EQ(root.getRight(), nullptr);
    // Can’t directly test left1 deletion, but no crash/leak is good
}

// Test replacing right child
TEST(BinaryTree, ReplaceRight) {
    BinaryTree<int> root(1);
    BinaryTree<int>* right1 = new BinaryTree<int>(4);
    BinaryTree<int>* right2 = new BinaryTree<int>(5);
    root.setRight(right1);
    root.setRight(right2);  // Should delete right1
    EXPECT_EQ(root.getRight()->getData(), 5);
    EXPECT_EQ(root.getLeft(), nullptr);
}

// Test full tree structure
TEST(BinaryTree, BuildTree) {
    BinaryTree<int> root(1);
    BinaryTree<int>* left = new BinaryTree<int>(2);
    BinaryTree<int>* right = new BinaryTree<int>(3);
    root.setLeft(left);
    root.setRight(right);
    BinaryTree<int>* leftLeft = new BinaryTree<int>(4);
    left->setLeft(leftLeft);
    EXPECT_EQ(root.getData(), 1);
    EXPECT_EQ(root.getLeft()->getData(), 2);
    EXPECT_EQ(root.getRight()->getData(), 3);
    EXPECT_EQ(root.getLeft()->getLeft()->getData(), 4);
    EXPECT_EQ(root.getLeft()->getRight(), nullptr);
}

// Test with non-default-constructible type
TEST(BinaryTree, NoDefaultType) {
    BinaryTree<NoDefault> tree(NoDefault(42));
    EXPECT_EQ(tree.getData().val, 42);
    tree.setData(NoDefault(10));
    EXPECT_EQ(tree.getData().val, 10);
    BinaryTree<NoDefault>* left = new BinaryTree<NoDefault>(NoDefault(20));
    tree.setLeft(left);
    EXPECT_EQ(tree.getLeft()->getData().val, 20);
}

// Test destructor (indirectly via scope)
TEST(BinaryTree, Destructor) {
    {
        BinaryTree<int> root(1);
        root.setLeft(new BinaryTree<int>(2));
        root.setRight(new BinaryTree<int>(3));
    }  // root destroyed here, should delete left and right
    // No direct assertion, but running with valgrind can confirm no leaks
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}