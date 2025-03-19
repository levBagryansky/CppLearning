#pragma once

class Rectangle;
class Circle;
class Triangle;
class Ellipse;
class Square;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const Rectangle& rectangle) const = 0;
    virtual void visit(const Circle& circle) const = 0;
    virtual void visit(const Triangle& triangle) const = 0;
    virtual void visit(const Ellipse& ellipse) const = 0;
    virtual void visit(const Square& square) const = 0;
};

class Serializer final: public Visitor {
    void visit(const Rectangle &rectangle) const override ;
    void visit(const Circle &circle) const override ;
    void visit(const Triangle &triangle) const override ;
    void visit(const Ellipse &ellipse) const override ;
    void visit(const Square &square) const override ;
};
