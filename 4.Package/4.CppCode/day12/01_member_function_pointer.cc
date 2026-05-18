#include <iostream>

using std::cout;
using std::endl;

void func1()
{
    cout << "func1() " << endl;
}

void func2()
{
    cout << "func2() " << endl;
}

void func3()
{
    cout << "func3() " << endl;
}

void test1()
{
    func1();
    func2();
    func3();
    cout << "-------" << endl;
    // 简写形式
    void (*f)() = func1;
    f();

    // 完整写法
    f = &func2;
    (*f)(); // func2()

    cout << "------" << endl;
    // 定义一个别名 
    typedef void (*F)();
    int a = 1;
    F ff = &func1;
    ff();

    cout << "------" << endl;
    // 其他写法 C++11后可以用using
    // using 别名 = 代指的类型
    using FFF = void(*)();
    int b = 1;
    FFF fff = &func3;
    fff();
}

class FFF
{
public:
    // 成员函数
    void f1()
    {
        cout << "FFF::f1()" << endl;
    }
    void f2()
    {
        cout << "FFF::f2()" << endl;
    }
    void f3()
    {
        cout << "FFF::f3()" << endl;
        cout << "m_data: " << m_data << endl;
    }

    int m_data = 1;
};

void test2()
{
    FFF obj;
    // 访问成员函数 对象.  指针->
    obj.f1();
    obj.f2();
    obj.f3();
    FFF * p = &obj;
    p->f1();
    p->f2();
    p->f3();
    cout << "------" << endl;
    // 使用类名作用域方式
    // 对与成员函数指针来说需要完整写法
    void (FFF::*f)() = &FFF::f1;
    // 成员函数的调用需要依赖于对象
    (obj.*f)();// 对象.f1();
    (p->*f)();// 指针->f1();
}

// 空指针测试
void test3()
{
    // 此时有没有对象存在? ---> 没有对象
    FFF * p = nullptr;
    p->f1();
    p->f2();
    p->f3();
    // 可以通过空指针调用成员函数 但是无法
    // 访问数据成员 数据成员依赖于对象的
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

