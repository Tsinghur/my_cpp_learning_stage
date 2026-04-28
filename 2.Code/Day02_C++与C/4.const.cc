#include <iostream>

using namespace std;

int main()
{
    int b = 20;
    const int a = b;
    b = 10;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}

