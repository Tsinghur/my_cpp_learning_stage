#include <iostream>

using std::cout;
using std::endl;

/* 单例的自动释放:
 * 方式一: 利用栈对象的生命周期进行自动释放
 *
 * 把单例对象作为资源,交给另一个对象来管理(管理者对象,MiddleLayer)
 *
 */
class Singleton
{
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
};

// 静态成员类外初始化
Singleton * Singleton::m_pInstance = nullptr;


// 管理者类
class AutoRelease
{
public:
    AutoRelease(Singleton * p)
    : m_p(p)
    {
        cout << "AutoRelease(Singleton*)" << endl;
    }

    // 析构函数
    ~AutoRelease()
    {
        cout << "~AutoRelease()" << endl;
        if(m_p){
            delete m_p;
            m_p = nullptr;
        }
    }
private:
    // 定义一个资源类型的指针 去指向所管理的资源
    Singleton * m_p;
};

void test1()
{
    // 创建管理者对象(栈对象)
    AutoRelease ar { Singleton::getInstance() };
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

