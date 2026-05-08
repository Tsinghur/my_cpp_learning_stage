#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

void test1() {
    string str;
    bool con = true;
    while (con) {
        std::cin >> str;
        for (auto& ch : str) {
            if (ch < '0' || ch > '9') {
                con = true;
                cout << "输入不合法" << endl;
                break; // 继续输入
            }
            con = false;
        }
    }
    std::istringstream iss(str);
    int num;
    iss >> num;
    cout << num << endl;
    // 没有外部资源，不用close
}

int main() {
    test1();

    return 0;
}
