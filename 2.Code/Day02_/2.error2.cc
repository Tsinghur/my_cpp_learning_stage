#include <iostream>

using namespace std;

int number = 100; // 全局变量int number

namespace wd
{
int number = 10;
void display()
{
	cout << "wd::display()" << endl;
}
}//end of namespace wd


void test0()
{
    using wd::number;
	/* 报错：using namespace wd; // wd中存在于全局位置实体同名的实体int number */
	cout << number << endl; // error,有冲突
}

int main()
{
    test0();
    return 0;
}
