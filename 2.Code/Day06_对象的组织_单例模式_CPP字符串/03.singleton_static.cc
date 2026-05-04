#include <iostream>

using namespace std;

class Singleton {
public:
    static Singleton &getInstance() {
        static Singleton instance;
        return instance; // 返回一个唯一的对象
    }
    // 删除复制函数
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
private:
    Singleton() {}
};

void test1() {
    /* Singleton s1; // error */
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
    cout << &Singleton::getInstance() << endl;
}

int main() {
    test1();

    return 0;
}

