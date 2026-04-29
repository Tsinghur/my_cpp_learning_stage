#include <string.h>
#include <iostream>

using namespace std;

// 简单类：类中数据成员都是内置类型，不涉及动态内存分配
class Point {
public:
    void setX(int x) {
        m_x = x;
    }
    void setY(int y) {
        m_y = y;
    }
    void print() {
        cout << m_x << " " << m_y << endl;
    }
private:
    int m_x;
    int m_y;
};

// 复杂类：设计动态分配
class Computer {
public:
    void setBrand(const char* brand) {
        // 动态内存分配
        m_brand = new char[strlen(brand) + 1]{};
        strcpy(m_brand, brand);
    }
    void setPrice(int price) {
        m_price = price;
    }
    void print() {
        cout << m_brand << " " << m_price << endl;
    }
    void release() {
        // 释放资源
    }
private:
    // 品牌
    char* m_brand;
    // 价格
    int m_price;
};

void test() {
    Point pt;
    /* pt.m_x = 1; */
    /* pt.m_y = 2; */
    pt.setX(1);
    pt.setY(2);
    pt.print();
    cout << "----------" << endl;
    Computer pc;
    pc.setBrand("Huawei");
    pc.setPrice(6999);
    pc.print();
}

int main() {
    test();

    return 0;
}
