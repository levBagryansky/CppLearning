#pragma once

#include "interfaces.hpp"
#include <cmath>
#include <cassert>

class Triangle: public IPolygon, public IShape {
public:
    Triangle(double a, double b, double c): a_(a), b_(b), c_(c) {}

    double perimeter() override {return a_ + b_ + c_;}

    double area() override {
        double p = perimeter() / 2;
        assert(p >= 0.0);
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    double a_, b_, c_;
};

