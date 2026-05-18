#include <string.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 定义一个字符数组类CharArray

class CharArray
{
public:
    // constructor
    CharArray(const char * pstr)
    : m_pstr(new char[strlen(pstr) + 1]{})
    , m_size(strlen(pstr))
    {
        cout << "constructor" << endl;
        strcpy(m_pstr, pstr);
    }

    // destructor
    ~CharArray()
    {
        cout << "~CharArray()" << endl;
        if(m_pstr){
            delete [] m_pstr;
            m_pstr = nullptr;
        }
    }
    // operator[] 重载
    char & operator[](int index)
    {
        // 判断index是否合法
        if(index < 0 || index >= m_size){
            cout << "index is illegal!!" << endl;
            /* throw "index is illegale!"; */
            static char nullChar = '\0';
            return nullChar;
        }

        return  m_pstr[index];
    }

    void print()
    {
        cout << m_pstr << endl;
    }
private:
    char * m_pstr;
    int m_size;
};


void test1()
{
    string str = "abc";
    cout << str[0] << endl;
    cout << str[1] << endl;
    cout << str[2] << endl;
    cout << "-------" << endl;
    cout << str.operator[](0) << endl;
}

void test2()
{
    CharArray ch {"abcd"};
    ch.print();
    // 通过下标去访问对应位置的元素
    ch[0] = 'A';
    cout << ch[0] << endl;
    /* ch.operator[](0); */
}
int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

