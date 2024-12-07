#include <gtest/gtest.h>

#include "BinSearch.hpp"

TEST(BinSearch, HasElement) {
    int array[]{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(find(array, std::size(array), 1));
}

TEST(BinSearch, DoesNotHaveElement) {
    int array[]{ 1, 2, 3, 4, 5 };
    EXPECT_FALSE(find(array, std::size(array), -1));
}
