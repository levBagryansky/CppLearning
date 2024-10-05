#pragma once

#include "Ellipse.hpp"

class Circle final: public Ellipse {
public:
    explicit Circle(double rad): Ellipse(rad, rad) {}
    double perimeter() override {
        return 2 * std::numbers::pi * Ellipse::a_;
    }
};
