#include <iostream>
#include <vector>

using namespace std;

vector<int> nums1{0, 1, 2};
vector<int> nums2{3, 4, 5};
vector<int> nums3{6, 7, 8};
vector<vector<int>> nums{nums1, nums2, nums3};

void test1() {
    for (auto& elems : nums) {
        for (auto& elem : elems) {
            cout << elem << " ";
        }
    }
    cout << endl;
}

void test2() {
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = 0; j < nums[i].size(); j++) {
            cout << nums[i][j] << " ";
        }
    }
    cout << endl;
}

void test3() {
    auto its = nums.begin();
    while (its != nums.end()) {
        auto it = (*its).begin();
        while (it != (*its).end()) {
            cout << *it << " ";
            it++;
        }
        its++;
    }
    cout << endl;
}

int main() {
    test1();
    cout << "-----------------" << endl;
    test2();
    cout << "-----------------" << endl;
    test3();

    return 0;
}
