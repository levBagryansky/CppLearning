#include <gtest/gtest.h>
#include <numeric>

#include "../factors-gen.h"

TEST(FactorGen, multiplies) {
    for (int i = 1; i < 1000; ++i) {
        std::vector<int> vector;
        FactorsGen::allFactors(i, std::back_inserter(vector));
        int prod = std::reduce(vector.begin(), vector.end(),
            1,
            [](int accum, int next) -> int {
                return accum * next;
            }
        );
        EXPECT_EQ(prod, i);
    }
}
