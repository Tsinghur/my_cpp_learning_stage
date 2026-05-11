#include <iostream>

using std::cout;
using std::endl;

// 外部类
class Line
{
public:
    // 内部类
    class Point{
    public:
        Point(int x,int y)
        : m_ix(x)
        , m_iy(y)
        {}
        static void func() {
            cout << "Line::Point::func()" << endl;
        }
        void func2() {
            func();
            /* func3(); // error:不能在没有对象的情况下访问外部类的成员函数 */
            /* func4(); // right */
            /* cout << Line::a << endl; // error:因为内部类不知道这个a是哪一个外层类对象的 */
            /*                          // 外层可以直接使用是因为隐含一个this指针，其永远指向调用函数的对象 */
            /*                          // 而内层类而言，而编译器不会凭空给你一个 Line 对象，所以 Line::a 这样的写法毫无意义，直接报错 */
        }
    private:
        int m_ix;
        int m_iy;
    };
public:
    int a;
    Line(int x1, int y1, int x2, int y2)
    : m_pt1(x1,y1)
    , m_pt2(x2,y2)
    {}
    void func3() {
        /* func(); // error */
        /* Line::Point::func(); // right */
        Point::func();
    }
    friend void test1();
    static void func4() {
        cout << "Line::func4()" << endl;
    }
private:
    Point m_pt1;
    Point m_pt2;
    double length = 10;
};

void test1() {
    Line line(1, 2, 3, 4);
    line.func3();
    line.m_pt1.func();
    line.m_pt1.func2();
}
// 外部类访问内部类
void test2() {
    /* Point::func(); // error */
    Line::Point::func();
    /* Point pt(1, 2); // error */
    Line::Point pt(1, 2); // error
    pt.func();
    pt.func2();
}

int main() {
    test1();
    cout << "------------" << endl;
    test2();

    return 0;
}

