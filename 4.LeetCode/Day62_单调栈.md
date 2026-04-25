# Day62

## 129.[[Medium]394. 字符串解码](https://leetcode.cn/problems/decode-string/)——“字符串”&“迭代/递归”

```c
// 写法1：迭代模拟递归
// 将src中的内容弹栈到dest中一直到遇到src中的第一个'['为止且'['置为0，但是要保证顺序与在src中顺序一致(即使用一个辅助栈多倒一次)，并返回'['左边的数字字符串到int型变量中
void pop(char* src, int* src_top, char* dest, int* dest_top, int* num) {    
    char* t = (char*)malloc(*src_top * sizeof(char));
    int t_top = 0;
    while (src[*src_top - 1] != '[') {
        t[t_top++] = src[--(*src_top)];
        src[*src_top] = '\0';
    }
    src[--(*src_top)] = '\0';
    while (t_top) {
        dest[(*dest_top)++] = t[--t_top];
    }
    int multi = 1;
    while (*src_top > 0 && src[*src_top - 1] >= '0' && src[*src_top - 1] <= '9') {
    	*num += multi * (src[--(*src_top)] - '0');
    	multi *= 10;
    	src[*src_top] = '\0';
	}
	free(t);
}

// 将src中的内容复制num次到dest中(从src的栈底开始复制)
void copy(char* src, char* dest, int* dest_top, int num) {
    int len = strlen(src);
    while (num--) {
        memcpy(dest + (*dest_top), src, len * sizeof(char));
        *dest_top += len;
    }
}

char* decodeString(char* s) {
    char* stack = (char*)calloc(10e5, sizeof(char));
    int stack_top = 0;
    char* ans = (char*)calloc(10e5, sizeof(char));
    int ans_top = 0;
    
    int left_count = 0;
    while (*s) {
        if (*s == '[') {
            left_count++;
        }
        if (left_count == 0 && (*s < '0' || *s > '9')) { // 入ans
            ans[ans_top++] = *s;
        }
        else {
            if (*s == ']') {
                char* temp = (char*)calloc(10e5, sizeof(char));
                int temp_top = 0;
                int num = 0;
                pop(stack, &stack_top, temp, &temp_top, &num);
                left_count--;
                if (left_count > 0) {
                    // temp中内容"复制"num次到stack中
                    copy(temp, stack, &stack_top, num);
                } else { // left_count=0
                    // temp中内容"复制"num次到ans中
                    copy(temp, ans, &ans_top, num);
                }
                free(temp);
            } else {
                stack[stack_top++] = *s;
            }
        }
        s++;
    } // 外层while (*s)
    
    free(stack);
    return ans;
}

// 写法2：递归(C++)
// class Solution {
// public:
//     string decodeString(string s) {
//         if (s.empty()) {
//             return s;
//         }

//         // s[0] 是字母
//         if (isalpha(s[0])) {
//             // 分离出 s[0]，解码剩下的
//             return s[0] + decodeString(s.substr(1));
//         }

//         // s[0] 是数字，后面至少有一对括号
//         int i = s.find('['); // 找左括号
//         // 找右括号，注意对于 [...[...]...] 这种情况，第一个右括号并不是我们要找的，第二个才是
//         int balance = 1; // 左括号个数减去右括号个数
//         for (int j = i + 1; ; j++) {
//             if (s[j] == '[') {
//                 balance++;
//             } else if (s[j] == ']') {
//                 balance--;
//                 if (balance == 0) { // 左右括号个数相等，找到与 s[i] 匹配的右括号 s[j]
//                     int k = stoi(s.substr(0, i));
//                     string t = decodeString(s.substr(i + 1, j - i - 1));
//                     string res;
//                     while (k--) {
//                         res += t;
//                     }
//                     return res + decodeString(s.substr(j + 1));
//                 }
//             }
//         }
//     }
// };
```

# ==单调栈==

在 LeetCode 的单调栈问题里，**绝大多数情况栈中存的都是数组下标**，但也不绝对，取决于题目需要什么信息

**为什么最常存下标？**

