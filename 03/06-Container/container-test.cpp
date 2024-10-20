#include <gtest/gtest.h>

#include "Container.hpp"

/**
 * Structure which should be correctly destructed.
 */
struct Item {
    explicit Item(): arr_(new int[10]) {std::cout << "Item()" << std::endl;}

    // Rule of 5
    Item(const Item& other): Item(){};
    Item(Item&& other) noexcept: arr_(other.arr_) {other.arr_ = nullptr;};
    Item & operator=(Item other) {std::swap(arr_, other.arr_); return *this;};
    ~Item() {delete[] arr_; std::cout << "~Item()" << std::endl;}
private:
    int* arr_;
};

TEST(Container, Container1) {
    Container<Item> items(0);
    std::cout << "Constructed" << std::endl;
    items.push_back(Item{});
    std::cout << "--------------------" << std::endl;
    Item item{};
    items.push_back(item);
}

TEST(Container, ContainerClear) {
    Container<Item> items(0);
    std::cout << "Constructed" << std::endl;
    items.push_back(Item{});
    items.push_back(Item{});
    std::cout << "====================" << std::endl;
    items.clear();
    EXPECT_TRUE(items.isEmpty());
    EXPECT_EQ(items.size(), 0);
    EXPECT_EQ(items.capacity(), 2);
    EXPECT_THROW(items.front(), std::runtime_error);
}

TEST(Container, ContainerAssignment) {
    Container<Item> items(0);
    std::cout << "Constructed" << std::endl;
    items.push_back(Item{});
    items.push_back(Item{});
    std::cout << "====================" << std::endl;
    EXPECT_EQ(items.size(), 2);
    Container<Item> aboba(std::move(items));
    std::cout << "aboba is created" << std::endl;
    EXPECT_EQ(aboba.size(), 2);
}

TEST(Container, ZeroElement) {
    Container<int> ints;
    ints.push_back(2);
    EXPECT_EQ(ints[0], 2);
}

TEST(Container, MoveContainer) {
    Container<int> ints;
    ints.push_back(1);
    ints.push_back(2);
    ints.push_back(3);
    Container<int> ints_2(std::move(ints));
    EXPECT_EQ(ints.size(), 0);
}

TEST(Container, VarargPushBack) {
    Container<int> ints;
    ints.push_back(0, 1, 2, 3, 4, 5);
    for (int i = 0; i < ints.size(); ++i) {
        EXPECT_EQ(ints[i], i);
    }
}
