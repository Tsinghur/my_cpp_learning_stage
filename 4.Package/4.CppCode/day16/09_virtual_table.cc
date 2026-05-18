#include <iostream>

using std::cout;
using std::endl;

class Father
{
public:
    virtual void func1()
    {
        cout << "Father::func1()" << endl;
    }
    virtual void func2()
    {
        cout << "Father::func2()" << endl;
    }
    virtual void func3()
    {
        cout << "Father::func3()" << endl;
    }
    long m_f = 1;
};

class Son : public Father
{
public:
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }
    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }
    /* virtual void func3() override */
    /* { */
    /*     cout << "Son::func3()" << endl; */
    /* } */
    long m_s = 2;

};
void test1()
{
    // 验证Father
    Father father;
    long * f =  (long*)&father;
    cout << f[0] << endl; // 虚函数表
    cout << f[1] << endl; // m_f成员的值
    long * vftable = (long*)f[0];                      
    typedef void(*F)();
    F f1 = (F)vftable[0];
    f1();
    f1 = (F)vftable[1];
    f1();
    f1 = (F)vftable[2];
    f1();
    cout << "----------" << endl;
    // 验证Son
    Son son;
    long * s =  (long*)&son;
    cout << s[0] << endl; // 虚函数表
    cout << s[1] << endl; // m_f成员的值
    cout << s[2] << endl; // m_f成员的值
    long * vftable2 = (long*)s[0];                      
    typedef void(*FF)();
    F f11 = (FF)vftable2[0];
    f11();
    f11 = (FF)vftable2[1];
    f11();
    f11 = (FF)vftable2[2];
    f11();

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

