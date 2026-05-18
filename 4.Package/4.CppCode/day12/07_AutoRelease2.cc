#include <iostream>

using std::cout;
using std::endl;

/* 单例的自动释放:
 * 方式二: 利用嵌套类 + 静态的内部类对象
 *
 *
 */
class Singleton
{
    // 内部类
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(m_pInstance){
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };
public:
    // 提供静态函数返回唯一的对象
    static Singleton * getInstance()
    {
        if(!m_pInstance){
            m_pInstance = new Singleton{};
        }
        return m_pInstance;
    }
    // 提供回收资源的操作
    /* static void destroyInstance() */
    /* { */
    /*     if(m_pInstance){ */
    /*         delete m_pInstance; */
    /*         m_pInstance = nullptr; */
    /*     } */
    /* } */
    // 删除复制控制相关的函数
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    // 把这个管理者类设置为友元
    friend class AutoRelease;
private:
    Singleton(){}
    ~Singleton(){}
    static Singleton * m_pInstance;
    // 内部类对象作为外部类成员 静态对象
    static AutoRelease m_autoRelease;
};

// 静态成员类外初始化
Singleton * Singleton::m_pInstance = nullptr;

Singleton::AutoRelease  Singleton::m_autoRelease; // 默认调用无参构造函数
                                                  // 默认初始化


void test1()
{
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

