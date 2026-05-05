#include <iostream>
#include <vector>

using namespace std;

class Point {
public:
    Point(int a, int b) 
    : m_a(a)
    , m_b(b)
    {
        cout << "Point(int, int)" << endl;
    }
    ~Point() {
        cout << "~Point()" << endl;
    }
    Point(const Point& p) 
    : m_a(p.m_a)
    , m_b(p.m_b)
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

void test() {
    /* vector<int> box{1, 2, 3, 4, 5}; */
    /* auto it = box.begin(); */
    /* box.insert(it, 10); */
}

int main() {
    /* test(); */
    vector<Point> v;
    Point p1{1, 2};
    Point p2{3, 4};
    Point p3{5, 6};
    cout << "----------------" << endl;
    v.push_back(p1); // 首次申请空间
    cout << "----------------" << endl;
    v.push_back(p2); // 第一次扩容 + 释放首次申请的空间
    cout << "----------------" << endl;
    v.push_back(p3); // 第二次扩容 + 释放第一次扩容的空间
    cout << "----------------" << endl;

    return 0;
}
