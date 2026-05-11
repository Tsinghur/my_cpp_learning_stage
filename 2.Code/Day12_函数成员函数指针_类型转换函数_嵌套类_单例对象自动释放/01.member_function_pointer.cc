#include <iostream>

using std::cout;
using std::endl;

class FFF {
public:
    void func() {
        cout << "---func---" << endl;
    }
private:

    
};

void func1() {
    cout << "---func1---" << endl;
}

void func2() {
    cout << "---func2---" << endl;
}

// 普通函数指针
void test1() {
    func1();
    // 简写写法
    void (*f)() = func1;
    f();
    // 完整写法
    f = &func2;
    (*f)(); // func2(); 
    // 定义一个别名
    typedef void (*F)();
    F ff = &func1;
    ff();
    using FF = void (*)();
    FF fff = &func2;
    fff();
}

// 成员函数指针
// 非静态成员函数—— 常规情况下不可以直接调用
// 因为调用它必须绑定一个具体的对象，用来初始化隐式的 this 指针
// 其实也可以通过空指针来调用，但是不应该在程序中这样做
void test2() {
    /* FFF::func(); // error */
}

int main() {
    /* test1(); */
    test2();

    return 0;
}
