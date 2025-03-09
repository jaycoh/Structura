#include <gtest/gtest.h>
#include <iostream>
#include "linked_list.h"

// Helper funtion to reset and populate a list for testing.
template <typename T>
void populateList(LinkedList<T>& list, const T* values, int size) {
    for (int i = 0; i < size; i++) {
        list.insert(values[i]);
    }
}

TEST(LinkedListTest, Constructor) {
    LinkedList<int> list;
    EXPECT_FALSE(list.search(1));
}

TEST(LinkedListTest, InsertSingleElement) {
    LinkedList<int> list;
    list.insert(42);
    EXPECT_TRUE(list.search(42));
    EXPECT_TRUE(list.search(42));
    EXPECT_FALSE(list.search(43));
}

TEST(LinkedListTest, InsertMultipleElements) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(3));
    EXPECT_FALSE(list.search(4));
}
TEST(LinkedListTest, RemoveEmptyList) {
    LinkedList<int> list;
    list.remove(1);  // Should do nothing
    EXPECT_FALSE(list.search(1));
}

TEST(LinkedListTest, RemoveHeadElement) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    list.remove(1);
    EXPECT_FALSE(list.search(1));
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(3));
}

TEST(LinkedListTest, RemoveMiddleElement) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    list.remove(2);
    EXPECT_TRUE(list.search(1));
    EXPECT_FALSE(list.search(2));
    EXPECT_TRUE(list.search(3));
}

TEST(LinkedListTest, RemoveTailElement) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    list.remove(3);
    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(2));
    EXPECT_FALSE(list.search(3));
}

TEST(LinkedListTest, RemoveNonExistentElement) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    list.remove(4);  // Should do nothing
    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(3));
}

TEST(LinkedListTest, Display) {
    LinkedList<int> list;
    int values[] = {1, 2, 3};
    populateList(list, values, 3);
    list.display();
}

TEST(LinkedListTest, SearchEmptyList) {
    LinkedList<int> list;
    EXPECT_FALSE(list.search(1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}