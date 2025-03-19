#pragma once

#include "Ellipse.hpp"

class Circle final: public Ellipse {
    friend class Serializer;
public:
    void visit_by(const Visitor &visitor) const override {
        visitor.visit(*this);
    }
    explicit Circle(double rad): Ellipse(rad, rad) {}
    double perimeter() const override {
        return 2 * std::numbers::pi * Ellipse::a_;
    }
};
