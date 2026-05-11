#include <iostream>

using std::cout;
using std::endl;

class Complex;
class Point {
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}
    Point(const Complex& rhs); // 需要Complex类前置声明
    Point& operator=(const Complex& rhs); 
    void print() const {
        cout << "(" << m_x << "," << m_y << ")" << endl;
    }
private:
    int m_x;
    int m_y;
};

class Complex {
public:
    Complex(int x = 0, int y = 0)
    : m_real(x)
    , m_image(y)
    {}
    operator Point() {
        cout << "类型转换函数operator Pointer被调用" << endl;
        return Point(m_real, m_image);
    }
    void print() const {
        cout << "(" << m_real << "," << m_image << ")" << endl;
    }
    friend class Point; // 使Point中通过Complex的构造函数可以访问Complex的私有成员
private:
    int m_real;
    int m_image;
};

Point::Point(const Complex& rhs) 
: m_x(rhs.m_real)
, m_y(rhs.m_image)
{
    cout << "Point的特殊构造函数" << endl;
}

Point& Point::operator=(const Complex& rhs) {   
    m_x = rhs.m_real;
    m_y = rhs.m_image;
    cout << "Point& operator=(const Complex&)" << endl;
    return *this;
}

// operator=(const Complex&) > oprator Point() > Point(const Complex&)
void test1() {
    Point pt(1, 2);
    Complex cx(3, 4);
    pt = cx;
    pt.print();
    cx.print();
}

int main() {
    test1();

    return 0;
}
