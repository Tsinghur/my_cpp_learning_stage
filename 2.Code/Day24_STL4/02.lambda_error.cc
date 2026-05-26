#include <iostream>

using std::cout;
using std::endl;

void test1() {
    int a = 10, b = 20;
    /* auto f1 = [] { return a; }; // error: 未捕获a */
    auto f2 = [&] { return a++; };
    f2();
    auto f3 = [=] { return a; };
    f3();
    /* auto f4 = [=] { return a++; }; // a++是写操作，而值捕获不能进行写操作 */
    /* auto f5 = [a] { return a + b; }; // 未捕获b */
    auto f6 = [a, &b] { return a + (b++); };
    f6();
    auto f7 = [=, &b] { return a + (b++); };
    f7();
}

int main() {
    test1();

    return 0;
}
