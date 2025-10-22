#include <cstddef>
template<typename T>
struct Rank {
    static constexpr size_t value = 0;
};

template<typename T>
struct Rank<T[]> {
    static constexpr size_t value = 1 + Rank<T>::value;
};

template<typename T, size_t N> 
struct Rank<T[N]> {
    static constexpr size_t value = 1 + Rank<T>::value;
};

static_assert(Rank<int>::value == 0);

static_assert(Rank<int[5]>::value == 1);

static_assert(Rank<int[]>::value == 1);

static_assert(Rank<int[10][10]>::value == 2);

static_assert(Rank<int[][10]>::value == 2);


