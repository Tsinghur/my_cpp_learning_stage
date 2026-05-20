#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Computer {
public:
    Computer(string brand, int price)
    : m_brand(brand)
    , m_price(price)
    {}
    ~Computer() 
    {}
    void print() {
        cout << m_brand << " " << m_price << endl;
    }
private:
    string m_brand;
    int m_price;
};

template <typename T>
class RAII {
public:
    RAII(T* data)
    : m_data(data)
    {}
    ~RAII() {
        if (m_data) {
            delete m_data;
            m_data = nullptr;
        }
    }
    T* operator->() {
        return m_data;
    }
    T& operator*() {
        return *m_data;
    }
    T* get() const {
        return m_data;
    }
    void set(T* data) {
        if (data != m_data) { // 防止传入其管理的资源的指针
            if (m_data) {
                delete m_data;
                m_data = nullptr;
            }
            m_data = data;
        }
    }
    RAII(const RAII& rhs) = delete;
    RAII& operator=(const RAII& rhs) = delete;
private:
    T* m_data;
};

int main() {
    /* Computer pc("huawei", 1111); // RAII不能、也不需要管理栈上资源 */
    /* RAII<Computer> raii(&pc); */
    Computer* pc = new Computer("huawei", 1111);
    RAII<Computer> raii(pc);
    raii->print();
    (*raii).print();
    raii.get()->print();

    return 0;
}
