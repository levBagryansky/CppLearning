#include <gtest/gtest.h>

#include "rectangle.hpp"

TEST(RectangleIntersections, PointOutside) {
    Rectangle rect1({0, 0}, 4, 4);
    Rectangle rect2({0, 0}, 0, 0);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, PointInside) {
    Rectangle rect1({0, 0}, 4, 4);
    Rectangle rect2({1, 1}, 0, 0);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, LineOutside) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({-1, -1}, 0, 5);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, LineInside) {
    Rectangle rect1({0, 0}, 4, 4);
    Rectangle rect2({1, 1}, 0, 2);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, LineIntersect) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({-1, 2}, 0, 10);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}


TEST(RectangleIntersections, RectangleOutside) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({5, 5}, 3, 10);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, RectangleIntersectPoint) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({4, 4}, 3, 10);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, RectangleIntersectLine) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({-1, 4}, 3, 10);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 0);
}

TEST(RectangleIntersections, RectangleInside) {
    const Rectangle rect1({0, 0}, 4, 4);
    const Rectangle rect2({0, 0}, 2, 2);
    const Rectangle rect3({ -1, -2 }, 3, 4);
    auto result = intersection({rect1, rect2, rect3 });
    EXPECT_EQ(result, 4);
}

TEST(RectangleIntersections, RectangleIntersection) {
    const Rectangle rect1({-10, -10}, 4, 4);
    const Rectangle rect2({-8, -8}, 10, 10);
    auto result = intersection({rect1, rect2});
    EXPECT_EQ(result, 4);
}