1. **能同时拿到值和位置**
   通过下标随时可以访问原数组的值（`arr[stack.top()]`），而且信息不丢失。如果只存值，就丢失了位置信息。
2. **很多题需要计算距离/宽度**
   比如「每日温度」求的是“隔了多少天”，本质是下标差；「柱状图中最大矩形」需要计算矩形的宽度，也依赖下标。这些必须用下标才能完成。
3. **代码模板通用性更强**
   存下标的模板稍加修改就能覆盖“需要下标”和“不需要下标”两种情况；反过来如果模板只存值，碰到需要下标的问题就得重写。

**典型例子**

- **必须存下标**：
  - LeetCode 739. 每日温度（输出距离）
  - LeetCode 84. 柱状图中最大的矩形（计算宽度）
  - LeetCode 85. 最大矩形（扩展版的宽度计算）
  - LeetCode 42. 接雨水（需要宽度和高度）
- **可以存值（但存下标同样能做）**：
  - LeetCode 496. 下一个更大元素 I（只需要元素值对应关系，可通过哈希表存值；但单调栈部分依然常用存下标或直接存值）。
  - LeetCode 503. 下一个更大元素 II（循环数组，存下标配合取模更好处理索引）。
  - LeetCode 1475. 商品折扣后的最终价格（仅需值，但存下标也完全可以）。

**什么时候会直接存值？**

如果问题**完全不关心位置，只关心相对大小关系**，并且最终答案也只需要值，那可以直接存值，代码会更简短一些。例如某些“将数组转换为某种单调序列”的模拟题。

**总结**：
“单调栈里一般存数组下标”这个经验在 LC 刷题中非常准确，也是大多数题解的做法。你可以把它当作**默认习惯**，只有当确定不需要位置信息时才考虑直接存值。

## 130.[[Medium]739. 每日温度](https://leetcode.cn/problems/daily-temperatures/)——“==单调栈==-从左往右/从右往左”

<img src="../0.TyporaPicture\image-20260425174231947.png" alt="image-20260425174231947" style="zoom:80%;" />

<img src="../0.TyporaPicture\image-20260425174252402.png" alt="image-20260425174252402" style="zoom:80%;" />

```c
// 单调栈
// 此题中单调栈存的是位置即数组下标

// 写法1：从右往左
// int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
//     int* ans = calloc(temperaturesSize, sizeof(int));
//     *returnSize = temperaturesSize; // 固定，因为对于ans的处理不一定有temperaturesSize次，所以直接初始化，而不是*returnSize++
//     int* stack = malloc(temperaturesSize * sizeof(int)); // 用数组模拟栈
//     int top = -1; // 栈顶下标
//     for (int i = temperaturesSize - 1; i >= 0; i--) {
//         int t = temperatures[i];
//         while (top >= 0 && t >= temperatures[stack[top]]) {
//             top--; // 找其后面的最大值(因为从右往左遍历，所以栈里存的都是依次在当前元素右边且越往栈顶在原数组中离其越远)
//         } // 此时要么是t < top_val 要么是top = -1
//         if (top >= 0) { // 仅对 t < top_val 做处理(即top != -1也即top >= 0)
//             ans[i] = stack[top] - i;
//         } // 对于top = -1即后面没有大于当前元素的也就是ans[i]就不需要更改了，为默认值0
//         stack[++top] = i; // 入栈
//     }
//     free(stack);
//     return ans;
// }

// 写法2：从左往右
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* ans = calloc(temperaturesSize, sizeof(int));
    int* stack = malloc(temperaturesSize * sizeof(int));
    int top = -1;
    for (int i = 0; i < temperaturesSize; i++) {
        int t = temperatures[i];
        while (top >= 0 && t > temperatures[stack[top]]) { // 栈不为空且当前元素大于栈顶元素，则栈顶元素对应的ans值得更新，然后其出栈，一直循环直到栈为空 或 当前元素小于等于栈顶元素时才将当前元素入栈
            int j = stack[top--];
            ans[j] = i - j;
        }
        stack[++top] = i; // 入栈
    }
    free(stack);
    return ans;
}
```