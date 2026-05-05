#include <iostream>

using namespace std;

class Stack {
private:
    int* data;      // 元素数组
    int top;        // 栈顶,永远指向栈顶元素,-1为空
    int capacity;   // 最大容量
public:
    // 构造函数，指定栈的容量
    Stack(int cap = 10) 
    : data(new int[cap]())
    , top(-1) 
    , capacity(cap)
    {
        cout << "Stack(int)" << endl;
    }
    // 析构函数
    ~Stack() {
        delete [] data;
    }
    // 删除复制函数
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    // 栈是否为空
    bool empty() {
        return top == -1;
    }

    // 栈是否满
    bool full() {
        return top == capacity - 1;
    }

    // 入栈
    void push(int value) {
        if (full()) {
            return;
        }
        data[++top] = value;
    }
    // 出栈
    void pop() {
        if (empty()) {
            return;
        }
        --top;
    }
    // 获取栈顶元素
    int get() {
        if (empty()) {
            return -1;
        }
        return data[top];
    }
};

int main() {
    Stack s(3);
    if (s.empty()) {
        cout << "stack empty" << endl;
    } else {
        cout << "stack not empty" << endl;
    }
    if (s.full()) {
        cout << "stack full" << endl;
    } else {
        cout << "stack not full" << endl;
    }

    s.push(1);
    s.push(2);
    s.push(3);
    if (s.empty()) {
        cout << "stack empty" << endl;
    } else {
        cout << "stack not empty" << endl;
    }
    if (s.full()) {
        cout << "stack full" << endl;
    } else {
        cout << "stack not full" << endl;
    }
    int val = s.get();
    cout << "stack top value = " << val << endl;

    s.pop();
    s.pop();
    s.pop();
    if (s.empty()) {
        cout << "stack empty" << endl;
    } else {
        cout << "stack not empty" << endl;
    }
    if (s.full()) {
        cout << "stack full" << endl;
    } else {
        cout << "stack not full" << endl;
    }

    return 0;
}
