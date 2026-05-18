#include <iostream>

using std::cout;
using std::endl;

/* 对象复制操作: 复制, 赋值
 *
 * 拷贝构造函数:理解成参数为const &的构造函数
 *
 * 语法:
 * 类名(const 类名 & rhs){
 *    构造函数体
 * }
 * 形参中
 * 1.为什么要使用const?
 * 2.为什么要使用&
 *  a.为了避免copy
 *  b.为了避免递归调用
 *
 *
 * 左值与右值:
 * 1.左值: 可以取地址的值
 *   有名字的变量,对象,字符串常量....
 * 2.右值: 不能取地址的值
 *   匿名的或者临时的变量或者对象,字面值常量 1,2....
 *
 *
 * 拷贝构造函数的调用时机有哪些?什么时候回触发拷贝构造调用?
 * 1.用一个已经存在的对象初始化新对象
 * 2.对象作为函数参数的时候
 * 3.对象作为函数返回值的时候
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

    // copy constructor
    // const Point & rhs = pt1
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point&)" << endl;
        /* m_x = rhs.m_x; */
        /* m_y = rhs.m_y; */
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
    int a = 1;
    // 用a变量来初始化新变量b
    int b = a;

    Point pt1{1,2};
    // 用一个已经存在的对象初始化一个新对象
    /* Point pt2 = pt1;// 这里会调用一个拷贝构造函数 */
    // 上下等价
    Point pt2 { pt1 };
    pt2.print();
}

// 常见的左值和右值
void test2()
{
    // 左值
    int a = 1;
    &a;
    Point pt{1,2};
    pt.print();
    &pt;
    &"hello";


    // 右值
    /* &Point{ 3, 4 }; // 匿名的对象 */
    int b = 1;
    int c = 2;
    /* &(b + c); */
    /* &100; */
}

void test3()
{
    int num = 1;
    int & ref = num;
    // 非const的引用可以绑定左值
    /* int & ref2 = 1; */
    // 非cosnt的引用不能绑定右值

    // const的引用可以绑定右值,也可以绑定左值
    const int & ref3 = 1;
    const int & ref4 = num;
}

// 测试拷贝构造函数的参数接收右值对象
void test4()
{
    /* Point pt1{1,2}; */
    /* Point pt { pt1 }; */

    // 传递右值对象报错: 原因参数没有带const
    // const Point & rhs = 匿名的临时对象
    Point pt { Point{ 1, 2 } };
}

// Point pt = p
/* void func(Point & pt) */
void func(Point pt)
{
    pt.print();
}

// 验证拷贝构造的调用时机
void test5()
{
    Point p{1,2};
    func(p);
}

Point func2()
{
    Point pt{1,2};
    return pt;
}

void test6()
{
    Point pt1 = func2();
}
int main(int argc, char * argv[])
{
    /* test1(); */
    /* test5(); */
    test6();
    return 0;
}

