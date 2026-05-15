#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    Base() {}
    Base(long base)
    : m_base(base)
    { 
        cout << "Base()" << endl;
    }

    /* void display() { */
    virtual void display() { // dynamic_cast需要多态支持，所以最少得有一个虚函数来形式多态类型
                             // 本质是需要虚函数表（vtable）里的运行时类型信息（RTTI）
        cout << "Base::display()" << endl;
    }

    ~Base() {
        cout << "~Base()" << endl;
    }
    long m_base = 10;
};

class Derived : public Base {
public:
    Derived() {}
	Derived(long base,long derived)
	: Base(base)
	, m_derived(derived)
	{
        cout << "Derived(long)" << endl;
    }

	~Derived(){
        cout << "~Derived()" << endl;
    }

    long m_derived;
};

void test1() {
    Base base;
    Derived d1;
    Base* pbase = &d1;

    /* d1.display(); */

    //向下转型
    Derived* pd = dynamic_cast<Derived*>(pbase);
    if (pd) {
        cout << "转换成功" << endl;
        pd->display();
    } else {
        cout << "转换失败" << endl;
    }
}

int main() {
    test1();

    return 0;
}
