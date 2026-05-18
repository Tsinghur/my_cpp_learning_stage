#include <iostream>

using std::cout;
using std::endl;


/*
 * 基本语法: 在已有的类的继承上进行扩展
 * 子类可以复用父类的成员, 也可以定义子类自己的成员
 *
 * class A{}--->父类 / 基类
 * class B : public A {} 子类/ 派生类
 */

class Father
{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class Son 
/* : public Father */
: Father // 没有加权限的话 默认是private继承
{

};

class GrandSon
: Son
{
public:
    void func(){
        /* m_data1; */
        /* m_data2; */
        /* m_data3; */
    }
};

class Father1
{
public:
    int m_father1Data;
};

class Father2
{
public:
    int m_father2Data;
};

// Son1多继承Father1和Father2
class Son1
/* : public Father1 , Father2 // public继承Father1 private继承Father2 */
: public Father1
, public Father2
{

};


void test1()
{
    Son1 son1;
    son1.m_father1Data;
    son1.m_father2Data;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

