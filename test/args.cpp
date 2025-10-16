#include <iostream>

using namespace std;

template<class... Args> 
void log(Args... args) {
    (cout << ... << args) << '\n';
}

void old_log() {}

template<class T, class... Args> 
void old_log(T first, Args... rest) {
    cout << first;
    old_log(rest...);
}


void print(const string& s) {
    cout << "copy: " << s << endl;
}

void print(string&& s) {
    cout << "move: " << s << endl;
}

template<class T>
void wrapper(T&& arg) {
    print(std::forward<T>(arg));
}

int main() {
    string a = "hello";
    wrapper(a);
    wrapper(string("hi"));
}