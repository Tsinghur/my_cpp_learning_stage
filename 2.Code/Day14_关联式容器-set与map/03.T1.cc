#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;

void test1() {
    std::map<int,string> m{{1, "a"}, {2, "b"}, {3, "c"}};
    cout << "m[1]=" << m[1] << endl;
    m[2] = "bb";
    cout << "m[2]=" << m[2] << endl;
    m[4] = "d";
    cout << "m[4]=" << m[4] << endl;
}

int main() {
    test1();

    return 0;
}
