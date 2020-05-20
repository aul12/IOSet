/**
 * @file generator.hpp
 * @author paul
 * @date 20.05.20
 * Description here TODO
 */
#ifndef IOSET_GENERATOR_HPP
#define IOSET_GENERATOR_HPP

template<typename T, T t0, T ... ts>
struct StaticListFromVariadicTemplate {
    using type = StaticList<T, t0, typename StaticListFromVariadicTemplate<T, ts...>::type>;
};

template<typename T, T t0>
struct StaticListFromVariadicTemplate<T, t0> {
    using type = StaticList<T, t0, ListEnd>;
};

template<typename T, T offset, T step, std::size_t num>
struct RangeImpl {
    using type = typename Prepend<
                    T,
                    typename RangeImpl<T, offset + step, step, num - 1>::type,
                    offset
                >::type;
};

template<typename T, T offset, T step>
struct RangeImpl<T, offset, step, 0> {
    using type = ListEnd;
};

template<typename T, T min, T max, T step = 1>
struct Range {
    using type = typename RangeImpl<T, min, step, (max-min)/step>::type;
};


#endif //IOSET_GENERATOR_HPP
