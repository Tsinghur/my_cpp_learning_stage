#include <iostream>

using std::cout;
using std::endl;


class A
{
public:
    void func()
    {
        cout << "A::func()" << endl;
    }
};

class B
{
public:
    void func()
    {
        cout << "B::func()" << endl;
    }

};

// C多继承A B
class C
: public A
, public B
{
public:
    void func()
    {
        cout << "C::func() " <<endl;
    }
};

void test1()
{
    // 如果C中没有func函数
    // 创建子类对象 通过子类对象调用同名的函数
    C c;
    /* c.func();// error 二义性 */


    // 如果子类中有和父类同名的成员函数func
    c.func();// 子类的结果
    // 想要访问父类的 类名作用域
    c.A::func();
    c.B::func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

