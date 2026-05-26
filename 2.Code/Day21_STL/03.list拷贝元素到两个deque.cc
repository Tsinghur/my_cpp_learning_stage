#include <iostream>
#include <deque>
#include <list>

using std::cout;
using std::endl;
using std::deque;
using std::list;

template <typename T>
void print(const T& box) { // const是兼容常量容器
    auto it = box.begin();
    for (; it != box.end(); ++it) {
        if (it != box.begin())
            cout << " ";
        cout << *it;
    }
    cout << endl;
}

void test1() {
    list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    deque<int> odd;
    deque<int> even;

    for (const auto& e : list) {
        if (e % 2 != 0) { // 兼容负数
            odd.push_back(e);
        } else {
            even.push_back(e);
        }
    }
    print(odd);
    print(even);
}

int main() {
    test1();
    
    return 0;
}
