#pragma once

#include "interfaces.hpp"
#include "Rectangle.hpp"

class Square final: public Rectangle {
    friend class Serializer;
public:
    void visit_by(const Visitor &visitor) const override {
        visitor.visit(*this);
    }
    explicit Square(double side): Rectangle(side, side) {};
    double perimeter() const override {
        return 4 * Rectangle::width_;
    }
};
