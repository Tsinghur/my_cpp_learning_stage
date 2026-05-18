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
class MyClass;

class FriendClass
{
public:
    // 函数声明
    void func(const MyClass & obj);
    void func2(const MyClass & obj);
    void func3(const MyClass & obj);
};

class MyClass
{
public:
    int getData()
    {
        return m_data;
    }
    /* friend */
    /* void FriendClass::func(const MyClass & obj); */

    /* friend */
    /* void FriendClass::func2(const MyClass & obj); */

    /* friend */
    /* void FriendClass::func3(const MyClass & obj); */

    // 把FriendClass声明为友元 好朋友
    friend class FriendClass;

private:
    int m_data = 1;
};

// FriendClass 中func的实现
void FriendClass::func(const MyClass & obj)
{
    obj.m_data;
}
void FriendClass::func2(const MyClass & obj)
{
    obj.m_data;
}
void FriendClass::func3(const MyClass & obj)
{
    obj.m_data;
}

void test1()
{
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

