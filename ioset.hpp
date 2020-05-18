/**
 * @file ioset.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_IOSET_HPP
#define IOSET_IOSET_HPP

template <typename T,  T elem_, typename next_>
struct StaticList {
    using type = T;
    using next = next_;
    static constexpr auto elem = elem_;
};

struct ListEnd {};

template<typename T, typename List, T toAdd> // Todo check that List is StaticList and T==List::type
struct Add {
    using type = StaticList<T, toAdd, List>;
};

template<typename List1, typename List2> // TODO Check that Lists have same type and are lists
struct Concat {
    using type = typename Add<typename List1::type, typename Concat<typename List1::next, List2>::type, List1::elem>::type;
};

template<typename List2>
struct Concat<ListEnd, List2> {
    using type = List2;
};



#endif //IOSET_IOSET_HPP
