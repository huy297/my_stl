// is void

#ifndef _TYPE_TRAITS_
#define _TYPE_TRAITS_

#include <cstddef>
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


#endif