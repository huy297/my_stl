#include <cstddef>
#include <iostream>

template<int D, typename T>
struct Vec : public std::vector<Vec<D - 1, T>> {

    template<typename... Args>
    Vec(int n = 0, Args... args) : std::vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};

template<typename T>
struct Vec<1, T> : public std::vector<T> {
    
    Vec(int n = 0, const T& val = T()) : std::vector<T>(n, val) {}
};


template<typename T, size_t N, size_t... Dims> 
struct nvec : public std::vector<nvec<T, Dims...>> {
    nvec() : std::vector<nvec<T, Dims...>>(N) {}

    nvec(T value) : std::vector<nvec<T, Dims...>>(N, nvec<T, Dims...>(value)) {}
};

template<typename T, size_t N>
struct nvec<T, N>: public std::vector<T> {
    nvec() : std::vector<T>(N) {}

    nvec(T value) : std::vector<T>(N, value) {}
};

int main() {
    Vec<3, int> v(4, 3, 2, 5);

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         for (int k = 0; k < 2; k++) {
    //             std::cout << v[i][j][k] << std::endl;
    //         }
    //     }
    // }

    nvec<int, 4, 3, 2> vec(5);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 2; k++) {
                std::cout << vec[i][j][k] << std::endl;
            }
        }
    }
}