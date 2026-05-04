#include <iostream>

using namespace std;

class Computer {
public:
    Computer(const char* brand, int price); 
    ~Computer();
private:
    char *m_brand;
    int m_price;
    void *operator new(size_t sz) {
        cout << "operator new" << endl;
        void *ret = malloc(sz);
        return ret;
    }
    void operator delete(void *pointer) {
        cout << "operator delete" << endl;
        free(pointer);
    }
};

int main() {
    

    return 0;
}

