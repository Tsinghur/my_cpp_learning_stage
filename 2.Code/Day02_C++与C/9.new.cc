#include <iostream>

using namespace std;

void test() {

}

int main() {
    int* a = new int[10]{1};
    for (int i = 0; i < 10; i++) {
        cout << a[i] << endl;
    }
    cout << "a = " << a << endl;
    cout << "&a = " << &a << endl;
    cout << "&a[0] = " << &a[0] << endl;
    int b = 10;
    int* p = &b;
    cout << "p = " << p << endl;
    return 0;
}
