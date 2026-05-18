#include <iostream>

using std::cout;
using std::endl;

/*
 * 在构造函数 析构函数中调用虚函数
 *
 */

class GrandFather
{
public:
    GrandFather()
    {
        cout << "GrandFather()" << endl;
    }
    
    ~GrandFather()
    {
        cout << "~GrandFather()" << endl;
    }
    virtual void func1()
    {
        cout << "GrandFather::func1()" << endl;
    }
    virtual void func2()
    {
        cout << "GrandFather::func2()" << endl;
    }
};

class Father : public GrandFather
{
public:
    Father()
    {
        cout << "Father()" << endl;
        func1();
        //C++标准中规定, 在构造析构函数调用虚函数
        //体现的是当前类的版本
    }
    ~Father()
    {
        cout << "~Father()" << endl;
        func2();
    }
    // 在Father类中重写虚函数
    virtual void func1() override
    {
        cout << "Father::func1()" << endl;
    }
    virtual void func2() override
    {
        cout << "Father::func2()" << endl;
    }

};

class Son : public Father
{
public:
    Son()
    {
        cout << "Son() " << endl;
    }
    ~Son()
    {
        cout << "~Son() " << endl;
    }
    virtual void func1() override
    {
        cout << "Son::func1()" << endl;
    }
    virtual void func2() override
    {
        cout << "Son::func2()" << endl;
    }

};

void test1()
{
    Son son;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

