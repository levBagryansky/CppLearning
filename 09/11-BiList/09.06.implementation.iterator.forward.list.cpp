#include <iterator>
#include <memory>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
class List {
private:
    struct Node {
        T data = T();
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;
    };

public:
    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;

        explicit Iterator(std::shared_ptr<Node> node = nullptr) : node_(node) {}

        Iterator operator++(int) {
            auto copy(*this);
            node_ = node_->next;
            return copy;
        }
        Iterator& operator++() {
            node_ = node_->next;
            return *this;
        }
        virtual Iterator operator--(int) {
            auto copy(*this);
            node_ = node_->prev.lock();
            return copy;
        }
        virtual Iterator& operator--() {
            node_ = node_->prev.lock();
            return *this;
        }
        T& operator*() const { return node_->data; }
        T* operator->() const { return &node_->data; }
        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.node_ == rhs.node_;
        }

    private:
        std::shared_ptr<Node> node_;
    };

    Iterator begin() const { return Iterator(head_); }
    Iterator end() const { return Iterator(); }

    const T& front() const { return head_->data; }
    T& front() { return head_->data; }
    const T& back() const { return tail_->data; }
    T& back() { return tail_->data; }

    void push_back(T x) {
        if (!tail_) {
            tail_ = std::make_shared<Node>(x, std::weak_ptr<Node>(), nullptr);
            head_ = tail_;
        } else {
            const std::shared_ptr<Node> node = std::make_shared<Node>(x, tail_, nullptr);
            tail_->next = node;
            tail_ = node;
        }
    }
    void push_front(T x) {
        if (!head_) {
            head_ = std::make_shared<Node>(x, std::weak_ptr<Node>(), nullptr);
            tail_ = head_;
        } else {
            const std::shared_ptr<Node> node =
                std::make_shared<Node>(x, std::weak_ptr<Node>(), head_);
            head_->prev = node;
            head_ = node;
        }
    }

private:
    std::shared_ptr<Node> head_;
    std::shared_ptr<Node> tail_;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    List < int > list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto it = std::begin(list);
    for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator) {
        std::cout << *iterator << std::endl;
        it = iterator;
    }

    for (; it != std::begin(list); --it) {
        std::cout << *it << std::endl;
    }
    std::cout << *it << std::endl;

    for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator);

    for ([[maybe_unused]] auto element : list); // support: cppinsights.io
}
