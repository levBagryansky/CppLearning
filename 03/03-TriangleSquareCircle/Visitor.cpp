#include <iostream>

#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Ellipse.hpp"
#include "Square.hpp"

void Serializer::visit(const Rectangle &rectangle) const  {
std::cout << "Rectangle{" << rectangle.length_ << ", " << rectangle.width_ << "}" << std::endl;
}
void Serializer::visit(const Circle &circle) const {
std::cout << "Circle{" << circle.a_ << "}" << std::endl;
}
void Serializer::visit(const Triangle &triangle) const {
std::cout << "Triangle{" << triangle.a_ << ", " << triangle.b_ << ", " << triangle.c_ << "}" << std::endl;
}
void Serializer::visit(const Ellipse &ellipse) const {
std::cout << "Ellipse{" << ellipse.a_ << ", " << ellipse.b_ << "}" << std::endl;
}
void Serializer::visit(const Square &square) const {
std::cout << "Square{" << square.width_ << "}" << std::endl;
}
