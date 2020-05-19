#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    StaticListFromVariadicTemplate<int, 1, 2, 3>::type a;


    std::cout << RemoveItemAtIndex<decltype(a), 2>::type{};

    return 0;
}
