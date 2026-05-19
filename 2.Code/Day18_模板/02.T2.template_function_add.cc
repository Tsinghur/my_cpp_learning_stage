#include <iostream>

using std::cout;
using std::endl;

template <typename T>
T add(T t) {
    return t;
}

template <typename T,class... Args>
T add(T first, Args... args) {
    return first + add(args...);
}

void test1() {
    cout << add(1, 2, 3) << endl;
    cout << add(1.5, 2.5, 3.5) << endl;
}

int main() {
    test1();

    return 0;
}
