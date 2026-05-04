#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton *getInstance() { // 提供一个静态方法返回静态对象
        if (ms_instance == nullptr) {
            ms_instance = new Singleton(); // 在堆上创建对象
        }
        return ms_instance;
    }
    static void destroyInstance() { // 提供一个静态方法来销毁对象 释放空间
        if (ms_instance != nullptr) {
            delete ms_instance;
            ms_instance = nullptr;
        }
    }
    void func() {
        cout << "func()" << endl;
    }
private:
    static Singleton *ms_instance; // 提供静态的自身类型的指针 指向唯一的实例
    Singleton() { // 构造函数私有 确保不能在外部创建对象
        cout << "default constructor" << endl;
    }
    ~Singleton() { // 析构函数私有 避免外部删除对象
        cout << "destructor" << endl;
    }
    // C++11之前可以将拷贝构造和赋值运算符函数设置为private
    // C++11以后可以删除类中的成员函数来避免外部复制对象 保证单例
    Singleton(const Singleton &) = delete; // 删除拷贝构造函数
    Singleton &operator=(const Singleton &) = delete; // 删除赋值运算符函数
};
Singleton *Singleton::ms_instance = nullptr; // 类中静态成员指针初始化为nullptr

int main() {
    Singleton *instance1 = Singleton::getInstance();
    cout << instance1 << endl;
    Singleton *instance2 = Singleton::getInstance();
    cout << instance2 << endl; // 地址相同
    Singleton::getInstance()->func(); // 单例对象的使用规范 避免多个指针拥有单例对象的管理权

    Singleton::destroyInstance();
    Singleton::destroyInstance(); // 多次destroy也不会double free
    return 0;
}

