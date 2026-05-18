#include <iostream>

using std::cout;
using std::endl;

/*
 *
 * 布尔类型: bool 当成基本数据类型对待
 *
 * true : 1 
 * false : 0
 *
 * bool可以和数值类型的数据进行转换
 */
void test1()
{
    bool flag1 = true;
    bool flag2 = false;
    cout << flag1 << endl;// 1 并不会打印"true"
    cout << flag2 << endl;// 0
}

void test2()
{
    // 数值类型和bool之间转换
    // 只有0是false, 其他正整数,负数,小数全都是true
    bool b1 = 1;
    bool b2 = 0;
    bool b3 = 100;
    bool b4 = -100;
    bool b5 = 3.14;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;
    cout << b5 << endl;
}

void test3()
{
    // 大小为1个字节
    bool flag = true;
    cout << sizeof(flag) << endl; // 1
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

