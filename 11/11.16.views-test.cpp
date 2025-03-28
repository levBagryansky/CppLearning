#include <gtest/gtest.h>
#include <ranges>
#include <iostream>
#include <vector>
//#include <range/v3/view/istream.hpp>
#include <numeric>
//#include <range/v3/view/stride.hpp>

TEST(ViewsTest, Istream) {
    std::istringstream input("10 20 30 40");
    for (int x : std::ranges::istream_view<int>(input)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

TEST(ViewsTest, CountedViewReturnsCorrectElements) {
    std::vector<int> v = {10, 20, 30, 40, 50};

    auto subrange = std::views::counted(v.begin(), 3);

    std::vector<int> expected = {10, 20, 30};
    std::vector<int> result(subrange.begin(), subrange.end());

    EXPECT_EQ(result, expected);
}

TEST(ViewsTest, JoinViewFlattensNestedVectors) {
    std::vector<std::vector<int>> nested = {{1, 2}, {3, 4}, {5}};

    auto flat = nested | std::views::join;

    std::vector<int> result(flat.begin(), flat.end());
    std::vector<int> expected = {1, 2, 3, 4, 5};

    EXPECT_EQ(result, expected);
}

TEST(ViewsTest, StrideViewSkipsElementsByStep) {
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);  // [0, 1, ..., 9]

    auto stride_view = v | std::ranges::views::stride(3);

    std::vector<int> result(stride_view.begin(), stride_view.end());
    std::vector<int> expected = {0, 3, 6, 9};

    EXPECT_EQ(result, expected);
}
