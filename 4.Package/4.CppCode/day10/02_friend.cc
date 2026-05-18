#include <iostream>

using std::cout;
using std::endl;

/*
 * friend友元 :
 * 1.普通函数的友元形式(友元函数)
 * 2.成员函数的友元形式(把成员函数声明为友元)
 * 3.友元类(把类声明为友元)
 *
 */
class MyClass
{
public:
    int getData()
    {
        return m_data;
    }
    // 把普通函数test1声明为友元
    friend void test1();
private:
    friend void test2();
    int m_data = 1;
};

void test1()
{
    MyClass obj;
    cout << obj.m_data << endl;
}
void test2()
{
    MyClass obj;
    cout << obj.m_data << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

