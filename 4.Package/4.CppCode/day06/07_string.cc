#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// string的构建
void test1()
{
//string();//无参构造函数，生成一个空字符串 ""
    string s1;
    cout << "s1=" << s1 << endl;
//string(const char * rhs);//通过c风格字符串构造一个string对象
    string s2 { "hello" };
    cout << "s2=" << s2 << endl;
//string(const char * rhs, size_type count);//通过rhs的前count个字符构造一个string对象
    string s3 { "hello", 3 };
    cout << "s3=" << s3 << endl;
//string(const string & rhs);//拷贝构造函数
    string s4 { s2 };
    cout << "s4=" << s4 << endl;
//string(const string & rhs，size_t pos, size_t count);//通过string对象的一部分创建新的string
    string s5{ s2, 1, 3 };
    cout << "s5=" << s5 << endl;
//string(size_type count, char ch);//生成一个string对象，该对象包含count个ch字符
    // 注意!!!!!
    string s6{ 98, 'a' };
    cout << "s6=" << s6 << endl;
    string s8{'a','b','c'};
    cout << "s8=" << s8 << endl;

    string s7(97,'a');
    cout << "s7=" << s7 << endl;
//string(InputIt first, InputIt last);//以区间[first, last)内的字符创建一个string对象

    string s9 { "abcdef" };
    string s10 { s9.begin(), s9.end() };
    
    cout << "s10=" << s10 << endl;
}


// 迭代器: 理解为广义的指针
// 可以像指针一样使用
void test2()
{
    string str { "abcdef" };
    // 获取首迭代器 : 指向的是第一个字符的位置
    /* auto itBegin = str.begin(); */

    string::iterator itBegin = str.begin();
    cout << *itBegin << endl;
    ++itBegin;
    cout << *itBegin << endl;
    // 尾迭代器:指向的是最后一个元素的下个位置
    auto itEnd = str.end();
    // 需要对尾迭代器做--操作
    /* cout << *itEnd << endl; */
}

// string中常见的操作
void test3()
{
    string str { "hello" };
    // 元素访问 at(index);
    cout << str.at(0) << endl;
    // 还可以通过operator[] 下标访问运算符函数
    cout << str[1] << endl;
    // 访问首字符 尾字符
    cout << str.front() << endl;
    cout << str.back() << endl;
    const char * p = str.c_str();
    cout << p << endl;

    cout << "-------" << endl;
    // 容量
    cout << str.size() << endl;
    cout << str.length() << endl;
    cout << str.empty() << endl;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

