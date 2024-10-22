#pragma once

using uint = unsigned int;

template<uint Index>
struct Fibonacci {
    constexpr static uint value = Fibonacci<Index - 1>::value + Fibonacci<Index - 2>::value;
};

template<>
struct Fibonacci<0> {
    constexpr static uint value = 0;
};

template<>
struct Fibonacci<1> {
    constexpr static uint value = 1;
};

template<uint value>
struct IntegralConstant{
    enum Enum {value_enum = value};
    uint operator()() {return value;}
};

template<uint i>
struct Fibo: IntegralConstant<Fibo<i-1>::Enum::value_enum + Fibo<i-2>::Enum::value_enum> {};

template<> struct Fibo<0>: IntegralConstant<0> {};
template<> struct Fibo<1>: IntegralConstant<1> {};
