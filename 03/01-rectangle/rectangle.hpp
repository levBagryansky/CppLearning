#pragma once

#include <cstdlib>
#include <vector>
#include <limits>

struct Point {
    int x_, y_;
};

class Rectangle{
public:
    Rectangle(int x, int y, int len_x, int len_y): left_lower_({x, y}), right_higher_({x+len_x, y+len_y}) {}
    Rectangle(Point left_lower, int len_x, int len_y): left_lower_(left_lower), right_higher_({left_lower.x_+len_x, left_lower.y_+len_y}) {}
    Rectangle(Point left_lower, Point right_higher): left_lower_(left_lower), right_higher_(right_higher) {}

public:
    Point left_lower_;
    Point right_higher_;
};

uint intersection(const std::vector<Rectangle>& vct) {
    if (vct.empty()) {
        return 0;
    }
    Point max_left_lower_{
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::min()
    };
    Point min_right_higher_{
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    };
    for (auto &rect: vct) {
        max_left_lower_.x_ = std::max(max_left_lower_.x_, rect.left_lower_.x_);
        max_left_lower_.y_ = std::max(max_left_lower_.y_, rect.left_lower_.y_);
        min_right_higher_.x_ = std::min(min_right_higher_.x_, rect.right_higher_.x_);
        min_right_higher_.y_ = std::min(min_right_higher_.y_, rect.right_higher_.y_);
    }
    if (min_right_higher_.x_ > max_left_lower_.x_ && min_right_higher_.y_ > max_left_lower_.y_) {
        return (min_right_higher_.x_ - max_left_lower_.x_) * (min_right_higher_.y_ - max_left_lower_.y_);
    }
    return 0;
}

