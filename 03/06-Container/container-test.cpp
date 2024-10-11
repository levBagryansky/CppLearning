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
