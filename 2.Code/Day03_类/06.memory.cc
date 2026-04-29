#include <iostream>

using namespace std;

int global = 10;
static int static_global = 20;

const int const_global = 111;

void test() {
    int local_a = 1;
    int local_b = 2;

    int* heap = new int[10]();
    
    static int static_local = 30;


    cout << "test函数局部变量：\n" << &local_a << endl << &local_b << endl;
    cout << "动态分配堆区空间：\n" << heap << endl;
    cout << "全局变量：\n" << &global << endl;
    cout << "静态全局变量：\n" << &static_global << endl;
    cout << "静态局部变量：\n" << &static_local << endl;
}

int main() {
    int stack_a = 1;
    int stack_b = 2;
    cout << "main函数局部变量：\n" << &stack_a << endl << &stack_b << endl;

    test();

    const int const_local = 40;
    cout << "局部常量：\n" << &const_local << endl; // 所有非静态的局部变量（包括局部常量）都存储在栈区
    cout << "全局常量：\n" << &const_global << endl;
    const char* s = "hello";
    /* cout << "字符串字面量：\n" << &s << endl; // 这样打印的是指针s的地址，不是字符串的地址 */
    // 打印字符串字面量 "hello" 的实际存放地址，应该输出 s 的值（即指针指向的地址）
    // 需要强制转成 void* 避免 cout 直接输出字符串内容：
    cout << "字符串字面量：\n" << static_cast<const void*>(s) << endl;
    void (*func_p)() = &test;
    printf("函数地址：\n%p\n", func_p);

    return 0;
}
