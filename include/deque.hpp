#include <cstddef>


template<class T, size_t buff_size>
class _deque_iterator {
public:
    using iterator = _deque_iterator<T, buff_size> ;
    using map_pointer = T**;
    using pointer = T*;
    using reference = T&;
    using value_type = T;

    // pointer to the chunk
private:
    pointer cur;
    pointer first; // begin chunk
    pointer last;  // end chunk

    map_pointer = node;

    int chunk_size() {
        return 8;
    }

public:
    _deque_iterator() 
        : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) {}

    _deque_iterator(pointer cur_, pointer first_, pointer last_, map_pointer node_)
        : cur(cur_), first(first_), last(last_), node(node_) {}

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + chunk_size();
    }

    reference opearator*() const {
        return *cur;
    }
    
};