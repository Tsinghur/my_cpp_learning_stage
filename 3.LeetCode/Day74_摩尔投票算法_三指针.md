# Day74

# ==Boyer-Moore投票算法(摩尔投票算法)==

**摩尔投票算法**用于在O(n)时间、O(1)空间内找出数组中出现次数**超过一半**（众数）的元素。

- **核心思想**：“两两抵消”。把不同的元素两两配对消除，若存在多数元素，它一定会“幸存”到最后。
- **步骤**：
  1. 设 `candidate`（候选）和 `count`（票数），初始 `count = 0`。
  2. 遍历数组：
     - 若 `count == 0`，将当前元素设为 `candidate`。
     - 若当前元素等于 `candidate`，则 `count++`；否则 `count--`。
  3. 遍历结束时，`candidate` 就是可能的多数元素。
- **注意**：如果题目不保证一定存在次数 > n/2 的元素，需要**二次遍历**，确认 `candidate` 出现次数是否真正过半。
- **例子**（数组 `[2,2,1,1,1,2,2]`）：
  - 2→candidate=2, count=1
  - 2→count=2
  - 1→count=1
  - 1→count=0
  - 1→candidate=1, count=1
  - 2→count=0
  - 2→candidate=2, count=1
  - 结束，候选为 2，且确实过半。

算法本质是用“多数派”在抵消战中最终胜出，高效且优雅。

## 135.[[Easy]169. 多数元素](https://leetcode.cn/problems/majority-element/)——==“Boyer-Moore投票算法(摩尔投票算法)”==

```cpp
// Boyer-Moore投票算法

// 在 LeetCode 169 的“一定存在 > n/2 多数”假设下完美正确
// int majorityElement(int* nums, int numsSize) {
//     int ans = nums[0], count = 1;
//     for (int i = 1; i < numsSize; i++) {
//         if (ans != nums[i]) {
//             count--;
//             if (count == 0) {
//                 ans = nums[i];
//                 count = 1;
//             }
//         } else { // ans == nums[i]
//             count++;
//         }
//     }

//     return ans;
// }

// 优化
int majorityElement(int* nums, int numsSize) {
    int ans = 0, hp = 0;
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        if (hp == 0) { // x 是初始擂主，生命值为 1
            ans = x;
            hp = 1;
        } else { // 比武，同门加血，否则扣血
            hp += x == ans ? 1 : -1;
        }
    }
    return ans;
}
```

## 136.[[Medium]75. 颜色分类](https://leetcode.cn/problems/sort-colors/)——“荷兰国旗问题-三指针”&==“O(n)插入排序-三指针原地重写”==

```cpp
// 法一：荷兰国旗问题&三指针
// void swap(int* a, int* b) {
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

// void sortColors(int* nums, int numsSize) {
//     int left = 0, mid = 0, right = numsSize - 1;
//     while (mid <= right) {
//         if (nums[mid] == 0) {
//             swap(&nums[left], &nums[mid]);
//             left++;
//             mid++; // 关键点，因为在这里换来的一定是0/1
//         } else if (nums[mid] == 2) {
//             swap(&nums[mid], &nums[right]);
//             right--;
//         } else { // nums[mid] == 1
//             mid++;
//         }
//     }
// }

// 法二：O(n)插入排序
void sortColors(int* nums, int numsSize) {
    int p0 = 0, p1 = 0; // p0指向最后一个0的下一个位置即第一个1，p1指向最后一个1的下一个位置即第一个2
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        nums[i] = 2;
        if (x <= 1) { // 插入0/1的公共操作
            nums[p1++] = 1;
        }
        if (x == 0) { // 插入0的额外操作
            nums[p0++] = 0;
        }
    }
}
/*
对比一下插入前后：
插入前——>[0,0,1,1,2,2]
插入0
插入后——>[0,0,0,1,1,2,2]
*/
```