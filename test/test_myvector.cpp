#include <iostream>
#include <cassert>
#include "../include/vector.hpp"   // adjust path if needed

int main() {
    _Vector<int> v;

    // --- Basic state checks ---
    assert(v.empty());
    assert(v.size() == 0);

    // --- push_back & operator[] ---
    //std::cerr << " push back " << v.capacity() << std::endl;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);

    // --- front() & back() ---
    assert(v.front() == 1);
    assert(v.back() == 3);

    // --- pop_back() ---
    v.pop_back();
    assert(v.size() == 2);
    assert(v.back() == 2);

    // --- insert() test ---
    v.insert(v.begin() + 1, 42);
    assert(v.size() == 3);
    assert(v[0] == 1);
    assert(v[1] == 42);
    assert(v[2] == 2);

    // --- erase() test ---
    v.erase(v.begin() + 1);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    // --- clear() test ---
    v.clear();
    assert(v.size() == 0);
    assert(v.empty());

    // --- push_back after clear ---
    v.push_back(10);
    assert(v.size() == 1);
    assert(v[0] == 10);

    // --- copy constructor ---
    _Vector<int> v2(v);
    assert(v2.size() == 1);
    assert(v2[0] == 10);

    // --- assignment operator ---
    _Vector<int> v3;
    v3 = v2;
    assert(v3.size() == 1);
    assert(v3[0] == 10);

    // --- move constructor ---
    _Vector<int> v4(std::move(v3));
    assert(v4.size() == 1);
    assert(v4[0] == 10);

    // --- move assignment ---
    _Vector<int> v5;
    v5 = std::move(v4);
    assert(v5.size() == 1);
    assert(v5[0] == 10);

    // --- stress push_back to trigger reallocation ---
    _Vector<int> big;
    for (int i = 0; i < 1000; ++i)
        big.push_back(i);
    assert(big.size() == 1000);
    for (int i = 0; i < 1000; ++i)
        assert(big[i] == i);

    std::cout << "All _Vector tests passed!\n";
}
