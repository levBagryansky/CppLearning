#pragma once

class Entity {
public:
    Entity();
    ~Entity();
    void foo();

private:
    class Impl;
    constexpr static size_t ImplBufSize = 128;
    std::byte buffer_[ImplBufSize];
};
