#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

/* 单例的自动释放:
 * 方式四: 利用atexit() + destroyInstance() + pthread_once
 * 线程安全的
 *
 */
class Singleton
{
public:
    // 提供静态函数返回唯一的对象
    static Singleton * getInstance()
    {
        // 执行初始化的那个函数
        pthread_once(&m_once_control,&initRoutine);
        return m_pInstance;
    }

    // 提供一个用来初始化的函数
    static void initRoutine()
    {
        // 初始化只会被执行一次
        m_pInstance = new Singleton{};
        atexit(&destroyInstance);
    }
    // 提供回收资源的操作
    static void destroyInstance()
    {
        cout << "destroyInstance" << endl;
        if(m_pInstance){
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }
    // 删除复制控制相关的函数
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;

    // 把这个管理者类设置为友元
    friend class AutoRelease;
private:
    Singleton(){}
    ~Singleton(){}
    static Singleton * m_pInstance;
    static pthread_once_t m_once_control;
};

// 静态成员类外初始化
Singleton * Singleton::m_pInstance = nullptr;

pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;


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

