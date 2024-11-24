#pragma once

class Entity {
public:
    Entity();
    void foo();

private:
    class Impl;
    Impl *impl_;
};
