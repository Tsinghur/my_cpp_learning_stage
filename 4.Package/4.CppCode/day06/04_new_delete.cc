#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int x, int y)
    : m_x(x)
    , m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
public:
    // copy constructor
    Point(const Point & rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    {
        cout << "Point(const Point &)" << endl;

    }
/* private: */   
    ~Point()
    {
        cout << "~Point()" << endl;
    }
public:
    void print()
    {
        cout << m_x << " " << m_y << endl;
    }

/* private: */
    // operator new
    void * operator new(size_t size)
    {
        cout << "operator new" << endl;
        // 底层使用malloc
        return malloc(size);
    }
/* private: */
    // operator delete
    void operator delete(void * p)
    {
        cout << "operator delete" << endl;
        free(p);
    }
private:
    int m_x;
    int m_y;
};

void test1()
{
    Point * p = new Point{ 1 ,2 };

    delete p;

}

// 创建栈对象需要什么条件?
// public权限的构造函数, public的析构函数
// 创建堆上的对象需要什么条件?
// public的构造函数,operator new, operator delete
// 只允许创建堆对象?
// 只允许创建栈对象?
void test2()
{
    Point pt{1,2};
}

void test3()
{
    Point * p = new Point{1,2};
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

