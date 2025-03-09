# For users outside of this package, we expose the data structures library.
cc_library(
    name = "core_data_structures",
    hdrs = glob(["*.h"]),
    srcs = glob(["*.cc"], exclude=["*_test.cc"]),
    visibility = ["//visibility:public"],
    deps = [
        # Add dependencies here
    ],
)

# Each test is defined separately, so we create a library for each data structure.

cc_library(
    name = "binary_tree",
    hdrs = ["binary_tree.h"],
)

cc_test(
    name = "binary_tree_test",
    srcs = ["binary_tree_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":binary_tree",
    ],
)

cc_library(
    name = "linked_list",
    hdrs = ["linked_list.h"],
)

cc_test(
    name = "linked_list_test",
    srcs = ["linked_list_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":linked_list",
    ],
)

cc_library(
    name = "lru_cache",
    hdrs = ["lru_cache.h"],
    deps = [
        ":linked_list",
    ],
)

cc_test(
    name = "lru_cache_test",
    srcs = ["lru_cache_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":lru_cache",
    ],
)

cc_library(
    name = "sorted_binary_tree",
    hdrs = ["sorted_binary_tree.h"],
    deps = [
        ":binary_tree",
    ],
)

cc_test(
    name = "sorted_binary_tree_test",
    srcs = ["sorted_binary_tree_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":sorted_binary_tree",
    ],
)

cc_library(
    name = "stack",
    hdrs = ["stack.h"],
)

cc_test(
    name = "stack_test",
    srcs = ["stack_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":stack",
    ],
)

cc_library(
    name = "trie",
    hdrs = ["trie.h"],
    srcs = ["trie.cc"],
)

cc_test(
    name = "trie_test",
    srcs = ["trie_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":trie",
    ],
)