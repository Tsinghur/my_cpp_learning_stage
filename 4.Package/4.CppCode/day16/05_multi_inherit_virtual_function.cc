#include <iostream>

using std::cout;
using std::endl;


class Father1
{
public:
    virtual void func1()
    {
        cout << "Father1::func1()" << endl;
    }
    double m_f1 = 1;
};

class Father2
{
public:
    virtual void func2()
    {
        cout << "Father2::func2()" << endl;
    }
    double m_f2 = 2;

};

class Son : public Father1, public Father2
{
public:
    // 重写虚函数
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }

    double m_s = 3;

};

void test1()
{
    Father1 father1;
    Father2 father2;
    Son son;
    cout << sizeof(father1) << endl;
    cout << sizeof(father2) << endl;
    cout << sizeof(son) << endl;
    cout << "-------" << endl;
    Father1 *  f1 = &son;
    f1->func1();
    /* f1->func2();// 父类型指针只能访问自己那部分 */
    Father2 * f2 = &son;
    f2->func2();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

