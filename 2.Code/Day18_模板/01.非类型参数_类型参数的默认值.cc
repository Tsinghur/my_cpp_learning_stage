#include <iostream>

using std::cout;
using std::endl;

template <typename T, int N>
void print(T t) {
    cout << t * N << endl;
}

void test1() {
    /* print(3); // error: 没有给定N的值，且N无法隐式推导 */
    /* print(3, 10); // error: print(只接收一个参数) */
    print<int,10>(3); // right
}

template <typename T = int> // 类型参数的默认值仅在无法推导出才会生效，与普通函数默认参数的逻辑完全相反
void print2(T t) {
    cout << t << endl;
}

void print3(int t) {
    cout << t << endl;
}

void test2() {
    print2(3);
    print2(3.14); // 不显式给出类型参数不代表一定使用默认值，因为此时可以推导出类型参数为double
    
    print3(3.14);
}

int main() {
    test1();
    cout << "----------" << endl;
    test2();

    return 0;
}
