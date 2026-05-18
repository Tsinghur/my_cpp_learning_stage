#include <iostream>

using std::cout;
using std::endl;

/* 单例的自动释放:
 * 方式三: 利用atexit() + destroyInstance()
 *
 * atexit(函数指针): 把函数指针指向的函数注册到atexit当中
 * 参数的这个函数是一个回调函数
 * 当程序结束时, 被注册到atexit当中的函数被自动调用
 *
 * 单例的两种模式:
 * 1.懒加载(懒汉模式): 不用的时候不创建, 用的时候再创建
 * 2.立即加载(饿汉模式) : 不管用不用这个单例对象, 先把这个单例对象
 * 创建出来,用的时候给你返回
 */
class Singleton
{
public:
    // 提供静态函数返回唯一的对象
    static Singleton * getInstance()
    {
        if(!m_pInstance){
            m_pInstance = new Singleton{};
            // 把destroyInstance函数注册到atexit中
            atexit(&destroyInstance);
        }
        return m_pInstance;
    }

    /* static Singleton * getInstance() */
    /* { */
    /*     return m_pInstance; */
    /* } */

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
};

// 静态成员类外初始化
// 懒加载
Singleton * Singleton::m_pInstance = nullptr;
// 立即加载
/* Singleton * Singleton::m_pInstance = new Singleton{}; */


void func()
{
    cout << "func()" << endl;
}
void func2()
{
    cout << "func2()" << endl;
}

void test0()
{
    cout << "test0 start" << endl;
    /* func(); */
    // 把func注册到atexit中
    atexit(&func);
    atexit(&func);
    atexit(&func2);
    // 先注册的后执行
    cout << "test0 end" << endl;
}

void test1()
{
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
    cout << Singleton::getInstance() << endl;
}

int main(int argc, char * argv[])
{
    cout << "main statr" << endl;
    /* test0(); */
    test1();
    cout << "main end" << endl;
    return 0;
}

