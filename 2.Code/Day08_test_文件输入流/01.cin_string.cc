#include <iostream>
#include <string>

using namespace std;

void test() {

}

int main() {
    /* char *str; */
    string str;
    cin >> str; // acbd 1234    使用 >> 运算符逐词读取，默认以换行符、空格作为间隔符
    cout << str << endl; // abcd

    return 0;
}

