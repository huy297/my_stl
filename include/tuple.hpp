#include <cstddef>

#include "../meta/type_traits.hpp"

template<size_t I, typename T>
struct tuple_leaf {
    T value;

    tuple_leaf() = default;

    tuple_leaf(const T& v) : value(v) {}
};

template<size_t I, typename... Ts>
struct tuple_impl;

template<size_t I>
struct tuple_impl<I> {};



template<size_t I, typename Head, typename... Tail>
struct tuple_impl<I, Head, Tail...>
    : tuple_leaf<I, Head>, tuple_impl<I + 1, Tail...> {
        tuple_impl() = default;

        tuple_impl(const Head& h, const Tail&... t) 
            : tuple_leaf<I, Head>(h), tuple_impl<I + 1, Tail...>(t) {}
};


template<typename... TS>
struct _Tuple
    : tuple_impl<0, TS> {
    using base = tuple_imple<0, TS>
    using base::base;
};

template<typename... Ts>
_Tuple<_decay_t<Ts>...> make_tuple(Ts&&... args) {
    return _Tuple<_decay_t<Ts>...>(std::forward<Ts>(args)...);
}



_Tuple<int, int, int> t;