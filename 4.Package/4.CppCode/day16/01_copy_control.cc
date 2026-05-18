#include <iostream>

using std::cout;
using std::endl;

/*
 *  拷贝构造  赋值运算符函数
 *
 *  如果类中没有显式写出来拷贝构造和赋值运算符函数,
 *  默认版本的拷贝构造 和赋值运算符函数
 *  子类自己的成员和继承来的父类成员都会进行复制
 *  如果你在代码中显式的写出来拷贝构造, 那么在子类中手动
 *  调用父类的拷贝构造或者父类的赋值运算符函数
 */

class Father
{
public:
    Father()
    {
        cout << "Fater constructor" << endl;
    }
    Father(int f)
    : m_f(f)
    {

    }
    // copy constructor
    // const Father & rhs = s1  (父引用接收了一个子对象)
    // 父类型的指针或引用只能访问父类自己的那部分
    Father(const Father & rhs)
    : m_f(rhs.m_f) 
    {
        cout << "Father copy constructor" << endl;
    }

    // operator=
    Father & operator=(const Father & rhs)
    {
        cout << "Father operator = " << endl;
        this->m_f = rhs.m_f;
        return *this;
    }
    int m_f;
};


class Son : public Father
{
public:
    Son(int f, int s)
    : Father(f)
    , m_s(s)
    {

    }
    // copy constructor
    Son(const Son & rhs)
    : Father(rhs) // 显式调用父类的拷贝构造
    , m_s(rhs.m_s)
    {
        cout << "Son copy constructor" << endl;
    }
    // operator=
    Son & operator=(const Son & rhs)
    {
        cout << "Son operator =" << endl;
        // 需要手动调用父类的赋值运算符函数
        // 需要使用类名作用域
        Father::operator=(rhs);
        this->m_s = rhs.m_s;
        return *this;
    }
    int m_s;

};

void test1()
{
    Son s1 {1, 2};
    Son s2 = s1; // 调用拷贝构造


    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}

void test2()
{
    Son s1 {1, 2};
    Son s2 {3, 4};
    s2 = s1; // 调用赋值运算符函数

    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}


int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

