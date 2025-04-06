#include "gtest/gtest.h"

#include "URL.hpp"

TEST(URL, CTOR) {
    EXPECT_EQ(
        URL("https://github.com/aboba/12-strings"),
        URL("https", "github.com", "", "/aboba/12-strings")
    );
}
