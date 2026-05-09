# Day76

## 137.[[Medium+]31. (整数数组)下一个排列](https://leetcode.cn/problems/next-permutation/)——“数组”&==“设计-字典序算法”==

**延伸：==上一个排列==**

- 一个取巧的做法是，把每个元素变成相反数，找上一个排列就变成找下一个排列了，最后再取相反数变回来

```cpp
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void reverse(int* nums, int start, int end) {
    while (start < end) {
        swap(&nums[start], &nums[end]);
        start++;
        end--;
    }
}
// 整数数组的下一个排列，本质上就是：用当前这些数字，重新排列出一个“刚好比当前数组大”的最小数组
// 即在所有可能排列组成的集合中，按照字典序从小到大排序，下一个排列就是那个恰好排在当前数组后面、且比它大的排列里最小的那个
/*
Q1：为什么不能从左往右找
原因在于要找的是“紧挨着”的下一个排列，即增幅必须最小。从左往右找会优先改变高位（左边的数字），导致增幅过大，跳过中间很多可能的排列
Q2：为什么从右往左找的是第一个相邻升序对，即降序序列为什么不用管
一个降序（非递增）的序列，已经是它能组成的最大排列，内部再怎么调换也没法变大
Q3：为什么要拿从右往左找的第一个大于nums[i]的元素
i 右侧是严格非递增（降序）的，因为 i 是从右往左找到的第一个升序对，意味着 i+1 到末尾已经是降序
用刚好比它大的最小值交换，才能让增幅最小
Q4：为什么最后还要反转nums[i]的后续序列，并且为什么不用排序而是能直接使用反转
（1）因为目标是找到“刚好比当前排列大的最小排列”。既然已经把 nums[i] 换成了一个稍微大一点点的值，那么 i 后面的数字就应该摆成它们能组成的最小值，这样才能保证整个排列的增长幅度最小。而一段数字的最小排列，就是升序排列
（2）反转而不排序，是因为交换操作神奇地保持了 i 后面那段序列的降序特性，而“降序序列”只要反转就是“升序”，也就是这些数字能组成的最小排列。排序是多余的，而且会浪费性能
*/
// 延伸：找上一个排列
// 一个取巧的做法是，把每个元素变成相反数，找上一个排列就变成找下一个排列了，最后再取相反数变回来
void nextPermutation(int* nums, int numsSize) {
    // 1. 从右向左找第一个升序对 nums[i] < nums[i+1]
    int i = numsSize - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // 2. 从右向左找第一个大于 nums[i] 的元素
        int j = numsSize - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        // 3. 交换
        swap(&nums[i], &nums[j]);
    }

    // 4. 反转 i+1 到末尾，使其变为升序（最小排列）
    reverse(nums, i + 1, numsSize - 1);
}

// 下面方法的最大问题在于没有读懂题目：
// 在交换第一次之后，还要保证交换位后续部分为自增，因为这是排列的规定：根据字典顺序从小到大排列
/*
1. 交换后没有将尾部变为最小排列
2. 外层 while 循环逻辑错误
内层 break 只跳出了 for (i) 循环，并未跳出 while，因此即使已经执行过一次交换，后续 count-- 仍可能再次修改数组，造成多次错误交换
正确的算法只需要一次从右向左的扫描即可定位交换点，不需要反复重试不同的左边界
3. 寻找交换点的方式不正确
4. 对特殊情况的处理存在隐患
用 max = -1 初始化，如果数组中包含负数或全为负数，会得出错误的最大值（应初始化为 INT_MIN 或直接取当前区间的第一个值）
全递减数组用 qsort 排序虽然结果正确（升序），但破坏了“原地操作、O(1) 额外空间”的要求，时间复杂度也变成了 O(n log n)。标准做法直接反转整个数组即可，O(n)
小结
你的思路试图通过逐步收缩左边界、寻找可增大的位置来构造下一个排列，但缺少了“交换后重排尾部”这一关键步骤，且控制流程上 while + break 配合不当，导致算法在多数情况下会输出错误结果。正确的解法应当是一次从右向左的扫描 + 交换 + 反转尾部
*/
// int cmp(const void* a, const void* b) {
//     return *(int*)a - *(int*)b;
// }

// void nextPermutation(int* nums, int numsSize) {
//     bool is_reversed = true; // 是否为非严格递减即nums[i] >= nums[i+1]，默认设为true
//     // if (i < numsSize - 1 && nums[i] < nums[i + 1])
//     for (int i = 0; i < numsSize - 1; i++)
//         if (i < numsSize - 1 && nums[i] < nums[i + 1])
//             is_reversed = false; // 初始值应该为true，判断有一个递增则就不是非严格递减了
//     if (is_reversed) {
//         qsort(nums, numsSize, sizeof(int), cmp);
//         return;
//     }

//     int count = numsSize;
//     while (count) {
//         int lower_bound = numsSize - count;

//         int max = -1;
//         for (int i = lower_bound; i < numsSize; i++) {
//             if (nums[i] > max)
//                 max = nums[i];
//         }

//         // for (int i = 0; i < numsSize; i++) {
//         for (int i = numsSize - 1; i >= lower_bound; i--) {
//             if (nums[i] < max) { // 若是"可能"替换为更大的值
//                 bool is_swap = false; // 是否应该交换
//                 int min = -1;
//                 int idx = -1;
//                 for (int j = i + 1; j < numsSize; j++) { // 应该选择之后大于它的最小的那一个
//                     if (nums[j] > nums[i]) {
//                         if (min == -1) {
//                             min = nums[j];
//                             idx = j;
//                             is_swap = true;
//                         }
//                         if (nums[j] < min) {
//                             min = nums[j];
//                             idx = j;
//                             is_swap = true;
//                         }
//                     }
//                 }
//                 if (is_swap) {
//                     int t = nums[i];
//                     nums[i] = nums[idx];
//                     nums[idx] = t;
//                     break;
//                 }
//             }
//         }
//         count--;
//     }
// }
```

## 138.[[Medium+]287. 寻找重复数](https://leetcode.cn/problems/find-the-duplicate-number/)——“==基环树==-数组形式的环形链表II”

```cpp
/*
Q1：为什么不能从环内的元素开始
从环内出发，会破坏快慢指针法寻找环入口的数学基础，导致无法定位重复数字
即虽然一定会在环中相遇，但是在这题中环的判断并不是目的，真正的目标是定位入环口即重复元素
所以，必须严格从 0 开始，因为 0 入度为零，一定不在任何环上，且能保证走到包含重复数字的环，同时满足快慢指针法的全部数学前提
*/
int findDuplicate(int* nums, int numsSize) {
    // 1.先判断有无环，虽然这题中一定有环，但这个判断环的操作也是找到入环口的必要前置
    int slow = 0, fast = 0; // 0 一定不在换上，适合作为起点，因为下一个位置的是靠当前元素的值映射的，因为这里1 <= nums[i] <= n，所以不会有元素映射到0，也就是说不会有元素是第一个元素的前驱，即nums[0]的入度为0
    while (true) {
        slow = nums[slow]; // 等价于 slow = slow.next
        fast = nums[nums[fast]]; // 等价于 fast = fast.next.next
        if (slow == fast) { // 快慢指针移动到同一个结点
            break;
        }
    }
    // 2.找出入环口即重复元素
    int head = 0;
    while (slow != head) {
        slow = nums[slow];
        head = nums[head];
    }
    return slow; // 入环口即重复元素
}
```

