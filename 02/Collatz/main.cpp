#include "Collatz.h"

#include <iostream>

int main() {
    Collatz collatz{};
    int num, max = 0;
    for (int i = 1; i < 10000; ++i) {
        int len = collatz.calcLen(i);
        num = len > max ? i : num;
        max = len > max ? len : max;
    }
    std::cout << "max length = " << max << " for num = " << num << std::endl;
//    collatz.calcSeq(3, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
