#include <gtest/gtest.h>

#include "Logger.hpp"

int Logger::nesting = 0;

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
