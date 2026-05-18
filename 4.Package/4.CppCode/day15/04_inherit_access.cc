#include <iostream>

using std::cout;
using std::endl;

/*
 * protected继承: 最下方的类也可以访问祖先类的成员
 * 千秋万代
 *
 * private继承: 最下方的类不能访问祖先类的成员
 * 断子绝孙
 */
class GrandFather
{
public:
    int m_data1;
};

class Father: public GrandFather
{
public:
    int m_data2;
};

class Son : public Father
{

};


class Father1
{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

// public继承
class Son1 : public Father1
{
public:
    void func()
    {
        m_data1;
        m_data2;
        /* m_data3; error private NO */
    }
};

class Father2
{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

// protected继承
class Son2 : protected Father2
{
public:
    void func()
    {
        m_data1;
        m_data2;
        /* m_data3; error private NO */
    }
};

class GrandSon2 : protected Son2
{
public:
    void func()
    {
        m_data1;
        m_data2;
        /* m_data3; // private NO  */
    }

};

class Father3
{
public:
    int m_data1;
protected:
    int m_data2;
private:
    int m_data3;
};

// private继承
class Son3 : private Father3
{
public:
    void func()
    {
        m_data1;
        m_data2;
        /* m_data3;// error private NO */
    }
};

class GrandSon3 : private Son3
{
public:
    void func()
    {
        /* m_data1; */
        /* m_data2; */
        /* m_data3; */

    }
};

class Father4
{
private:
    double m_f;
};

class Son4 : public Father4
{
public:
    double m_s;
};

void test2()
{
    Son4 son4;

    /* son4.m_f; */
    son4.m_s;
    cout << sizeof(son4) << endl;//16
    // 父类中的private成员 子类继承了 但是没权限访问
}

void test1()
{
    Son son ;
    son.m_data1;
    son.m_data2;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

