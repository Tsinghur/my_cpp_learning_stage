# Day61

## 127.[[Medium]79. 单词搜索](https://leetcode.cn/problems/word-search/)——==“回溯-二维网格型”&“矩阵”==

```c
int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// bool dfs(char** board, char* word, int m, int n, int i, int j, int k) {
//     if (board[i][j] != word[k]) { // 匹配失败
//         return false; 
//     } // else 当前的word[k]匹配成功
//     if (word[k + 1] == '\0') { // 完全匹配成功
//         return true; 
//     } // else 未匹配完全，仅当前的word[k]匹配成功 
//     board[i][j] = 0; // 标记访问过，注意这是在原字符网格中替换字符，且当前格的字符等于当前的word[k]
//     for (int d = 0; d < 4; d++) {
//         int x = i + DIRS[d][0], y = j + DIRS[d][1]; // 访问相邻格子，即x/y就是新的i/j
//         if (0 <= x && x < m && 0 <= y && y < n && dfs(board, word, m, n, x, y, k + 1)) {
//             return true; // 之后的部分匹配成功
//         }
//     }
//     board[i][j] = word[k]; // 恢复现场，因为当前格的字符等于当前的word[k]
//     return false; // 之后的部分匹配失败
// }

// bool exist(char** board, int boardSize, int* boardColSize, char* word) {
//     int m = boardSize, n = boardColSize[0];
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++) {
//             if (dfs(board, word, m, n, i, j, 0)) {
//                 return true; // 匹配成功
//             }
//         }
//     }

//     return false; // 匹配成功
// }

// 两个优化
/*
1.如果 word 的某个字母的出现次数，比 board 中的这个字母的出现次数还要多，可以直接返回 false
2.设 word 的第一个字母在 board 中出现了 x 次，word 的最后一个字母在 board 中出现了 y 次,如果 y<x，我们可以把 word 反转，相当于从 word 的最后一个字母开始搜索，这样更容易在一开始就满足 board[i][j] != word[k]，不会往下递归，递归的总次数更少
*/
bool dfs(char** board, char* word, int m, int n, int i, int j, int k) {
    if (board[i][j] != word[k]) {
        return false; // 匹配失败
    }
    if (word[k + 1] == '\0') {
        return true; // 匹配成功！
    }
    board[i][j] = 0; // 标记访问过
    for (int d = 0; d < 4; d++) {
        int x = i + DIRS[d][0], y = j + DIRS[d][1]; // 相邻格子
        if (0 <= x && x < m && 0 <= y && y < n && dfs(board, word, m, n, x, y, k + 1)) {
            return true; // 搜到了！
        }
    }
    board[i][j] = word[k]; // 恢复现场
    return false; // 没搜到
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int m = boardSize, n = boardColSize[0];
    // 为了方便，用数组代替哈希表
    int cnt[128] = {};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cnt[board[i][j]]++;
        }
    }

    // 优化一
    int word_cnt[128] = {};
    int k = 0;
    for (; word[k]; k++) {
        if (++word_cnt[word[k]] > cnt[word[k]]) {
            return false;
        }
    }

    // 优化二
    if (cnt[word[k - 1]] < cnt[word[0]]) {
        // 反转 word
        for (int i = 0; i < k / 2; i++) {
            char tmp = word[i];
            word[i] = word[k - i - 1];
            word[k - i - 1] = tmp;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfs(board, word, m, n, i, j, 0)) {
                return true; // 搜到了！
            }
        }
    }
    return false; // 没搜到
}
```

# ==最小栈、最小普通/双端队列的设计==

## 128.[[⭐Medium+]155. 最小栈](https://leetcode.cn/problems/min-stack/)——“设计”

