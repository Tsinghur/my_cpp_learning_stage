#include "3.externA.hpp"
#include <iostream>
using namespace std;

// 全局变量 & 函数定义
int val = 100;
void display() {
    cout << "全局 display()" << endl;
}

// 命名空间 wd 定义
namespace wd
{
    int val = 300;
    void display() {
        cout << "wd::display()" << endl;
    }
}
