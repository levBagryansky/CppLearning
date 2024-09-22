#include <gtest/gtest.h>

#include "Collatz.h"

/**
 * For number = 3;
 */
TEST(Collatz, CorrectSeq) {
    std::vector<int> correct{3, 10, 5, 16, 8, 4, 2, 1};
    std::vector<int> computed{};
    Collatz{}.calcSeq(3, std::back_insert_iterator(computed));
    EXPECT_EQ(computed, correct);
}

/**
 * Check that the biggest len is correct.
 */
TEST(Collatz, CorrectAnswer) {
    Collatz collatz{};
    int num, max_len = 0;
    for (int i = 1; i < 10000; ++i) {
        int len = collatz.calcLen(i);
        num = len > max_len ? i : num;
        max_len = len > max_len ? len : max_len;
    }
    EXPECT_EQ(num, 6171);
    EXPECT_EQ(max_len, 262);
}
