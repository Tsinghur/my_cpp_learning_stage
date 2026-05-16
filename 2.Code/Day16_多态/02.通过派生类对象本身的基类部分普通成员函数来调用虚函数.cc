#include <iostream>

using std::cout;
using std::endl;

class Base{
public:
    Base(long x)
    : m_base(x)
    {}

    /* void display() const */
    virtual void display() const
    {
        cout << "Base::display()" << endl;
    }

    void func1()
    {
        display();
        cout << m_base << endl;
    }

    void func2()
    {
        Base::display();
    }
private:
    long m_base = 10;
};


class Derived
: public Base
{
public:
    Derived(long base,long derived)
    : Base(base)
    , m_derived(derived)
    {}


    void display() const
    {
        cout << "Derived::display()" << endl;
    }
private:
    long m_derived;
};

void test1()
{
    Base base(20);
    Derived derived(1,2);

    base.func1();
    base.func2();

    derived.func1();
    derived.func2();
}

int main() {
    test1();

    return 0;
}
