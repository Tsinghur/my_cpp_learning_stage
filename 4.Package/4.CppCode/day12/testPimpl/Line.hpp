#ifndef __LINE_HPP__ 
#define __LINE_HPP__

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine();
private:
    class LineImpl;
    LineImpl * m_pimpl;
};


#endif

