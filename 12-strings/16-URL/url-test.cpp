#include "gtest/gtest.h"

#include "URL.hpp"

TEST(URL, CTOR) {
    EXPECT_EQ(
        URL("https://github.com/aboba/12-strings"),
        URL("https", "github.com", "", "/aboba/12-strings")
    );
}

TEST(URL, InvalidInput) {
    EXPECT_THROW(URL("aboba"), std::runtime_error);
}
