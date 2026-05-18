#include <iostream>

using std::cout;
using std::endl;

class Father
{
public:
    virtual void func()
    {
        cout << "Father::func()" << endl;
    }
    void fatherMethod1()
    {
        cout << "fatherMethod1()" << endl;
        // 通过类名作用域调用虚函数
        Father::func();
    }

    void fatherMethod2()
    {
        cout << this << endl;
        cout << "fatherMethod2()" << endl;
        // 直接调用虚函数
        func();

        // 通过son.调用该函数 所以this指针指向的是son对象
        // 当前对象是Son对象 
        // 这里体现的是一个特殊的多态, 运行的结果
        // 取决于具体对象的类型
    }
};

class Son : public Father
{
public:
    virtual void func() override
    {
        cout << "Son::func()" << endl;
    }
};

void test1()
{
    // 测试Father对象
    Father father;
    father.fatherMethod1();// Father
    father.fatherMethod2();// Father
    cout << "---------" << endl;
    // 测试Son对象
    Son son;
    // fatherMethod1和2这两个函数都是继承来的
    son.fatherMethod1();// Father的结果:类名作用域
    son.fatherMethod2();// Son的结果
    cout << &son << endl;

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

