/**
 * @file op.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_OP_HPP
#define IOSET_OP_HPP

#include "staticlist.hpp"
#include "util.hpp"

// Concepts for operations
template<typename F, typename T>
concept unary_op = std::is_invocable<F, T>::value;

template<typename F, typename T>
concept binary_op = std::is_invocable<F, T, T>::value;

// Transform a set with a unary operation
template<static_list List, typename F, F f> requires unary_op<F, typename List::type>
struct AppleUnaryOpImpl {
    using type = typename Prepend<
                    typename List::type,
                    typename AppleUnaryOpImpl<typename List::next, F, f>::type
                    , f(List::elem)
                 >::type;
};

template<typename F, F f>
struct AppleUnaryOpImpl<ListEnd, F, f> {
    using type = ListEnd;
};

template<static_list List, typename F, F f> requires unary_op<F, typename List::type>
struct AppleUnaryOp {
    using type = typename NormalizeList<typename AppleUnaryOpImpl<List, F, f>::type>::type;
};

// Helper function: Apply a binary operation with one fixed operand
template<typename T, static_list List, T b, typename F, F f> requires list_of_type<T, List> && binary_op<F, T>
struct ApplyBinaryOpVec {
    using type = typename Prepend<
                    T,
                    typename ApplyBinaryOpVec<T, typename List::next, b, F, f>::type,
                    f(List::elem, b)
                >::type;
};

template<typename T, T b, typename F, F f>
struct ApplyBinaryOpVec<T, ListEnd, b, F, f> {
    using type = ListEnd;
};

// Calculate the cartesian product of a set over a given operation
template<static_list List1, static_list List2, typename F, F f> requires same_list_type<List1, List2> &&
                                                                         binary_op<F, typename List2::type>
struct CartesianProductImpl {
    using type = typename Concat<
                    typename ApplyBinaryOpVec<typename List1::type, List2, List1::elem, F, f>::type,
                    typename CartesianProductImpl<typename List1::next, List2, F, f>::type
                >::type;
};

template<static_list List2, typename F, F f>
struct CartesianProductImpl<ListEnd, List2, F, f> {
    using type = ListEnd;
};

template<static_list List1, static_list List2, typename F, F f> requires same_list_type<List1, List2> &&
                                                                         binary_op<F, typename List2::type>
struct CartesianProduct {
    using type = typename NormalizeList<typename CartesianProductImpl<List1, List2, F, f>::type>::type;
};

#endif //IOSEtypename T_OP_HPP
