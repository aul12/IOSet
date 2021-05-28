#include <iostream>

#include "generator.hpp"
#include "operators.hpp"

using Test = Enumerated<int, 0, 13>;

auto works(Range<int, 0, 3>) {}

auto doesNotWork(Range<int, 1, 3>) {}

int main() {
    Range<int, 0, 10> a{1};
    Constant<int, 0> b{0};

    auto prod = a * b;

    works(prod);

    doesNotWork(prod);

    return 0;
}
