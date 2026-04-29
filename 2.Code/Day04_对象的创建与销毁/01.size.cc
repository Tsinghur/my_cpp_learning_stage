#include <iostream>

using namespace std;

class A {
    int a;
    double b;
    int c;
};

struct B {
    int a;
    double b;
    int c;
};

void test() {
    A a;
    B b;
    cout << "class: " << sizeof(a) << endl;
    cout << "struct " << sizeof(b) << endl;
}

int main() {
    test();

    return 0;
}
