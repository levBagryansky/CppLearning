#pragma once

class Person {
public:
    Person(): age_(std::nullopt), height_(std::nullopt), name_(std::nullopt) {}

    // setters
    Person& setAge(std::optional<uint8_t> age) {
        age_ = age;
        return *this;
    }
    Person& setHeight(std::optional<uint8_t> height) {
        height_ = height;
        return *this;
    }
    Person& setName(std::optional<std::string> &&name) {
        name_ = std::move(name);
        return *this;
    }

    // getters
    const auto& getAge() const {return age_;}
    const auto& getHeight() const {return height_;}
    const auto& getName() const {return name_;}

    friend std::ostream& operator<< (std::ostream& os, const Person& person) {
        constexpr auto empty = "empty";
        return os << "Person{"
                  << (person.age_.has_value() ? std::to_string(person.age_.value()) : empty) << ", "
                  << (person.height_.has_value() ? std::to_string(person.height_.value()) : empty) << ", "
                  << (person.name_.has_value() ? person.name_.value() : empty)
                  << "}";
    }

private:
    std::optional<uint8_t> age_;
    std::optional<uint8_t> height_;
    std::optional<std::string> name_;
};
