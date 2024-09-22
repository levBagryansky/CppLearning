#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>

struct Item {
    int len_;
    int next_;
    bool inited() const {
        if (len_ == 0 || next_ == 0)
            assert(len_ == 0 && next_ == 0);
        return len_ != 0;
    }
};

int counter = 0;
/**
 * Safe vector.
 * @tparam T element type. Note, T should be easy to copy.
 */
template<typename T>
class SafeVector {
public:
    void set(size_t index, T item) {
        if (index >= data_.size()) {
            ++counter;
            data_.resize(data_.size() * 2);
        }
        data_[index] = item;
    }

    Item get(int index) {
        if (index < data_.size())
            return data_[index];
        else
            return T{};
    }

    ~SafeVector() {
        int count_of_inited = 0;
        for (int i = 10001; i < data_.size(); ++i) {
            count_of_inited += data_[i].inited();
        }
        std::cout << "count of inited after 10000 = " << count_of_inited << "/" << data_.size() << " = 1/" << data_.size() / count_of_inited << std::endl;
    }

private:
    static constexpr int THRESHOLD = 10000;
    std::vector<T> data_{THRESHOLD};
};

class Collatz {
public:

    Collatz(): storage_{} {
        storage_.set(0, {0, 0}); // Undefined element
        storage_.set(1, {1, 1}); // First element
    }

    template<typename OutputIt>
    int calcSeq(int num, OutputIt out) {
        *out = num;
        ++out;

        return 0;
    }

    int calcLen(int num) {
        return calcItem(num).len_;
    }

private:
    Item calcItem(int num) {
        Item item = storage_.get(num);
//        std::cout << item.len_ << " " << item.next_ << std::endl;
        if (item.inited())
            return item;
        int next = applyStep(num);
        int len = calcLen(next) + 1;
        storage_.set(num, {len, next});
        return storage_.get(num);
    }

    static int applyStep(int curr) {
        assert(curr > 0);
        if (curr % 2) {
            return 3 * curr + 1;
        } else {
            return curr / 2;
        }
    }

private:
    SafeVector<Item> storage_;
};

int main() {
    Collatz collatz{};
    int max = 0;
    for (int i = 1; i < 10000; ++i) {
        int len = collatz.calcLen(i);
        max = len > max ? len : max;
    }
    std::cout << "max len = " << max << std::endl;
    return 0;
}
