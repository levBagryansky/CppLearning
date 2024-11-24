#include <gtest/gtest.h>

#include "Entity.hpp"

TEST(PIMPL, CreatesAndCalls) {
    Entity{}.foo();
}
