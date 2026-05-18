#include <iostream>

using std::cout;
using std::endl;

/*
 * 模板的参数:
 * 1.类型参数 : T , K ,U ,V....
 * 2.非类型参数 : 一般是整数类型 int ,size_t....
 *
 * 模板参数也可以设置默认值
 */

template <typename T, int N>
void print(T t)
{
    cout << t * N << endl;
}

void test1()
{
    // 显式实例化
    print<int,10>(3); // T=int N=10
    // 隐式实例化
    /* print(3);//没有指定N的值 error */

}

// 使用默认值
template <typename T = int, int N = 10>
void print2(T t)
{
    cout << t * N << endl;
}

void test2()
{
    // 隐式实例化OK N有默认值
    print2(3);
    // 显式实例化
    print2<double>(3.14);
    print2<double, 100>(3.14);
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

