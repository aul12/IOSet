/**
 * @file ioset.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_IOSET_HPP
#define IOSET_IOSET_HPP

#include "staticlist.hpp"
#include "op.hpp"

template<typename T, typename List, T t>
struct Contains {
    static constexpr bool val = (List::elem == t || Contains<T, typename List::next, t>::val);
};

template<typename T, T t>
struct Contains<T, ListEnd, t> {
    static constexpr bool val = false;
};

template<bool isNecessary, typename T, typename List, T toAdd>
struct PrependIfNecessary {
    using type = typename Prepend<T, List, toAdd>::type;
};

template<typename T, typename List, T toAdd>
struct PrependIfNecessary<false, T, List, toAdd> {
    using type = List;
};


template<typename List>
struct RemoveDuplicates {
    using type = typename PrependIfNecessary<!Contains<typename List::type, typename List::next, List::elem>::val,
                    typename List::type, typename RemoveDuplicates<typename List::next>::type, List::elem>::type;
};

template<>
struct RemoveDuplicates<ListEnd> {
    using type = ListEnd;
};

#endif //IOSET_IOSET_HPP
