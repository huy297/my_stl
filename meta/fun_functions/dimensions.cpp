#include <cstddef>
#include <vector>

template<typename T>
struct vdim {
    static constexpr size_t value = 0;
};

template<typename T>
struct vdim<std::vector<T>> {
    static constexpr size_t value = 1 + vdim<T>::value; 
};

static_assert(vdim<int>::value == 0);

static_assert(vdim<std::vector<int>>::value == 1);


static_assert(vdim<std::vector<std::vector<int>>>::value == 2);
