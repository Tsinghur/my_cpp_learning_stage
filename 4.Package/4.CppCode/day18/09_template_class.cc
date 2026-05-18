#include <iostream>
#include <array>

using std::cout;
using std::endl;
using std::array;

/*
 * 类模板: 把模板作用于类上
 * template <typename T>
 * class Box
 * {
 *
 * }
 * 在类中可以正常使用T类型
 *
 */

class Data
{
public:
    int getData()
    {
        return m_data;
    }
private:
    int m_data;
};

// 需求: 希望 管理者可以管理任何类型的资源
// 而不是单一的Data资源 --->使用模板
class MiddleLayer
{
public:
    MiddleLayer(Data * p)
    : m_p(p)
    {}
    ~MiddleLayer()
    {
        delete m_p;
    }
    // operator->
    Data * operator->()
    {
        return m_p;
    }

    // operator*
    Data & operator*()
    {
        return *m_p;
    }
private:
    // 资源类型的指针
    Data * m_p;
};


void test1()
{
    MiddleLayer ml { new Data{} };
    ml->getData();
    (*ml).getData();
    cout << "-----" << endl;
    /* MiddleLayer ml2{ new int{100} }; */
}


template <typename T = int>
class Box
{
public:
    Box(T data)
    : m_data(data)
    {
    }

    // 成员函数
    void print(T t)
    {
        cout << "print()" << endl;
    }
    
    // 声明和实现分开写
    void print2(T t);

private:
    /* int m_data; */
    T m_data;
};
// 类外实现成员函数
// 再写一遍template
// 类名作用域使用的时候要加上类型参数Box<T>::
// 如果有默认值的话, 类外实现的时候不要再把它写一遍了
template <typename T>
void Box<T>::print2(T t)
{
    cout << "xxxxx" << endl;
}


/* class Box2 */
/* { */
/* public: */
/*     Box2(double data) */
/*     : m_data(data) */
/*     { */
/*     } */
/* private: */
/*     double m_data; */
/* }; */

void test3()
{
    /* Box box1{ 100 }; */
    /* Box2 box2{ 3.14 }; */

    // 显式实例化
    Box<int> box1{100};
    Box<double> box2{3.13};
    Box<std::string> box3{"abc"};
    /* Box<Point> box3{ Point{1,2} }; */

    // 隐式实例化 需要加一个<>
    /* Box<> box4{100}; */
    Box<int> box4{100};
    box4.print(10);
    box4.print2(10);
}

// 作业: 自定义一个栈stack, 可以存储任意类型的数据
// 入栈 出栈...相关操作

template <typename T = int, int CAPACITY = 10>
class Stack
{
public:
    Stack()
    : m_p(new T[CAPACITY]{})
    {

    }
    // ~Stack()
    // push
    // pop
    // isEmpty
    // isFull
    // top
    T top(){}
private:
    T * m_p;
    int m_size;
};

// stl: std::array 静态数组
void test4()
{
    array<int,5> arr{1,2,3,4,5};
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    cout << arr[3] << endl;
    cout << arr[4] << endl;
    cout <<" ----" << endl;
    cout << arr.size() << endl;
    cout <<" ----" << endl;
    cout << arr.front() << endl;
    cout <<" ----" << endl;
    cout << arr.back() << endl;
};

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test3(); */
    test4();
    return 0;
}

