#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    StaticList<int, 1, StaticList<int, 2, StaticList<int, 3, ListEnd>>> a;
    StaticList<int, 1, StaticList<int, 2, ListEnd>> b;

    using CartesianProductT = CartesianProduct<decltype(a), decltype(b), decltype(&add<int>), add<int>>::type;

    std::cout << RemoveDuplicates<CartesianProductT>::type{};

    return 0;
}
