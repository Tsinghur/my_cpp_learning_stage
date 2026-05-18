#include <iostream>

using std::cout;
using std::endl;

/*
 * 规范的初始化一般使用初始化列表的方式进行
 * 数据成员的初始化
 * 
 * 如果有多个数据成员要初始化,中间有逗号分割
 *
 * 初始化顺序和声明的数据成员的顺序相关,和初始化列表的
 * 顺序没有关系
 */
class Point
{
public:
    // 无参构造函数
    Point()
    {
        cout << "Point()" << endl;
    }
    // 有参构造函数
    Point(int x, int y) 
    :m_x(x) 
    ,m_y(m_x)
    {
        cout << "Point(int,int)" << endl;
    }
       void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_y;

    int m_x;
};

void test1()
{
    Point pt{ 1, 2 };
    pt.print();
}

class MyClass
{
public:
    // 注意!: 如果构造函数有默认值, 尽量不要重载
    MyClass(int data1 = 1, int data2 = 1)
    : m_data1(data1)
    , m_data2(data2)
    {

    }
    /* MyClass() */
    /* { */

    /* } */
    int m_data1 = 10; // C++11之后可以直接给数据成员赋值 相当于默认值
    int m_data2 = 20;
};

void test2()
{
    MyClass obj;
}
int main(int argc, char * argv[])
{
    test1();
    return 0;
}

