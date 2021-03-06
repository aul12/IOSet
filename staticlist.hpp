/**
 * @file staticlist.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_STATICLIST_HPP
#define IOSET_STATICLIST_HPP

template<typename T, T elem_, typename next_>
struct StaticList {
    using type = T;
    using next = next_;
    static constexpr auto elem = elem_;
};

struct ListEnd {};

// List concepts
template<typename T>
struct IsList {
    static constexpr bool val = false;
};

template<typename T, T elem, typename next>
struct IsList<StaticList<T, elem, next>> {
    static constexpr bool val = true;
};

template<>
struct IsList<ListEnd> {
    static constexpr bool val = true;
};

template<typename T>
concept static_list = IsList<T>::val;

// List of Type concepts
template<typename T, static_list List>
struct IsListOfType {
    static constexpr bool val = std::is_same<T, typename List::type>::value;
};

template<typename T>
struct IsListOfType<T, ListEnd> {
    static constexpr bool val = true;
};

template<typename T, typename List>
concept list_of_type = IsListOfType<T, List>::val;

template<typename List>
concept list_end = std::is_same<List, ListEnd>::value;

// List of same type concepts
template<static_list L1, static_list L2>
struct ListOfSameType {
    static constexpr bool val = std::is_same<typename L1::type, typename L2::type>::value;
};

template<static_list L>
struct ListOfSameType<ListEnd, L> {
    static constexpr bool val = true;
};

template<static_list L>
struct ListOfSameType<L, ListEnd> {
    static constexpr bool val = true;
};
template<>
struct ListOfSameType<ListEnd, ListEnd> {
    static constexpr bool val = true;
};

template<typename T1, typename T2>
concept same_list_type = ListOfSameType<T1, T2>::val;


// List helper functions
template<typename T, static_list List, T toAdd> requires list_of_type<T, List>
struct Prepend {
    using type = StaticList<T, toAdd, List>;
};

template<static_list List1, static_list List2> requires same_list_type<List1, List2>
struct Concat {
    using type = typename Prepend<
                    typename List1::type,
                    typename Concat<
                        typename List1::next, List2
                    >::type,
                    List1::elem
                >::type;
};

template<static_list List2>
struct Concat<ListEnd, List2> {
    using type = List2;
};

template<static_list List>
struct Size {
    static constexpr std::size_t val = Size<typename List::next>::val + 1;
};

template<>
struct Size<ListEnd> {
    static constexpr std::size_t val = 0;
};

template<typename T, static_list List, T t> requires list_of_type<T, List>
struct Contains {
    static constexpr bool val = (List::elem == t || Contains<T, typename List::next, t>::val);
};

template<typename T, T t>
struct Contains<T, ListEnd, t> {
    static constexpr bool val = false;
};


#endif //IOSET_STATICLIST_HPP
