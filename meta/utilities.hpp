#include "./type_traits.hpp"
#include "iostream"

// forward

template<typename T>
constexpr T&& _forward(_remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& _forward(_remove_reference_t<T>&& t) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value,
                  "_forward must not forward an rvalue as an lvalue");
    return static_cast<T&&>(t);

};

// move

template<typename T>
constexpr _remove_reference_t<T>&& _move(T&& t) noexcept {
    return static_cast<_remove_reference_t<T>&&>(t);
};

// swap

template<typename T>
void _swap(T& a, T& b) noexcept {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

// make pair
template<typename T, typename F>
std::pair<T, F> _make_pair(T t, F f) {
    return std::pair(t, f);
}

template<typename T, typename F>
std::pair<T, F> _make_pair(T&& t, F&& f) {
    return std::pair(t, f);
}