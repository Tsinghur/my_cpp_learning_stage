#include <string.h>
#include <iostream>

using namespace std;

class Computer {
public:
    Computer(const char* brand, int price) 
        : m_brand(new char[strlen(brand) + 1]{})
        , m_price(price)
        {
            cout << "constructor" << endl;
            strcpy(m_brand, brand);
        }
    void print() {
        cout << m_brand << " " << m_price << endl;
    }
    void release() {
        if (m_brand) {
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
    // destructor
    ~Computer() {
        cout << "~Computer" << endl;
        if (m_brand) {
            delete [] m_brand;
            m_brand = nullptr;
        }
    }
private:
    char* m_brand;
    int m_price;
};

void test() {
    // 局部对象
    Computer pc{"SAMSUNG", 1111};
    pc.print();
    /* pc.~Computer(); // 不要手动调用析构函数，一般让其自动被调用执行 */
}

// 全局对象
/* Computer pc{"SAMSUNG", 2222}; */

void test2() {
    // 静态对象
    cout << "test2 begin" << endl;
    static Computer pc{"SAMSUNG", 3333};
    cout << "test2 end" << endl;
}

void test3() {
    // 堆上对象—— 唯一需要手动调用析构函数
    /* int* p = new int(1); */
    Computer* p = new Computer("SAMSUNG", 4444);
    // 指针通过'->'访问成员
    p->print();
    // delete指针时会调用析构函数
    delete p;
    p = nullptr;
}

int main() {
    cout << "main begin" << endl;


    /* test(); */
    /* test2(); */
    test3();

    cout << "main end" << endl;

    return 0;
}

