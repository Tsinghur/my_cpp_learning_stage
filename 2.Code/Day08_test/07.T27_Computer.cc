#include <string.h>
#include <iostream>

using namespace std;

class Computer {
public:
    Computer(const char* brand, const double price) 
    : m_brand(new char[strlen(brand) + 1]{})
    , m_price(price)
    {
        strcpy(m_brand, brand);
        cout << "Computer(const char*, const double)" << endl;
    }
    Computer(const Computer& pc)
    : m_brand(new char[strlen(pc.m_brand) + 1]{})
    , m_price(pc.m_price)
    {
        strcpy(m_brand, pc.m_brand);
        cout << "Computer(const Computer&)" << endl;
    }
    Computer& operator=(const Computer& pc) {
        if (this != &pc) {
            if (m_brand) {
                delete [] m_brand;
                m_brand = nullptr;
            }
            m_brand = new char[strlen(pc.m_brand) + 1]{};
            strcpy(m_brand, pc.m_brand);
        }
        m_price = pc.m_price;
        cout << "oprator=" << endl;

        return *this;
    }
    ~Computer() {
        if (m_brand) {
            delete [] m_brand;
            m_brand = nullptr;
        }
        cout << "~Computer" << endl;
    }
    void print() {
        cout << m_brand << "    " << m_price << endl;
    }
private:
    char* m_brand;
    double m_price;
};

int main() {
    Computer pc1{"xiaomi", 1111};
    Computer pc2{"huawei", 2222};
    Computer pc3(pc1);
    pc3.print();
    pc3 = pc2;
    pc3.print();

    return 0;
}
