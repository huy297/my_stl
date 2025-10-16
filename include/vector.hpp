#include <cstddef>
#include <memory>

#include "./include/allocator.hpp"

template<typename T, typename Allocator = _Allocator<T>> 
class _Vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    using pointer = T*;
    using const_pointer = const T*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    pointer data_;
    size_type size_;
    size_type cap_;
    allocator_type alloc_;

    void ensure_capacity(size_type new_cap_) {
        if (cap_ >= new_cap_) {
            return;
        }

        pointer new_data_ = alloc_.allocate(new_cap_);

        size_type i = 0;

        try {
            for (; i < size_; i++) {
                alloc_.construct(new_data_ + i, std::move_if_noexcept(data_[i]));
            }
        } 
        catch (...) {
            for (size_type j = 0; j < i; j++) {
                alloc_.destroy(new_data_ + j);
            }

            alloc_.deallocate(new_data_, new_cap_);
            throw;
        }

        for (size_type i = 0; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }

        if (data_) {
            alloc_.deallocate(data_, cap_);
        }

        cap_ = new_cap_;
        
    }

public:

    // constructor 

    _Vector() noexcept: data_(nullptr), size_(0), cap_(0) {}

    explicit _Vector(size_type n, const T& value = T()) {
        if (n > 0) {
            data_ = alloc_.allocate(n);

            for (size_type i = 0; i < n; i++) {
                data_[i] = value;
            }

            size_ = n;
            cap_ = n;
        }
    }

    // copy constructor

    _Vector(const _Vector& other) : data_(nullptr), size_(0), cap_(0) {
        if (other.size_ == 0) {
            return;
        }

        data_ = alloc_.allocate(other.size_);

        for (size_type i = 0; i < other.size_; i++) {
            alloc_.construct(data_ + i, other.data_[i]);
        }

        size_ = other.size_;
        data_ = size_;
    }

    // destructor

    ~_Vector() {
        for (size_type i = 0; i < size_;  i++) {
            alloc_.destroy(data_ + i);
        }

        if (data_) {
            alloc_.deallocate(data_, cap_)
        }
    }

    // operator

    _Vector& operator=(const _Vector& other) {
        if (this == &other) {
            return *this;
        }

        ensure_capacity(other.size_);
        
        size_type i = 0;

        for (; i < size_ && i < other.size_; i++) {
            data_[i] = other.data_[i];
        }

        for (; i < other.size_; i++) {
            alloc_.construct(data_ + i, other.data_[i]);
        } 

        for (; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }
        
        size_ = other.size_;

        return *this;
    }

    void assign(size_type count, const T& value) {
        ensure_capacity(count);

        for (size_type i = 0; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }

        for (size_type i = 0; i < count; i++) {
            alloc_.construct(data_ + i, value);
        }

        size_ = count;
    }

    void assign(size_type count, const T&& value) {
        ensure_capacity(count);

        for (size_type i = 0; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }

        for (size_type i = 0; i < count; i++) {
            alloc_.construct(data_ + i, std::move(value));
        }

        size_ = count;
    }

    allocator_type get_allocator() {
        return alloc_;
    }

    // element access

    value_type& at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[pos];
    } 

    const value_type& at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[pos];
    }

    value_type& operator[](size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[pos];
    }

    const value_type& operator[](size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[pos];
    }

    value_type& front() {
        if (size_ == 0) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[0];
    }

    const value_type& front() const {
        if (size_ == 0) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[0];
    }

    value_type& back() {
        if (size_ == 0) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[size_ - 1];
    }

    const value_type& back() const {
        if (size_ == 0) {
            throw std::out_of_range("accessing vector out of range");
        }

        return data_[size_ - 1];
    }

    pointer data() {
        return data_;
    }

    const pointer data() const {
        return data_;
    }

    // iterator

    // begin

    iterator begin() {
        return data_;
    }

    const iterator begin() const {
        return data_;
    }

    const iterator cbegin() const {
        return data_;
    }

    // end

    iterator end() {
        return data_ + size_;
    }

    const iterator end() const {
        return data_ + size_;
    }

    const iterator cend() const{
        return data_ + size_;
    }

    // rbegin

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    // rend

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }


    // capacity

    bool empty() const {
        return size_ == 0;
    }

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        // just some large

        return 100000000000;
    }

    void reserve(size_type new_cap_) {
        ensure_capacity(new_cap_);
    }

    size_type capacity() const {
        return cap_;
    }

    void shrink_to_fit() {
        pointer new_data_ = alloc_.allocate(size_);

        for (int i = 0; i < size_; i++) {
            alloc_.construct(new_data_ + i, std::move(data_[i]));
        }

        for (int i = 0; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }

        alloc_.deallocate(data_, cap_);

        cap_ = size_;
        data_ = new_data_;
    }

    // modifer
    void clear() noexcept {
        for (int i = 0; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }

        size_ = 0;
    }


    iterator insert(const_iterator pos, const T& value) {
        size_type index = pos - cbegin();

        if (size_ == cap_) {
            size_type new_cap = cap_ == 0 ? 1 : cap_ * 2;
            reserve(new_cap);
        }

        for (int i = size_; i > index; i--) {
            alloc_.construct(data_ + i, std::move(data_[i - 1]));
            alloc_.destroy(data + i - 1);
        }

        alloc_.construct(data_ + index, value);
        size_++;

        return data_ + index;
    }

    iterator insert(const_iterator pos, const T&& value) {
        size_type index = pos - cbegin();

        if (size_ == cap_) {
            size_type new_cap = cap_ == 0 ? 1 : cap_ * 2;
            reserve(new_cap);
        }

        for (size_type i = size_; i > index; i--) {
            alloc_.construct(data_ + i, std::move(data_[i - 1]));
            alloc_.destroy(data + i - 1);
        }

        alloc_.construct(data_ + index, std::move(value));
        size_++;

        return data_ + index;
    }



    iterator insert(const_iterator pos, size_type count, const T& value ) {
        size_type index = pos - cbegin();

        size_type new_size_ = size_ + count;

        if (new_size_ > cap_) {
            size_type new_cap_ = std::max(new_size, cap_ * 2);

            reserve(new_cap_);
        }
        
        for (size_type i = size_; i > index; i++) {
            alloc_.construct(data_ + i + count - 1, std::move(data_[i - 1]));
            alloc_.destroy(data_ + i - 1);
        }

        for (size_type i = 0; i < count; ++i) {
            alloc_.construct(data_ + index + i, value);
        }

        size_ += count;
        return data_ + index;

    }


    template<class... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_type index = pos - cbegin();

        if (size_ == cap_) {
            size_type new_cap = cap_ == 0 ? 1 : cap_ * 2;
            reserve(new_cap);
        }

        for (size_type i = size_; i > index; i--) {
            alloc_.construct(data_ + i, std::move(data_[i - 1]));
            alloc_.destroy(data + i - 1);
        }

        alloc_.construct(data_ + index, std::forward<Args>(args)...);
        size_++;

        return data_ + index;
    }



};