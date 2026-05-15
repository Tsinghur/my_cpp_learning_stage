#include <cmath>
#include <string>
#include <iostream>

const double PI = 3.14159265358979323846;

using std::cout;
using std::endl;
using std::string;
using std::pow;
using std::sqrt;

class Figure {
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

// 矩形
class Rectangle : public Figure{
public:
    Rectangle(double length, double width)
    : m_length(length)
    , m_width(width)
    {}
    string getName() const override {
        return string("矩形");
    }
    double getArea() const override {
        return m_length * m_width;
    }
private:
    double m_length; // 长
    double m_width; // 宽
};

// 圆
class Circle : public Figure {
public:
    Circle(double radius)
    : m_radius(radius)
    {}
    string getName() const override {
        return string("圆");
}
    double getArea() const override {
        /* return M_PI * pow(m_radius, 2); // M_PI为POSIX扩展 */
        return PI * pow(m_radius, 2);
    }
private:
    double m_radius; // 半径
};

class Triangle : public Figure {
public:
    Triangle(double a, double b, double c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
    {}
    string getName() const override {
        return string("三角形");
    }
    double getArea() const override {
        double p = (m_a + m_b + m_c) / 2;
        return sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
    }
private:
    double m_a;
    double m_b;
    double m_c;
};

void display(Figure& fig) {
    cout << fig.getName()
         << "的面积是:"
         << fig.getArea() << endl ;
}
void test() {
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3, 4, 5);

    display(r);
    display(c);
    display(t);
}

int main() {
    test();

    return 0;
}
