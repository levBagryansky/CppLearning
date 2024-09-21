#include <iostream>

struct Hack {

    Hack() {
        std::cout << "Hello world" << std::endl;
    }
};

Hack global_hack{};

int main() {}
