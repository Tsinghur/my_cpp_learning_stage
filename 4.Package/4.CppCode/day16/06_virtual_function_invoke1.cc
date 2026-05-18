#include <iostream>

using std::cout;
using std::endl;

/*
 * 直接通过子对象调用: 这不是多态
 *
 */
class Father
{
public:
    virtual void func()
    {
        cout << "Father::func()" << endl;
    }
};

class Son : public Father
{
public:
    virtual void func()
    {
        cout << "Son::func()" << endl;
    }

};

void test1()
{
    // 创建子类对象
    // 通过子对象直接调用虚函数
    // 不满足多态条件
    Son son;
    son.func();
    // 如果子类中没有这个虚函数 ---> 继承的表现
    // 子类中如果有这个虚函数 ---> 隐藏的效果
    son.Father::func();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

