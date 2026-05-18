#include <iostream>

using std::cout;
using std::endl;

/*
 * 菱形继承
 *
 *  虚拟继承在继承时使用关键字virtual:
 *
 *  1.会使基类的子对象放到对象结构的最下方
 *  2.会使对象结构中多一个指针 vbptr 虚基指针 
 *  指向一个虚基表: 放的时偏移信息  通过vbptr + 偏移信息 --->找到基类子对象
 *
 */
class A
{
public:
    double m_a = 1;
};

class B
: virtual public A // B虚拟继承A
{
public:
    double m_b = 2;
};

class C
: virtual public A // C虚拟继承A
{
public:
    double m_c = 3;
};

class D
: public B
, public C
{
public:
    double m_d = 4;
};

void test1()
{
    D d;
    d.m_d;
    d.m_b;
    d.m_c;
    // 没有使用虚拟继承
    /* d.m_a;// D对象中有2份m_a, 不知道访问哪个 二义性 */
    // 使用了虚拟继承: 保证基类子对象 m_a只有1份
    // 并且被放入到了对象结构的最下方
    d.m_a;
    cout << sizeof(d) << endl;

}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

