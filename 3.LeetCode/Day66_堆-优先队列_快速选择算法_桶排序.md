# Day66

# ==堆-优先队列==

[堆 + 堆排序 + topK问题 大顶堆 topk问题-CSDN博客](https://lzc-c.blog.csdn.net/article/details/142168356)

1. **什么是优先队列？**

   - 优先队列是一种特殊的队列，和普通队列“先进先出”不同，它里面的每个元素都有一个**优先级**，每次出队的都是当前队列里**优先级最高**的元素（优先级可以是数值最大或最小，取决于定义）

   - 普通队列：像排队买票，先来先服务

     优先队列：像医院急诊，病情越重越优先处理，哪怕他来得晚

2. **核心操作**

   - **插入（enqueue）**：放入一个元素，并带上优先级
   - **取出（dequeue）**：移除并返回优先级最高的元素
   - **查看（peek）**：看一眼优先级最高的元素，不删除

3. **常见实现**

   通常用**堆**（二叉堆）来实现，插入和删除的时间复杂度都是 **O(log n)**，效率很高

4. **优先队列的大小**

   **优先队列的堆大小，完全由你决定——你可以只放 k 个元素（容量固定），也可以放进所有元素（容量与数据量同阶）。topK 问题里精妙的地方，就是故意让堆大小保持为 k，远小于 n**

5. **典型应用**

   - 操作系统任务调度（高优先级进程先运行）
   - 图算法（如 Dijkstra 最短路径）
   - 带时效的事件模拟

# ==快速选择算法==

1. **场景**

   你想在班上**不排序**就直接找出第 *k* 矮的同学。

   普通做法是让所有人按身高排好队，再数第 *k* 个——但这样太慢了。

   快速选择的做法是：

   1. **随便拉出一个同学当“标尺”（pivot）**
   2. **比他矮的站左边，比他高的站右边**（这叫一次分区）
   3. 这时“标尺”所在的位置就是他在班上的准确排名
      - 如果这个排名刚好是 *k*，搞定！
      - 如果 *k* 小于这个排名，说明你要找的人在**左边那群人**里
      - 如果 *k* 大于这个排名，说明你要找的人在**右边那群人**里
   4. **只往某一侧继续找**，另一侧直接不管了

2. **为什么快？**

   每轮只递归处理一边，平均每次砍掉约一半的数据，所以平均时间复杂度是 **O(n)**，比先全排序（O(n log n)）快得多

3. **与优先队列对比**

   - 优先队列（大小为 k 的小顶堆）找第 k 大/小，复杂度是 **O(n log k)**
   - 快速选择平均能做到 **O(n)**，更胜一筹；但最坏情况会退化到 O(n²)（可通过随机选标尺避免）

4. **典型应用**

   - 求中位数、百分位数
   - 快速解决“第 K 大/小元素”问题**（TopK）**
   - 需要线性时间找到某个顺序统计量的场景

## 132.[[Medium+]215. 数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)——==“堆-优先队列”==&==“快速选择算法”==

```c
// 法一：小根堆
/*
使用小根堆方法，堆的大小维持在k
遍历数组，将元素插入堆中，当堆大小超过k时弹出堆顶（最小值）
最后堆顶就是第k大
*/
// void swap(int* a, int* b) {
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

// // 调整：小根堆的下沉操作（向下调整以i为堆顶的小根堆-整个堆/子堆）
// void minHeapify(int* heap, int heapSize, int i) {
//     int left = 2 * i + 1; // 数组存储的堆的左孩子下标(下标从0开始)
//     int right = 2 * i + 2; // 右孩子
//     int smallest = i; // 作为下一次向下调整的子堆的堆顶 的下标
//     if (left < heapSize && heap[left] < heap[smallest]) {
//         smallest = left;
//     }
//     if (right < heapSize && heap[right] < heap[smallest]) {
//         smallest = right;
//     }
//     if (smallest != i) { // 即smallest=i时无需继续向下调整
//         swap(&heap[i], &heap[smallest]);
//         minHeapify(heap, heapSize, smallest);
//     }
// }

// // 建堆：小根堆的上浮操作(插入新元素时使用)
// void heapifyUp(int* heap, int i) {
//     while (i > 0) {
//         int parent = (i - 1) / 2; // 数组存储的堆的父结点的下标
//         if (heap[i] < heap[parent]) { // 不满足小根堆
//             swap(&heap[i], &heap[parent]);
//             i = parent;
//         } else {
//             break; // 即父结点大于当前结点，无需继续向上调整可提前结束循环
//         }
//     }
// }

// int findKthLargest(int* nums, int numsSize, int k) {
//     int* heap = malloc(k * sizeof(int));
//     int heapSize = 0;

//     for (int i = 0; i < numsSize; i++) {
//         int num = nums[i];
//         if (heapSize < k) { // 堆未满，即处于建堆阶段使用上浮操作函数
//             heap[heapSize] = num; // 不提前自增heapSize
//             heapifyUp(heap, heapSize); // 这里的heapsize是这次插入的新元素的下标
//             heapSize++; // 此语句结束时才真正代表当前堆的元素数量
//         } else if (num > heap[0]) { // 堆已满，且当前元素比堆顶大，才有必要加入堆，即替换堆顶并使用下浮操作函数
//             heap[0] = num; // 此时的堆顶为新元素
//             minHeapify(heap, heapSize, 0); // 从整个堆的堆顶(即下标0)开始向下调整
//         } // else 即新元素还要小于等于堆顶，肯定不是我们要找的元素，所以什么都不做，直接跳过
//     }

//     int res = heap[0];
//     free(heap);
//     return res;
// }

// 法二：快速选择算法——O(n) = O(n + n/2 + n/4 + ...)
// 末尾不能加';'，因为调用时SWAP(a, b)后面一般都会有';'，正好与while(0)匹配
#define SWAP(a, b) do { int tmp = (a); (a) = (b); (b) = tmp; } while (0)

int partition(int* nums, int left, int right) {
    int i = left + rand() % (right - left + 1); // 要将i映射到闭区间[left,right]中
    int pivot = nums[i];
    // 把 pivot 与子数组第一个元素交换，避免 pivot 干扰后续划分，从而简化实现逻辑
    SWAP(nums[i], nums[left]);

    i = left + 1;
    int j = right;
    while (1) {
        while (i <= j && nums[i] < pivot) {
            i++;
        } // 此时 nums[i] >= pivot
        while (i <= j && nums[j] > pivot) {
            j--;
        } // 此时 nums[j] <= pivot

        if (i >= j) {
            break;
        }

        SWAP(nums[i], nums[j]); // 宏定义的函数，直接传变量即可
        i++;
        j--;
    }

    // 循环结束后
    // [ pivot | <=pivot | >=pivot ]
    //   ^             ^   ^     ^
    //   left          j   i     right

    // 为什么与 j 交换？
    // 如果与 i 交换，可能会出现 i = right + 1 的情况，已经下标越界(即超出当前闭区间代表的子数组)了，无法交换
    // (主要)另一个原因是如果 nums[i] > pivot，交换会导致一个大于 pivot 的数出现在子数组最左边，不是有效划分
    // 与 j 交换，即使 j = left，交换也不会出错
    SWAP(nums[left], nums[j]);
    // 交换后
    // [ <=pivot | pivot | >=pivot ]
    //               ^
    //               j
    
    // 返回 pivot 的下标
    return j;
}

int findKthLargest(int* nums, int numsSize, int k) {
    srand(time(NULL));
    int target_index = numsSize - k; // 即第k大元素在升序排序中的下标就是左边小于等于它的元素个数即n-k
    int left = 0, right = numsSize - 1; // 闭区间
    while (1) {
        int i = partition(nums, left, right);
        if (i == target_index) { // 找到第 k 大元素
            return nums[i]; // 注：原数组被改变
        } else if (i > target_index) { // 第 k 大元素在 [left, i - 1] 中
            right = i - 1;
        } else { // i < target_index // 第 k 大元素在 [i + 1, right] 中
            left = i + 1;
        }
    }
}
```

# ==桶排序==

**桶排序（Bucket Sort）** 是一种分布式排序算法，它将元素分散到多个有序的“桶”中，每个桶内部再分别排序，最后按桶的顺序依次取出所有元素，得到有序序列。

1. **核心思想**

   - **分桶**：把待排序的数据按照某种映射规则分配到若干个桶里。

   - **桶内排序**：每个桶独立排序（常用插入排序或递归使用桶排序）。

   - **合并**：按桶的次序，依次收集每个桶中的元素。

2. **算法步骤**

   1. 创建若干个空桶（通常为数组的数组或链表）。
   2. 遍历原始数据，通过映射函数 `f(x)` 决定每个元素放入哪个桶。
      例如：若数据范围是 `[0, 1)`，可设 `桶索引 = floor(n * x)`。
   3. 对每个非空桶进行内部排序。
   4. 按桶的编号从小到大，依次把桶内元素取出放回原数组。

3. **复杂度**

   - **平均时间复杂度**：`O(n + k)`，其中 `n` 是元素总数，`k` 是桶的数量（假设桶内排序足够快，且元素均匀分布）。

   - **最坏时间复杂度**：`O(n²)`（当所有元素都集中到一个桶里，退化为一个普通的比较排序，如插入排序）。

   - **空间复杂度**：`O(n + k)`，需要额外存储桶及其中元素。

   - **稳定性**：取决于桶内排序算法是否稳定（若用插入排序，则是稳定的）。

4. **适用场景**

   - 数据均匀分布在一个范围内，如浮点数 `[0, 1)` 的均匀分布。

   - 数据能容易地按区间划分，例如按年龄、成绩分数段等等。

   - 桶排序也常用于**外部排序**（数据量太大，无法一次性装入内存时，可先按范围分桶）。

5. **简单示例**

   排序数组 `[0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68]`（范围 0~1）
   假设建 10 个桶，映射函数 `桶索引 = floor(10 * 数值)`：

   - 桶 1: `0.12, 0.17` → 内部排序后 `0.12, 0.17`

   - 桶 2: `0.21, 0.23, 0.26` → 排序后 `0.21, 0.23, 0.26`

   - 桶 3: `0.39`

   - 桶 6: `0.68`

   - 桶 7: `0.72, 0.78`

   - 桶 9: `0.94`

     合并所有桶即得到最终有序数组。

桶排序通过**牺牲空间来换取平均情况下的线性时间**，是一种非常实用的**非比较类**排序算法

## 133.[[Medium+]347. 前 K 个高频元素](https://leetcode.cn/problems/top-k-frequent-elements/)——“堆-优先队列”&==”桶排序“==

```c
// 法一：小根堆-优先队列
// void swap(int* a, int* b) {
//     int t = *a;
//     *a = *b;
//     *b = t;
// }

// int* hash;
// int zero = 10e4;

// // 调整：小根堆的下沉操作（向下调整以i为堆顶的小根堆-整个堆/子堆）
// void minHeapify(int* heap, int heapSize, int i) {
//     int left = 2 * i + 1; // 数组存储的堆的左孩子下标(下标从0开始)
//     int right = 2 * i + 2; // 右孩子
//     int smallest = i; // 作为下一次向下调整的子堆的堆顶 的下标
//     if (left < heapSize && hash[zero + heap[left]] < hash[zero + heap[smallest]]) {
//         smallest = left;
//     }
//     if (right < heapSize && hash[zero + heap[right]] < hash[zero + heap[smallest]]) {
//         smallest = right;
//     }
//     if (smallest != i) { // 即smallest=i时无需继续向下调整
//         swap(&heap[i], &heap[smallest]);
//         minHeapify(heap, heapSize, smallest);
//     }
// }

// // 建堆：小根堆的上浮操作(插入新元素时使用)
// void heapifyUp(int* heap, int i) {
//     while (i > 0) {
//         int parent = (i - 1) / 2; // 数组存储的堆的父结点的下标
//         if (hash[zero + heap[i]] < hash[zero + heap[parent]]) { // 不满足小根堆
//             swap(&heap[i], &heap[parent]);
//             i = parent;
//         } else {
//             break; // 即父结点大于当前结点，无需继续向上调整可提前结束循环
//         }
//     }
// }

// int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
//     // memset(hash, 0, sizeof(hash)); // 全局 hash 未清零，多测试用例下会污染
//     hash = calloc(2 * 10e4 + 1, sizeof(int)); // numsSize 最大可达 10^5，频率会轻易超过 char 的上限 255。结果就是频率溢出，堆的比较全错，应该使用int
//     // for (int i = 0; i < numsSize; i++) {
//     //     hash[zero + nums[i]]++;
//     // }

//     // 同时收集所有不同的数字，防止相同元素入堆，本题中对比的是频率，而一组相同的数字对应的频率是同一个，所以不应考虑一组相同元素中除第一个之外的其余元素
//     int* unique = malloc(numsSize * sizeof(int));
//     int uniqueSize = 0;
//     for (int i = 0; i < numsSize; i++) {
//         int idx = nums[i] + zero;
//         if (hash[idx] == 0) {
//             unique[uniqueSize++] = nums[i];   // 第一次出现，记入不同数字列表
//         }
//         hash[idx]++;
//     }

//     int* heap = malloc(k * sizeof(int));
//     int heapSize = 0;
//     *returnSize = k;

//     for (int i = 0; i < uniqueSize; i++) {
//         int num = unique[i];
//         if (heapSize < k) { // 堆未满，即处于建堆阶段使用上浮操作函数
//             heap[heapSize] = num; // 不提前自增heapSize
//             heapifyUp(heap, heapSize); // 这里的heapsize是这次插入的新元素的下标
//             heapSize++; // 此语句结束时才真正代表当前堆的元素数量
//         } else if (hash[zero + num] > hash[zero + heap[0]]) { // 堆已满，且当前元素比堆顶大，才有必要加入堆，即替换堆顶并使用下浮操作函数
//             heap[0] = num; // 此时的堆顶为新元素
//             minHeapify(heap, heapSize, 0); // 从整个堆的堆顶(即下标0)开始向下调整
//         } // else 即新元素还要小于等于堆顶，肯定不是我们要找的元素，所以什么都不做，直接跳过
//     }

//     free(hash);
//     free(unique);
//     return heap;
// }

// 法二：桶排序-uthash
// 哈希表结点，哈希表节点 HashNode 是用来记录单个不同元素及其出现次数的，一个节点就对应一个唯一的数值（比如数字 5 出现了 3 次），不需要数组
typedef struct {
    int key;            // 数值
    int count;          // 出现次数
    UT_hash_handle hh;  // uthash必需的控制字段
} HashNode;

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = k;
    if (numsSize == 0 || k == 0)
        return NULL;
    // 1.统计频率（使用uthash）
    HashNode* hash = NULL; // 哈希表头指针，初始为空
    int max_cnt = 0; // 最大频率
    for (int i = 0; i < numsSize; i++) {
        HashNode* node;
        // 在哈希表中查找key是否存在
        HASH_FIND_INT(hash, &nums[i], node); // 三个参数全是地址，其中node接收结果
        if (node == NULL) { // 不存在则创建新结点
            node = (HashNode*)malloc(sizeof(HashNode));
            node->key = nums[i];
            node->count = 1;
            HASH_ADD_INT(hash, key, node); // 参数1,3参数均为地址，参数2为结构体成员变量名，具体可AI搜索uthash的宏操作
        } else { // 存在则直接计数count++
            node->count++;
        }
        if (node->count > max_cnt) {
            max_cnt = node->count; // 动态更新最大频率
        }
    }
    // 2.遍历哈希表，收集所有结点（此时已经完成对相同元素的过滤，之后就是按照频率来遍历）
    int uniqueCount = HASH_COUNT(hash); // 不同元素的个数，遍历宏-获取元素个数
    HashNode** nodes = (HashNode**)malloc(uniqueCount * sizeof(HashNode*)); // 存的元素是哈希结点的地址
    HashNode* cur, * tmp;
    int idx;
    HASH_ITER(hh, hash, cur, tmp) { // 遍历宏-安全遍历
        nodes[idx++] = cur;
    }
    // 3.统计每个频次的元素个数（便于分配桶大小）
    int* freqSize = (int*)calloc(max_cnt + 1, sizeof(int)); // max_cnt + 1 对应次数0...max_cnt共max_cnt+1个
    for (int i = 0; i < uniqueCount; i++) {
        freqSize[nodes[i]->count]++;
    }
    // 4.创建桶并填入元素
    int** buckets = (int**)malloc((max_cnt + 1) * sizeof(int*));
    int* bucketPos = (int*)calloc(max_cnt + 1, sizeof(int)); // 为每个桶分配一个“写入指针”，bucketPos[c]：表示第 c 号桶下一次写入元素时的下标位置
    for (int c = 0; c <= max_cnt; c++) {
        if (freqSize[c] > 0) {
            buckets[c] = (int*)malloc(freqSize[c] * sizeof(int)); // 只为元素个数大于0的频次分配桶实体，这也是为了记录元素，为后续更新ans做准备
        } else {
            buckets[c] = NULL;
        }
    }
    for (int i = 0; i < uniqueCount; i++) {
        int cnt = nodes[i]->count;
        int key = nodes[i]->key;
        buckets[cnt][bucketPos[cnt]++] = key; // 初始化各个桶，这行代码意为：将当前出现为cnt次且值为key的元素插入的桶cnt即一维数组buckets[cnt]（注：buckets为二维数组，它的每个元素都是一个一维数组；bucketPos实际代表每个桶当前的元素数，也即下一个入桶元素的位置下标）
    }
    // 5.基于频次倒序收集前k个元素
    int* ans = (int*)malloc(k * sizeof(int));
    int ansIdx = 0;
    for (int i = max_cnt; i >= 0 && ansIdx < k; i--) {
        int len = freqSize[i];
        for (int j = 0; j < len && ansIdx < k; j++) {
            ans[ansIdx++] = buckets[i][j];
        }
    }
    // 6.释放资源
    for (int c = 0; c <= max_cnt; c++) {
        free(buckets[c]);
    }
    free(buckets);
    free(bucketPos);
    free(freqSize);
    free(nodes);
    // 释放uthash中所有结点
    HASH_ITER(hh, hash, cur, tmp) { // 遍历宏-安全遍历
        HASH_DEL(hash, cur);
        free(cur);
    }

    return ans;
}
```
