#include <iostream>
#include <string>
#include <functional>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::bind;
using std::function;
// using namespace std::placeholders; // 不是类而是命名空间
using std::move;
class Figure {
public:
    // 定义回调函数
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;
    // 注册回调函数
    void setDisplayCallback(DisplayCallback&& cb) { // 使用&&右值引用是为了利用移动语义，高效地将临时回调对象“转移”进类内部，而不是进行昂贵的拷贝
        m_displayCallback = move(cb);
    }
    void setAreaCallback(AreaCallback&& cb) {
        m_areaCallback = move(cb);
    }
    // 执行回调函数
    void handleDisplay() { // 因为std::function的operator()是非const函数，所以这里的成员函数不能加const
                           // 否则m_displayCallback();就相当于const std::function<void()>();
                           // 即使能正确运行也是未定义行为
        if (m_displayCallback) { // 确保回调已注册才执行
            m_displayCallback();
        }
    }
    double handleArea() {
        if (m_areaCallback) {
            return m_areaCallback();
        }
        return 0.0; // 未注册时返回默认值
    }
private:
    DisplayCallback m_displayCallback;
    AreaCallback m_areaCallback;
};

class Rectangle {
public:
    Rectangle(double width, double height)
    : m_width(width)
    , m_height(height)
    {}
    void display() const {
        cout << "---------" << m_name << "---------" <<endl;
        cout << "size: " << m_width << " * " << m_height << endl;
    }
    double area() const {
        return m_width * m_height;
    }
private:
    string m_name = "Rectangle";
    double m_width;
    double m_height;
};

class Circle {
public:
    Circle(double radius)
    : m_radius(radius)
    {}
    void display() const {
        cout << "---------" << m_name << "---------" <<endl;
        cout << "size: " << m_radius << endl;
    }
    double area() const {
        return 3.1415926 * m_radius * m_radius;
    }
private:
    string m_name = "Circle";
    double m_radius;
};

// 统一接口函数
void printFigure(Figure& figure) {
    figure.handleDisplay();
    cout << "Area: " << figure.handleArea() << endl;
}
void test() {
    Figure figure;
    // 1.矩形对象
    Rectangle rect(10.0, 20.0);
    // 使用std::bind将成员函数+对象绑定为可调用对象，适配std::function——即注册回调函数
    figure.setDisplayCallback(bind(&Rectangle::display, &rect));
    figure.setAreaCallback(bind(&Rectangle::area, &rect));
    printFigure(figure); // 执行回调函数

    // 2.圆形对象
    Circle circle(10.0);
    // 注册回调函数
    figure.setDisplayCallback(bind(&Circle::display, &circle));
    figure.setAreaCallback(bind(&Circle::area, &circle));
    printFigure(figure);
}

int main() {
    test(); 

    return 0;
}