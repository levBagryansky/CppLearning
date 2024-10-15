#pragma once

class IPv4 {
public:
    IPv4(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth):
        first_(first), second_(second), third_(third), fourth_(fourth) {}

public:
    friend std::istream & operator>>(std::istream & istream, IPv4 & ipv4) {
        char dot;
        constexpr auto ERROR = "Correct format of IPv4: <u8>.<u8>.<u8>.<u8>";
        unsigned int first, second, third, fourth;
        istream >> first >> dot;
        if (dot != '.' || first > 255)
            throw std::runtime_error(ERROR);
        istream >> second >> dot;
        if (dot != '.' || second > 255)
            throw std::runtime_error(ERROR);
        istream >> third >> dot;
        if (dot != '.' || third > 255)
            throw std::runtime_error(ERROR);
        istream >> fourth;
        if (fourth > 255)
            throw std::runtime_error(ERROR);
        ipv4 = IPv4(first, second, third, fourth);
        return istream;
    }

    friend std::ostream & operator<<(std::ostream & ostream, const IPv4 & ipv4) {
        constexpr char dot = '.';
        ostream << static_cast<int>(ipv4.first_) << dot <<  static_cast<int>(ipv4.second_) << dot << static_cast<int>(ipv4.third_) << dot << static_cast<int>(ipv4.fourth_);
        return ostream;
    }

private:
    uint8_t first_, second_, third_, fourth_;
};
