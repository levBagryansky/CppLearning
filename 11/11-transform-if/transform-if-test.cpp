#include <gtest/gtest.h>

#include "transform_if.hpp"

TEST(TransformIfTest, SquaresEvenNumbers) {
    std::vector<int> input = {1, 2, 3, 4, 5, 6};
    std::vector<int> output;

    auto is_even = [](int x) { return x % 2 == 0; };
    auto square = [](int x) { return x * x; };

    transform_if(input.begin(), input.end(), std::back_inserter(output), is_even, square);

    std::vector<int> expected = {4, 16, 36};
    EXPECT_EQ(output, expected);
}

TEST(TransformIfTest, UppercaseOnlyAlphabeticChars) {
    std::string input = "Ab1cD!";
    std::string output;

    auto is_alpha = [](char c) { return std::isalpha(static_cast<unsigned char>(c)); };
    auto to_upper = [](char c) { return std::toupper(static_cast<unsigned char>(c)); };

    transform_if(input.begin(), input.end(), std::back_inserter(output), is_alpha, to_upper);

    std::string expected = "ABCD";
    EXPECT_EQ(output, expected);
}

TEST(TransformIfTest, EmptyInput) {
    std::vector<int> input;
    std::vector<int> output;

    transform_if(input.begin(), input.end(), std::back_inserter(output),
              [](int) { return true; },
              [](int x) { return x * 2; });

    EXPECT_TRUE(output.empty());
}

TEST(TransformIfTest, NoElementSatisfiesPredicate) {
    std::vector<int> input = {1, 3, 5};
    std::vector<int> output;

    transform_if(input.begin(), input.end(), std::back_inserter(output),
              [](int x) { return x % 2 == 0; },
              [](int x) { return x * x; });

    EXPECT_TRUE(output.empty());
}

TEST(TransformIfTest, AllElementsSatisfyPredicate) {
    std::vector<int> input = {1, 2, 3};
    std::vector<int> output;

    transform_if(input.begin(), input.end(), std::back_inserter(output),
              [](int) { return true; },
              [](int x) { return x + 10; });

    std::vector<int> expected = {11, 12, 13};
    EXPECT_EQ(output, expected);
}
