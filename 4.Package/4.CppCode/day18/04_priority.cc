#include <iostream>

using std::cout;
using std::endl;

/*
 * 匹配优先级的问题:
 * 1.普通函数和函数模板之间-->普通函数优先级更高
 * 2. 函数模板之间重载
 *    不需要付出额外代价的那个函数模板优先级更高
 *     参数约束更严格的优先级更高
 */
template <class T> //模板一
T add(T t1,T t2)
{ 
    cout << "模板一" << endl;
return t1 + t2;
}

template <class T1, class T2>  //模板二
T1 add(T1 t1, T2 t2)
{
    cout << "模板二" << endl;
return t1 + t2;
}


void test1()
{
    double x = 9.1;
    int y = 10; 
    cout << add<int,int>(x,y) << endl; //模板二  （1） cout << add<int>(x,y) << endl; //模板一   （2）
    // 对于模板一:
    // T = int
    // int add(int,int); // t1,t2必须一样
    // 对于模板二:
    // T1 = int, T2 = int
    // int add(int,int)
    //
    cout << add<int>(y,x) << endl; //模板二   （3）
    // 对于模板一:
    // T = int
    // int add(int,int)
    // 对于模板二:
    // T1 = int , 自动推导出来T2 = double
    // int add(int, double)
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

