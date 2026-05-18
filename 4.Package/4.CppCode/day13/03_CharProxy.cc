#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
    // 定义一个内部类CharProxy 帮CowString进行读写区分
    class CharProxy
    {
    public:
        CharProxy(CowString& cow, int index)
        : m_self(cow)
        , m_index(index)
        {

        }

        // operator <<
        // cout << s[0]; 对CowString对象调用operator[]-->
        // -->CharProxy对象-->m_self--->m_pStr --> char
        friend
        ostream & operator<<(ostream & os, const CharProxy & rhs);

        // operator =
        // s[0] = 'A' CowString对象调用operator[]-->CharProxy对象
        // -->m_self--->m_pStr[m_index]
        char & operator=(const char & ch)
        {
            if(m_index < 0 || m_index >= strlen(m_self.m_pStr))
            {
                static char nullChar = '\0';
                return nullChar;
            }else{
                // 获取引用计数 是否大于1
                // 如果大于1 说明有共享
                if(m_self.getRefCount() > 1){
                    // 当前的引用计数-1
                    m_self.decrementRefCount();
                    // 再进行深拷贝
                    char * temp = new char[4 + strlen(m_self.m_pStr) + 1]{} + 4;
                    strcpy(temp, m_self.m_pStr);
                    // 更改底层指针 指向新空间
                    m_self.m_pStr = temp;
                    // 新的空间的引用计数初始化为1
                    m_self.initRefCount();
                }
                // 赋值字符
                m_self.m_pStr[m_index] = ch;
                // 返回字符
                return m_self.m_pStr[m_index];
        }

        }
    private:
        CowString & m_self; // 记录当前字符串对象的状态
        int m_index; // 记录访问的数组的下标
    };
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

#if 0
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
    // 无法区分读写操作
#endif

    // operator []
    CharProxy operator[](int index)
    {
        return CharProxy{*this, index};
    };


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

    friend
    ostream & operator<<(ostream & os, const CowString::CharProxy & rhs);
};

// operator << 
ostream & operator<<(ostream & os, const CowString & rhs)
{

    os << rhs.m_pStr;
    return os;
}

// CharProxy 类的operator<<
ostream & operator<<(ostream & os, const CowString::CharProxy & rhs)
{

    os << rhs.m_self.m_pStr[rhs.m_index];
    return os;
}

void test1()
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
    s1[0] = 'A';
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

