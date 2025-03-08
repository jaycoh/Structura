cc_library(
    name = "data_structures",
    hdrs = ["linked_list.h"],
    visibility = ["//visibility:public"],
    deps = [
        # Add dependencies here
    ],
)

cc_test(
    name = "data_structures_test",
    srcs = ["linked_list_test.cc"],
    deps = [
        "@googletest//:gtest_main",
        ":data_structures",
    ],
)