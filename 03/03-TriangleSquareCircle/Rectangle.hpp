#pragma once

#include "interfaces.hpp"

class Rectangle: public IPolygon, public IShape {
public:
    Rectangle(double length, double width): length_(length), width_(width) {}
    double perimeter() override {
        return 2 * (length_ + width_);
    }
    double area() override {
        return length_ * width_;
    }

protected:
    double length_, width_;
};
