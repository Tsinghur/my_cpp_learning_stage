#include <iostream>

using std::cout;
using std::endl;

class Phone {
public:
    /* void print() { */
    virtual void print() {
        cout << "Phone" << endl;
    }
    virtual double getData() {
        return m_p;
    }
private:
    /* int m_p; // 由于内存对齐的机制，所以这里会填充4字节，因为前面有个虚指针 */
    double m_p;
};

class Phone1 : public Phone {
public:
    void print() {
        cout << "Phone1" << endl;
    }
    double getData() {
        return m_p1;
    }
private:
    double m_p1;
};

class Phone2 : virtual public Phone {
public:
    void print() {
        cout << "Phone2" << endl;
    }
private:
    double m_p2;
};

class Phone3 : public Phone {
public:
    void print() {
        cout << "Phone3" << endl;
    }
};
void test1() {
    Phone1 p1;
    Phone2 p2;
    Phone3 p3;
    /* p1.print(); */
    /* p2.print(); */
    /* p3.print(); */
    cout << "-------" << endl;
    Phone* P1 = &p1;
    Phone* P2 = &p2;
    Phone* P3 = &p3;
    P1->print();
    P2->print();
    P3->print();
    cout << "-------" << endl;
    Phone1 p;
    Phone& P4 = p;
    Phone P5 = p;
    P4.print();
    P5.print();
    cout << "-------" << endl;
}

void test2() {
    Phone p;
    Phone1 p1;
    Phone2 p2;
    cout << "1个虚函数表+1个double：" << sizeof(p) << endl;
    cout << "1个虚函数表+2个double：" << sizeof(p1) << endl;
    cout << "1个虚函数表+2个double+虚继承：" << sizeof(p2) << endl;
}

/*
Phone2 对象内存（总32字节）
┌─────────────────────────────┐  0x0000 首地址（最上面）
│   合并指针(vptr+vbptr)      │  8字节
├─────────────────────────────┤
│   double m_p2               │  8字节
├─────────────────────────────┤
│   ┌─────────────────────┐   │
│   │  Phone基类          │   │
│   │  虚指针 vptr(8)     │   │
│   │  double m_p(8)      │   │  16字节
│   └─────────────────────┘   │
└─────────────────────────────┘ 
*/

int main() {
    test1();
    /* test2(); */

    return 0;
}
