#include <iostream>

using std::cout;
using std::endl;

class Father {
public:
    Father() {}
    Father(int f)
    : m_f(f)
    {}
    Father(const Father& father)
    : m_f(father.m_f)
    {}
    int m_f;
private:
};

class Son : public Father {
public:
    Son(int f, int s)
    : Father(f)
    , m_s(s)
    {}
    /* Son(const Son& son) */ 
    /* /1* : Father(son.m_f) *1/ */
    /* : m_s(son.m_s) */
    /* {} */
    int m_s;
private:
};

void test1() {
    Son s1(1, 2);
    Son s2 = s1;
    cout << s2.m_f << endl;
    cout << s2.m_s << endl;
}

int main() {
    test1();

    return 0;
}
