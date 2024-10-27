#include <gtest/gtest.h>

#include "typeList.hpp"

TEST(TypeList, TypeList) {
    static_assert(Contains<int, List<int>>::value);
    static_assert(contains<int, List<int>>);
    static_assert(contains<int, List<int, double>>);
    static_assert(contains<int, List<float, int>>);
    static_assert(contains<int, List<float, int, double>>);
    static_assert(!contains<char, List<float, int, double>>);
}
