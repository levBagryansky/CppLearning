#pragma once

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

class IShape: public IPerimeter, public IArea {};

class IPolygon {};
