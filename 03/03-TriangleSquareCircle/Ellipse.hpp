#pragma once

#include <numbers>

#include "interfaces.hpp"
#include "Visitor.hpp"

class Ellipse: public IShape {
    friend class Serializer;
public:
    Ellipse(double semiMajorAxis, double semiMinorAxis): a_(semiMajorAxis), b_(semiMinorAxis) {}
    void visit_by(const Visitor &visitor) const override;

    double perimeter() const override;
    double area() const override;

protected:
    double a_, b_;
};

