/**
 * @file util.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_UTIL_HPP
#define IOSET_UTIL_HPP

#include "staticlist.hpp"
#include "sort.hpp"

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
    using type = typename PrependIfNecessary<
                    !Contains<typename List::type, typename List::next, List::elem>::val,
                    typename List::type,
                    typename RemoveDuplicates<typename List::next>::type,
                    List::elem
                 >::type;
};

template<>
struct RemoveDuplicates<ListEnd> {
    using type = ListEnd;
};


template<static_list List>
struct NormalizeList {
    using type = typename Sort<typename RemoveDuplicates<List>::type>::type;
};

template<typename T, static_list List> requires list_of_type<T, List>
struct DynamicContains {
    constexpr static auto check(typename List::type t) {
        return t == List::elem || DynamicContains<T, typename List::next>::check(t);
    }
};

template<typename T>
struct DynamicContains<T, ListEnd> {
    constexpr static auto check(T) {
        return false;
    }
};

#endif //IOSET_UTIL_HPP
