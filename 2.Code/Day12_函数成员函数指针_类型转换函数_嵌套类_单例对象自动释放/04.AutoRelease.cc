#include <iostream>

using std::cout;
using std::endl;

// 方式一: 利用栈对象的生命周期进行自动释放

class Singleton {
public:
    static Singleton* getInstance() {
        if (!m_pInstance) {
            m_pInstance = new Singleton();
        }
        return m_pInstance;
    }
    /* static void destroyInstance() { */
    /*     if (m_pInstance) { */
    /*         delete  m_pInstance; */
    /*         m_pInstance = nullptr; */
    /*     } */
    /* } */
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // 管理类中删除Singleton单例对象时一定会触发~Single()，而它是私有成员
    friend class AutoRelease; // 本身就可以作为一个类的前向声明
private:
    Singleton() {}
    ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                    // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
    static Singleton* m_pInstance;
};
Singleton* Singleton::m_pInstance = nullptr;

// 管理者类
class AutoRelease {
public:
    AutoRelease(Singleton* p)
    : m_p(p)
    {
        cout << "AutoRelease(Singleton*)" << endl;
    }
    ~AutoRelease() {
        if (m_p) {
            delete m_p;
            m_p = nullptr;
        }
        cout << "~AutoRelease()" << endl;
    }
private:
    Singleton* m_p;
};

int main() {
    AutoRelease ar(Singleton::getInstance()); // 创建管理者对象(栈对象)
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    return 0;
}
