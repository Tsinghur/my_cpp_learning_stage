#include <iostream>
#include <vector>
#include <memory>
#include <utility> // move

using std::cout;
using std::endl;
using std::vector;

class Point {
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {}
    ~Point()
    {}
    void print() {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_x;
    int m_y;
};

void test1() {
    vector<std::unique_ptr<Point>> box;

    std::unique_ptr<Point> up1(new Point(1, 2));
    std::unique_ptr<Point> up2(new Point(3, 4));
    /* std::unique_ptr<Point> up3(new Point(5, 6)); */
    auto up3 = std::make_unique<Point>(5, 6); // C++14起

    // error: 独占式智能指针，对托管的空间独立拥有，其拷贝构造函数、与赋值运算符函数均已删除
    /* box.push_back(up1); */
    /* box.push_back(up2); */
    /* box.push_back(up3); */
    // right
    /* box.push_back(std::move(up1)); // 使用移动构造 */
    /* box.push_back(std::move(up2)); // 使用移动构造 */
    /* box.push_back(std::move(up3)); // 使用移动构造 */
    // better: emplace_back 可以直接拿构造参数，在容器内部原地构造对象，连临时对象都不会产生
    box.emplace_back(std::make_unique<Point>(1, 2));
    box.emplace_back(std::make_unique<Point>(3, 4));
    box.emplace_back(std::make_unique<Point>(5, 6));

    for (auto& e : box) {
        e->print();
    }
    cout << "--------" << endl;
    for (auto& e : box) {
        (*e).print();
    }
    cout << "--------" << endl;
    for (auto& e : box) {
        e.get()->print();
    }
}

int main() {
    test1();

    return 0;
}
