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
    StaticListFromVariadicTemplate<int, 4, 5, 5, 2, 3, 0, 1, 6>::type a;
    Range<int, 0, 10>::type b;

    std::cout << CartesianProduct<decltype(a), decltype(b), decltype(&mul<int>), mul<int>>::type{};

    return 0;
}
