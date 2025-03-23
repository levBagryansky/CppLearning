#include <gtest/gtest.h>

#include "Checkes.hpp"

TEST(Checkers, HasOne) {
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6};
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_TRUE(has_one(v, i)) << "has_one(v, " << i << ") returned false, but expected true";
    }
    EXPECT_FALSE(has_one(v, 7));
}


TEST(Checkers, AnyOf) {
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(any_of(v, 3, 8));
    EXPECT_FALSE(any_of(v, 8, 9, 10));
}

TEST(Checkers, AllOf) {
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(all_of(v, 2, 3, 4, 5, 6));
    EXPECT_FALSE(all_of(v, 2, 3, 4, 5, 6, 7));
}

TEST(Checkers, NoneOf) {
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(none_of(v, 7, 8, 9, 10));
    EXPECT_FALSE(none_of(v, 7, 8, 9, 10, 6));
}
