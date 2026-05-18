#include <iostream>

using std::cout;
using std::endl;

/*
 * 虚函数: 使用virtual 修饰类中成员函数----> 虚函数
 *
 */

class Father
{
public:
    virtual  // 虚函数
    void func1()
    {
        cout << "Father::func1()" << endl;
    }

    void func2()
    {

    }
    // 声明虚函数
    virtual void func3();
};

// 类外给具体的实现
/* virtual // 类外实现时不要再加virtual*/ 
void Father::func3()
{

}

class Son : public Father
{
public:
    // 子类中重写虚函数
    // override:用来标记子类中重写的父类的虚函数
    // 在子类中virtual 和 override可以省略
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    void func2() //override 只能标记虚函数
    {

    }
};

void test1()
{
    Son son;
    son.func1(); //体现的是子类的结果
    son.Father::func1();// 父的结果
    // 上面的代码不是多态 是隐藏

    // 下面的代码才是多态
    Father * f = &son;
    f->func1();
    // 多态的条件
    // 1.继承为前提条件
    // 2.父类中要定义虚函数
    // 3.子类中要重写父类的虚函数 override
    // 4.父类的指针或引用接收子对象
    // 5.通过父类型调用同名的虚函数
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

