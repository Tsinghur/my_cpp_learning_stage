#include <iostream>

using namespace std;

double divide (double x, double y) {
    if (y == 0) {
        throw "x / 0";
    }

    return x / y;
}

int main() {
    double x, y;
    x = 1, y = 0;
    try {
        double res = divide(x, y);
        cout << res << endl;
    } catch (const char* a) {
        cout << "error: " << a << endl;
    }

    return 0;
}
