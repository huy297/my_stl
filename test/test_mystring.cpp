#include <iostream>
#include <cassert>
#include "../include/string.hpp"

int main() {
    _String s("Hello");

    // Basic checks
    assert(s.size() == 5);
    assert(s[0] == 'H');
    assert(!s.empty());

    s.insert(5, " World");
    assert(std::string(s.c_str()) == "Hello World");

    s.clear();
    assert(s.empty());
    assert(s.c_str()[0] == '\0');

    s.push_back('c');
    assert(s[0] == 'c');

    s.pop_back();
    assert(s.empty());

    s.append("abc");
    assert(std::string(s.c_str()) == "abc");

    s += s;

    assert(std::string(s.c_str()) == "abcabc");

    std::cout << "✅ All tests passed!\n";
}
