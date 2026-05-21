#include <iostream>
#include <forward_list>

using std::cout;
using std::endl;

void test1() {
    std::forward_list<int> fl{1, 2, 3};
}

int main() {
    test1();

    return 0;
}
