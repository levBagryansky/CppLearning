#include <iostream>
#include <cassert>

void* foo();

template <auto F>
void* addressF() {
    return reinterpret_cast<void*>(F);
}

void* foo() {
    return addressF<foo>();
}

int main() {
    void* pfoo = foo();
    auto funcPtr = reinterpret_cast<void* (*)()>(pfoo);
    assert(funcPtr() == foo());
    std::cout << "Address of foo(): " << foo() << std::endl;
}
