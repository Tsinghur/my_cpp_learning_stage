#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

/*
 * 输入 输出运算符的重载
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

void test1()
{
    Complex cx {1, 1};
    cout << cx << endl;
    // 本质
    /* operator<<(cout,cx); */
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
void test2()
{
    Complex cx;
    cout << "input a real, image:" << endl;
    cin >> cx;    
    // operator>>(cin,cx)
    cout << cx << endl;
}

/*
 * 思考?
 * class A{
 *  private:
 *  int m_dataA;
 *
 * }
 * A a;
 * cout << a << endl; 
 * class B{
 * private:
 *    int m_dataB;
 *    A m_a;
 * };
 * B b;
 * cout << b << endl; 
 * 思考的过程
 * ostream & operator<<(ostream& os, const B & b){
 *    os << b.m_dataB << b.m_a; 
 *    return os;
 * }
 * ostream & operator<<(ostream& os, const A & a){
 *    os << a.m_dataA; 
 *    return os;
 * }

 */
int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}


