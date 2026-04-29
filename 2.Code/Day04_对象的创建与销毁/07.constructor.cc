#include <iostream>

using namespace std;

class Point {
public:
    // 无参构造函数
    Point() {
        cout << "Point()" << endl;
        m_x = 1;
        m_y = 1;
    }
    // 有参构造函数
    /* Point(int x, int y) { */
    /*     cout << "Point(int, int)" << endl; */
    /*     m_x = x; */
    /*     m_y = y; */
    /* } */
    Point(int x, int y) 
    /* : m_x(x) */
    /* , m_y(m_x) // 数据成员初始化顺序只与其声明顺序有关 */
    /* : m_y(m_x) */
    /* , m_x(x) */
    /* : m_x(x) // 虽然没有依赖则无报错，但是顺序不一致仍会警告 */
    /* , m_y(y) */
    : m_y(y)
    , m_x(x)
    {
        cout << "Point(int, int)" << endl;
    }
    Point(int x) {
        m_x = x;
    }
    void print() {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_y = 0;
    int m_x;
};

void test() {
    // 无参构造函数调用时即使用无参构造函数初始化时不要加()，会被当做函数声明
    /* Point pt1(); // 警告 */
    /* pt1.print(); // 直接报错 */
    /* Point pt1{}; */
    // 或
    Point pt1;
    pt1.print();
    cout << "-----------" << endl;
    Point pt2(1, 2);
    // 或
    /* Point pt2{2, 2}; */
    pt2.print();
    cout << "-----------" << endl;
    Point pt3(3);
    pt3.print();
}

class MyClass {
public:
    // 无参构造函数在什么都不做时还可以简写
    /* MyClass() = default; */  
    // 增加一个构造函数
    /* MyClass(int data) { */
    /*     m_data1 = data; */
    /* } */
    // ！！！如果构造函数参数有默认值，尽量不要重载，很容易导致二义性
    MyClass(int data1 = 1, int data2 = 2)
    : m_data1(data1)
    , m_data2(data2)
    {
        
    }
    int m_data1 = 10; // C++11之后可以直接给数据成员赋初始值，相当于默认值
    int m_data2 = 20;
};

void test2() {
    MyClass obj{}; // 会调用无参构造函数
    MyClass obj2{10};
}

int main() {
    test();

    return 0;
}
