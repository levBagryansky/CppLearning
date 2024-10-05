#include "interfaces.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"

#include <iostream>

int main() {
    Triangle triangle{3, 4, 5};
    std::cout << "Perimeter of triangle = " << triangle.perimeter() << std::endl;
    std::cout << "Area of triangle = " << triangle.area() << std::endl << std::endl;

    Rectangle rectangle{2, 5};
    std::cout << "Perimeter of rectangle = " << rectangle.perimeter() << std::endl;
    std::cout << "Area of rectangle = " << rectangle.area() << std::endl << std::endl;

    return 0;
}
