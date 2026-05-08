#include <iostream>

using std::cout;
using std::endl;

class A {
public:
    A(int a, int b) 
        : m_a(a)
          , m_b(b)
    {

    }
    A(const A& A)
        : m_a(A.m_a)
          , m_b(A.m_b)
    {

    }
    friend std::ostream& operator<<(std::ostream& os, const A& a);
private:
    int m_a;
    int m_b;
};
std::ostream& operator<<(std::ostream& os, const A& A) {
    os << A.m_a << " " << A.m_b;
    return os;
}
class B {
public:
    B(const int& a,const A& A)
        : m_a(a)
          , m_A(A)
    {

    }
    friend std::ostream& operator<<(std::ostream& os, const B& B);
private:
    int m_a;
    A m_A;
};
std::ostream& operator<<(std::ostream& os, const B& B) {
    os << B.m_a << " " << B.m_A;
    return os;
}
int main() {
    // {2, 3}是一个花括号初始化列表(列表初始化)
    // 在这里它被用来直接构造一个临时的 A 对象
    B B(1, {2, 3});
    // 为什么 B B(1, (2, 3)); 不行
    // (2, 3)是一个括号表达式，里面有一个逗号运算符。
    // 逗号运算符会依次计算2(丢弃)，然后计算3，整个表达式的值就是3
    // 所以这行代码实际上变成了：B b(1, 3);
    // 而 B 的构造函数要求第二个参数是 const A&
    cout << B << endl;
    cout << "--------" << endl;
    A A(2, 3);
    cout << A << endl;

    return 0;
}
