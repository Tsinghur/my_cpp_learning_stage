#include <iostream>

using std::cout;
using std::endl;

/*
 * 虚函数的原理: 对象结构发生了变化 多了一个指针
 * 虚函数指针: vfptr
 *
 */
class Father
{
public:
    
    virtual  // 虚函数
    void func2()
    {
        cout << "Father::func1()" << endl;
    }
    
    virtual void display()
    {
        cout << "Father::display()" << endl;
    }
    double m_f = 1;

};


class Son : public Father
{
public:
    // 子类中重写了其中一个虚函数
    virtual void display() override
    {
        cout << "SOn::display() " << endl;
    }

    double m_f = 2;
};

void test1()
{
    Father father;
    cout << sizeof(father) << endl;// 8--->16
    Son son;
    cout << sizeof(son) << endl;// 16--->24
}

// 使用多态
void test2()
{
    Son son;
    Father * f = &son;
    f->func2(); // 父类的结果
    f->display();// 子类的结果
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

