#include <iostream>

using std::cout;
using std::endl;

/*
 * 把模板作用于成员函数中
 *
 */

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {

    }

    // 把模板作用于成员函数中
    template <typename T>
    void print(T t)
    {
        cout << t << endl;
    }

    // 类中声明 类外实现
    template <typename T>
    void print2(T t);

private:
    int m_x;
    int m_y;
};

// 类外实现成员函数 
// 模板再写一遍
template <typename  T>
void Point::print2(T t)
{
    cout << t << endl;
    cout << "print2" << endl;
}

void test1()
{
    // 创建Point对象
    Point pt { 1, 2 };
    pt.print(100);
    pt.print(3.14);

    pt.print2(100);
    pt.print2<std::string>("abc");
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

