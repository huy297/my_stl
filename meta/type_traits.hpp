// is void

#ifndef _TYPE_TRAITS_
#define _TYPE_TRAITS_

#include <cstddef>


template<typename T, T v>
struct _integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = _intergal_constant;

    constexpr operator value_type() const noexcept { return value; };
};

using _true_type  = _integral_constant<bool, true>;
using _false_type = _integral_constant<bool, false>;

template<bool B, typename T, typename F>
struct _conditional {using type = T; };

template<typename T, typename F>
struct _conditional<false, T, F> { using type = F; };

template<typename T>
struct _is_void {
    static constexpr bool value = false;
};

template<>
struct _is_void<void> {
    static constexpr bool value = true;
};

// ------------------

template<typename T>
struct _is_null_pointer {
    static constexpr bool value = false;
};

template<>
struct _is_void<std::nullptr_t> {
    static constexpr bool value = true;
};

// ------------------

template<typename T>
struct _is_intergral {
    static constexpr bool value = false;
};

template<typename T>
struct _is_integral {
    static constexpr bool value = false;
};

template<> struct _is_integral<bool>               { static constexpr bool value = true; };
template<> struct _is_integral<char>               { static constexpr bool value = true; };
template<> struct _is_integral<signed char>        { static constexpr bool value = true; };
template<> struct _is_integral<unsigned char>      { static constexpr bool value = true; };
template<> struct _is_integral<wchar_t>            { static constexpr bool value = true; };
template<> struct _is_integral<char16_t>           { static constexpr bool value = true; };
template<> struct _is_integral<char32_t>           { static constexpr bool value = true; };
template<> struct _is_integral<short>              { static constexpr bool value = true; };
template<> struct _is_integral<unsigned short>     { static constexpr bool value = true; };
template<> struct _is_integral<int>                { static constexpr bool value = true; };
template<> struct _is_integral<unsigned int>       { static constexpr bool value = true; };
template<> struct _is_integral<long>               { static constexpr bool value = true; };
template<> struct _is_integral<unsigned long>      { static constexpr bool value = true; };
template<> struct _is_integral<long long>          { static constexpr bool value = true; };
template<> struct _is_integral<unsigned long long> { static constexpr bool value = true; };

// ------------------


// remove rf
template<typename T> struct _remove_reference { using type = T; };
template<typename T> struct _remove_reference<T&> { using type = T; };
template<typename T> struct _remove_reference<T&&> { using type = T; };

template<typename T>
using _remove_reference_t = typename _remove_reference<T>::type;

// remove cv
template<typename T> struct _remove_const          { using type = T; };
template<typename T> struct _remove_const<const T>  { using type = T; };
template<typename T> struct _remove_volatile        { using type = T; };
template<typename T> struct _remove_volatile<volatile T> { using type = T; };

template<typename T>
struct _remove_cv {
    using type = typename _remove_volatile<typename _remove_const<T>::type>::type;
};

// add pointer
template<typename T> struct _add_pointer { using type = T*; };

// is_array
template<typename T> struct _is_array : _false_type {};
template<typename T> struct _is_array<T[]> : _true_type{ };
template<typename T, size_t N> struct _is_array<T[N]> : _true_type {}; 

// remove_extent

template<typename T> struct _remove_extent {using type = T; };
template<typename T> struct _remove_extent<T[]> {using type = T; };
template<typename T, size_t N> struct _remove_extent<T[N]> {using type = T; };

// is function
template<typename T> struct _is_function : _false_type {};
template<typename Ret, typename... Args>
struct _is_function<Ret(Args...)> : _true_type {};

// decay

template<typename T>
struct _decay {
private:
    using U = typename _remove_reference<T>::type;
public:
    using type = typename _conditional<
        _is_array<U>::value,
        typename _remove_extent<U>::type*,
        typename _conditional<
            _is_function<U>::value,
            typename _add_pointer<U>::type,
            typename _remove_cv<U>::type
        >::type
    >::type;
};

template<typename T>
using _decay_t = typename _decay<T>::type;


template<typename T, typename F>
struct _is_same : _false_type {};

template<typename T>
struct _is_same<T, T> : _true_type {};


static_assert(_is_same<_decay_t<int>, int>::value);
static_assert(_is_same<_decay_t<const int&>, int>::value);
static_assert(_is_same<_decay_t<int[5]>, int*>::value);
static_assert(_is_same<_decay_t<void(int)>, void(*)(int)>::value);





#endif