#pragma once

#include "interfaces.hpp"
#include <cmath>
#include <cassert>

class Triangle: public IPolygon, public IShape {
public:
    Triangle(double a, double b, double c): a_(a), b_(b), c_(c) {
        assert(a_ > 0.0);
        assert(b_ > 0.0);
        assert(c_ > 0.0);
        assert(2 * std::max(a_, std::max(b_, c_)) - a_ - b_ - c_ < 0); // Condition for sides of triangle.
    }

    double perimeter() const override {return a_ + b_ + c_;}

    double area() const override {
        double p = perimeter() / 2;
        assert(p >= 0.0);
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    double a_, b_, c_;
};

