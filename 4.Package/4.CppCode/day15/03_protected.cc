#include <iostream>

using std::cout;
using std::endl;
/*
 * 访问权限修饰符:
 * public
 *
 * private
 *
 * protected
 *
 *
 * private VS protected:
 * 继承时访问的权限不一样
 * 父类中的protected成员 在子类中可以访问
 * 父类中的private成员 在子类中不可以访问
 *
 * private权限最严格, 只能在类的内部访问
 * 即使有继承关系 在类的外部(子类) 访问不了
 */

class MyClass
{
public:
    void func()
    {
        // 类内部不受权限影响
        m_data1;
        m_data2;
        m_data3;
    }
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

void test1()
{
    MyClass obj;
    obj.m_data1; // public ok
    /* obj.m_data2; // protected NO */
    /* obj.m_data3; // private No */
}

class Father
{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

class Son : public Father
{
public:
    void sonMethod()
    {
        m_data1; // public OK
        m_data2;// protected ok
        /* m_data3;// private NO */ 
    }

};
int main(int argc, char * argv[])
{
    test1();
    return 0;
}

