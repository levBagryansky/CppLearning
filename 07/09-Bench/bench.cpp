#include <cmath>
#include <exception>
#include <benchmark/benchmark.h>

struct Base {
    virtual int foo() = 0;
    virtual ~Base() = default;
};

struct Derived1 final : public Base{
    int foo() override {
        return 123;
    }
};

struct Derived2 final : public Base{
    int foo() override {
        return 321;
    }
};

Base* supplierBase() {
    srand((unsigned)time(0));
    if (rand() % 2)
        return new Derived1();
    return new Derived2();
}

template<typename T> struct Supplier{
    T* operator()() {
        return new T();
    }
};

template<> struct Supplier<Base> {
    Base* operator()() {
        return supplierBase();
    }
};

template<typename T>
void test(benchmark::State & state)
{
    T *inst = Supplier<T>()();
    for (auto _ : state)
    {
        auto result = inst->foo();
        benchmark::DoNotOptimize(result);
    }
    delete inst;
}

BENCHMARK(test<Derived1>);
BENCHMARK(test<Base>);

BENCHMARK_MAIN();
