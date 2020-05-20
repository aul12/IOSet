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
    using type = typename Prepend<
                    typename List::type,
                    typename RemoveItemAtIndexImpl<
                        typename List::next,
                        index - 1,
                        NextExists<typename List::next::next>::val
                    >::type,
                    List::elem
                 >::type;
};

template<static_list List, bool nextExists>
struct RemoveItemAtIndexImpl<List, 0, nextExists> {
    using type = typename Prepend<
                    typename List::type,
                    typename List::next::next,
                    List::next::elem
                 >::type;
};

template<static_list List>
struct RemoveItemAtIndexImpl<List, 0, false> {
    using type = ListEnd;
};

template<static_list List, std::size_t index>
struct RemoveItemAtIndex {
    static_assert(index < Size<List>::val, "Remove out of bounds!");
    using type = typename RemoveItemAtIndexImpl<
                    List,
                    index,
                    NextExists<typename List::next>::val
                >::type;
};

template<static_list List, bool nextExists>
struct MinImpl {
    static constexpr auto val =
            List::elem < MinImpl<typename List::next, NextExists<typename List::next::next>::val>::val ?
                List::elem
            :
                MinImpl<
                        typename List::next,
                        NextExists<typename List::next::next>::val
                >::val;
    static constexpr std::size_t index =
            List::elem < MinImpl<typename List::next, NextExists<typename List::next::next>::val>::val ?
                0
            :
                MinImpl<
                    typename List::next,
                    NextExists<typename List::next::next>::val
                >::index + 1;
};

template<static_list List>
struct MinImpl<List, false> {
    static constexpr auto val = List::elem;
    static constexpr std::size_t index = 0;
};


template<static_list List>
struct Min {
    static constexpr auto val = MinImpl<List, NextExists<typename List::next>::val>::val;
    static constexpr std::size_t index = MinImpl<List, NextExists<typename List::next>::val>::index;
};


template<static_list List>
struct Sort {
    using type = typename Prepend<
                    typename List::type,
                    typename Sort<
                        typename RemoveItemAtIndex<
                                List, Min<List>::index
                        >::type
                    >::type,
                    Min<List>::val
                >::type;
};

template<>
struct Sort<ListEnd> {
    using type = ListEnd;
};

#endif //IOSET_SORT_HPP
