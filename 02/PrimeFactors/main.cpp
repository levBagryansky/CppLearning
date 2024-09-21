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
        for (int i = max_prime_; i < num_; ++i) {

        }
    }

private:
    int num_;
    int max_prime_{2};
};

int main(int argc, char *argv[]) {
    if (argc != 2)
        abort();

    return 0;
}


