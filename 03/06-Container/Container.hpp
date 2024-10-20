#pragma once


template <typename T>
class Container {
public:
    explicit Container(size_t capacity);
    Container();
    Container(const Container& other);
    Container(Container&& other) noexcept;
    ~Container();

    int size() const;
    int capacity() const;
    bool isEmpty() const;
    void clear();
    void push_back(const T& value);

    template<typename ... Types>
    void push_back(const T& value, const Types & ... values) {
        push_back(value);
        push_back(values...);
    }

    T& front() const;
    T& front();
    T& back() const;
    T& back();
    T& operator[](int index) const;
    T& operator[](int index);
    void swap(Container<T>& other);

    Container & operator=(Container<T> other);
    bool operator==(const Container<T>& other) const;
    bool operator!=(const Container<T>& other) const;

private:
    constexpr static double FACTOR = 1.78;
    size_t size_;
    size_t capacity_;
    T* data_;
};

template <typename T>
Container<T>::Container(size_t capacity)
    : size_(0), capacity_(capacity), data_(new T[capacity]) {}

template <typename T>
Container<T>::Container(): Container(4) {
    std::cout << "Container<T>::Container(): capacity = " << capacity_ << std::endl;
}

template <typename T>
Container<T>::Container(const Container& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      data_(new T[other.capacity_]) {
    std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
Container<T>::Container(Container&& other) noexcept
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_) {
          other.data_ = nullptr;
          other.size_ = 0;
          other.capacity_ = 0;
      }

template <typename T>
Container<T>::~Container() {
    std::cout << "Capacity = " << capacity_ << ", size = " << size_ << ", destructing.." << std::endl;
    delete[] data_;
    std::cout << "Destructed" << std::endl;
}

template <typename T>
int Container<T>::size() const {
    return size_;
}

template <typename T>
int Container<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool Container<T>::isEmpty() const {
    return size_ == 0;
}

template <typename T>
void Container<T>::clear() {
    size_ = 0;
}

template <typename T>
void Container<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        std::cout << "Capacity = " << capacity_<< ", resizing.." << std::endl;
        auto new_capacity = 2 + FACTOR * capacity_;
        T* new_data = new T[static_cast<int>(new_capacity)];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = static_cast<int>(new_capacity);
        std::cout << "Resized" << std::endl;
    }
    data_[size_] = value;
    ++size_;
}

template <typename T>
T& Container<T>::front() const {
    if (size_ == 0) {
        throw std::runtime_error("Container is empty");
    }

    return data_[0];
}

template <typename T>
T& Container<T>::front() {
    if (size_ == 0) {
        throw std::runtime_error("Container is empty");
    }

    return data_[0];
}

template <typename T>
T& Container<T>::back() const {
    if (size_ == 0) {
        throw std::runtime_error("Container is empty");
    }

    return data_[size_ - 1];
}

template <typename T>
T& Container<T>::back() {
    if (size_ == 0) {
        throw std::runtime_error("Container is empty");
    }

    return data_[size_ - 1];
}

template<typename T>
T &Container<T>::operator[](int index) const {
    if (index > size_ || index < 0) {
        throw std::runtime_error("Index is out of boundaries");
    }

    return data_[index];
}

template<typename T>
T &Container<T>::operator[](int index) {
    if (index > size_ || index < 0) {
        throw std::runtime_error("Index is out of boundaries");
    }

    return data_[index];
}

template <typename T>
void Container<T>::swap(Container<T>& other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template<typename T>
Container<T> & Container<T>::operator=(Container<T> other) {
    std::cout << "Container::operator= (swap)" << std::endl;
    swap(other);
    return *this;
}

template <typename T>
bool Container<T>::operator==(const Container<T>& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (uint64_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Container<T>::operator!=(const Container<T>& other) const {
    return !(operator==(other));
}
