/**
 * @file ioset.hpp
 * @author paul
 * @date 18.05.20
 * Description here TODO
 */
#ifndef IOSET_IOSET_HPP
#define IOSET_IOSET_HPP

#include "op.hpp"
#include "util.hpp"

template<static_list List>
class IOListBase {
  public:
    using list = List;
    using type = typename List::type;

    // Only required runtime check prefer literals
    explicit IOListBase(type t) : val{t} {
        if (!DynamicContains<type, List>::check(t)) {
            throw std::runtime_error{"Invalid Input for IOSet"};
        }
    }

    // Immutable
    template<typename T>
    IOListBase &operator=(T) = delete;

    // Universal unary op
    template<typename F, F f>
    requires unary_op<F, type>
    auto unaryOp() const {
        return IOListBase<typename ApplyUnaryOp<List, F, f>::type>{f(val)};
    }

    // Universal binary op
    template<static_list ListRhs, typename F, F f>
    requires binary_op<F, type> && same_list_type<List, ListRhs>
    auto binaryOp(IOListBase<ListRhs> rhs) const {
        return IOListBase<typename CartesianProduct<List, ListRhs, F, f>::type>{f(val, static_cast<type>(rhs))};
    }

    // Get underlying value
    explicit operator type() const {
        return val;
    }

    template<static_list otherList>
    explicit(not IsSubset<list, otherList>::val) operator IOListBase<otherList>() const {
        return IOListBase<otherList>(val);
    }

  protected:
    type val;
};

template<typename T>
struct IsIOListBase {
    static constexpr auto val = false;
};

template<static_list list>
struct IsIOListBase<IOListBase<list>> {
    static constexpr auto val = true;
};


template<typename T>
concept IOListBaseInst = IsIOListBase<T>::val;

#endif // IOSET_IOSET_HPP
