#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

class Point {
public:
    Point(int a, int b)
    : m_a(a)
    , m_b(b)
    {}
    
    bool operator<(const Point& rhs) const {
        if (m_a != rhs.m_a)
            return m_a < rhs.m_a;            
        else 
            return m_b < rhs.m_b;
    }

    int getA() const { return m_a; }
    int getB() const { return m_b; }
private:
    int m_a;
    int m_b;
};

struct Compare {
    /* bool operator()(const Point& lhs, const Point& rhs) { // error: lack const */
    bool operator()(const Point& lhs, const Point& rhs) const { // 算法或容器内部，会把比较器当作const对象来调用
        if (lhs.getA() != rhs.getA())
            return lhs.getA() < rhs.getA();
        else
            return lhs.getB() < rhs.getB();
    }
};

template <typename T>
void print(T& box) {
    for (auto& e : box) {
        cout << e.getA() << " " << e.getB() << endl;
    }
}

// 法一：自定函数对象比较器
void test1() {
    set<Point,Compare> s{
        {3, 4},
        {4, 5},
        {1, 2},
        {2, 3}
    };

    print(s);
}

/* namespace std { */
/*     template <> */
/*     struct less<Point> { */
/*         bool operator()(const Point& lhs, const Point& rhs) const { // 算法或容器内部，会把比较器当作const对象来调用 */
/*         if (lhs.getA() != rhs.getA()) */
/*             return lhs.getA() < rhs.getA(); */
/*         else */
/*             return lhs.getB() < rhs.getB(); */
/*         } */
/*     }; */
/* }; */

// 法二：模板特化
void test2() {
    // 相当于 set<Point,std::less<Point>> s{};
    set<Point> s{
        {3, 4},
        {4, 5},
        {1, 2},
        {2, 3}
    };

    print(s);
}

// 法三：运算符重载
void test3() {
    set<Point> s{
        {3, 4},
        {4, 5},
        {1, 2},
        {2, 3}
    };

    print(s);
}

int main() {
    test1();
    cout << "---------" << endl;
    test2();
    cout << "---------" << endl;
    test3();

    return 0;
}
