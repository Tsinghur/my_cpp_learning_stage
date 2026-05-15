#include <iostream>

using std::cout;
using std::endl;

class A
{
public:
    int m_num1;
protected:
    int m_num2;
private:
    int m_num3;
};

class B : public A {
public:
    int m_num4;
    void print(const A& a) {
        cout << m_num1 << endl;
        cout << m_num2 << endl;
        /* m_num3; // error: private */
        cout << a.m_num1 << endl;
        /* a.m_num2; // error: by objection access protected */
        /* a.m_num3; // error: by objection access private */
    }
};

void test1() {

}

int main() {
    test1();

    return 0;
}
