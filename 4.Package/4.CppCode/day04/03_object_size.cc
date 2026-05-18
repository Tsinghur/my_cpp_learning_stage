#include <iostream>

using std::cout;
using std::endl;

/*
 * 一个对象的大小和类中数据成员有关，取决于数据成员的类型
 *
 * 特殊情况:
 * 内存对齐: 会按照类中最大的那个数据成员的整数倍对其
 * 还和声明的数据成员的顺序有关
 * 如果类中有数组作为数据成员, 会按照除了数组外,最大的
 * 数据成员的整数倍对齐
 */
class Point
{
public:
    // 无参构造函数
    Point()
    {
        cout << "Point()" << endl;
    }
    // 有参构造函数
    Point(int x, int y) 
    :m_x(x) 
    ,m_y(y)
    {
        cout << "Point(int,int)" << endl;
    }
       void print()
    {
        cout << m_x << " " << m_y << endl;
    }
private:

    /* int m_x; */
    /* int m_y; */

    int m_x;
    double m_y;

};

void test1()
{
    Point pt;
    cout << sizeof(pt) << endl;// int --> 8
                               // double--->16
}

class C{
    int m_c1;
    int m_c2;
    double m_c3;
};

class D{
    int m_d1;
    double m_d2;
    int m_d3;
};

void test2()
{
    C c;
    D d;
    cout << sizeof(c) << endl;// 16
    cout << sizeof(d) << endl;// 24
}

class E{
    double m_e;
    char m_eArr[20];
    double m_e1;
    int m_e2;
};

class F{
    char m_fArr[20];
};

class G
{

};

void test3()
{
    E e;
    F f;
    cout << sizeof(e) << endl;// 48
    cout << sizeof(f) << endl;// 20

    G g;
    cout << sizeof(g) << endl;//空对象大小 1
}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

