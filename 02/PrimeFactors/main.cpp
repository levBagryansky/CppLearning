#include <iostream>
#include <vector>
#include <iterator>
#include <string>

#include "factors-gen.h"

int main(int argc, char *argv[]) {
    int num = std::stoi(argv[1], nullptr);
    std::vector<int> vector;
    FactorsGen::allFactors(num, std::back_inserter(vector));
    FactorsGen::allFactors(num, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
