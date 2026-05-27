#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;

void modify(int &a, int &b) {
/* void modify(int a, int b) { */
    a *= 2;
    b += 10;
}

void test1() {
    int x = 5, y = 5;
    auto f = bind(modify, x, y);
    f(x, y);
    cout << x << "," << y << endl; // ?
}

void test2() {
    int x = 5, y = 5;
    auto f = bind(modify, _1, _2);
    f(x, y);
    cout << x << "," << y << endl; // ?
}

void test3() {
    int x = 5, y = 5;
    auto g = bind(modify, ref(x), ref(y));
    g();
    cout << x << "," << y << endl; // ?
}

int main() {
    cout << "---------test1()---------" << endl;
    test1();
    cout << "---------test2()---------" << endl;
    test2();
    cout << "---------test3()---------" << endl;
    test3();

    return 0;
}

/*
---------test1()---------
5,5
---------test2()---------
10,15
---------test3()---------
10,15
*/
