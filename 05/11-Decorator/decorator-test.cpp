#include <gtest/gtest.h>

#include "text.hpp"

TEST(Decorator, Decorator_0) {
    const std::string content = "     \n\t   Hello, world! \t      \n    ";
    const Text& text = TrimmedText{
        std::make_unique<CapitalizedText>(CapitalizedText{
            std::make_unique<TextFromString>(TextFromString{
                content
            })
        })
    };
    const std::string result = text.content();
    EXPECT_EQ(result, "HELLO, WORLD!");
}
