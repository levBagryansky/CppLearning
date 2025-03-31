#include "gtest/gtest.h"

#include "a3b3c3.hpp"

TEST(A3B3C3Test, BasicCompression) {
    EXPECT_EQ(a3b3c3("aaabbbccc"), "a3b3c3");
}

TEST(A3B3C3Test, SingleCharacters) {
    EXPECT_EQ(a3b3c3("abc"), "a1b1c1");
}

TEST(A3B3C3Test, MixedRepeats) {
    EXPECT_EQ(a3b3c3("aabccccaaa"), "a2b1c4a3");
}

TEST(A3B3C3Test, EmptyString) {
    EXPECT_EQ(a3b3c3(""), "");
}

TEST(A3B3C3Test, OneCharacterRepeated) {
    EXPECT_EQ(a3b3c3("aaaaaa"), "a6");
}

TEST(A3B3C3Test, NoRepeats) {
    EXPECT_EQ(a3b3c3("xyz"), "x1y1z1");
}

TEST(A3B3C3Test, AllSameLetterBlocks) {
    EXPECT_EQ(a3b3c3("aaabbb"), "a3b3");
}

TEST(A3B3C3Test, AlternatingLetters) {
    EXPECT_EQ(a3b3c3("ababab"), "a1b1a1b1a1b1");
}
