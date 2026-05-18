#include <iostream>

using std::cout;
using std::endl;

/*
 * overload VS oversee VS override
 *
 *
 * oversee : 隐藏 
 * 父类和子类中有同名的成员
 * 通过子类对象访问父子同名成员时, 父类的会被隐藏
 *
 */

class Father
{
public:
    void func()
    {
        cout << "Father::func()" << endl;
    }
    int m_data = 1;
};

class Son : public Father
{
public:
    void func()
    {
        cout << "Son::func()" << endl;
    }
    int m_data = 2;
};

void test1()
{
    Son son;
    cout << son.m_data << endl;// 体现出的是子类的结果

    cout << sizeof(son) << endl;
    // 如果想要访问父类的同名的成员
    // 通过类名作用域方式访问
    cout << son.Father::m_data << endl;
    cout << "---------" << endl;

    son.func();// 子类的结果
    son.Father::func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

