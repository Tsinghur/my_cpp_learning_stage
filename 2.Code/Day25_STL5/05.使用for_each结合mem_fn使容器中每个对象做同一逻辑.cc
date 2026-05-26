#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::for_each;
using std::mem_fn;

class Printer {
public:
    void print(const string& s) const {
        cout << s << endl;
    }
};

void test1() {
    vector<Printer> vp(3);
    // for_each(vp.begin(), vp.end(), mem_fn(&Printer::print)); // error: 这里是二元函数，不能仅用mem_fn，还需要使用bind/lambda进一步打包
    for_each(vp.begin(), vp.end(), bind(&Printer::print, std::placeholders::_1, "hello"));
}

int main() {
    test1();

    return 0;
}