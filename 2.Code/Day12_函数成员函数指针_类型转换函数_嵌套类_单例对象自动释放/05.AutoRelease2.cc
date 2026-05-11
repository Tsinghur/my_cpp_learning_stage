#include <iostream>

using std::cout;
using std::endl;

// 方式二: 利用嵌套类 + 静态的内部类对象

class Singleton {
    // 内部类
    class AutoRelease {
    public:
        AutoRelease() {
            cout << "AutoRelease()" << endl;
        }
        
        ~AutoRelease() {
            if (m_pInstance) { // 内部类中可直接访问外部类的静态成员
                delete m_pInstance;
                m_pInstance = nullptr;
            }
            cout << "~AutoRelease()" << endl;
        }
    };
public:
    static Singleton* getInstance() {
        if (!m_pInstance) {
            m_pInstance = new Singleton();
        }
        return m_pInstance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    // 管理类中删除Singleton单例对象时一定会触发~Single()，而它是私有成员
    friend class AutoRelease; // 本身就可以作为一个类的前向声明
private:
    Singleton() {}
    ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                    // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
    static Singleton* m_pInstance;
    static AutoRelease m_autoRelease; // 内部类对象作为外部类成员 静态对象
};
Singleton* Singleton::m_pInstance = nullptr;
Singleton::AutoRelease Singleton::m_autoRelease; // 调用了AutoRelease的无参构造函数

int main() {
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;

    return 0;
}
