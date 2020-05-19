/**
 * @file sort.hpp
 * @author paul
 * @date 19.05.20
 * Description here TODO
 */
#ifndef IOSET_SORT_HPP
#define IOSET_SORT_HPP

#include "staticlist.hpp"
#include "util.hpp"

template<static_list List>
struct NextExists {
    static constexpr auto val = true;
};

template<>
struct NextExists<ListEnd> {
    static constexpr auto val = false;
};

template<static_list List, std::size_t index, bool nextExists>
struct RemoveItemAtIndexImpl {
    using type = typename Prepend<typename List::type, typename RemoveItemAtIndexImpl<typename List::next,
            index - 1, NextExists<typename List::next::next>::val>::type, List::elem>::type;
};

template<static_list List, bool nextExists>
struct RemoveItemAtIndexImpl<List, 0, nextExists> {
    using type = typename Prepend<typename List::type, typename List::next::next, List::next::elem>::type;
};

template<static_list List>
struct RemoveItemAtIndexImpl<List, 0, false> {
    using type = ListEnd;
};

template<static_list List, std::size_t index>
struct RemoveItemAtIndex {
    using type = typename RemoveItemAtIndexImpl<List, index, NextExists<typename List::next>::val>::type;
};


#endif //IOSET_SORT_HPP
