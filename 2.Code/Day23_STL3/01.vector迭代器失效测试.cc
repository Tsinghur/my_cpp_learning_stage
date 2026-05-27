#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test1() {
    vector<int> vec = {1, 2, 3, 4, 5};
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it % 2 == 0) {
            it = vec.insert(it + 1, *it * 2); // it没有+1 或 没有更新it(即没有用it接收返回值) 均是经典错误
        }
    }
    for (auto& e : vec) {
        cout << e << " ";
    }
    cout << endl;
}

int main() {
    test1();

    return 0;
}
