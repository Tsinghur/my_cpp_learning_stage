#include "Line.hpp"
#include <iostream>

using std::cout;
using std::endl;


// 给出LineImpl的具体实现
class Line::LineImpl
{
    // 内部类
    class Point
    {
    public:
        Point(int x, int y)
        : m_x(x)
        , m_y(y)
        {

        }
        void print()
        {
            cout << m_x << " " << m_y << endl;
        }
    private:
        int m_x;
        int m_y;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2)
    : m_pt1(x1, y1)
    , m_pt2(x2, y2)
    {

    }
    void print()
    {
        m_pt1.print();
        m_pt2.print();
    }
private:
    Point m_pt1;
    Point m_pt2;
};

// 给出Line中函数的实现
Line::Line(int x1, int y1, int x2, int y2)
: m_pimpl(new LineImpl{x1, y1, x2, y2})
{

    cout << "Line(int,int,int,int)" << endl;
}

Line::~Line()
{
    cout << "~Line()" << endl;
    if(m_pimpl){
        delete m_pimpl;
        m_pimpl = nullptr;
    }
}

void Line::printLine()
{
    m_pimpl->print();
}
