# Day73

## 134.[[Hard]295. 数据流的中位数](https://leetcode.cn/problems/find-median-from-data-stream/)——“设计”&“优先队列-==对顶堆==”

```cpp
typedef struct {
    int* left;      // 最大堆，存储较小的一半
    int leftSize;
    int* right;     // 最小堆，存储较大的一半
    int rightSize;
    int capacity;   // 每个堆的最大容量
} MedianFinder;

// ----------------------------------------------------------------
// 向上调整：最大堆
void maxHeapSiftUp(int* heap, int idx) {
    int val = heap[idx];
    while (idx > 1 && heap[idx / 2] < val) { // idx=1即调整到根结点 或 父结点>=当前结点 时停止调整
        heap[idx] = heap[idx / 2]; // 将父结点移到当前结点
        idx /= 2;
    }
    heap[idx] = val; // 到最终位置时才将val放下，这样的话省去了swap操作
}
// 向下调整：最大堆
void maxHeapSiftDown(int* heap, int size, int idx) {
    int val = heap[idx];
    int child;
    while (2 * idx <= size) {
        child = 2 * idx;
        if (child + 1 <= size && heap[child + 1] > heap[child]) // 若是右孩子存在且右孩子大于左孩子
            child++; // 则将child指向右孩子
        if (val >= heap[child])
            break; // 若是当前左或右孩子小于等于val，则什么都不做
        heap[idx] = heap[child];
        idx = child;
    }
    heap[idx] = val;
}
// 向上调整：最小堆
void minHeapSiftUp(int* heap, int idx) {
    int val = heap[idx];
    while (idx > 1 && heap[idx / 2] > val) {
        heap[idx] = heap[idx / 2];
        idx /= 2;
    }
    heap[idx] = val;
}
// 向下调整：最小堆
void minHeapSiftDown(int* heap, int size, int idx) {
    int val = heap[idx];
    int child;
    while (2 * idx <= size) {
        child = 2 * idx;
        if (child + 1 <= size && heap[child + 1] < heap[child])
            child++;
        if (val <= heap[child])
            break;
        heap[idx] = heap[child];
        idx = child;
    }
    heap[idx] = val;
}
// ----------------------------------------------------------------

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->capacity = 50001;
    obj->left = (int*)malloc((obj->capacity + 1) * sizeof(int)); // 1‑based 索引：堆数组的有效元素从索引 1 开始存放，而不是通常的 0，更方便地计算父子关系
    obj->right = (int*)malloc((obj->capacity + 1) * sizeof(int));
    obj->leftSize = obj->rightSize = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->leftSize == obj->rightSize) { 
    // 插入right(最小堆)，然后把最小堆的堆顶移到left(最大堆)
    obj->right[++obj->rightSize] = num; // 由于下标从1开始，所有size就是最后一个元素的下标，而不是最后一个元素的下一个位置的下标
    minHeapSiftUp(obj->right, obj->rightSize); // 并非冗余操作
    int top = obj->right[1]; // 弹出(插入新元素并且调整之后的)最小堆顶
    obj->right[1] = obj->right[obj->rightSize--]; // 将最后一个元素放到堆顶，调整
    minHeapSiftDown(obj->right, obj->rightSize, 1);
    obj->left[++obj->leftSize] = top; // 插入最大堆
    maxHeapSiftUp(obj->left, obj->leftSize);
    } else { // left元素数量比right多一个
    // 插入left(最大堆)，然后把最大堆的堆顶移到right(最小堆)
    obj->left[++obj->leftSize] = num;
    maxHeapSiftUp(obj->left, obj->leftSize);
    int top = obj->left[1]; // 弹出最大堆顶
    obj->left[1] = obj->left[obj->leftSize--];
    maxHeapSiftDown(obj->left, obj->leftSize, 1);
    obj->right[++obj->rightSize] = top; // 插入最小堆
    minHeapSiftUp(obj->right, obj->rightSize);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->leftSize > obj->rightSize) { // 即总数为奇数
        return obj->left[1];
    }
    return (obj->left[1] + obj->right[1]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->left);
    free(obj->right);
    free(obj);
}
```

