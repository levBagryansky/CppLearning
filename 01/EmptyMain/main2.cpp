#include <iostream>

struct Hack {

    Hack() {
        std::cout << "А руки то вот они" << std::endl;
    }
};

Hack global_hack{};

int main() {}
