#include <iostream>
#include <cassert>

class Base1 {
public:
    virtual int foo() = 0;
};

class ProxyBase1: public Base1 {
public:
    int foo() override {
        return foo1();
    }

private:
    virtual int foo1 () = 0;
};

class Base2 {
public:
    virtual int foo() = 0;
};

class ProxyBase2: public Base2 {
public:
    int foo() override {
        return foo2();
    }

private:
    virtual int foo2 () = 0;
};

class Derived: public ProxyBase1, public ProxyBase2 {
private:
    int foo1() override {
        return 1;
    }
    int foo2() override {
        return 2;
    }
};



int main() {
    Derived *derived = new Derived{};
    Base1* base1 = derived;
    assert(base1->foo() == 1);
    Base2* base2 = derived;
    assert(base2->foo() == 2);
    delete derived;
    return 0;
}
