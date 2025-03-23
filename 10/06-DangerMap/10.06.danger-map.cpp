#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>

TEST(DangerMap, ConstCast) {
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    auto it = myMap.find(2);
    if (it != myMap.end()) {
        int* keyPtr = const_cast<int*>(&it->first);
        *keyPtr = 5;
    }

    std::cout << "Ordering violation" << std::endl;
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << std::endl;
    }

    EXPECT_FALSE(std::is_sorted(myMap.begin(), myMap.end()));
}

TEST(DangerMap, ReinterpretCast) {
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    auto it = myMap.find(2);
    if (it != myMap.end()) {
        auto* pairPtr = reinterpret_cast<std::pair<int, std::string>*>(&(*it));
        pairPtr->first = 5;
    }

    std::cout << "Ordering violation" << std::endl;
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << std::endl;
    }

    EXPECT_FALSE(std::is_sorted(myMap.begin(), myMap.end()));
}

TEST(DangerMap, Memcpy) {
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    auto it = myMap.find(2);
    if (it != myMap.end()) {
        int newKey = 5;
        std::memcpy((void*)&it->first, &newKey, sizeof(int));
    }

    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << std::endl;
    }

    EXPECT_FALSE(std::is_sorted(myMap.begin(), myMap.end()));
}
