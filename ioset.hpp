/**
 * @file ioset.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_IOSET_HPP
#define IOSET_IOSET_HPP

#include "staticlist.hpp"

template<typename T, typename List, T b, typename F, F f>
struct ApplyOpVec {
    using type = typename Prepend<T,
            typename ApplyOpVec<T, typename List::next, b, F, f>::type, f(List::elem, b)>::type;
};

template<typename T, T b, typename F, F f>
struct ApplyOpVec<T, ListEnd, b, F, f> {
    using type = ListEnd;
};

template<typename List1, typename List2, typename F, F f>
struct CartesianProduct {
    using type = typename Concat<typename ApplyOpVec<typename List1::type, List2, List1::elem, F, f>::type,
            typename CartesianProduct<typename List1::next, List2, F, f>::type>::type;
};

template<typename List2, typename F, F f>
struct CartesianProduct<ListEnd, List2, F, f> {
    using type = ListEnd;
};

#endif //IOSET_IOSET_HPP
