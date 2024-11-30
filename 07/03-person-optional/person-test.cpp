#include <gtest/gtest.h>

#include "Person.h"

TEST(Person, Optional) {
    Person person{};
    std::cout << person << std::endl;
    person.setAge(12).setHeight(180).setName("Semen");
    std::cout << person << std::endl;
}
