#include "3.externA.hpp"   // 必须包含头文件！
#include <iostream>
using namespace std;

// 全局变量、函数声明
extern int val;
void display();

// 命名空间声明
namespace wd
{
    extern int val;
    void display();
}
// test0：直接访问 → 全局
void test0() {
    cout << "test0:" << val << endl;
    display();
}

// test1：加命名空间限定 → wd 里的实体
void test1() {
    cout << "\ntest1:" << wd::val << endl;
    wd::display();
}

// test2：using namespace 会冲突（编译报错）
void test2() {
    using namespace wd;
    // cout << val << endl;  // 报错：二义性
    // display();            // 报错：二义性
}

// test4：局部 using 声明 → 屏蔽全局，使用 wd
void test4() {
    using wd::val;
    using wd::display;
    /* 报错： using namespace wd; */
    
    cout  << "\ntest4:" << val << endl;   // 300
    display();             // wd::display()
}

int main() {
    test0();
    test1();
    /* test2(); */
    test4();
    return 0;
}
