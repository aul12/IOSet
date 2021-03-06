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
#include "util.hpp"
#include "sort.hpp"
#include "generator.hpp"

template<static_list List>
class IOListBase {
    public:
        using list = List;
        using type = typename List::type;

        // Only required runtime check prefer literals
        explicit IOListBase(type t) : val{t} {
            if (!DynamicContains<type, List>::check(t)) {
                throw std::runtime_error{"Invalid Input"};
            }
        }

        // Immutable
        template<typename T>
        IOListBase &operator=(T) = delete;

        // Universal unary op
        template<typename F, F f> requires unary_op<F, type>
        auto unaryOp() const {
            return IOListBase<typename ApplyUnaryOp<List, F, f>::type>{f(val)};
        }

        // Universal binary op
        template<static_list ListRhs, typename F, F f> requires binary_op<F, type> && same_list_type<List, ListRhs>
        auto binaryOp(IOListBase<ListRhs> rhs) const {
            return IOListBase<typename CartesianProduct<List, ListRhs, F, f>::type>{f(val, static_cast<type>(rhs))};
        }

        // Get underlying value
        explicit operator type() const {
            return val;
        }

    protected:
        type val;
};

// @TODO literals

#endif //IOSET_IOSET_HPP
