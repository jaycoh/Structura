#include <gtest/gtest.h>
#include "lru_cache.h"

TEST(LRUCache, EmptyCache) {
    LRUCache<int, int> cache(2);
    EXPECT_EQ(cache.get(1), nullptr);
}

TEST(LRUCache, PutAndGet) {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    int* value = cache.get(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, 10);
    EXPECT_EQ(cache.get(2), nullptr);
}

TEST(LRUCache, UpdateExistingKey) {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    cache.put(1, 20);
    int* value = cache.get(1);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, 20);
}

TEST(LRUCache, Eviction) {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    EXPECT_EQ(cache.get(1), nullptr);
    int* value2 = cache.get(2);
    int* value3 = cache.get(3);
    ASSERT_NE(value2, nullptr);
    ASSERT_NE(value3, nullptr);
    EXPECT_EQ(*value2, 20);
    EXPECT_EQ(*value3, 30);
}

TEST(LRUCache, MoveToFront) {
    LRUCache<int, int> cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.get(1);
    cache.put(3, 30);
    EXPECT_EQ(cache.get(2), nullptr);
    int* value1 = cache.get(1);
    int* value3 = cache.get(3);
    ASSERT_NE(value1, nullptr);
    ASSERT_NE(value3, nullptr);
    EXPECT_EQ(*value1, 10);
    EXPECT_EQ(*value3, 30);
}

TEST(LRUCache, SingleCapacity) {
    LRUCache<int, int> cache(1);
    cache.put(1, 10);
    cache.put(2, 20);  // Evicts 1
    EXPECT_EQ(cache.get(1), nullptr);
    int32_t* value = cache.get(2);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(*value, 20);
}

TEST(LRUCache, ZeroCapacity) {
    LRUCache<int, int> cache(0);
    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}