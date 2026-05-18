#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

/*
 * operator ++ 的重载
 *
 * int a = 1;
 * a++;
 * ++a;
 *
 */

class Complex
{
public:
    Complex() = default;

    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {

    }
    int getReal() const
    {
        return m_real;
    }

    int getImage() const
    {
        return m_image;
    }
    void print()
    {
        cout << m_real << "+" << m_image << "i" << endl;
    }
    // 把普通函数声明为友元函数
    friend
    Complex operator+(const Complex & lhs, const Complex & rhs);


    // 采用成员函数形式
    // 函数返回值
    // 函数参数: Complex对象 参数对象
    // this指向的是当前对象 调用者对象
    Complex operator+(const Complex & rhs)
    {
        return
            Complex{this->m_real+rhs.m_real, this->m_image + rhs.m_image};
    }
    // 声明普通函数operator<<()为友元函数
    friend
    ostream & operator<<(ostream & os, const Complex & cx);

    friend
    istream & operator>>(istream & is, Complex & cx);

    // operator += 重载
    // 返回值是当前对象 cx1自己
    // 参数为cx2对象
    Complex & operator+=(const Complex & rhs)
    {
        cout << "operator+=" << endl;
        this->m_real += rhs.m_real;
        this->m_image += rhs.m_image;
        return *this;
    }

    // operator++ 前置++
    // 参数: 无参
    // 返回值: Complex & 返回的是当前对象自己
    Complex & operator++()
    {
        cout << "operator++()" << endl;
        this->m_real += 1;
        this->m_image += 1;
        return *this;
    }

    // operator++ 后置++
    // 参数:无参
    // 返回值:返回的是个临时对象 Complex
    // C++标准中规定 对与后置++ 参数设置int
    // int本身没有任何含义,就是一个标记 用来区分前置后置++
    Complex operator++(int)
    {
        // 用一个临时的对象来保持初始的对象状态
        Complex temp = *this;
        this->m_real += 1;
        this->m_image += 1;
        return temp;
    }
private:
    int m_real;
    int m_image;
};

// 普通函数形式
/* Complex operator+(const Complex & lhs, const Complex & rhs) */
/* { */
/*     return Complex{lhs.getReal()+rhs.getReal(), lhs.getImage() + rhs.getImage()}; */

/* } */

// 友元函数形式
/* Complex operator+(const Complex & lhs, const Complex & rhs) */
/* { */
/*     return Complex{lhs.m_real + rhs.m_real, lhs.m_image + rhs.m_image}; */

/* } */


// 采用友元函数的重载 operator<<
ostream & operator<<(ostream & os, const Complex & cx)
{

    os << cx.m_real << "+" << cx.m_image << "i";
    // 返回流对象
    return os;
}



/*
 * Complex对象的实部, 虚部通过键盘进行输入
 *
 */
// operator>> 重载
istream & operator>>(istream & is, Complex & cx)
{
    is >> cx.m_real >> cx.m_image;
    // 返回流对象
    return  is;
}

void test1()
{
    int a = 1;
    &(++a); // 左值
    /* &(a++); // 右值 */
            
    Complex cx { 1, 1 };
    // 前置++  形式上用成员函数
    ++cx;
    cout << cx << endl;
    // cx.operator++()
 }

void test2()
{

    Complex cx { 1, 1 };
    // 后置++ 成员函数形式
    Complex cx2 = cx++;
    // 本质
    // cx.operator++()
    // cx++
    cout << cx << endl;
    cout << cx2 << endl;
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}