```c
// 优化方向
/*
1.结构体优化：
    (1)使用全局变量 -- int st[30001][2] = {{0, INT_MAX}}; // 栈底哨兵（0 写成任意数都可以，反正用不到）
       结构体只存栈顶下标
    (2)或者结构体中使用一个数组指针 -- int (*st)[2] = malloc((cap) * sizeof(int[2]));
2.Push操作优化：
    使用min函数代替if-else -- st[obj->top][1] = MIN(st[obj->top - 1][1], val);
*/

typedef struct {
    int* ordinary_stack;
    int o_top;
    int* min_stack;
    int m_top;
} MinStack;

MinStack* minStackCreate() {
    MinStack* min_stack = (MinStack*)calloc(1, sizeof(MinStack)); // 两个栈顶指针默认为0，省去初始化操作
    min_stack->ordinary_stack = (int*)malloc(3e4 * sizeof(int));
    min_stack->min_stack = (int*)malloc(3e4 * sizeof(int));

    return min_stack;
}

// 注意优先级: '后缀++/--' > '->' > '前缀++/--' 
// pop、top 和 getMin 操作总是在 非空栈 上调用，也就是说Push时可能为空栈
void minStackPush(MinStack* obj, int val) {
    // if (obj->o_top < 3e4) { // 无需考虑，申请空间时已经考虑
        obj->ordinary_stack[(obj->o_top)++] = val;
        if (obj->m_top == 0) {
            obj->min_stack[(obj->m_top)++] = val;
            return;
        }
        if (val < obj->min_stack[obj->m_top - 1]) {
            obj->min_stack[(obj->m_top)++] = val;
        } else {
            obj->min_stack[(obj->m_top)++] = obj->min_stack[obj->m_top - 1];
        }
    // }
}

void minStackPop(MinStack* obj) {
    // if (obj->o_top > 0) {
        obj->o_top--;
        obj->m_top--;
    // }
}

int minStackTop(MinStack* obj) {
    // if (obj->o_top > 0) {
        return obj->ordinary_stack[obj->o_top - 1];
    // }

}

int minStackGetMin(MinStack* obj) {
    // if (obj->m_top > 0) {
        return obj->min_stack[obj->m_top - 1];
    // }
}

void minStackFree(MinStack* obj) {
    free(obj->ordinary_stack);
    free(obj->min_stack);
    free(obj);
}

// 更优雅的版本：
/*
#define MIN(a, b) ((b) < (a) ? (b) : (a))

int st[30001][2] = {{0, INT_MAX}}; // 栈底哨兵（0 写成任意数都可以，反正用不到）

typedef struct {
    int top; // 当前栈顶下标
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = malloc(sizeof(MinStack));
    obj->top = 0;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    obj->top++;
    st[obj->top][0] = val;
    st[obj->top][1] = MIN(st[obj->top - 1][1], val);
}

void minStackPop(MinStack* obj) {
    obj->top--;
}

int minStackTop(MinStack* obj) {
    return st[obj->top][0];
}

int minStackGetMin(MinStack* obj) {
    return st[obj->top][1];
}

void minStackFree(MinStack* obj) {
    free(obj);
}
*/

// 最小普通队列
// 维护两个栈，每个栈都和 LeetCode 155 一样，在存元素的同时记录当前栈内最小值 
// in 栈：专门用于入队，out 栈：专门用于出队    out 的栈顶就是队列的队首
// push(x) — 入队   直接压入 in 栈，并更新 in 的最小值：
// pop() — 出队     如果 out 为空，就把 in 里的所有元素逐个弹出，并压入 out（全量搬运），在这个过程中 out 会自动维护自己的最小值，然后从 out 弹出栈顶。
// 取两个栈各自的最小值的较小者(即取两个栈顶元素之中较小者)

// 最小双端队列
// struct minstack {
// 	stack<pair<int, int>> st;
// 	int getmin() {return st.top().second;}
// 	bool empty() {return st.empty();}
// 	int size() {return st.size();}
// 	void push(int x) {
// 		int mn = x;
// 		if (!empty()) mn = min(mn, getmin());
// 		st.push({x, mn});
// 	}
// 	void pop() {st.pop();}
// 	int top() {return st.top().first;}
// 	void swap(minstack &x) {st.swap(x.st);}
// };

// struct mindeque {
// 	minstack l, r, t;
// 	void rebalance() {
// 		bool f = false;
// 		if (r.empty()) {f = true; l.swap(r);}
// 		int sz = r.size() / 2;
// 		while (sz--) {t.push(r.top()); r.pop();}
// 		while (!r.empty()) {l.push(r.top()); r.pop();}
// 		while (!t.empty()) {r.push(t.top()); t.pop();}
// 		if (f) l.swap(r);
// 	}
// 	int getmin() {
// 		if (l.empty()) return r.getmin();
// 		if (r.empty()) return l.getmin();
// 		return min(l.getmin(), r.getmin());
// 	}
// 	bool empty() {return l.empty() && r.empty();}
// 	int size() {return l.size() + r.size();}
// 	void push_front(int x) {l.push(x);}
// 	void push_back(int x) {r.push(x);}
// 	void pop_front() {if (l.empty()) rebalance(); l.pop();}
// 	void pop_back() {if (r.empty()) rebalance(); r.pop();}
// 	int front() {if (l.empty()) rebalance(); return l.top();}
// 	int back() {if (r.empty()) rebalance(); return r.top();}
// 	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
// };
```
