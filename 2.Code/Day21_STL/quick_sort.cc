#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int pivot = nums[left + (right - left) / 2];

    while (i <= j) {
        while (nums[i] < pivot) {
            ++i;
        }
        while (nums[j] > pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(nums[i], nums[j]);
            ++i;
            --j;
        }
    }

    if (left < j) {
        quickSort(nums, left, j);
    }
    if (i < right) {
        quickSort(nums, i, right);
    }
}

void test1() {
    vector<int> nums = {6, 1, 8, 3, 5, 2, 7, 4};

    quickSort(nums, 0, nums.size() - 1);

    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    test1();

    return 0;
}
