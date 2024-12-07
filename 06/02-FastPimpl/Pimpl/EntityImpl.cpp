#include <iostream>

#include "Entity.hpp"

class Entity::Impl {
public:
    void foo_impl() {
        std::cout << "Hello" << std::endl;
    }

private:
    int f_ = 0;
};

Entity::Entity(): impl_(new Impl()) {}
Entity::~Entity() {delete impl_;}

void Entity::foo() {
    impl_->foo_impl();
}
