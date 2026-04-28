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
    cout << "局部常量：\n" << &const_local << endl;
    cout << "全局常量：\n" << &const_global << endl;
    /* const char* s = "hello"; */
    /* cout << "常量：\n" << &s << endl; */
    void (*func_p)() = &test;
    printf("函数地址：\n%p\n", func_p);

    return 0;
}
