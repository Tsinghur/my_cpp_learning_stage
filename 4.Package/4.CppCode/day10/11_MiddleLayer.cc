#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::auto_ptr;

/*
 * 成员访问运算符 : ->  *
 * operator->
 *
 * operator*
 * 
 * Type * p = new Type();
 * p->m_data;
 * p->func();
 *
 * (*p).m_data;
 * (*p).func();
 *
 * 一般情况下通过指针来做的操作, 重载后可以像使用指针一样
 * 去使用对象
 *
 * 自动资源释放: 利用栈对象的生命周期进行自动资源释放
 *
 */

class Data
{
public:
    Data()
    {
        cout << "Data()" << endl;
    }

    int getData()
    {
        return m_data;
    }
/* private: */
    int m_data = 1;
};


class MiddleLayer
{
public:
    // constructor
    MiddleLayer(Data * p)
    : m_p(p)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }

    ~MiddleLayer()
    {
        cout << "~MiddleLayer()" << endl;
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }
    // operator->
    // 返回值必须是指针或者重载了->运算符的对象
    Data * operator->()
    {
        return  m_p;
    }
    // operator*
    Data & operator*()
    {
        return *m_p;
    }
private:
    // 原生指针 原始指针 裸指针 底层指针
    Data * m_p;
};
void test1()
{
    // 栈对象
    Data data;
    // 对象.成员访问
    data.getData();

    // 堆对象
    Data * p = new Data{};
    // 指针->成员访问
    p->getData();

    // *指针 .成员访问
    (*p).getData();

    // 释放资源
    delete  p;
}

void test2()
{

    Data * p = new Data{};
    // 创建栈对象
    MiddleLayer ml { p };

    /* delete p; 自动资源管理 不需要手动释放 */
}

void test3()
{

    // 把Data对象当做一个内存资源, 把该资源交给了ml
    // 管理者对象,由管理者对象回收内存资源
    MiddleLayer ml { new Data{} };
    // ml对象就在扮演智能指针的角色

    // 希望通过ml对象访问所管理的资源 getData()
    // 简写
    ml->getData();
    // ml.operator->()
    // getData()的调用: Data对象.getData() Data*->getData()
    // ml.operator->()-->Data*-->getData();
    // 本质
    ml.operator->()->getData();

    cout << "-----" << endl;
    // ml.operator*()--> Data对象.getData()
    // 本质
    ml.operator*().getData();
    // 简写
    (*ml).getData();
}

void test4()
{
    // 通过智能指针进行资源管理
    auto_ptr<Data> ap{ new Data{} };
    cout << ap->getData() << endl;
    cout << (*ap).getData() << endl;

}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test4();
    return 0;
}

