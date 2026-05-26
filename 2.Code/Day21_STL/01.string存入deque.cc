#include <iostream>
#include <string>
#include <deque>

using std::cout;
using std::endl;
using std::string;
using std::deque;

void test1() {
    deque<string> deq;
    string s;
    while (std::cin >> s && s != "quit") {
        deq.push_back(s);
    }

    auto it = deq.begin();
    for (; it != deq.end(); ++it) { // ++it可以避免某些情况下的多余临时对象
        if (it != deq.cbegin())   // 第一个元素前不加空格
            cout << " ";
        cout << *it;
    }
    cout << endl;
}

int main() {
    test1();

    return 0;
}