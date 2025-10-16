#include <cstddef>
#include <iterator>
#include <stdexcept>




class _String {
private:
    char* data_;
    size_t size_;
    size_t cap_;
    using iterator = char*;
    using const_iterator = const char*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    void ensure_capacity(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }

        cap_ = new_cap * 2;
        char* new_data  = new char[cap_];
        std::memcpy(new_data, data_, size_ + 1);
        delete[] data_;
        data_ = new_data;
    }

public:
    _String(): data_(new char[1]{'\0'}), size_(0), cap_(1) {}

    _String(const char* s) {
        size_ = std::strlen(s);
        cap_ = size_ + 1;
        data_ = new char[cap_];
        std::memcpy(data_, s, size_ + 1);
    }

    _String(const _String& other) : size_(other.size_), cap_(other.cap_) {
        data_ = new char[cap_];
        std::memcpy(data_, &other, size_ + 1);
    }

    _String(_String&& other) noexcept : data_(other.data_), size_(other.size_), cap_(other.cap_) {
        other.data_ = nullptr;
        other.size_ = other.cap_ = 0;
    }

    ~_String() {delete[] data_;}

    _String& operator=(const _String& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            cap_ = other.cap_;
            data_ = new char[cap_];
            std::memcpy(data_, other.data_, size_ + 1);
        }

        return *this;
    }

    void assign(const char* s) {
        size_t new_size_ = std::strlen(s);
        ensure_capacity(new_size_ + 1);

        std::memcpy(data_, s, new_size_ + 1);
        size_ = new_size_;
    }

    void assign(const _String &other) {
        if (this != &other) {
            ensure_capacity(other.size_ + 1);
            std::memcpy(data_, other.data_, other.size_ + 1);
            size_ = other.size_;
        }
    }

    // element access

    char& at(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("String::at: index out of range");
        }

        return data_[pos];
    }

    const char& at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("String::at: index out of range");
        }

        return data_[pos];
    }

    char& operator[](size_t pos) {
        return data_[pos];
    }

    const char& operator[](size_t pos) const {
        return data_[pos];
    }

    char& front() {
        return data_[0];
    }

    const char& front() const {
        return data_[0];
    }

    char& back() {
        return data_[size_ - 1];
    }

    const char& back() const {
        return data_[size_ - 1];
    }

    char* data() noexcept {
        return data_;
    }

    const char* data() const noexcept {
        return data_;
    }

    const char* c_str() const {
        return data_;
    }

    // iterator

    iterator begin() noexcept {
        return data_;
    }

    const_iterator begin() const noexcept {
        return data_;
    }

    const_iterator cbegin() const noexcept {
        return data_;
    }

    iterator end() noexcept {
        return data_ + size_;
    }

    const_iterator end() const noexcept {
        return data_ + size_;
    }

    const_iterator cend() const noexcept {
        return data_ + size_;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

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

    size_t size() const {
        return size_;
    }

    size_t length() const {
        return size_;
    }

    void reserve(size_t new_cap = 0) {
        ensure_capacity(new_cap);
    }


    size_t capacity() const {
        return cap_;
    }

    void shrink_to_fit() {
        if (cap_ > size_ + 1) {
            char* new_data = new char[size_ + 1];
            std::memcpy(new_data, data_, size_ + 1);

            delete[] data_;

            data_ = new_data;
            cap_ = size_ + 1;
        }
    }

    // modifier

    void clear() {
        size_ = 0;
        if (data_) {
            data_[0] = '\0';
        }
    }

    void insert(int pos, const char* s) {
        if (pos > size_) {
            throw std::out_of_range("insert position out of range");
        }

        size_t len = std::strlen(s);

        if (size_ + len + 1 > cap_) {
            this->reserve((size_ + len + 1) * 2);
        }

        std::memmove(data_ + pos + len, data_ + pos, size_ - pos + 1);

        std::memcpy(data_ + pos, s, len);

        size_ += len;
    }

    void push_back(char ch) {
        if (size_ + 1 > cap_)  {
            reserve(2 * cap_);
        }

        this->data_[size_ ++] = ch;  
        this->data_[size_] = '\0';
    } 

    void pop_back() {
        if (this->empty()) {
            throw std::out_of_range("blank string"); 
        }
        this->size_ -= 1;
        this->data_[size_ - 1] = '\0';
    }

    _String& append(const char* s) {
        size_t len = std::strlen(s);
        size_t new_size_ = this->size_ + len;

        if (new_size_ + 1 > this->cap_) {
            reserve((new_size_ + 1) * 2);
        }

        char* pos = this->data_ + this->size_;

        std::memcpy(pos, s, len);
        this->size_ = new_size_;
        this->data_[size_] = '\0';

        return *this;

    }

    _String& operator+=(const _String& other) {
        return this->append(other.c_str());
    } 

    void swap(_String& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }



};
