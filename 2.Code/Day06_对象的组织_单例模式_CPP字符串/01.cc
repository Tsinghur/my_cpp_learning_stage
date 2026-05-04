#include <string.h>
#include <iostream>

using namespace std;

class Computer {
public:
    // init
    void init(const char* brand, double price)
    {
        // 回收之前的空间
        delete [] m_brand;
        m_brand = new char[strlen(brand)+1]{};
        strcpy(m_brand, brand);
        m_price = price;
    }
    // 静态方法来返回实例
    static Computer * getInstance()
    {
        if(ms_pInstance == nullptr){
            ms_pInstance = new Computer{};
        }
        return ms_pInstance;
    }
    static void destroyInstance()
    {
        if(ms_pInstance != nullptr)
        {
            delete ms_pInstance;
            ms_pInstance = nullptr;
        }
    }
    Computer(const Computer & pc) = delete;
    Computer & operator=(const Computer & com) = delete;

private:
    // constructor
    Computer(){}
    // destructor
	~Computer()
	{
        if(m_brand){
            delete [] m_brand;
        	m_brand = nullptr; //设为空指针，安全回收
        }
		cout << "destructor" << endl;
	}


	char * m_brand;
	double m_price;
    static Computer * ms_pInstance;
};
Computer * Computer::ms_pInstance = nullptr;
void test1() {
    cout << Computer::getInstance() << endl;
    cout << Computer::getInstance() << endl;
    Computer::getInstance()->init("xiaomi",2999);
    Computer::getInstance()->init("huawei",3999);
    cout << Computer::getInstance() << endl;

    Computer::destroyInstance();
}

int main(void) {
    test1();

    return 0;
}
