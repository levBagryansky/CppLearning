#include "Ellipse.hpp"

#include <complex>

void Ellipse::visit_by(const Visitor &visitor) const {
visitor.visit(*this);
}

double Ellipse::perimeter() const {
return std::numbers::pi * std::sqrt(
    2 * (a_ * a_ + b_ * b_)
);
}
double Ellipse::area() const {
return std::numbers::pi * b_ * a_;
}
