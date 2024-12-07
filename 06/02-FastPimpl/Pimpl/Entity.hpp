#pragma once

class Entity {
public:
    Entity();
    ~Entity();
    void foo();

private:
    class Impl;
    Impl *impl_;
};
