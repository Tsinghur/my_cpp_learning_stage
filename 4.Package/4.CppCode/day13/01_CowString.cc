#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
public:
    // no arg constructor
    CowString()
    : m_pStr(new char[4 + 1]{} + 4)
    {
        // 初始化引用计数器为1
       /* *(int*)(m_pStr - 4) = 1; */
        // 替换成函数调用
        initRefCount();
    }
    // arg constructor
    CowString(const char * pStr)
    : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4)// 让底层指针指向字符数据部分
    {
        // 初始化引用计数器为1
       /* *(int*)(m_pStr - 4) = 1; */
        initRefCount();
       // 数据复制
       strcpy(m_pStr, pStr);
    }

    // destructor
    ~CowString()
    {
        // 引用计数-1
        decrementRefCount();
        // 判断引用计数和0 的关系
        // 如果为0, 说明没有字符串对象引用这个空间了
        if(getRefCount() == 0){
            // 进行回收
            delete [] (m_pStr - 4);
            cout << "release heap====>" << endl;
        }
        // 如果不为0 啥也不干 将指针设置为空
        m_pStr = nullptr;

    }

    // copy constructor
    CowString(const CowString & rhs)
    : m_pStr(rhs.m_pStr)// 深拷贝-->浅拷贝 共享空间
    {
        // 引用计数+1
        /* ++*(int*)(m_pStr - 4); */
        incrementRefCount();
    }

    // operator << 
    friend
    ostream & operator<<(ostream & os, const CowString & rhs);

    // operator =
    CowString & operator=(const CowString & rhs)
    {
        // 自赋值判断
        if(this != &rhs){
            // 引用计数-1
            decrementRefCount();
            // 获取引用计数 判断和0的关系
            if(getRefCount() == 0){
                // 如果为0 回收原本空间
                delete [] (m_pStr - 4);
                cout << "release heap=====>" << endl;
            }
            // 让当前对象的字符指针指向新空间
            m_pStr = rhs.m_pStr;
            // 新空间的引用计数+1
            incrementRefCount();
        }
        // 返回当前对象*this
        return  *this;
    }

# if 0
    // operator []
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr)){
            cout << "index is illegal" << endl;
            // throw "index is illegal";
            static char nullChar = '\0';
            return nullChar;
        }else{
            return m_pStr[index];
        }   
    }
    // 通过下标访问index位置的字符没问题
    // 但是有共享时,修改会对其他的string对象产生影响
#endif

    // operator []
    char & operator[](int index)
    {
        if(index < 0 || index >= strlen(m_pStr))
        {
            static char nullChar = '\0';
            return nullChar;
        }else{
            // 获取引用计数 是否大于1
            // 如果大于1 说明有共享
            if(getRefCount() > 1){
                // 当前的引用计数-1
                decrementRefCount();
                // 再进行深拷贝
                char * temp = new char[4 + strlen(m_pStr) + 1]{} + 4;
                strcpy(temp, m_pStr);
                // 更改底层指针 指向新空间
                m_pStr = temp;
                // 新的空间的引用计数初始化为1
                initRefCount();
            }
            
            // 返回字符
            return m_pStr[index];
        }
    }

    // 用于获取字符串长度的方法
    int size()
    {
        return strlen(m_pStr);
    }
    // 返回C风格字符串
    char * c_str()
    {
        return m_pStr;
    }

    // 获取引用计数
    int getRefCount()
    {
        return *(int*)(m_pStr - 4);
    }
private:
    // 封装一些代码片段作为函数 方便使用
    // 初始化引用计数器
    void initRefCount()
    {
       *(int*)(m_pStr - 4) = 1;
    }
    // 引用计数+1
    void incrementRefCount()
    {

       ++*(int*)(m_pStr - 4);
    }
    // 引用计数-1
    void decrementRefCount()
    {

       --*(int*)(m_pStr - 4);
    }

    // pointer to char array
    char * m_pStr;
};

// operator << 
ostream & operator<<(ostream & os, const CowString & rhs)
{

    os << rhs.m_pStr;
    return os;
}

// 测试的是构造函数
void test1()
{
    CowString s1;
    CowString s2{"abc"};
    cout << s1 << endl;
    cout << s2 << endl;
}

// 测试拷贝构造函数
void test2()
{
    CowString s1{"abc"};

    cout << "s1 refCount:" << s1.getRefCount() << endl;
    cout << "-------" << endl;
    CowString s2 = s1; // 调用拷贝构造函数

    cout << s1 << endl;
    cout << s2 << endl;
    cout << "s1 refCount:" << s1.getRefCount() << endl;
    cout << "s2 refCount:" << s2.getRefCount() << endl;
}

// 测试析构函数
void test3()
{
    // 没有共享
    CowString s1{"abc"};
    cout << s1 << endl;
    cout << "-----" << endl;
    // 共享的情况
    CowString s2{"hello"};
    CowString s3 = s2;
    cout << "s2:" << s2 << endl;
    cout << "s3:" << s3 << endl;
    cout << "s2 cout:" << s2.getRefCount() << endl;
    cout << "s3 cout:" << s3.getRefCount() << endl;
}

// 测试对象的赋值操作
void test4()
{
    CowString s1{"abc"};
    CowString s2 = s1;
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    cout << "s1 cout:" << s1.getRefCount() << endl;
    cout << "s2 cout:" << s2.getRefCount() << endl;

    CowString s3{"bcd"};
    cout << "s3:" << s3 << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
    cout << "--------" << endl;
    s1 = s3;
    cout << "s1:" << s1 << endl;
    cout << "s1 cout:" << s1.getRefCount() << endl;
    cout << "s2 cout:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
    cout << "-----" << endl;
    s2 = s3;
    cout << "s2:" << s2 << endl;
    cout << "s2 cout:" << s2.getRefCount() << endl;
    cout << "s3 count:" << s3.getRefCount() << endl;
}

void test5()
{
    // 此时底层数组空间没有共享 --->OK的
    // 如果发生了共享
    CowString s1{"abc"};
    CowString s2 = s1;
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;
    cout << s1[0] << endl;
    /* s1[0] = 'A'; */
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;

}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();
    return 0;
}

