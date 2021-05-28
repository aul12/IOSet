/**
 * @file operators.hpp
 * @author paul
 * @date 28.05.21
 * Description here TODO
 */
#ifndef IOSET_OPERATORS_HPP
#define IOSET_OPERATORS_HPP

#include "ioset.hpp"

template<IOListBaseInst A, IOListBaseInst B>
auto operator*(A a, B b) {
    auto mul = [](auto a, auto b) { return a * b; };
    return a.template binaryOp<typename decltype(b)::list, decltype(mul), mul>(b);
}

template<IOListBaseInst A, IOListBaseInst B>
auto operator+(A a, B b) {
    auto add = [](auto a, auto b) { return a + b; };
    return a.template binaryOp<typename decltype(b)::list, decltype(add), add>(b);
}

#endif // IOSET_OPERATORS_HPP
