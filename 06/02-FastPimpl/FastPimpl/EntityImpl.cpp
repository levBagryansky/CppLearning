#include <iostream>
#include <cassert>

#include "Entity.hpp"

class Entity::Impl {
public:
    Impl() {std::cout << "Entity::Impl()" << std::endl;}
    ~Impl() {std::cout << "~Entity::Impl()" << std::endl;}

    void foo_impl() {
        assert(f_ == 12345);
        std::cout << "Hello" << std::endl;
    }

    int f_ = 12345;
};

Entity::Entity() {
    static_assert(sizeof(Impl) <= sizeof(buffer_));
    new (buffer_) Impl();
}

Entity::~Entity() {
    reinterpret_cast<Impl*>(buffer_)->~Impl();
}

void Entity::foo() {
    Impl* pimpl = reinterpret_cast<Impl*>(buffer_);
    assert(pimpl->f_ == 12345);
    pimpl->foo_impl();
}
