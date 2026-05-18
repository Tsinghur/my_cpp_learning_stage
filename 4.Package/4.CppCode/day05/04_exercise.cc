#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char * brand, int price)
    : m_brand(new char[strlen(brand) + 1]{})
    , m_price(price)
    {
        cout << "constructor" << endl;
        strcpy(m_brand, brand);
    }

    // copy constructor
    Computer(const Computer & rhs)
    : m_brand(new char[strlen(rhs.m_brand) + 1]{})
    , m_price(rhs.m_price)
    {
        cout << "copy constructor" << endl;
        strcpy(m_brand, rhs.m_brand);
    }

    // operator=
    Computer & operator=(const Computer & rhs)
    {

        cout << "operator=" << endl;
        // 自赋值判断
        if(this != &rhs){
            // 回收原本的空间
            delete [] m_brand;
            m_brand = nullptr;
            // 把浅拷贝--->深拷贝
            /* this->m_brand = rhs.m_brand; */
            this->m_brand = new char[strlen(rhs.m_brand)+1]{};
            strcpy(m_brand, rhs.m_brand);
            this->m_price = rhs.m_price;

        }

        // 返回当前对象
        return *this;
    }

    ~Computer()
    {
        cout << "~Computer()" << endl;
        if(m_brand){

            delete[] m_brand;
            m_brand = nullptr;
        }
    }

    void print()
    {
        cout << m_brand << " " << m_price << endl;
    }
private:
    char * m_brand;
    int m_price;
};
void test1()
{
    Computer pc1{"xiaomi", 1999};
    Computer pc2 = pc1;
    pc2.print();
}

void test2()
{
    Computer pc1{"xiaomi", 1999};
    Computer pc2{"huawei", 6999};
    pc2 = pc1;
    pc2.print();
}

int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

