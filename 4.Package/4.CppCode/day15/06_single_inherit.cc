#include <iostream>

using std::cout;
using std::endl;

/*
 * 单继承下的子类对象的创建和销毁过程
 *
 * 创建过程: 先父后子
 * 销毁过程: 和创建执行的过程逆序
 */
class Father
{
public:
    Father()
    {
        cout << "Father()" << endl;
    }
    Father(int f)
    : m_f(f)
    {
        cout << "Fahter(int)" << endl;
    }
    ~Father()
    {
        cout << "~Father()" << endl;
    }
    double m_f;
};

class Son : public Father
{
public:
    Son()  // 有个隐式的初始化 默认会调用父类的无参构造
    {
        cout << "Son()" << endl;
    }
    // 有参构造函数
    Son(int f, int s) //显式把初始化列表写出来
    : Father(f) // 显式调用父类的1参的构造函数
    , m_s(s)
    {
        cout << "Son(int,int)" << endl;
    }
    ~Son()
    {
        cout << "~Son()" << endl;
    }
    double m_s;
};

void test1()
{
    Son son;
    cout << son.m_f << endl;
    cout << son.m_s << endl;
    cout << sizeof(son) << endl;// 16
    // 子类对象中有2部分,一部分继承来的父类的成员
    // 另一部分子类自己定义的
}

// 测试子类对象的创建过程
void test2()
{
    // 栈对象
    /* Son son; */
    /* cout << "--------" << endl; */
    Son son2{ 1, 2 };
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

