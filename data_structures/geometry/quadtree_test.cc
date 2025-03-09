// data_structures/quadtree_test.cc
#include <gtest/gtest.h>
#include "quadtree.h"

// Test fixture for reusable setup
class QuadtreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize a 100x100 quadtree
        qt_ = std::make_unique<Quadtree<int>>(Point(0, 0), Point(100, 100));
    }

    std::unique_ptr<Quadtree<int>> qt_;  // Test instance
};

// Test basic insertion and search
TEST_F(QuadtreeTest, InsertAndSearchSinglePoint) {
    qt_->insert(Point(50, 50), 42);
    const int* result = qt_->search(Point(50, 50));
    ASSERT_NE(result, nullptr) << "Search should find the inserted point";
    EXPECT_EQ(*result, 42) << "Data should match inserted value";
    EXPECT_EQ(qt_->search(Point(51, 51)), nullptr) << "Non-inserted point should return nullptr";
}

// Test splitting when inserting multiple points
TEST_F(QuadtreeTest, InsertMultiplePointsWithSplit) {
    qt_->insert(Point(50, 50), 42);  // First point
    qt_->insert(Point(25, 25), 84);  // Second point — triggers split

    const int* result1 = qt_->search(Point(50, 50));
    ASSERT_NE(result1, nullptr);
    EXPECT_EQ(*result1, 42);

    const int* result2 = qt_->search(Point(25, 25));
    ASSERT_NE(result2, nullptr);
    EXPECT_EQ(*result2, 84);

    EXPECT_EQ(qt_->search(Point(75, 75)), nullptr) << "Non-inserted point should return nullptr";
}

// Test out-of-bounds insertion throws
TEST_F(QuadtreeTest, InsertOutOfBoundsThrows) {
    EXPECT_THROW(qt_->insert(Point(150, 150), 99), std::runtime_error)
        << "Inserting outside bounds should throw";
    EXPECT_THROW(qt_->insert(Point(-1, 50), 99), std::runtime_error)
        << "Inserting below bounds should throw";
}

// Test search on empty tree
TEST_F(QuadtreeTest, SearchEmptyTree) {
    EXPECT_EQ(qt_->search(Point(50, 50)), nullptr)
        << "Search on empty tree should return nullptr";
}

// Test constructor with invalid bounds
TEST_F(QuadtreeTest, InvalidBoundsThrows) {
    EXPECT_THROW(Quadtree<int>(Point(50, 50), Point(0, 0)), std::invalid_argument)
        << "Invalid bounds (topLeft >= bottomRight) should throw";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}