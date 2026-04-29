#include <iostream>

using namespace std;

class Test1 {
public:
    int a;
    ~Test1() {
        cout << "全局对象析构" << endl;
    }
};

class Test2 {
public:
    int a;
    ~Test2() {
        cout << "局部对象析构" << endl;
    }
};

class Test3 {
public:
    int a;
    ~Test3() {
        cout << "静态对象析构" << endl;
    }
};

class Test4 {
public:
    int a;
    ~Test4() {
        cout << "堆对象析构" << endl;
    }
};

Test1 t1;

int main() {
    Test2 t2;
    static Test3 t3;
    Test4* t4 = new Test4();

    delete t4;

    return 0;
}
