#include <iostream>

using std::cout;
using std::endl;

// 用运算符重载方式实现Complex类对象的+、-、+=、-=、自增、自减操作
class Complex {
public:
    Complex()
    : m_real(0)
    , m_image(0)
    {}
    Complex(int real, int image)
    : m_real(real)
    , m_image(image)
    {}
    Complex(const Complex& c)
    : m_real(c.m_real)
    , m_image(c.m_image)
    {}
    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    Complex& operator+=(const Complex& rhs) {
        m_real += rhs.m_real;
        m_image += rhs.m_image;
        return *this;
    }
    Complex& operator-=(const Complex& rhs) {
        m_real -= rhs.m_real;
        m_image -= rhs.m_image;
        return *this;
    }
    Complex& operator++() {
        m_real++;
        m_image++;
        return *this;
    }
    Complex operator++(int) {
        /* return {m_real++, m_image++}; // 能正常工作,但是存在一个其余场景的隐患，不过在这里不会出现问题 */
                                         // 即花括号初始化列表{...}中，m_real++与m_image++的求值顺序是不保证的
                                         // C++ 标准只规定了它们会在返回之前全部求值，但不规定谁先谁后
        Complex t(*this);
        m_real++;
        m_image++;
        return t;
    }
    Complex& operator--() {
        m_real--;
        m_image--;
        return *this;
    }
    Complex operator--(int) {
        /* return {m_real--, m_image--}; */
        Complex t(*this);
        m_real--;
        m_image--;
        return t;
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& rhs); // 不能使用成员函数，因为成员函数第一个参数默认为当前对象指针
    void print() {
        cout << m_real << "+" << m_image << "i" << endl;
    }
private:
    int m_real;
    int m_image;
};

std::ostream& operator<<(std::ostream& os, const Complex& rhs) {
    os << rhs.m_real << "+" << rhs.m_image << "i";
    return os;
}

Complex operator+(const Complex& c1, const Complex& c2) {
    return {c1.m_real + c2.m_real, c1.m_image + c2.m_image};
}
Complex operator-(const Complex& c1, const Complex& c2) {
    return {c1.m_real - c2.m_real, c1.m_image - c2.m_image};
}

void test1() {
    Complex c1(1, 1);
    Complex c2(2, 2);
    cout << "c1(1,1) + c2(2,2) : "<< c1 + c2 << endl;
    cout << "c2(2,2) - c1(1,1) : "<< c2 - c1 << endl;
}

void test2() {
    Complex c1(2, 2);
    cout << "++c1(2,2) : "<< ++c1 << endl;
    Complex c2(2, 2);
    cout << "c2(2,2)++ : "<< c2++ << "  c2 : " << c2 << endl;

}

int main() {
    test1();
    cout << "---------------------------" << endl;
    test2();

    return 0;
}
