#include <gtest/gtest.h>

#include "interfaces.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"

using std::numbers::pi;

TEST(TriangleSquareCircle_03, Triangle) {
    Triangle triangle{3, 4, 5};
    IShape &shape = triangle;

    EXPECT_DOUBLE_EQ(shape.area(), 6.0);
    EXPECT_DOUBLE_EQ(shape.perimeter(), 12.0);
}

TEST(TriangleSquareCircle_03, Circle) {
    Circle obj{1};
    IShape &shape = obj;

    EXPECT_DOUBLE_EQ(shape.area(), pi);
    EXPECT_DOUBLE_EQ(shape.perimeter(), 2 * pi);
}

TEST(TriangleSquareCircle_03, Rectangle) {
    Rectangle obj{1, 2};
    IShape &shape = obj;
    EXPECT_DOUBLE_EQ(shape.area(), 2);
    EXPECT_DOUBLE_EQ(shape.perimeter(), 6);
}
