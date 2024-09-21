#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>

class FactorsGen {
public:
    explicit FactorsGen(int initial): num_(initial) {
        assert(num_ >= 0);
    }

    int next() {
        if (num_ < 2) {
            return -1;
        }
        for (int i = curr_prime_; i <= num_; ++i) {
            if (num_ % i == 0) {
                curr_prime_ = i;
                num_ /= curr_prime_;
                return curr_prime_;
            }
        }
        assert(false); // Should not be here
    }

    bool notEmpty() {
        return num_ != 1;
    }

    template<typename OutIt>
    static void allFactors(int num, OutIt start) {
        FactorsGen gen{num};
        while (gen.notEmpty()) {
            *start = gen.next();
            ++start;
        }
    }

private:
    int num_;
    int curr_prime_{2};
};

int main(int argc, char *argv[]) {
    int num = std::stoi(argv[1], nullptr);
    std::vector<int> vector;
    FactorsGen::allFactors(num, std::back_inserter(vector));
    FactorsGen::allFactors(num, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
