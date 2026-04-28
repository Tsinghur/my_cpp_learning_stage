#include <iostream>

using namespace std;

namespace Math {
int add(int x, int y) {
    long long res = x + y;
    return res;
}

int subtract(int x, int y) {
    long long res = x - y;
    return res;
}
}

int main() {
    using Math::add;
    using Math::subtract;

    int x = 10, y = 10;
    cout << add(x, y) << endl;
    cout << subtract(x, y) << endl;

    return 0;
}
