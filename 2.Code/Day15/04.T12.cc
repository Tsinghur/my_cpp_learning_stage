#include <cstring>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::fabs;
using std::sqrt;
using std::pow;

class Point {
    friend class Line; // 隐式前向声明
public:
    Point(float a, float o)
    : m_abscissa(a)
    , m_ordinate(o)
    {}
    Point(const Point& pt)
    : m_abscissa(pt.m_abscissa)
    , m_ordinate(pt.m_ordinate)
    {}
private:
    float m_abscissa;
    float m_ordinate;
};

class Color {
public:
    Color(const char* color) 
    : m_color(new char[strlen(color) + 1])
    {
        strcpy(m_color, color);
    }
    // 动态分配不要忘记自定义析构
    ~Color() {
        if (m_color) {
            delete[] m_color;
            m_color = nullptr;
        }
    }
    /* char* getColor() { */
    const char* getColor() const { // char* 类型一般要保护对象，并且允许常量对象调用
        return m_color;
    }
private:
    char* m_color;
};

class Line {
public:
    Line(const Point& pt1, const Point& pt2) 
    : m_origin(pt1)
    , m_dest(pt2)
    {}
    float getBase() {
        float res = sqrt(pow(fabs(m_origin.m_abscissa - m_dest.m_abscissa), 2) + 
                         pow(fabs(m_origin.m_ordinate - m_dest.m_ordinate), 2)); // fabs多余，因为其外层就是平方
        return res;
    }
private:
    Point m_origin;
    Point m_dest;
};

class Triangle
: public Line
, public Color
{
public:
    Triangle(const Point& pt1, const Point& pt2, const char* color, float height)
    : Line(pt1, pt2)
    , Color(color)
    , m_height(height)
    {}
    float getPerimeter() {
        float base = getBase();
        float hypotenuse = sqrt(pow(base, 2) + pow(m_height, 2));
        return base + m_height + hypotenuse;
    }
    float getArea() {
        float base = getBase();
        return base * m_height / 2;
    }
private:
    float m_height;
};

int main() {
    Point pt1(0, 0);
    Point pt2(0, 3);
    Triangle tri(pt1, pt2, "red", 4);

    cout << "颜色：" << tri.getColor() << endl;
    cout << "周长：" << tri.getPerimeter() << endl;
    cout << "面积：" << tri.getArea() << endl;
    
    return 0;
}
