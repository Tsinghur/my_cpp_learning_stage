#include <iostream>

using std::cout;
using std::endl;


/*
 *
 * 对象的赋值操作: 赋值运算符函数
 *
 * 语法:
 * 类名& operator=(const 类名& rhs){
 *
 *    函数体
 * }
 * 形式上:
 * 1.为啥返回值要设置成&?  为了能够连续赋值
 * 2.参数为啥要加const
 * 3.参数为啥要加&
 */
class Point
{
public:
    Point(int x ,int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point&)" << endl;
    }

    // operator = 
    // const Point & rhs = pt1
    // 调用这个函数的对象是pt2, 就是当前对象
    Point & operator=(const Point & rhs)
    /* void operator=(const Point & rhs) */
    {
        cout << "operator=" << endl;
        this->m_x = rhs.m_x;
        this->m_y = rhs.m_y;
        /* return *this; */
    }
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
    // 内置类型
    int a = 1;
    int b = 2;
    int c = 3;
    b = a = c;

    // 推广到自定义类型
    Point pt1{1,2};
    Point pt2{3,4};
    Point pt3{5,6};
    pt2 = pt1;// 调用一个赋值运算符函数
    // 赋值运算符函数的本质就是一个成员函数
    /* pt2.operator=(pt1); */
    pt2.print();

    cout << "------" << endl;
    pt3 = pt2 = pt1;
    // 本质: 连续的函数调用
    pt3.operator=(pt2.operator=(pt1));
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

