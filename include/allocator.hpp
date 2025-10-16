#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_

#include <iostream>
#include <new>       // for std::bad_alloc
#include <cstddef>   // for std::size_t
#include <vector>

template<typename T>
class _Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;


    _Allocator() noexcept{}

    template<class U> _Allocator(const _Allocator<U>&) noexcept{}

    pointer allocate(std::size_t n) {

        if (n > std::size_t(-1) / sizeof(T)) {
            throw std::bad_alloc();
        }

        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, std::size_t) noexcept {
        ::operator delete(p);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

    template<typename U, class... Args>
    void construct(U* p, Args&&... args) {
        ::new((void*)p) U(std::forward<Args>(args)...);
    } 

};

template<class T, class U>
bool operator==(const _Allocator<T>&, const _Allocator<U>&) {
    return true;
}

template<class T, class U>
bool operator!=(const _Allocator<T>&, const _Allocator<U>&) {
    return false;
}


#endif // _ALLOCATOR_HPP
