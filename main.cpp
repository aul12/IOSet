#include <iostream>

#include "ioset.hpp"

int main() {
    StaticList<int, 1, ListEnd> i;
    StaticList<int, 2, ListEnd> j;
    std::cout << Add<int, decltype(i), 2>::type{} << std::endl;
    std::cout << Concat<decltype(i), decltype(j)>::type{} << std::endl;

    StaticList<int, 1, StaticList<int, 2, StaticList<int, 3, ListEnd>>> a;
    StaticList<int, 4, StaticList<int, 5, StaticList<int, 6, ListEnd>>> b;
    std::cout << Concat<decltype(a), decltype(b)>::type{} << std::endl;
    return 0;
}
