# Day65

## 131.[[Hard]84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)——“单调栈”

```c
// 单调栈
#define MY_MAX(a, b) ((b) > (a) ? (b) : (a))

// 写法1：三次遍历
/*
第一次遍历：得left数组，left[i]为heights[i]在heights中左边第一个小于其本身的元素的下标
第二次遍历：得right数组，right[i]为heights[i]在heights中右边第一个小于其本身的元素的下标
第三次遍历：更新ans，根据(right[i] - left[i] - 1) * heights[i]得每个元素作为高时可构成的最大矩形的面积
*/
// int largestRectangleArea(int* heights, int heightsSize) {
//     int* left = malloc(heightsSize * sizeof(int));
//     int* right = malloc(heightsSize * sizeof(int));
//     int* stack = malloc(heightsSize * sizeof(int)); // 单调增，存下标
//     int top = -1; // 栈顶下标，-1表示栈为空

//     // 更新left数组
//     for (int i = 0; i < heightsSize; i++) {
//         int h = heights[i];
//         while (top >= 0 && heights[stack[top]] >= h) {
//             top--; // 出栈，保证单调栈的递增性
//         } // 跳出时，栈顶对应值小于当前遍历元素的值，即当前元素的值左边的第一个小于其本身的元素
//         left[i] = top < 0 ? -1 : stack[top]; // 左边所有元素都大于它就取向左越界的第一个下标 -1
//         stack[++top] = i; // 入栈，保证单调栈的递增性
//     }

//     // 更新right数组，同理
//     top = -1; // 清空栈(逻辑上)
//     for (int i = heightsSize - 1; i >= 0; i--) {
//         int h = heights[i];
//         while (top >= 0 && heights[stack[top]] >= h) {
//             top--; // 出栈
//         }
//         right[i] = top < 0 ? heightsSize : stack[top]; // 右边所有元素都大于它就取向右越界的第一个下标 heightsSize
//         stack[++top] = i; // 入栈
//     }

//     // 更新ans
//     long long ans = 0;
//     for (int i = 0; i < heightsSize; i++) {
//         ans = MY_MAX(ans, heights[i] * (right[i] - left[i] - 1));
//     }

//     free(left);
//     free(right);
//     free(stack);
//     return ans;
// }

// 写法2：两次遍历
/*
    可以将left与right的更新合并在一次遍历中，即在计算 left 的过程中，如果栈顶元素 ≥heights[i]，那么 i 就是栈顶元素的 right
虽然这样的话right更新的条件更宽容，即可能存在相同值元素的干扰，但实际的话并不影响答案，例：
    heights=[1,3,4,3,2]，左边那个 3 的 right[i] 会变小，导致矩形面积变小，但是在这种情况下，这两个高为 3 的柱子，对应的矩形面积（在写法一中）是一样大的，虽然（在写法二中）左边那个 3 的矩形面积变小了，但右边那个 3 的矩形面积是不变的，所以我们不会错过正确答案
*/
// int largestRectangleArea(int* heights, int n) {
//     int* left = malloc(sizeof(int) * n);
//     int* right = malloc(sizeof(int) * n);
//     int* stack = malloc(sizeof(int) * n);
//     int top = -1; // 栈顶下标（-1 表示栈为空）
//     for (int i = 0; i < n; i++) {
//         int h = heights[i];
//         while (top >= 0 && heights[stack[top]] >= h) {
//             right[stack[top--]] = i; // 出栈并更新stack[top]的right
//         }
//         left[i] = top < 0 ? -1 : stack[top];
//         stack[++top] = i; // 入栈
//     }

//     // 栈中剩余元素的 right 都是 n ，此时栈里的元素是递增的，而元素已经遍历完了，在它们的右边没有小于它们的
//     for (int i = 0; i <= top; i++) {
//         right[stack[i]] = n;
//     }

//     int ans = 0;
//     for (int i = 0; i < n; i++) {
//         ans = MAX(ans, heights[i] * (right[i] - left[i] - 1));
//     }

//     free(left);
//     free(right);
//     free(stack);
//     return ans;
// }

// 写法3：一次遍历
/*
    写法2中栈顶出栈时，当前下标就是栈顶的 right，此时栈顶的left正是栈顶下面的值（单调栈是底小顶大的）
    为简化代码逻辑，可以在一开始把 −1 入栈，当作哨兵。当栈中只有一个数的时候，栈顶下面那个数刚好就是 −1，对应 left[i]=−1 的情况，所以这里的stack就需要申请n+1个空间了
*/
int largestRectangleArea(int* heights, int n) {
    int* stack = malloc((n + 1) * sizeof(int));
    int top = -1; // 栈顶下标
    stack[++top] = -1; // 在栈中只有一个数的时候，栈顶的「下面那个数」是 -1，对应 left[i] = -1 的情况
    int ans = 0;

    for (int right = 0; right <= n; right++) { // right = n的原因见下一行
        int h = right < n ? heights[right] : -1; // 这是为了让所有的元素都有一次出栈的过程，即使每个元素都作为高来计算一次，这样就可以保证不错过答案
        // 每一次while就是一次出栈
        while (top > 0 && heights[stack[top]] >= h) {
            int i = stack[top--]; // 矩形的高（的下标），也是出栈，且出栈的就是这次计算的高
            int left = stack[top]; // 栈顶下面那个数就是 left
            ans = MAX(ans, heights[i] * (right - left - 1));
        }
        stack[++top] = right;
    }

    free(stack);
    return ans;
}
```

