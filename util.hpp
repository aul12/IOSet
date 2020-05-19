/**
 * @file util.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_UTIL_HPP
#define IOSET_UTIL_HPP

#include "staticlist.hpp"

template<typename T, static_list List, T t> requires list_of_type<T, List>
struct Contains {
    static constexpr bool val = (List::elem == t || Contains<T, typename List::next, t>::val);
};

template<typename T, T t>
struct Contains<T, ListEnd, t> {
    static constexpr bool val = false;
};

template<bool isNecessary, typename T, static_list List, T toAdd> requires list_of_type<T, List>
struct PrependIfNecessary {
    using type = typename Prepend<T, List, toAdd>::type;
};

template<typename T, static_list List, T toAdd> requires list_of_type<T, List>
struct PrependIfNecessary<false, T, List, toAdd> {
    using type = List;
};


template<static_list List>
struct RemoveDuplicates {
    using type = typename PrependIfNecessary<!Contains<typename List::type, typename List::next, List::elem>::val,
            typename List::type, typename RemoveDuplicates<typename List::next>::type, List::elem>::type;
};

template<>
struct RemoveDuplicates<ListEnd> {
    using type = ListEnd;
};


template<typename T, T t0, T ... ts>
struct StaticListFromVariadicTemplate {
    using type = StaticList<T, t0, typename StaticListFromVariadicTemplate<T, ts...>::type>;
};

template<typename T, T t0>
struct StaticListFromVariadicTemplate<T, t0> {
    using type = StaticList<T, t0, ListEnd>;
};

#endif //IOSET_UTIL_HPP
