#include <gtest/gtest.h>
#include "trie.h"

TEST(Trie, EmptyTrie) {
    Trie trie;
    EXPECT_FALSE(trie.search("cat"));  // Nothing inserted
    EXPECT_FALSE(trie.search(""));     // Empty string not inserted
}

TEST(Trie, InsertAndSearchSingleWord) {
    Trie trie;
    trie.insert("cat");
    EXPECT_TRUE(trie.search("cat"));
    EXPECT_FALSE(trie.search("ca"));   // Prefix, not a word
    EXPECT_FALSE(trie.search("dog"));  // Not inserted
}

TEST(Trie, MultipleWords) {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("card");
    EXPECT_TRUE(trie.search("cat"));
    EXPECT_TRUE(trie.search("car"));
    EXPECT_TRUE(trie.search("card"));
    EXPECT_FALSE(trie.search("ca"));    // Prefix only
    EXPECT_FALSE(trie.search("cards")); // Beyond inserted word
}

TEST(Trie, EmptyString) {
    Trie trie;
    trie.insert("");
    EXPECT_TRUE(trie.search(""));       // Empty string as a valid word
    EXPECT_FALSE(trie.search("a"));     // Not inserted
    trie.insert("a");
    EXPECT_TRUE(trie.search("a"));
    EXPECT_TRUE(trie.search(""));       // Still valid
}

TEST(Trie, CaseSensitivity) {
    Trie trie;
    trie.insert("Cat");
    trie.insert("cat");
    EXPECT_TRUE(trie.search("Cat"));
    EXPECT_TRUE(trie.search("cat"));
    EXPECT_FALSE(trie.search("CAT"));   // Different case
}

TEST(Trie, SpecialCharacters) {
    Trie trie;
    trie.insert("cat!");
    trie.insert("dog#");
    trie.insert("123");
    EXPECT_TRUE(trie.search("cat!"));
    EXPECT_TRUE(trie.search("dog#"));
    EXPECT_TRUE(trie.search("123"));
    EXPECT_FALSE(trie.search("cat"));
    EXPECT_FALSE(trie.search("12"));
}

TEST(Trie, OverwriteSameWord) {
    Trie trie;
    trie.insert("cat");
    trie.insert("cat");  // Insert again
    EXPECT_TRUE(trie.search("cat"));
    EXPECT_FALSE(trie.search("ca"));
    // No crash or unexpected behavior
}

TEST(Trie, Destructor) {
    {
        Trie trie;
        trie.insert("cat");
        trie.insert("car");
        trie.insert("dog");
    }  // Destructor called here
    // No assertion, but valgrind can confirm no leaks
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}