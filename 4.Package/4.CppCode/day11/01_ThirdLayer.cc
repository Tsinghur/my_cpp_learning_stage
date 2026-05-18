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
    // operator*11
    Data & operator*()
    {
        return *m_p;
    }
private:
    // 原生指针 原始指针 裸指针 底层指针
    Data * m_p;
};

// 定义一个第三层结构
class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer * m_p)
    : m_pml(m_p)
    {
        cout << "ThirdLayer(MiddleLayer*)" << endl;
    }
    ~ThirdLayer()
    {
        cout << "~ThirdLayer()" << endl;
        if(m_pml){
            delete m_pml;
            m_pml = nullptr;
        }
    }

    // operator-> 
    MiddleLayer & operator->()
    {
        return *m_pml;
    }

    // operator*
    MiddleLayer & operator*()
    {
        return *m_pml;
    }
    /* Data & operator*() */
    /* { */
    /*     return **m_pml; */
    /* } */

private:
    MiddleLayer * m_pml;
};

// 让第三层对象作为管理者对象
void test1()
{
    /* MiddleLayer ml { new Data{} }; */

    ThirdLayer tl {new MiddleLayer{ new Data{} }};
    // 通过tl对象访问所管理的资源 Data类中的getData函数

    //tl中的operator->  ml中的operator-> Data*->getData()
    // 本质
    //tl.operator->().operator->()->getData()
    tl.operator->().operator->()->getData();
    // 简写
    tl->getData();


    cout << "----------" << endl;
    //tl.operator*(). ml.operator*()--> Data对象.getData()
    // 本质
    tl.operator*().operator*().getData();
    // 简写
    (*(*tl)).getData();

    // 如果希望解引用一次就能访问getData()
    // 修改operator*(), 返回值直接设置为Data&
    /* (*tl).getData(); */
}

int main(int argc, char * argv[])
{
    test1();

    return 0;
}

