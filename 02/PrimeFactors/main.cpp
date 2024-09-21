#include <iostream>
#include <cassert>

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

private:
    int num_;
    int curr_prime_{2};
};

int main(int argc, char *argv[]) {
    FactorsGen gen{16};
    while (gen.notEmpty()) {
        std::cout << gen.next() << " ";
    }
    std::cout << std::endl;
    return 0;
}


