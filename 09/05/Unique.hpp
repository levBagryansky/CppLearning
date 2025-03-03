#include <cassert>
#include <utility>

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////////////////////

template < typename T > class Unique : private boost::noncopyable
{
public:
    explicit Unique(T* ptr = nullptr) : data_(ptr) {}
    template <typename U>
    requires std::convertible_to<U*, T*>
    explicit Unique(Unique<U>&& other) : Unique() {
        data_ = other.release();
    }
    Unique(Unique&& other) : Unique() { swap(other); }

    template <typename U>
    requires std::convertible_to<U*, T*>
    auto& operator=(Unique<U>&& other) {
        reset(other.release());
        return *this;
    }
    auto& operator=(Unique&& other) noexcept {
        reset(other.release());
        return *this;
    }

    ~Unique() { reset(); }

    void swap(Unique& other) { std::swap(data_, other.data_); }
    T* get() const { return data_; }
    T* release() { return std::exchange(data_, nullptr); }
    void reset(T* ptr = nullptr) {
        delete data_;
        data_ = ptr;
    }

    T& operator*() const { return *get(); }
    T* operator->() const { return get(); }
    explicit operator bool() const { return get() != nullptr; }

private:
    T* data_ = nullptr;
};

/////////////////////////////////////////////////////////////////////////

template <typename T, typename... Ts>
auto make_unique(Ts&&... xs) {
    return Unique<T>(new T(std::forward<Ts>(xs)...));
}

