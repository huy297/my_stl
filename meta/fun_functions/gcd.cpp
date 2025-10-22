template<int A, int B>
struct gcd {
    static constexpr int value = gcd<B, A % B>::value;
};

template<int A>
struct gcd<A, 0> {
    static constexpr int value = A;
};

static_assert(gcd<30, 18>::value == 6);

