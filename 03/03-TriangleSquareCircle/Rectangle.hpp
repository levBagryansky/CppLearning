#pragma once

#include "interfaces.hpp"
#include "Visitor.hpp"

class Rectangle: public IPolygon, public IShape {
    friend class Serializer;
public:
    void visit_by(const Visitor &visitor) const override {
        visitor.visit(*this);
    }
    Rectangle(double length, double width): length_(length), width_(width) {}
    double perimeter() const override {
        return 2 * (length_ + width_);
    }
    double area() const override {
        return length_ * width_;
    }

protected:
    double length_, width_;
};
