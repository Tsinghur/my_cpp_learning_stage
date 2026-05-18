#include <iostream>

using std::cout;
using std::endl;

/*
 * 纯虚函数 : 虚函数, 但是没有实现
 *
 * 抽象类 : 类中有纯虚函数的类 ---> 不能进行实例化(不能创建对象)
 * 
 * 抽象类一般作为接口或者标准存在, 具体的实现交给子类去做
 * 强制子类去实现这个接口
 *
 * 特殊的: 如果子类中有还没有实现的纯虚函数, 那么这个子类
 * 也是抽象类,也不能实例化
 */
// 抽象类
class AbstractClass
{
public:
    // 纯虚函数
    virtual void func() = 0;
};


void test1()
{
    // 不能进行实例化
    /* AbstractClass obj; */
}

class Animal
{
public:
    // 纯虚函数
    virtual void eat() = 0;
};

class Dog : public Animal
{
public:
    // 强制子类去实现纯虚函数
    virtual void eat()
    {
        cout << "eat meat!" << endl;
    }
};

class Cat : public Animal
{
public:
    // 强制子类去实现纯虚函数
    virtual void eat()
    {
        cout << "eat fish!" << endl;
    }
};

void test2()
{
    /* Animal animal; */
    Dog dog;
    Cat cat;
    Animal * p = &dog;
    p->eat();
    p = &cat;
    p->eat();
}

void handle(Animal * p)
{
    p->eat();
}

/*
 *
 * void handleShape(Shape* p)
 * {
 *
 * }
 *
 */
// A是抽象类
class A
{
public:
    // 纯虚函数
    virtual void func1() = 0;
    virtual void func2() = 0;
    virtual void func3() = 0;
};
// B只实现了func1 ---> 抽象类
class B  : public A
{
public:
    virtual void func1(){}
    virtual void func2(){}
};

// 对于C来讲,所有的纯虚函数都实现了 C具体类型
// 可有创建对象
class C : public B
{
public:
    virtual void func3(){}
};

void test3()
{
    // 抽象类不能创建对象
    /* A a; */
    /* B b; */
    C c;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

