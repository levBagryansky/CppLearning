#pragma once

#include "interfaces.hpp"

#include <numbers>

class Ellipse: public IShape {
public:
    Ellipse(double semiMajorAxis, double semiMinorAxis): a_(semiMajorAxis), b_(semiMinorAxis) {}
    double perimeter() override {
        return std::numbers::pi * std::sqrt(
            2 * (a_ * a_ + b_ * b_)
        );
    }
    double area() override {
        return std::numbers::pi * b_ * a_;
    }

protected:
    double a_, b_;
};

