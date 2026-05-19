#include <iostream>

using std::cout;
using std::endl;

template <typename T, size_t capacity = 10>
class Stack {
public:
    Stack()
    : m_data(new T[capacity]{})
    , m_top(-1)
    {
        cout << "init stack" << endl;
    }
    ~Stack() {
            delete[] m_data; // 对空指针使用 delete 或 delete[] 是合法的，什么都不会发生
            /* m_data = nullptr; // 多余，析构函数结束之后，成员变量 m_data 所占用的内存也会随着对象一起被回收 */
    }

    void push(const T& value);
    void pop();
    bool empty() const;
    bool full() const;
    T top() const;
private:
    T* m_data;
    int m_top; // 永远指向栈顶元素
};

// 类外实现成员函数
template <typename T, size_t capacity>
bool Stack<T,capacity>::empty() const {
    return m_top == -1;
}

template <typename T, size_t capacity>
bool Stack<T,capacity>::full() const {
    return m_top == capacity - 1;
}

template <typename T, size_t capacity>
void Stack<T,capacity>::push(const T & value) {
    if (full()) {
        cout << "stack is full" << endl;
        return;
    } else {
        m_data[++m_top] = value;
    }
}

template <typename T, size_t capacity>
void Stack<T,capacity>::pop() {
    if (empty()) {
        cout << "stack is empty" << endl;
        return;
    } else {
        --m_top;
    }
}

template <typename T, size_t capacity>
T Stack<T,capacity>::top() const {
    if (!empty()) {
        return m_data[m_top];
    } else {
        cout << "stack is empty" << endl;
        /* throw "stack is empty"; */
    }
}

int main() {

    return 0;
}
