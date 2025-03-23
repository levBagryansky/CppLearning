#pragma once

class Visitor;

/**
 * Шалость во имя ISP.
 */
class IVirtualDestructable {
public: virtual ~IVirtualDestructable() = default;
};

class IPerimeter: public virtual IVirtualDestructable {
public: virtual double perimeter() const = 0;
};

class IArea: public virtual IVirtualDestructable {
public: virtual double area() const = 0;
};

class IShape: public IPerimeter, public IArea {
    friend class Visitor;
    virtual void visit_by(const Visitor& visitor) const = 0;
};

class IPolygon {};
