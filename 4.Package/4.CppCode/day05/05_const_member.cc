#include <iostream>

using std::cout;
using std::endl;

/*
 * 特殊的数据成员:
 * 1.常量const数据成员
 * 2.引用数据成员
 * 3.对象数据成员
 * 4.静态数据成员
 *
 * const数据成员必须要进行初始化,要在初始化列表中进行初始化,
 * 如果类中有多个构造函数,所有的构造函数中都要进行初始化
 *
 * 
 */
class MyClass
{
public:
    MyClass()
    : m_data2(10)
    {}

    MyClass(int data1)
    : m_data1(data1)
    , m_data2(100)
    {}
    int m_data1;

    // 常量数据成员
    const int m_data2 = 20;
    // C++11后声明时候可以直接赋值 默认值
};

void test1()
{
    const int num = 1;
    /* num = 2; */
    cout << num << endl;

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

