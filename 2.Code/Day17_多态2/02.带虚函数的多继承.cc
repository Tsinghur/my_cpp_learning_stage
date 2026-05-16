#include <iostream>

using std::cout;
using std::endl;

class Base1 {
public:
	Base1()
	: m_base1(10)
	{
        cout << "Base1()" << endl;
    }
	virtual void f() {
		cout << "Base1::f()" << endl;
	}
	virtual void g() {
		cout << "Base1::g()" << endl;
	}
	virtual void h() {
		cout << "Base1::h()" << endl;
	}
	virtual ~Base1() {}
private:
	double m_base1;
};

class Base2 {
public:
    Base2()
	: m_base2(10)
	{
        cout << "Base2()" << endl;
    }
	virtual void f() {
		cout << "Base2::f()" << endl;
	}
	virtual void g() {
		cout << "Base2::g()" << endl;
	}
	virtual void h() {
		cout << "Base2::h()" << endl;
	}
	virtual ~Base2() {}
private:
	double m_base2;
};

class Base3 {
public:
    Base3()
	: m_base3(10)
	{
        cout << "Base3()" << endl;
    }
	virtual void f() {
		cout << "Base3::f()" << endl;
	}
	virtual void g() {
		cout << "Base3::g()" << endl;
	}
	virtual void h() {
		cout << "Base3::h()" << endl;
	}
	virtual ~Base3() {}
private:
	double m_base3;
};

class Derived
: public Base1
, public Base2
, public Base3
{
public:
	Derived()
	: m_derived(10000)
	{
        cout << "Derived()" << endl;
    }
	void f() {
		cout << "Derived::f()" << endl;
	}
    virtual void g1() {
		cout << "Derived::g1()" << endl;
	}
private:
	double m_derived;
};

int main(void) {
	cout << sizeof(Derived) << endl;

	Derived d;
	Base1* pBase1 = &d;
	Base2* pBase2 = &d;
	Base3* pBase3 = &d;

	cout << "&Derived = " << &d << endl;
	cout << "pBase1 = " << pBase1 << endl;
	cout << "pBase2 = " << pBase2 << endl;
    cout << "pBase3 = " << pBase3 << endl;

	return 0;
}
