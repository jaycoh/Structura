// geometry/octree_test.cc
#include <gtest/gtest.h>
#include "octree.h"

// Test fixture for reusable setup
class OctreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize a 100x100x100 octree
        ot_ = std::make_unique<Octree<int>>(Point3(0, 0, 0), Point3(100, 100, 100));
    }

    std::unique_ptr<Octree<int>> ot_;
};

TEST_F(OctreeTest, InsertAndSearchSinglePoint) {
    ot_->insert(Point3(50, 50, 50), 7);
    const int* result = ot_->search(Point3(50, 50, 50));
    ASSERT_NE(result, nullptr) << "Search should find the inserted point";
    EXPECT_EQ(*result, 7) << "Data should match inserted value";
    EXPECT_EQ(ot_->search(Point3(51, 51, 51)), nullptr) << "Non-inserted point should return nullptr";
}

TEST_F(OctreeTest, InsertMultiplePointsWithSplit) {
    ot_->insert(Point3(50, 50, 50), 7);
    ot_->insert(Point3(25, 25, 25), 14);

    const int* r1 = ot_->search(Point3(50, 50, 50));
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(*r1, 7);

    const int* r2 = ot_->search(Point3(25, 25, 25));
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(*r2, 14);

    EXPECT_EQ(ot_->search(Point3(75, 75, 75)), nullptr) << "Non-inserted point should return nullptr";
}

TEST_F(OctreeTest, InsertOutOfBoundsThrows) {
    EXPECT_THROW(ot_->insert(Point3(150,150,150), 99), std::runtime_error)
        << "Inserting outside bounds should throw";
    EXPECT_THROW(ot_->insert(Point3(-1,50,50), 99), std::runtime_error)
        << "Inserting below bounds should throw";
}

TEST_F(OctreeTest, SearchEmptyTree) {
    EXPECT_EQ(ot_->search(Point3(50,50,50)), nullptr)
        << "Search on empty tree should return nullptr";
}

TEST_F(OctreeTest, InvalidBoundsThrows) {
    EXPECT_THROW(Octree<int>(Point3(50,50,50), Point3(0,0,0)), std::invalid_argument)
        << "Invalid bounds (min >= max) should throw";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
