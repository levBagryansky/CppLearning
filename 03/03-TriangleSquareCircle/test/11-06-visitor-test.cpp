#include <gtest/gtest.h>

#include "interfaces.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"
#include "Square.hpp"

TEST(TriangleSquareCircle_11_06, Triangle) {
    Triangle t{3, 4, 5};
    Serializer serializer{};
    t.visit_by(serializer);

    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Triangle{3, 4, 5}"), std::string::npos);
}

TEST(TriangleSquareCircle_11_06, Circle) {
    Circle c{3};
    Serializer serializer{};
    c.visit_by(serializer);

    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Circle{3}"), std::string::npos);
}

TEST(TriangleSquareCircle_11_06, Rectangle) {
    Rectangle r{3, 4};
    Serializer serializer{};
    r.visit_by(serializer);

    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Rectangle{3, 4}"), std::string::npos);
}

TEST(TriangleSquareCircle_11_06, Square) {
    Square s{3};
    Serializer serializer{};
    s.visit_by(serializer);

    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.find("Square{3, 4}"), std::string::npos);
}
