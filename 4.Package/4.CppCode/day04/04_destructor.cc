#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 析构函数destructor: 特殊的成员函数
 * 作用: 对象销毁时会自动调用该函数
 * 语法:
 * ~类名(){
 *   析构函数体
 *   释放资源的操作
 * }
 *
 * 资源: 
 * 内存资源
 * 网络资源
 * 文件资源
 * 数据连接
 *
 *
 * 析构函数的调用时机:(生命周期)
 * 1.局部对象: 离开局部作用域
 * 2.全局对象: 程序结束时
 * 3.静态对象: 同上
 * 4.堆上对象: !!需要手动delete指针
 */
class Computer
{
public:
    Computer(const char * brand, int price)
    : m_brand(new char[strlen(brand)+ 1]{})
    , m_price(price)
    {
        cout << "constructor" << endl;
        strcpy(m_brand, brand);
    }
    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }
    /* void release() */
    /* { */
    /*     if(m_brand){ */
    /*         delete [] m_brand; */
    /*         m_brand = nullptr; */
    /*     } */
    /* } */

    // destructor
    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(m_brand){
            delete [] m_brand;
            m_brand = nullptr;
        }

    }
private:
    char * m_brand;
    int m_price;
};

void test1()
{
    // 局部对象
    Computer pc { "xiaomi", 1999 };
    pc.print();
    /* pc.~Computer();// 手动调用析构函数,不要这样写 */
                   // 一般让析构函数自动去执行
}

// 全局对象
/* Computer pc{"apple",9999}; */

void test2()
{
    cout << "test2 start" <<  endl;
    // 静态对象
    static Computer pc { "apple", 9999 };
    cout << "test2 end" <<  endl;
}

void test3()
{
    // 堆上对象
    /* int * p = new int{1}; */
    Computer * p = new Computer{"xiaomi", 1999};
    // 通过指针->访问成员
    p->print();
    /* p->m_brand; */
    // delete指针时会调用析构函数
    delete p;
    p = nullptr;
}

int main(int argc, char * argv[])
{
    /* cout << "main start" << endl; */
    /* test1(); */
    /* test2(); */
    test3();
    /* cout << "main end" << endl; */
    return 0;
}

