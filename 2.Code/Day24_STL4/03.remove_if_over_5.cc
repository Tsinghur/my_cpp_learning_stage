#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::remove_if;
using std::for_each;

void test1() {
    vector<int> nums = {1, 5, 8, 3, 6, 9, 2, 7, 4};
    auto it = remove_if(nums.begin(), nums.end(), [](int n) { return n > 5; });
    nums.erase(it, nums.end());
    for_each(nums.begin(), nums.end(), [](int n) { cout << n << " "; });
    cout << endl;
}

int main() {
    test1();

    return 0;
}