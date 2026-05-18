#include <iostream>

using std::cout;
using std::endl;


/*
 * 继承的实质: 把子类当做父类来使用,满足子类is a父类关系
 * 逻辑层面:
 * 狗是动物
 * 苹果是水果
 * 代码层面:
 * 可以使用父类型去接收子类的对象
 *
 * 反过来的不行
 * 动物是狗
 * 水果是苹果
 *
 *
 * 继承的前提条件下, 父子类之间的转换
 * 1.向上转型(自动类型转换)
 * 2.向下转型(强转类型转换)
 * 注意!! 转换的是接收的类型
 */

class Animal
{

};

class Dog : public Animal
{

};

class Cat : public Animal
{

};

void test1()
{
    // 之前的做法: 用哪个对象,用类型相同的变量接收同类型的对象
    Animal animal;
    Dog dog;
    Cat cat;
    Dog &dog2 = dog;
    Cat & cat2 = cat;
    cout << "-----" << endl;
    // 使用继承后 满足子类 is a 父类
    // 子类可以当做父类来使用
    // 可以使用父类接收子对象
    Animal &animal2 = dog; 
    Animal * p = &dog;
    Animal & animal3 = cat;
    Animal * p2 = &cat;

    // 如果反过来就不行
    /* Dog dog3 = animal; // 动物是狗 */
    // 如果两个类没有任何关系
    /* Dog dog4 = cat; */
}

void handleDog(Dog & dog)
{
    // do sth
}

void handleCat(Cat & cat)
{
    // do sth
}

// 可以复用的函数
void handleAnimal(Animal & animal)
{
    // do sth
}

void test2()
{
    Dog dog;
    Cat cat;
    handleAnimal(dog);
    handleAnimal(cat);
}

class GrandFather
{
public:
    virtual void func(){}

};

class Father : public GrandFather
{
public:
    int m_f = 1;
};

class Son : public Father
{
public:
    int m_s = 2;
};

class GrandSon : public Son
{

};

void test3()
{
    // 使用父类型接收子对象
    Son son;
    Son * ps = &son;
    // 向上转型
    /* Father * pf = &son; */
    Father * pf = ps; // 接收的类型 Son--->Father
                      // Father * pf = &son;
    
    pf->m_f;
    /* pf->m_s; */
    // 只能通过父指针访问子类继承父类的那部分数据
    // 不能访问属于子类自己定义的那部分

    // 向下转型
    Father father;
    Father * f = &father;
    Son * s = (Son*)f; // Father--->Son
}

// 转换的是接收的类型 跟对象是啥类型没关系
void test4()
{
    GrandFather * gf = new Son{};
    // 向下转型
    Father * f = dynamic_cast<Father*>(gf);
    if(f){
        cout << "GrandFather * ---> Father *" << endl;
    }
    Son * s = dynamic_cast<Son*>(f);
    if(s){
        cout << "Father * ------> Son *" << endl;
    }
    GrandSon * gs = dynamic_cast<GrandSon*>(s);
    // 此时 转换失败了!!!!!
    if(gs){
        cout << "Son*---->GrandSon*" << endl;
    }
}
int main(int argc, char * argv[])
{
    /* test1(); */
    test4();
    return 0;
}

