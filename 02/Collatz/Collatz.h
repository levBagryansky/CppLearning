#pragma once

#include <unordered_map>
#include <vector>
#include <cassert>

struct Item {
    int len_;
    int next_;
    bool inited() const {
        if (len_ == 0 || next_ == 0)
            assert(len_ == 0 && next_ == 0);
        return len_ != 0;
    }
};

/**
 * Safe vector.
 * @tparam T element type. Note, T should be easy to copy.
 */
template<typename T>
class SafeVector {
public:
    void set(size_t index, T item) {
        if (index >= data_.size()) {
            map_[index] = item;
        }
        else {
            data_[index] = item;
        }
    }

    Item get(int index) {
        if (index >= data_.size()) {
            return map_[index];
        } else {
            return data_[index];
        }
    }

private:
    static constexpr int THRESHOLD = 10001;
    std::vector<T> data_{THRESHOLD};
    std::unordered_map<int, Item> map_{};
};

class Collatz {
public:

    Collatz(): storage_{} {
        storage_.set(0, {0, 0}); // Undefined element
        storage_.set(1, {1, 1}); // First element
    }

    template<typename OutputIt>
    void calcSeq(int num, OutputIt out) {
        while (num != 1) {
            *out = num;
            ++out;
            num = calcItem(num).next_;
        }
        *out = num;
    }

    int calcLen(int num) {
        return calcItem(num).len_;
    }

private:
    Item calcItem(int num) {
        Item item = storage_.get(num);
        if (item.inited())
            return item;
        int next = applyStep(num);
        int len = calcLen(next) + 1;
        storage_.set(num, {len, next});
        return storage_.get(num);
    }

public:
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

