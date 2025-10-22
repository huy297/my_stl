template<int N>
struct fib {
    static constexpr int value = fib<N - 1>::value + fib<N - 2>::value;
};

template<> struct fib<1> { static constexpr int value = 1; };
template<> struct fib<0> { static constexpr int value = 0; };

static_assert(fib<10>::value != 0);
