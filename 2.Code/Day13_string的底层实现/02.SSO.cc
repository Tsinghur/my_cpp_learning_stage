#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char* pStr) {
        m_size = strlen(pStr);
        if (m_size < 16) {
            strcpy(m_buffer.m_local, pStr);
            m_capacity = 16;
        } else {
            m_buffer.m_pointer = new char[m_size + 1]{};
            strcpy(m_buffer.m_pointer, pStr);
            m_capacity = m_size + 1;
        }
    }
    ~String() {
        if (m_size >= 16) {
            delete[] m_buffer.m_pointer;
            m_buffer.m_pointer = nullptr;
        } else {
            bzero(m_buffer.m_local, 16);
        }
    }
    
    char& operator[](size_t idx) {
        if (idx >= m_size) {
            cout << "idx is illegal" << endl;
            static char nullChar = '\0';
            return nullChar;
        }
        if (m_size < 16) {
            return m_buffer.m_local[idx];
        } else {
            return m_buffer.m_pointer[idx];
        }
    }

    friend
    ostream& operator<<(ostream& os,const String& rhs);
private:
	union Buffer{
		char * m_pointer;
		char m_local[16];
	};
	size_t m_size;
	size_t m_capacity;
    Buffer m_buffer;
};

ostream& operator<<(ostream& os,const String& rhs) {
    if (rhs.m_size < 16) {
        os << rhs.m_buffer.m_local;
    } else {
        os << rhs.m_buffer.m_pointer;
    }
    return os;
}

void test1() {
    String str1("hello");
    String str2("hello,world!!!!!");
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str2[6] : " << str2[6] << endl;
    str1[0] = 'w';
    str2[6] = 'h';
    cout << "after str1[0] = 'w' and str2[6] = 'h' : " << endl;
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str2[6] : " << str2[6] << endl;
}

int main() {
    test1();

    return 0;
}
