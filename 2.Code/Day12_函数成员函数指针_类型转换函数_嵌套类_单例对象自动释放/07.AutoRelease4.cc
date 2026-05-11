#include <pthread.h>    // for pthread_once
#include <cstdlib>      // for atexit
#include <iostream>

using std::cout;
using std::endl;

// 方式四: 利用atexit() + destroyInstance() + pthread_once
// 线程安全

class Singleton {
public:
    static Singleton* getInstance() {
        /* if (!m_pInstance) */
        pthread_once(&m_once_control, &initRoute); // pthread_once可以确保这个函数只会执行一次
        return m_pInstance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    static void initRoute() {
        // 初始化只会被执行一次
        m_pInstance = new Singleton();
        atexit(&destroyInstance);
    }
    static void destroyInstance() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
        cout << "destroyInstance()" << endl;
    }
    Singleton() {}
    ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                    // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
    static Singleton* m_pInstance;
    static pthread_once_t m_once_control;
};
Singleton* Singleton::m_pInstance = nullptr; // 懒加载
/* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */
pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;

int main() {
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    return 0;
}
