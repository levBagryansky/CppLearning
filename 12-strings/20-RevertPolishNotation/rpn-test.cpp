#include "gtest/gtest.h"

#include "RevertPolishNotation.hpp"

TEST(CalculateTest, BasicOperations) {
    EXPECT_DOUBLE_EQ(calculate("3 4 +"), 7);
    EXPECT_DOUBLE_EQ(calculate("10 2 -"), 8);
    EXPECT_DOUBLE_EQ(calculate("5 6 *"), 30);
    EXPECT_DOUBLE_EQ(calculate("8 2 /"), 4);
}

TEST(CalculateTest, MultipleOperations) {
    EXPECT_DOUBLE_EQ(calculate("1 2 + 3 *"), 9);           // (1 + 2) * 3 = 9
    EXPECT_DOUBLE_EQ(calculate("5 1 2 + 4 * + 3 -"), 14);  // 5 + ((1 + 2) * 4) - 3 = 14
}

TEST(CalculateTest, FloatingPointSupport) {
    EXPECT_DOUBLE_EQ(calculate("3.5 2.5 +"), 6.0);
    EXPECT_DOUBLE_EQ(calculate("10 4.5 -"), 5.5);
}

TEST(CalculateTest, DivisionByZero) {
    EXPECT_THROW(calculate("5 0 /"), std::runtime_error);
}
