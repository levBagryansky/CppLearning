#include <gtest/gtest.h>

#include "Logger.hpp"

void foo() {
    Logger logger{};
}

void bar() {
    Logger logger{};
    foo();
}

TEST(Logger, logs) {
    Logger log{};
    bar();
}
