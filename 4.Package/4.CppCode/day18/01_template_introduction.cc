#include <iostream>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;


/*
 *
 *  模板: 把类型参数化, 像参数一样传递, 模板编程--->泛型编程(通用编程技术)
 *
 *  分类
 *  函数模板: 把模板作用在函数上
 *  类模板: 把模板作用于类上
 *
 *  本质是一个代码生成器:
 *  在编译时期, 编译器会根据模板生成具体的代码
 *  函数模板: 生成一个具体的函数 ----> 模板函数
 *  类模板: 生成具体的类
 *
 *  由模板生成具体的代码的过程--->实例化
 *  显式实例化: 指明具体的类型是什么
 *  隐式实例化: 不指明具体的类型,编译器自动推导出具体的类型是什么
 */
/* int add(int a,int b) */
/* { */
/*     return a + b; */
/* } */

/* double add(double a, double b) */
/* { */
/*     return a +b; */
/* } */

/* string add(string a, string b) */
/* { */
/*     return  a + b; */
/* } */


// 把模板作用在函数上
// 定义模板的关键字: template
// T : 类型参数或模板参数, 可以是任意的字母
template <typename T>
T add(T a, T b)
{
    cout << "使用了模板"<< endl;
    return  a + b;
}
// 好处: 简洁 , 可以进行复用

void test1()
{
    // 隐式实例化
    add(1, 2); // add(int,int)
    add(1.1, 2.2);// add(double,double)
    string s1 = "abc";
    string s2 = "bcd";
    cout << add(s1,s2) << endl; // add(string,string)

    // 显式实例化
    add<int>(1,2);
}


// 把模板作用于类上, T类型可以作为成员函数的参数 返回值
// 作为数据成员的类型....
template <typename T>
class Box
{
public:
    Box(T data)
    : m_data1(data)
    {

    }
private:
    T m_data1;
};

class Point;

void test2()
{
    //之前已经使用过模板了
    vector<int> v1;
    vector<string> v2;
    vector<Point> v3;
    
    map<int, int> m1;
    map<int, string> m2;

    Box<int> box{100};
    Box<double> box2{1.1};
}
int main(int argc, char * argv[])
{
    test1();
    return 0;
}

