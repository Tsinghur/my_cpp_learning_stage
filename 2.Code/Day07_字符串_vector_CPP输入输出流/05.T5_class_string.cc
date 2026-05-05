#include <string.h>
#include <iostream>

using namespace std;

class String {
public:
    String() {
        m_str = new char[1]{};
        cout << "String()" << endl;
    }
    String(const char *str) 
        : m_str(new char[strlen(str) + 1]{})
        {
            strcpy(m_str, str);
            cout << "String(const char*)" << endl;
        }
    String(const String &rhs) 
        : m_str(new char[strlen(rhs.m_str) + 1]{})
        {
            strcpy(m_str, rhs.m_str);
            cout << "String(const String&)" << endl;
        }
    String &operator=(const String &rhs){
        if (this != &rhs) { // 避免自赋值出错
            if (m_str) {
                delete [] m_str;
                m_str = nullptr;
            }
            m_str = new char[strlen(rhs.m_str) + 1]{};
            strcpy(m_str, rhs.m_str);
            cout << "String& operator=" << endl;
        }

        return *this;
    }
    ~String() {
        if (m_str != nullptr) { // 其实无需判断，对象创建起码也会指向一块堆内存（1字节的'\0'）
            delete [] m_str;
        }
        cout << "~String()" << endl;
    };
    void print() const {
        cout << m_str << endl;
    };
    String& append(const String & rhs) {
        if (m_str) {
            char* new_str = new char[length() + strlen(rhs.m_str) + 1]{};
            strcpy(new_str, m_str);
            delete [] m_str;
            m_str = new_str;
        }
        strcpy(m_str + length(), rhs.m_str);

        return *this;
    }
    String& append(const char * str) {
        if (m_str) {
            char* new_str = new char[length() + strlen(str) + 1]{};
            strcpy(new_str, m_str);
            delete [] m_str;
            m_str = new_str;
        }
        strcpy(m_str + length(), str);

        return *this;
    }
    size_t length() const {
        return strlen(m_str);
    }
    const char * c_str() const {
        return m_str;
    }
private:
    char * m_str;
};

int main() {
    String str1;
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    str2.print();		
    str3.print();	

    String str4 = str3;
    str4.print();

    str4 = str2;
    str4.print();

    return 0;
}
