#include <gtest/gtest.h>

#include "SquareEquation.hpp"

using answer_t = SquareEquation::answer_t;

TEST(SquareEquation, NoSolution) {
    answer_t result = SquareEquation{1, 0, 1}.answer();
    EXPECT_TRUE(std::holds_alternative<std::monostate>(result));
}


TEST(SquareEquation, OneSolution) {
    answer_t result = SquareEquation{1.0, -2.0, 1.0}.answer();
    EXPECT_TRUE(std::holds_alternative<double>(result));
    EXPECT_DOUBLE_EQ(std::get<double>(result), 1.0);
}

TEST(SquareEquation, TwoSolutionsDistinct) {
    answer_t result = SquareEquation{1.0, -3.0, 2.0}.answer();
    EXPECT_TRUE((std::holds_alternative<std::pair<double, double>>(result)));
    auto solutions = std::get<std::pair<double, double>>(result);
    EXPECT_DOUBLE_EQ(solutions.first, 1.0);
    EXPECT_DOUBLE_EQ(solutions.second, 2.0);
}