#include <iostream>

using std::cout;
using std::endl;

/*
 * 构造函数constructor: 特殊的成员函数
 * 作用: 在对象创建过程中会自动调用
 *
 * 语法:
 * 类名(形参列表){
 *   构造函数体
 * }
 * 说明:
 * 1.没有返回值类型
 * 2.函数名必须和类名一样
 * 3.形参列表和普通函数一样
 * 无参: 无参构造函数
 * 有参: 有参构造函数
 * ---->构成构造函数的重载(类中可以有多个构造函数)
 * 4.把一些初始化的操作放在构造函数体内部
 *
 * 注意:
 * 1.如果类中没有写任何的构造函数,编译器会帮我们生成
 * 一个默认无参的构造函数
 * 2.如果类中有任意的构造函数了,类中就没有了这个默认无参
 * 构造函数
 *
 */
class Point
{
public:
    // 无参构造函数
    Point()
    {
        cout << "Point()" << endl;
        m_x = 1;
        m_y = 2;
    }
    // 有参构造函数
    Point(int x, int y)
    {
        cout << "Point(int,int)" << endl;
        m_x = x;
        m_y = y;
    }
    Point(int x)
    {
        m_x = x;
    }
    /* void setX(int x) */
    /* { */
    /*     m_x = x; */
    /* } */
    /* void setY(int y) */
    /* { */
    /*     m_y = y; */
    /* } */
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_x;
    int m_y;
};

void test1()
{
    // 注意!!无参构造函数调用时, 不要加()
    /* Point pt(); */
    /* Point pt; */
    Point pt {  };
    /* pt.m_x = 1; */
    /* pt.m_y = 2; */
    /* pt.setX(1); */
    /* pt.setY(2); */
    pt.print();

    cout << "-----" << endl;
    /* Point pt2(1,2); */
    Point pt2{ 10, 20 };
    // 还可以使用{}, 初始化列表方式
    pt2.print();
}

class MyClass
{
public:
    // 可以显式的把无参构造函数写出来
    // 也可以简写
    /* MyClass(){} */
    MyClass() = default;

    // 增加一个构造函数
    MyClass(int data)
    {
        m_data = data;
    }
    int m_data;
};

void test2()
{
    MyClass obj; // 会调用无参构造

    MyClass obj2 { 10 };
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

