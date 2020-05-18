#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    StaticListFromVariadicTemplate<int, 1, 2, 3>::type a;
    StaticListFromVariadicTemplate<int, 1, 2>::type b;

    using CartesianProductT = CartesianProduct<decltype(a), decltype(b), decltype(&add<int>), add<int>>::type;

    std::cout << RemoveDuplicates<CartesianProductT>::type{};

    return 0;
}
