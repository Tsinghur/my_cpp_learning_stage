#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

/*
 * operator += 的重载
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
    // += 
    int a = 1;
    int b = 2;
    b += a;

    Complex cx1 { 1, 1 };
    Complex cx2 { 2, 2 };
    cx1 += cx2;
    // 形式上选择成员函数
    // cx1.operator+=(cx2)
    cout << cx1 << endl;
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}


