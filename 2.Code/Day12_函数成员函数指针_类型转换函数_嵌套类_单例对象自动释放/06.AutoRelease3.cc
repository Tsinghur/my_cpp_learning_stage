#include <iostream>

using std::cout;
using std::endl;

// 方式三: 利用atexit() + destroyInstance()
/*
 * atexit(函数指针): 把函数指针指向的函数注册到atexit当中
 * 参数的这个函数是一个回调函数
 * 当程序结束时, 被注册到atexit当中的函数被自动调用
 *
 * 单例的两种模式:
 * 1.懒加载(懒汉模式): 不用的时候不创建, 用的时候再创建
 * 2.立即加载(饿汉模式) : 不管用不用这个单例对象, 先把这个单例对象
 * 创建出来,用的时候给你返回
 */

class Singleton {
public:
    // 由于这是单例模式，所以构造函数是万万不能重载的
    /* Singleton() { */
    /*     cout << "Singleton()" << endl; */
    /* } */
    static Singleton* getInstance() {
        if (!m_pInstance) {
            m_pInstance = new Singleton();
            /* atexit(destroyInstance); // right */
            atexit(&destroyInstance); // 注册几次，程序结束时调用几次
        }
        return m_pInstance;
    }
    static void destroyInstance() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
        cout << "destroyInstance()" << endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton() {}
    ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                    // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
    static Singleton* m_pInstance;
};
Singleton* Singleton::m_pInstance = nullptr; // 懒加载
/* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */


int main() {
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    return 0;
}
