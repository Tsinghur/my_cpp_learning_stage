#include <iostream>

using namespace std;

class Point {
public:
    // 无参构造函数
    Point() {
        cout << "Point()" << endl;
    }
    // 有参构造函数
    Point(int x, int y) 
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int, int)" << endl;
    }
    void print() {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_x;
    int m_y;
};

void test1() {
    Point pt;
    cout << sizeof(pt) << endl; // 8
}

class A {
    int m_a1;
    int m_a2;
    double m_a3;
};

class B {
    int m_b1;
    double m_b2;
    int m_b3;
};

void test2() {
    A a;
    B b;
    cout << sizeof(a) << endl; // 16
    cout << sizeof(b) << endl; // 24
}

class C {
    double m_c1;
    char m_cArr[20];
    double m_c2;
    int m_c3;
};

class D {
    char m_dArr[20];
};

class E {

};

void test3() {
    C c;
    D d;
    E e;
    cout << sizeof(c) << endl; // 48
    cout << sizeof(d) << endl; // 20
    cout << sizeof(e) << endl; // 1
}

int main() {
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}
