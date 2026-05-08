#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    Base(int num) 
    : m_num(num)
    {}
    friend int operator+(const Base& x, const Base& y);
private:
    int m_num;
};

int operator+(const Base& x, const Base& y) {
    return y.m_num - x.m_num;
}

int main() {
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x + y == j - i) << endl;

    return 0;
}
