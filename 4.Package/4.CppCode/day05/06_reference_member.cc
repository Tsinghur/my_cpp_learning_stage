#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/*
 * 引用数据成员: 必须要在初始化列表中进行初始化
 * 引用所绑定的变量或者对象生命周期大于等于该对象
 *
 *
 */

class Point
{
public:
    // int & z = num 
    // int & m_z = num
    Point(int x, int y, int & z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    {

    }
    void print()
    {
        cout << m_x << " " << m_y << " " << m_z << endl;
        // 使用了这个p指针
        // 做非空判断
        // if(p) xxxxxx
        // do sth
    }
    int m_x;
    int m_y;
    // 引用数据成员
    int & m_z;
    int * p;
};

void test1()
{
    int num = 3;
    Point pt{1, 2 ,num};
    pt.print();
}

class Mather;

class Baby
{
public:
    Baby(string name, Mather & m)
    : m_name(name)
    , m_mather(m)
    {}
    string m_name;    
    Mather & m_mather;
};

class Mather
{
public:
    Mather(string name)
    : m_name(name)
    {}
    string m_name;
};

void test2()
{
    Mather mather{"lili"};
    Baby baby{"kongling", mather};
}

class Printer
{
public:
    Printer(ostream & os)
    : m_os(os)
    {}

    void print()
    {
        m_os << "123";
    }
    ostream & m_os;
};

void test3()
{
    Printer printer{ cout };
    printer.print();
    // cout << "123"
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

