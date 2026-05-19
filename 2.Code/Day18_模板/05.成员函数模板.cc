#include <iostream>

using std::cout;
using std::endl;

class Point {
public:
	Point(double x,double y)
	: m_x(x)
	, m_y(y)
	{}
	// ...
    template <class T>
	T add(T t1);
private:
    double m_x;
    double m_y;
};

template <class T>
T Point::add(T t1) {
	return m_x + m_y + t1;
}

void test1() {

}

int main() {
    test1();

    return 0;
}
