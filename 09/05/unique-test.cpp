#include <gtest/gtest.h>

#include "Unique.hpp"


class Base {
public:
    explicit Base(int a) : a_(a) {}
    virtual ~Base() {}

    int a_;
};

class Derived : public Base {
public:
    Derived(int a, int b) : Base(a), b_(b) {}

    int b_;
};

TEST(UniquePtr, DefaultConstructor) {
    const Unique<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, ConstructorWithValue) {
    const Unique<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
}

TEST(UniquePtr, ConstructorWithValueInheritance) {
    const Unique<Base> ptr(new Derived(41, 42));
    EXPECT_EQ(ptr->a_, 41);
    EXPECT_EQ(dynamic_cast<Derived*>(ptr.get())->b_, 42);
}

TEST(UniquePtr, MoveConstructor) {
    Unique<int> ptr1(new int(42));  
    const Unique<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.release(), nullptr);  
}

TEST(UniquePtr, MoveConstructorInheritance) {
    Unique<Derived> ptr_derived(new Derived(41, 42));  
    const Unique<Base> ptr_base(std::move(ptr_derived));
    EXPECT_EQ(ptr_base->a_, 41);
    EXPECT_EQ(dynamic_cast<Derived*>(ptr_base.get())->b_, 42);
    EXPECT_EQ(ptr_derived.release(), nullptr);  
}

TEST(UniquePtr, MoveAssignment) {
    Unique<int> ptr1(new int(42));  
    Unique<int> ptr2;
    ptr2 = std::move(ptr1);
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.release(), nullptr);  
}

TEST(UniquePtr, MoveAssignmentInheritance) {
    Unique<Derived> ptr_derived(new Derived(41, 42));  
    Unique<Base> ptr_base;
    ptr_base = std::move(ptr_derived);
    EXPECT_EQ(ptr_base->a_, 41);
    EXPECT_EQ(dynamic_cast<Derived*>(ptr_base.get())->b_, 42);
    EXPECT_EQ(ptr_derived.release(), nullptr);  
}

TEST(UniquePtr, Reset) {
    Unique<int> ptr(new int(42));  
    ptr.reset(new int(99));        
    EXPECT_EQ(*ptr, 99);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, Release) {
    Unique<int> ptr(new int(42));  
    int* raw = ptr.release();
    EXPECT_EQ(*raw, 42);
    EXPECT_EQ(ptr.get(), nullptr);
    delete raw;
}

TEST(UniquePtr, Swap) {
    Unique<int> ptr1(new int(42));  
    Unique<int> ptr2(new int(99));  
    ptr1.swap(ptr2);
    EXPECT_EQ(*ptr1, 99);
    EXPECT_EQ(*ptr2, 42);
}

TEST(UniquePtr, BooleanConversion) {
    const Unique<int> ptr1(new int(42));  
    const Unique<int> ptr2;
    EXPECT_TRUE(ptr1);
    EXPECT_FALSE(ptr2);
}

TEST(UniquePtr, ArrowOperator) {
    const Unique<Derived> ptr(new Derived(41, 42));  
    EXPECT_EQ(ptr->a_, 41);
    EXPECT_EQ(ptr->b_, 42);
}
