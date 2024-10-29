#include <gtest/gtest.h>

template<typename T>
struct Not {
    static constexpr bool value = !T::value;
};

template<typename T>
struct IsClass: Not<std::is_fundamental<T>> {};

struct myInt
{
    int data;
};

TEST(IsClass, IsClass) {
    EXPECT_TRUE(IsClass<std::vector<int>>::value);
}

TEST(IsClass, IsMyClass) {
    EXPECT_TRUE(IsClass<myInt>::value);
}

TEST(IsClass, IntNotClass) {
    EXPECT_FALSE(IsClass<int>::value);
}

TEST(IsClass, ConstIntNotClass) {
    EXPECT_FALSE(IsClass<const int>::value);
}
