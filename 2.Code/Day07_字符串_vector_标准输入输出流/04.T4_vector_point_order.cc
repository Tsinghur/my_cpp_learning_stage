#include <iostream>
#include <vector>

using namespace std;

class Point {
public:
    Point(int a = 0, int b = 0)
        : m_a(a)
          , m_b(b)
    {
        cout << "Point(int, int)" << endl;
    }
    Point(const Point& pt)
        : m_a(pt.m_a)
          , m_b(pt.m_b)
    {
        cout << "Point(const Point&)" << endl;
    }
    void print() {
        cout << m_a << " " << m_b << endl;
    }
private:
    int m_a;
    int m_b;
};

/* vector<Point> points; */
// C++ 全局区域 只有编译期，没有运行期
// 不能写：调用方法、循环、判断、赋值、函数调用

void test1(vector<Point>& points) {
    for (auto& pt : points) {
        pt.print();
    }
}

void test2(vector<Point>& points) {
    for (size_t i = 0; i < points.size(); i++) {
        points[i].print();
    }
}

void test3(vector<Point>& points) {
    auto it = points.begin();
    while (it != points.end()) {
        (*it).print();
        it++;
    }
}

int main() {
    Point pt1{1, 2};
    Point pt2{3, 4};
    Point pt3{5, 6};
    vector<Point> points;
    points.reserve(3);
    points.push_back(pt1);
    points.push_back(pt2);
    points.push_back(pt3);
    // 或者
    /* vector<Point> points; */
    /* points.reserve(3); */
    /* points.emplace_back(1, 2); // 直接构造，无拷贝 */
    /* points.emplace_back(3, 4); */
    /* points.emplace_back(5, 6); */

    test1(points);
    cout << "----" << endl;
    test2(points);
    cout << "----" << endl;
    test3(points);

    return 0;
}
