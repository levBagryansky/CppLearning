#include <cmath>
#include <iostream>
#include <cassert>

/**
 * Шалость во имя ISP.
 */
class IVirtualDestructable {
    public: virtual ~IVirtualDestructable() = default;
};

class IPerimeter: public IVirtualDestructable {
    public: virtual double perimeter() = 0;
};

class IArea: public IVirtualDestructable {
    public: virtual double area() = 0;
};

class Triangle: public IPerimeter, IArea {
public:
    Triangle(double a, double b, double c): a_(a), b_(b), c_(c) {}

    double perimeter() override {return a_ + b_ + c_;}

    double area() override {
        double p = perimeter() / 2;
        assert(p >= 0.0);
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    double a_, b_, c_;
};

int main() {
    Triangle triangle{3, 4, 5};
    std::cout << "Perimeter of triangle = " << triangle.perimeter() << std::endl;
    std::cout << "Area of triangle = " << triangle.area() << std::endl;


    return 0;
}
