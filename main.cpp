#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

template<typename T>
constexpr auto mul(T a, T b) -> T {
    return a * b;
}


int main() {
    IOListBase<Range<int, 0, 10>::type> a{-1};
    IOListBase<Range<int, 0, 20>::type> b{2};

    std::cout << a.binaryOp<decltype(b)::list, decltype(&mul<int>), mul>(b);

    return 0;
}
