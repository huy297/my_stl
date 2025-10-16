#include <iostream>

#include "../meta/type_traits.hpp"

using namespace std;



int main() {
    static_assert(_is_void<void>::value);
    static_assert(!_is_void<int>::value);

}