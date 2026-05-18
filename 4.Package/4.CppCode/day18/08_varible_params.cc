#include <iostream>

using std::cout;
using std::endl;

/*
 * 可变参数模板: 适用于模板参数的个数不确定,类型不确定
 *
 * 语法:
 * template <typename ...Args>
 * void func(Args ...args)
 * {
 *
 * }
 *
 * 如何理解:
 * 把Args当做一个类型容器, 装类型参数,K,T,U,T2....
 * args: 当做一个容器, 装函数的所有的参数,K k, T t1, T t2....
 *
 * ...Args : 打包, 模板参数包,把类型参数打包在一起
 * ...args : 打包, 函数参数包
 * 
 * Args... : 解包
 * args... : 解包
 *
 * 使用可变参数模板: 一般情况下需要使用递归操作
 * 1.递归体: 依次从包里取出来一个一个的数据
 * 2.递归出口: 一般情况下定义一个普通函数作为递归出口
 */

template <typename  ...Args>
void print(Args ...args)
{
    // 获取的是模板参数的个数
    cout << sizeof...(Args) << endl;
    // 获取的函数参数包的里面参数的个数
    cout << sizeof...(args) << endl;
}


void test1()
{
    print();
    print(1);
    print(1, 3.14);
    print(1, 3.14, "abc");
    // <T1,T2,T3,T4>
    // print<int,double,const char*,int>
    print(1, 3.14, "abc", 1);
    // 注意: 参数的类型是一样的,不会任务你的类型参数是同一个
    // 还是会把它当成新的类型对待
}

// 需求: 打印可变参数模板中的所有的数据


// 递归出口 普通函数
void show()
{
    // do nothing 
    cout << endl;
}

template <typename First ,typename ...Args>
void show(First first ,Args ...args)
{
    // 递归体
    // 先处理第一个数据
    cout << first << " ";
    // 再处理剩余数据
    // 递归调用
    show(args...); // 解包

    // 模拟一下过程
    // cout << 1
    // show(3,14,"abc", 100)
    // cout << 3.14
    // show("abc", 100)
    // cout << "abc"
    // show(100)
    // cout << 100
    // show();
}

void test2()
{
    show(1, 3.14, "abc", 100);
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

