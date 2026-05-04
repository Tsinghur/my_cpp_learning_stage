#include <string.h>
#include <iostream>

using namespace std;

class Computer {
public:
    // init
    void init(const char *brand, double price) {
        // 回收之前的空间
        delete [] m_brand;
        m_brand = new char[strlen(brand) + 1]{};
        strcpy(m_brand, brand);
        m_price = price;
    }
    // 静态方法返回实例
    static Computer *getInstance() {
        if (ms_pInstance == nullptr) {
            ms_pInstance = new Computer{};
        }
        return ms_pInstance;
    }
    static void destroyInstance() {
        if (ms_pInstance != nullptr) {
            delete ms_pInstance;
            ms_pInstance = nullptr;
        }
    }
    Computer(const Computer &pc) = delete;
    Computer &operator=(const Computer &pc) = delete; 
private:
    char *m_brand;
    double m_price;
    static Computer *ms_pInstance;
    Computer() {}
    ~Computer() {
        if (m_brand) {
            delete [] m_brand;
            m_brand = nullptr;
        }
        cout << "destructor" << endl;
    }
};
Computer *Computer::ms_pInstance = nullptr;

int main() {
    cout << Computer::getInstance() << endl;
    cout << Computer::getInstance() << endl;
    Computer::getInstance()->init("xiaomi", 1111);
    Computer::getInstance()->init("hauwei", 2222);

    Computer::destroyInstance();
    return 0;
}

