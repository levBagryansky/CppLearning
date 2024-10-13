#include <iostream>
#include "IPv4.hpp"

int main() {
    IPv4 ipv4{0, 0, 0, 0};
    std::cin >> ipv4;
    std::cout << "printing.." << std::endl << ipv4 << std::endl;
    return 0;
}