#include "gtest/gtest.h"

#include <iomanip>
#include <list>
#include <array>

template<std::ranges::range Range> requires std::same_as<typename Range::value_type, uint8_t>
std::string toHexString(const Range& data) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex;

    for (uint8_t byte : data) {
        oss << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}

TEST(ToHexStringTest, VectorBasic) {
    std::vector<uint8_t> data = {0xBA, 0xAD};
    EXPECT_EQ(toHexString(data), "BAAD");
}

TEST(ToHexStringTest, ArrayWithLeadingZeros) {
    std::array<uint8_t, 3> data = {0x01, 0x0F, 0x00};
    EXPECT_EQ(toHexString(data), "010F00");
}

TEST(ToHexStringTest, ListContainer) {
    std::list<uint8_t> data = {0x12, 0x34, 0x56};
    EXPECT_EQ(toHexString(data), "123456");
}

TEST(ToHexStringTest, EmptyContainer) {
    std::vector<uint8_t> data;
    EXPECT_EQ(toHexString(data), "");
}

TEST(ToHexStringTest, AllHexLetters) {
    std::vector<uint8_t> data = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
    EXPECT_EQ(toHexString(data), "0A0B0C0D0E0F");
}

