#include <iostream>

using std::cout;
using std::endl;

/*
 *
 * 把模板作用在函数上: 函数模板
 *
 * 基本语法:
 * template <typename/class T,typename U, typename K>
 * template : 关键字
 * T/U/K : 模板参数(类型参数), 一种通用类型, 这个字母
 * 使用什么无所谓, 就是一个"代号".
 * 通常一般会使用几个大写字母
 * T : type
 * K : key
 * V : value
 * E : element
 * 尽量不要使用XYZ像这样的命名 
 * 
 */


// 函数声明 和 实现写在一起的
template <typename T>
void print(T t)
{
    cout << "print(T)" << endl;
    cout << t << endl;
}

// 编译器会根据模板生成具体的函数
/*
 * 代码生成器
 * void print(int t)
 * {
 *    cout ....
 * }
 *
 * void print(double t)
 * {
 *   cout ....
 * }
 *
 */

// 函数声明
template <typename T, typename R>
R func(T t1, T t2)
{

}


// 函数声明和实现分开写
template <typename T>
void print2(T t);


// 函数实现 还需要再定义template
template <typename T>
void print2(T t)
{
    // do sth
    cout << "print2(T)" << endl;
}

void test1()
{
    // 显式实例化 指明具体类型是啥
    print<int>(100);
    print<double>(3.14);

    cout << "------" << endl;
    // 隐式实例化
    print(10);
    print(3.14);

}

void test2()
{
    print2<int>(100);

    print2(3.14);
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

