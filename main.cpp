#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    StaticListFromVariadicTemplate<int, 4, 5, 5, 2, 3, 0, 1, 6>::type a;

    std::cout << NormalizeList<decltype(a)>::type{};

    return 0;
}
