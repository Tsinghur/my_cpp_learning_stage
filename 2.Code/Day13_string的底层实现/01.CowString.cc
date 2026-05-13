#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString {
private:
    class CharProxy {
    public:
        CharProxy(CowString& cowString, int index) 
        : m_self(cowString)
        , m_index(index)
        {
            /* cout << "CharProxy(CowString&, size_t)" << endl; */ 
        }

        friend ostream& operator<<(ostream& os, const CharProxy& proxy);

        char& operator=(const char& ch) {
            if (m_index < 0 || m_index >= m_self.size()) {
                cout << "index is illegal" << endl;
                static char nullChar = '\0';
                return nullChar;
            } else {
                if (m_self.getRefCount() > 1) {
                    m_self.decrementRefCount();
                    char* tmp = new char[4 + m_self.size() + 1]{} + 4;
                    strcpy(tmp, m_self.m_pStr);
                    m_self.m_pStr = tmp;
                    m_self.initRefCount();
                }
                m_self.m_pStr[m_index] = ch;
                return m_self.m_pStr[m_index];
            }
        }
    private:
        CowString& m_self;
        int m_index;
    }; // class CharProxy
public:
    CowString()
    : m_pStr(allocate())
    {
        initRefCount();
        cout << "CowString()" << endl;
    }
    CowString(const char* pStr) 
    : m_pStr(allocate(pStr))
    {
        strcpy(m_pStr, pStr);
        initRefCount();
        cout << "CowString(const char*)" << endl;
    }
    CowString(const CowString& rhs) // 这里是拷贝构造，即已经存在一个对象
    : m_pStr(rhs.m_pStr) // 在这里应该使用浅拷贝
    {
        // 错误：使用浅拷贝而不是深拷贝
        /* strcpy(m_pStr, rhs.m_pStr); */
        /* initRefCount(); */
        incrementRefCount();
        cout << "CowString(const CowString&)" << endl;
    }
    CowString& operator=(const CowString& rhs) {
        if (&rhs != this) {
            /* decrementRefCount(); */
            /* if (getRefCount() == 0) { */
            /*     delete[] (m_pStr - 4); // 应该先将指针向左偏移4个字节，因为这才是申请空间的基地址 */
            /* cout << "---release heap---" << endl; */
            /* } */
            /* m_pStr = nullptr; */
            release();
            // 错误：不应该深拷贝，而是应该直接共享即可
            /* char* tmp = allocate(rhs.m_pStr); */
            /* strcpy(tmp, rhs.m_pStr); */
            /* m_pStr = tmp; */
            m_pStr = rhs.m_pStr;
            incrementRefCount();
        }
        cout << "operator=(const CowString&)" << endl;
        return *this;
    }
    ~CowString() {
        /* decrementRefCount(); */
        /* if (getRefCount() == 0) { */
        /*     delete[] (m_pStr - 4); */
        /*     cout << "---release heap---" << endl; */
        /* } */ 
        /* m_pStr = nullptr; */
        release();
    }

    friend ostream& operator<<(ostream& os, const CowString& rhs);

    /* char& operator[](int index); */
    CharProxy operator[](int index) {
        return {*this, index};
    }

    // 常量对象只能调用常量版本的成员函数（这里体现在函数名之后的const）
    const char& operator[](int index) const {
        if (index < 0 || index >= size()) {
            static char nullChar = '\0';
            return nullChar;
        }
        return m_pStr[index];
    }

    // 不仅在内部类中声明友元，还要在外部类中声明友元
    // 因为函数中所使用的CharProxy类，是位于外部类中的私有成员
    friend ostream& operator<<(ostream& os, const CharProxy& proxy);

    int size() const { // 数组大小、sizeof()返回值标准就是size_t
        return strlen(m_pStr);
    }

    const char* c_str() const {
        return m_pStr;
    }
    // 获取引用计数
    int getRefCount() {
        return *(int*)(m_pStr - 4);
    }
private:
    char* m_pStr;
    // 引用计数相关操作
    // 初始化引用计数
    void initRefCount() {
        *(int*)(m_pStr - 4) = 1;
    }
    // 引用计数+1
    int incrementRefCount() {
        return ++*(int*)(m_pStr - 4);
    }
    // 引用计数-1
    int decrementRefCount() {
        return --*(int*)(m_pStr - 4);
    }
    // 初始化列表中分配字符数组指针空间
    char* allocate(const char* pStr = nullptr) {
        if (!pStr) { // 无参构造中使用
            return new char[4 + 1]{} + 4;
        } else { // C风格字符串构造中使用
            return new char[4+ strlen(pStr) + 1]{} + 4;
        }
    }
    // 可以将析构函数中内容抽取到CowString类的release方法中，进行复用
    void release() {
        // 引用计数-1
        decrementRefCount();
        if (getRefCount() == 0) {
            // 引用计数为0 删除空间
            delete [] (m_pStr - 4);
            cout << "---release heap---" << endl;
        }
        m_pStr = nullptr;
    }
};

ostream& operator<<(ostream& os, const CowString& rhs){
    os << rhs.m_pStr;
    return os;
} 

ostream& operator<<(ostream& os, const CowString::CharProxy& proxy) {
    if (proxy.m_index < 0 || proxy.m_index >= proxy.m_self.size()) {
        os << "index is illegal";
    } else {
        os << proxy.m_self.m_pStr[proxy.m_index];
    }
    return os;
}

void test1() {
    CowString s1{"abc"};
    cout << "before operator= : " << endl;
    cout <<"s1:" <<  s1 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    CowString s2 = s1;
    cout << "after copy structor : " << endl;
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
    cout << "----------" << endl;
    cout << "before operator= : s1[0] = " << s1[0] << endl;
    s1[0] = 'A';
    cout << "after operator= : s1[0] = " << s1[0] << endl;
    cout <<"s1:" <<  s1 << endl;
    cout <<"s2:" <<  s2 << endl;
    cout << "s1 count:" << s1.getRefCount() << endl;
    cout << "s2 count:" << s2.getRefCount() << endl;
}

int main() {
    test1();

    return 0;
}
