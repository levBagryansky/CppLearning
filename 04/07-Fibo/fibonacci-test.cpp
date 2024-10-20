#include <gtest/gtest.h>

#include "Fibobacci.hpp"

TEST(Fibonacci, Fibonacci) {
    EXPECT_EQ(Fibonacci<6>::value, 8);
    EXPECT_EQ(Fibonacci<0>::value, 0);
    EXPECT_EQ(Fibonacci<1>::value, 1);
}

TEST(Fibonacci, Fibo) {
    EXPECT_EQ(Fibo<6>{}(), 8);
    EXPECT_EQ(Fibo<1>{}(), 1);
    EXPECT_EQ(Fibo<0>{}(), 0);
}
