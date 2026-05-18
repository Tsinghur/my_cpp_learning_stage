#include <iostream>

using std::cout;
using std::endl;

/*
 * 代理设计模式: 委托类  代理类--> 帮委托做事情
 *
 * 景天类 : 委托 ----> 买包子
 *  
 * 空灵类 : 代理
 *
 * 常见的代理实现方式:
 * 1.将委托作为代理类中的数据成员
 * 2.将委托作为代理类的父类 使用继承
 */

// 委托类
class JingTian
{
public:
    void buyBreakFast()
    {
        cout << "买2个包子.." << endl;
    }
};

// 代理类
class KongLing
{
public:
    KongLing(JingTian & jingtian)
    : m_jingtian(jingtian)
    {

    }
    void buyBreakFast()
    {
        cout << "帮景天" << endl;
        m_jingtian.buyBreakFast();
    }
    // 将委托设置为数据成员
    JingTian & m_jingtian;
};

void test1()
{
    JingTian jingtian;
    KongLing kl{ jingtian };
    kl.buyBreakFast();
}

// 使用方式二实现代理模式
// 委托类
class JingTian2
{
public:
    void buyBreakFast()
    {
        cout << "买2个包子.." << endl;
    }
};

// 代理类
// 将景天设置为空灵的爸爸  
class KongLing2 : public JingTian2
{
public:
    void buyBreakFast()
    {
        cout << "帮景天" << endl;
        // 调用父类的同名的成员函数
        // 通过类名作用域进行调用
        JingTian2::buyBreakFast();
    }
};

void test2()
{
    KongLing2 kl;
    kl.buyBreakFast();
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

