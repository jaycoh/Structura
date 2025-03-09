# For users outside of this package, we expose the data structures library.
cc_library(
    name = "geometry_data_structures",
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        # Add dependencies here
    ],
)

# Each test is defined separately, so we create a library for each data structure.

cc_library(
    name = "quadtree",
    hdrs = ["quadtree.h"],
)

cc_test(
    name = "quadtree_test",
    srcs = ["quadtree_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":quadtree",
    ],
)