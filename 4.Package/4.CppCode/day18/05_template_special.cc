#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

/*
 * 模板的特化 : 针对某种特殊的类型, 普通函数模板处理不了
 * 专门针对该类型进行特殊处理
 *
 * 语法:
 * template <>
 * void func<特殊类型>(参数列表){}
 *
 * 注意: 模板的特化需要依赖通用模板,通用模板不匹配
 * 才会使用特化
 */

// 普通的通用模板
template <typename T>
T add(T t1, T t2)
{
    return t1 + t2;
}
//  自定义类型中需要operator + 重载

// 模板的特化
template <>
const char * add<const char *>(const char * c1, const char * c2)
{
    char * temp = new char[strlen(c1) + strlen(c2)  + 1]{};
    strcpy(temp,c1);
    strcat(temp,c2);
    return temp;
}


class Complex;

void test1()
{
    cout << add<int>(1,2) << endl;
    cout << add<double>(1.1, 2.2) << endl;
    cout << add("ab", "cd") << endl;
    /* add<Complex>(cx1,cx2); */
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

