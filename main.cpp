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

constexpr auto dub(int a) -> int {
    return a*2;
}

int main() {
    /*StaticListFromVariadicTemplate<int, 4, 5, 5, 2, 3, 0, 1, 6>::type a;
    Range<int, 0, 10>::type b;

    std::cout << CartesianProduct<decltype(a), decltype(b), decltype(&mul<int>), mul<int>>::type{};*/

    IOListBase<Range<int, 0, 10>::type> iol{-1};
    std::cout << iol.unaryOp<decltype(&dub), dub>();

    return 0;
}
