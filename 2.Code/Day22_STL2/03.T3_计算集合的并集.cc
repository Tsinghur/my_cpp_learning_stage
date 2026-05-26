#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::cin;
using std::set;

void print(set<int> box) {
    auto it = box.begin();
    for (; it != box.end(); ++it) {
        if (it != box.begin())
            cout << " ";
        cout << *it;
    }
    cout << endl;
}

void test() {
    cout << "输入格式：第一行分别输入集合A、B的元素个数，后两行分别输入集合A、B的元素" << endl;
    int n, m;
    cin >> n;
    cin >> m;
    int tmp;
    set<int> a, b;
    while (n-- && cin >> tmp) {
        a.insert(tmp);
    }
    while (m-- && cin >> tmp) {
        b.insert(tmp);
    }

    cout << "a: ";
    print(a);
    cout << "b: ";
    print(b);
    cout << "c = a + b: ";
    set<int> c;
    c.insert(a.begin(), a.end());
    c.insert(b.begin(), b.end());
    print(c);
}

int main() {
    test();

    return 0;
}
