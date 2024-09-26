#include <iostream>
#include <cassert>
#include <iterator>
#include <sstream>

enum Rod {
    FIRST = 1,
    SECOND,
    THIRD,
};

/**
 * Find an extra option. There are 3 options and 2 are given.
 * @param one First option.
 * @param two Second option.
 * @return Extra option.
 */
Rod anotherVertical(Rod one, Rod two) {
    assert(one != two);
    return static_cast<Rod>(FIRST + SECOND + THIRD - one - two);
}

struct Instruction {
    Rod src;
    Rod dst;
    friend std::ostream& operator<< (std::ostream& os, const Instruction& instruction) {
        return os << instruction.src << " -> " << instruction.dst;
    }
};

template<typename OutputIt>
void shift(Rod src, Rod dst, int N, OutputIt dump) {
    assert(src != dst);
    assert(N > 0);
    if (N > 1) {
        Rod buf = anotherVertical(src, dst);
        shift(src, buf, N-1, dump);
        *(dump++) = Instruction{src, dst};
        shift(buf, dst, N-1, dump);
    } else {
        *(dump++) = Instruction{src, dst};
    }
}

int main(int argc, char **argv) {
    assert(argc == 2);
    std::istringstream ss(argv[1]);
    int N;
    if (!(ss >> N)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
    } else if (!ss.eof()) {
        std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    }

    shift(FIRST, SECOND, N, std::ostream_iterator<Instruction>(std::cout, "\n"));
    return 0;
}
