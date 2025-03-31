#include <utility>
#include "gtest/gtest.h"

#include "hex-strings-to-bytes.hpp"

TEST(HexStringToVecTest, BasicUppercaseHex) {
    auto vec = hexStringToVec("0A1B2C");
    std::vector<uint8_t> expected = {0x0A, 0x1B, 0x2C};
    EXPECT_EQ(vec, expected);
}

TEST(HexStringToVecTest, AllZeros) {
    auto vec = hexStringToVec("000000");
    std::vector<uint8_t> expected = {0x00, 0x00, 0x00};
    EXPECT_EQ(vec, expected);
}

TEST(HexStringToVecTest, MaxByteValues) {
    auto vec = hexStringToVec("FFEE");
    std::vector<uint8_t> expected = {0xFF, 0xEE};
    EXPECT_EQ(vec, expected);
}

TEST(HexStringToVecTest, EmptyString) {
    auto vec = hexStringToVec("");
    std::vector<uint8_t> expected = {};
    EXPECT_EQ(vec, expected);
}

TEST(HexStringToVecTest, OddLengthString) {
    EXPECT_DEATH({
                     hexStringToVec(std::string_view("ABC"));
                 }, ".*");
}

TEST(HexStringToVecTest, CustomVectorType) {
    struct CustomVector : public std::vector<uint8_t> {
        CustomVector() = default;
        CustomVector(std::vector<uint8_t> data): std::vector<uint8_t>(std::move(data)) {};
    };
    auto vec = hexStringToVec<CustomVector>(std::string_view("01FF"));
    CustomVector expected = std::vector<uint8_t>{0x01, 0xFF};
    EXPECT_EQ(vec, expected);
}
