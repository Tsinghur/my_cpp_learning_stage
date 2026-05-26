#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

class LRUCache {
public:
    void refer(int page) {
        bool isFind = false;
        auto it = lst.begin();
        for (; it != lst.end(); ++it) {
            if (*it == page) {
                isFind = true;
                break;
            }
        }
        if (isFind) {
            lst.splice(lst.begin(), lst, it);
        } else if (lst.size() == cap) {
            lst.pop_back();
            lst.push_front(page);
        } else {
            lst.push_front(page);
        }
    }
    void print() {
        auto it = lst.begin();
        for (; it != lst.end(); ++it) {
            if (it != lst.begin())
                cout << " ";
            cout << *it;
        }
        cout << endl;
    }
private:
    list<int> lst; // 容器
    size_t cap = 3; // 容量为3
};

void test1() {
    LRUCache cache;
    cache.refer(1); // 1
    cache.print();
    cache.refer(2); // 2 1
    cache.print();
    cache.refer(3); // 3 2 1
    cache.print();
    cache.refer(2); // 2 3 1
    cache.print();
    cache.refer(4); // 4 2 3
    cache.print();
    cache.refer(1); // 1 4 2
    cache.print();
}

int main() {
    test1();

    return 0;
}
