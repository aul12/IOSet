/**
 * @file generator.hpp
 * @author paul
 * @date 20.05.20
 * Description here TODO
 */
#ifndef IOSET_GENERATOR_HPP
#define IOSET_GENERATOR_HPP

#include "ioset.hpp"

template<typename T, T t0, T ... ts>
struct StaticListFromVariadicTemplate {
    using type = typename Sort<StaticList<T, t0, typename StaticListFromVariadicTemplate<T, ts...>::type>>::type;
};

template<typename T, T t0>
struct StaticListFromVariadicTemplate<T, t0> {
    using type = StaticList<T, t0, ListEnd>;
};

template<typename T, T ... ts>
using Enumerated = IOListBase<typename StaticListFromVariadicTemplate<T, ts...>::type>;

template<typename T, T offset, T step, std::size_t num>
struct RangeSetImpl {
    using type = typename Prepend<
                    T,
                    typename RangeSetImpl<T, offset + step, step, num - 1>::type,
                    offset
                >::type;
};

template<typename T, T offset, T step>
struct RangeSetImpl<T, offset, step, 0> {
    using type = ListEnd;
};

template<typename T, T min, T max, T step = 1>
struct RangeSet {
    using type = typename RangeSetImpl<T, min, step, (max-min)/step>::type;
};

template<typename T, T min, T max, T step = 1>
using Range = IOListBase<typename RangeSet<T, min, max, step>::type>;

template<typename T, T val>
using Constant = Enumerated<T, val>;

#endif //IOSET_GENERATOR_HPP
