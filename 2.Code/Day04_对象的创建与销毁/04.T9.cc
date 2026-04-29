#include <iostream>

using namespace std;

class Rectangle {
public:
    Rectangle(int length, int width) {
        m_length = length;
        m_width = width;
    }
    int perimeter() {
        return 2 * (m_length + m_width);
    }
    int area() {
        return m_length * m_width;
    }
private:
    int m_length;
    int m_width;
};

int main() {
    

    return 0;
}

