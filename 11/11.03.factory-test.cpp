#include <gtest/gtest.h>

#include <functional>
#include <map>
#include <typeindex>
#include <variant>

template <typename... Ts>
class Factory {
public:
    using creator_type = std::variant<std::function<Ts()>...>;
    explicit Factory(std::function<Ts()>... args) : map_{{typeid(Ts), creator_type(args)}...} {}

    template <typename T>
    T create() const {
        return std::get<std::function<T()>>(map_.find(typeid(T))->second)();
    }

private:
    std::unordered_map<std::type_index, std::variant<std::function<Ts()>...>> map_;
};



struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

class Person {
public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {}
    std::string getName() const { return name_; }
    int getAge() const { return age_; }
    bool operator==(const Person& other) const {
        return name_ == other.name_ && age_ == other.age_;
    }

private:
    std::string name_;
    int age_;
};

TEST(Factory, StandardTypes) {
    constexpr int ret1 = 42;
    constexpr double ret2 = 42.42;
    const Factory<int, double> factory{[]() { return ret1; }, []() { return ret2; }};
    EXPECT_EQ(factory.create<int>(), ret1);
    EXPECT_FLOAT_EQ(factory.create<double>(), ret2);
}

TEST(Factory, CustomTypes) {
    const Point point{10, 20};
    const Person person{"Alice", 30};
    const Factory<Point, Person> factory{[point]() { return point; },
                                         [person]() { return person; }};
    EXPECT_EQ(factory.create<Point>(), point);
    EXPECT_EQ(factory.create<Person>(), person);
}

TEST(Factory, ComplexConstructors) {
    const Factory<std::vector<int>, std::string> factory{
        []() { return std::vector<int>{1, 2, 3}; }, []() { return std::string("Hello, World!"); }};
    const std::vector<int> expected_vector{1, 2, 3};
    const std::string expected_string = "Hello, World!";
    EXPECT_EQ(factory.create<std::vector<int>>(), expected_vector);
    EXPECT_EQ(factory.create<std::string>(), expected_string);
}

TEST(Factory, SmartPointers) {
    constexpr int ret1 = 42;
    constexpr double ret2 = 3.14;
    const Factory<std::unique_ptr<int>, std::shared_ptr<double>> factory{
        [ret1]() { return std::make_unique<int>(ret1); },
        [ret2]() { return std::make_shared<double>(ret2); }};
    auto unique_ptr = factory.create<std::unique_ptr<int>>();
    auto shared_ptr = factory.create<std::shared_ptr<double>>();
    EXPECT_EQ(*unique_ptr, ret1);
    EXPECT_DOUBLE_EQ(*shared_ptr, ret2);
}

TEST(Factory, OptionalTypes) {
    const Factory<std::optional<int>, std::optional<std::string>> factory{
        []() { return std::optional<int>(42); },
        []() { return std::optional<std::string>("Hello"); }};
    EXPECT_EQ(factory.create<std::optional<int>>().value(), 42);
    EXPECT_EQ(factory.create<std::optional<std::string>>().value(), "Hello");
}
