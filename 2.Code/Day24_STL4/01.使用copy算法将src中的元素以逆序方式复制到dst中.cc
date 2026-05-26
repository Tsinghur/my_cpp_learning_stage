#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::copy;
using std::for_each;
using std::back_inserter;
using std::front_inserter;

void test1() {
    vector<int> src{1, 2, 3, 4, 5};
    list<int> dst;
    copy(src.rbegin(), src.rend(), back_inserter(dst)); // 5 4 3 2 1
    // copy(src.rbegin(), src.rend(), front_inserter(dst)); // 1 2 3 4 5
    for_each(dst.begin(), dst.end(), [](int i) { cout << i << " "; });
    cout << endl;
}

int main() {
    test1();    

    return 0;
}