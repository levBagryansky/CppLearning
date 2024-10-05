#include <gtest/gtest.h>

#include "interfaces.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Ellipse.hpp"
#include "Circle.hpp"
#include "Square.hpp"

TEST(Castings_05, UpCasting) {
    Ellipse* ellipse = new Ellipse{1, 2};
    Square* square = new Square{1};

    std::vector<IShape*> shapes{ellipse, square};
    std::transform(
        shapes.begin(), shapes.end(),
        std::ostream_iterator<double>(std::cout, " "), [] (IShape* shape) {return shape->perimeter();}
    );
    std::for_each(shapes.begin(), shapes.end(), [] (auto *shape) {delete shape;});
}

IShape* buildShape() {
    return new Circle{1};
}
TEST(Castings_05, DownCasting) {
    IShape* shape = buildShape();
    EXPECT_TRUE(dynamic_cast<Ellipse*>(shape));
    EXPECT_TRUE(dynamic_cast<Circle*>(shape));
    EXPECT_FALSE(dynamic_cast<Rectangle*>(shape));
    delete shape;
}

TEST(Castings_05, SideCasting) {
    IVirtualDestructable *destructable = new Triangle{3, 4, 5};

    IPerimeter* perimeter = dynamic_cast<IPerimeter*>(destructable);
    EXPECT_TRUE(perimeter);
    std::cout << "Perimeter = " << perimeter->perimeter() << std::endl;

    IArea* area = dynamic_cast<IArea*>(perimeter);
    EXPECT_TRUE(area);
    std::cout << "Area = " << area->area() << std::endl;

    Triangle *triangle = dynamic_cast<Triangle*>(destructable);
    EXPECT_TRUE(triangle);
    EXPECT_FALSE(dynamic_cast<Rectangle*>(triangle));

    delete destructable;
}