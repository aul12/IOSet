/**
 * @file op.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_OP_HPP
#define IOSET_OP_HPP

#include "staticlist.hpp"

// Concepts for operations
template<typename F, typename T>
concept unary_op = std::is_invocable<F, T>::value;

template<typename F, typename T>
concept binary_op = std::is_invocable<F, T, T>::value;

// Transform a set with a unary operation
template<static_list List, typename F, F f> requires unary_op<F, typename List::type>
struct ApplyUnaryOp {
    using type = typename Prepend<
                    typename List::type,
                    typename ApplyUnaryOp<typename List::next, F, f>::type
                    , f(List::elem)
                 >::type;
};

template<typename F, F f>
struct ApplyUnaryOp<ListEnd, F, f> {
    using type = ListEnd;
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
struct CartesianProduct {
    using type = typename Concat<
                    typename ApplyBinaryOpVec<typename List1::type, List2, List1::elem, F, f>::type,
                    typename CartesianProduct<typename List1::next, List2, F, f>::type
                >::type;
};

template<static_list List2, typename F, F f>
struct CartesianProduct<ListEnd, List2, F, f> {
    using type = ListEnd;
};


#endif //IOSET_OP_HPP
