#include <iostream>

using std::cout;
using std::endl;

/*
 * 可调用实体:
 * 普通函数
 * 成员函数
 * 函数指针
 * 成员函数指针
 * 函数对象
 * lambda表达式
 *
 * 函数对象: 类中重载了operator()函数调用运算符的对象
 * 可以像函数一样被调用
 *
 * 使用场景:
 * 1.配合算法库使用
 * 2.函数对象的本质是对象, 可以存储一些额外的数据
 * 这个数据的生命周期和对象是一致的
 */

class MyClass
{
public:
    // operator() 函数调用运算符 后面的()才是参数列表
    void operator()()
    {
        cout << "operator()()" << endl;
    }
    // 对函数调用运算符进行重载
    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        cout << "num=" << num << endl;
    }
    int  operator()(int a, int b)
    {
        cout << "operator()(int,int)" << endl;
        return a + b;
    } };

void test1()
{
    MyClass obj;
    // obj是个对象 但是可以像函数一样调用()
    obj();  // 调用的是无参的那个函数
    // 本质
    /* obj.operator()(); */

    obj(100);
    // 本质
    /* obj.operator()(100); */

    int sum = obj(1,2);
    cout << sum << endl;
    // 本质
    /* int sum = obj.operator()(1,2); */

}

void test2()
{
    int count = 0;
}

void test3()
{   
    // 无法访问test2里面的局部变量
    /* cout << count << endl; */
}

// 统计一下MyClass2这个对象被调用了几次
class MyClass2
{
public:
    // operator ()
    void operator()()
    {
        cout << "operator()()" << endl;
        count++;
    }
    void operator()(int num)
    {
        cout << "operator()(int)" << endl;
        count++;
    }

    int count = 0;
};

void test4()
{
    MyClass2 obj;
    obj();
    obj();
    obj(100);

    cout << obj.count << endl;
}
int main(int argc, char * argv[])
{
    /* test1(); */
    test4();
    return 0;
}

