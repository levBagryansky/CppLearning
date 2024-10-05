#pragma once

#include "interfaces.hpp"
#include "Rectangle.hpp"

class Square final: public Rectangle {
public:
    explicit Square(double side): Rectangle(side, side) {};
    double perimeter() override {
        return 4 * Rectangle::width_;
    }
};
