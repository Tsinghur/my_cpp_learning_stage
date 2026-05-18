#include <iostream>

using std::cout;
using std::endl;

/*
 * 函数模板和普通函数重载
 * 普通函数和函数模板之间重载了, 普通函数的优先级更高
 *
 *
 * 函数模板和函数模板之间的重载
 * 1.通过个数区分, T ,  T,U
 * 2.通过位置区分
 * 怎么区分, 最好把具体的函数写出来
 */
void print(int a)
{
    cout << "普通函数" << endl;
    cout << a << endl;
}

template <typename T>
void print(T t)
{
    cout << t << endl;
    cout << "使用了模板" << endl;
}


template <typename T>
void print2(T t)
{
    cout << "使用了模板一" << endl;
}

template <typename T, typename U>
void print2(T t, U u)
{
    cout << "使用了模板二" << endl;
}

void test1()
{
    print(100);

}

void test2()
{
    // 指定类型为int, 函数参数为1个
    print2<int>(100);
    // 指定类型为int, 函数参数有2个
    // T = int, U自动推导int
    // print<int,int>(100,200)
    print2<int>(100,200);
    print2<int,int>(300,400);
    cout << "-----" << endl;

}

template <typename T>
void print3(T t1, T t2)
{
    cout << "使用了模板一" << endl;
}

template <typename T, typename U>
void print3(T t, U u)
{
    cout << "使用了模板二" << endl;
}

void test3()
{
    print3(1,2); // 模板一
    print3<int>(1,2);// 模板一
    print3<int,int>(1,2);// 模板二
}

template <typename T, typename U>
T print4(T t, U u)
{
    cout << "使用了模板一" << endl;
    return t;
}

template <typename T, typename U>
T print4(U u, T t)
{
    cout << "使用了模板二" << endl;
    return t;
}

void test4()
{
    /* print4(1, 3.14); */
    // 对于模板一:
    // T=int , U=double 
    // int print4(int,double)
    // 对于模板二:
    // T = double, U=int
    // double print4(int,double)

    int x = 1;
    double y = 3.14;

    print4<int,double>(x, y);// 模板一
    // 对于模板一:
    // T=int U=double
    // int print4(int,double)
    // 对于模板二:
    // T=int U = double
    // int print(double,int)

    print4<double,int>(x, y);// 模板二
    // 对于模板一:
    // T = double  U = int
    // double print4(double,int)
    // 对于模板二:
    // T = double U = int
    // double print4(int,double)
}


int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    return 0;
}

