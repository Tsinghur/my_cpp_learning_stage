#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <string>

using std::cout;
using std::endl;
using std::stack;
using std::queue;
using std::list;
using std::string;

void test1() {
    stack<int,list<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl;
    s.pop();
}

void test2() {
    queue<string,list<string>> q;
    q.push("a");
    q.push("b");
    q.push("b");
    cout << q.front() << endl;
    q.pop();
}

int main() {
    test1();
    test2();

    return 0;
}