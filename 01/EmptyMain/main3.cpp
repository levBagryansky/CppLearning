#include <iostream>

#define foo() main()
int foo() {
    std::cout << "Hello world" << std::endl;
}

#define main() bar()
int main() {
    return 0;
}
