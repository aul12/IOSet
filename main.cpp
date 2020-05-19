#include <iostream>

#include "ioset.hpp"

template<typename T>
constexpr auto add(T a, T b) -> T {
    return a + b;
}

int main() {
    StaticListFromVariadicTemplate<int, 3, 2, 1>::type a;


    std::cout << Min<decltype(a)>::val << std::endl;
    std::cout << Min<decltype(a)>::index << std::endl;

    return 0;
}
