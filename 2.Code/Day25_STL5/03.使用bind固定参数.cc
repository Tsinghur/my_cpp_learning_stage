#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;
using namespace std::placeholders; // placeholders不是类

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
};

void test1() {
    Calculator c;
    function<int(int)> f1 = bind(&Calculator::add, &c, 10, _1); 
    function<int(int)> f2 = bind(&Calculator::add, &c, _1, 20);
    cout << f1(1) << endl;
    cout << f2(2) << endl;
}

int main() {
    test1();

    return 0;
}