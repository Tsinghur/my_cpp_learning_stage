#include <iostream>
#include <string>
#include <map>
#include <utility> // make_pair
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::pair;
using std::make_pair;
using std::function;
using namespace std::placeholders;

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

void test1() {
    map<string,function<int(int,int)>> calculator;
    // 非bind方法，直接将函数绑定给function对象
    // 法一
    // calculator.insert({"+",add});
    // 法二
    // calculator.insert(pair("+",add));
    // 法三
    // calculator.insert(make_pair("+",add));
    // 法四
    // calculator["+"] = add;
    // 法五
    // calculator.emplace("+",add);

    // 使用bind
    calculator.insert({"+", bind(add, _1, _2)});
    calculator["-"] = bind(sub, _1, _2);
    calculator.emplace("*", bind(mul, _1, _2));

    // 输出测试
    cout << calculator["+"](1, 2) << endl;
    cout << calculator["-"](1, 2) << endl;
    cout << calculator["*"](1, 2) << endl;
}

int main() {
    test1();

    return 0;
}