#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <iostream>

template<typename T, std::size_t N>
class _Array {
private:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using iterator = pointer;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
public:

    // storage
    value_type _M_elements[N ? N : 1];

    // for iterator

    iterator begin() noexcept {
        return _M_elements;
    }

    const_iterator begin() const noexcept {
        return _M_elements;
    }

    iterator end() noexcept {
        return _M_elements + N;
    }

    const_iterator end() const noexcept {
        return _M_elements + N;
    }

    // for reverse iterator

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    // for capacity

    constexpr size_type size() const noexcept {
        return N;
    }

    constexpr size_type max_size() const noexcept {
        return N;
    }

    constexpr bool empty() const noexcept {
        return N == 0;
    }
    
    // element access

    reference operator[](size_type n) noexcept {
        return _M_elements[n];
    }

    const_reference operator[](size_type n) const noexcept {
        return _M_elements[n];
    }

    reference at(size_type n) {
        if (n >= N) {
            throw std::out_of_range("_Array::at");
        }
        return _M_elements[n];
    }

    const_reference at(size_type n) const {
        if (n >= N) {
            throw std::out_of_range("_Array::at");
        }
        return _M_elements[n];
    }

    reference front() noexcept {
        return _M_elements[0];
    }

    const_reference front() const noexcept {
        return _M_elements[0];
    }

    reference back() noexcept {
        return _M_elements[N - 1];
    }

    const_reference back() const noexcept {
        return _M_elements[N - 1];
    }

    pointer data() noexcept {
        return _M_elements;
    }

    const_pointer data() const noexcept {
        return _M_elements;
    }

    // modify

    void fill(const value_type& value) {
        std::fill_n(begin(), size(), value);
    }

    void swap(_Array &other) {
        std::swap_ranges(begin(), end(), other.begin());
    }

};


// ======================================================
// ✅ Test driver
// ======================================================
int main() {
    _Array<int, 5> arr1;
    arr1.fill(10);

    std::cout << "After fill(10): ";
    for (auto x : arr1) std::cout << x << " ";
    std::cout << "\n";

    arr1[2] = 99;
    std::cout << "arr1[2] = " << arr1[2] << "\n";

    std::cout << "Front = " << arr1.front()
              << ", Back = " << arr1.back()
              << ", Size = " << arr1.size()
              << ", Empty = " << std::boolalpha << arr1.empty() << "\n";

    try {
        arr1.at(10);  // should throw
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception from at(): " << e.what() << "\n";
    }

    _Array<int, 5> arr2;
    arr2.fill(3);
    arr1.swap(arr2);

    std::cout << "After swap: arr1 = ";
    for (auto x : arr1) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Reverse iteration (arr1): ";
    for (auto it = arr1.rbegin(); it != arr1.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Data pointer = " << static_cast<void*>(arr1.data()) << "\n";
}
