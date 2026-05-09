#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class CountEven {
public:
    CountEven() 
    : m_count(0)
    , m_callCount(0)
    {}
    void operator()(int val) {
        m_callCount++;
        if ((val & 1) == 0)
            m_count++;
    }
    int getCount() const {
        return m_count;
    }
    int getCallCount() const {
        return m_callCount;
    }
private:
    int m_count; // 偶数个数
    int m_callCount; // 调用次数
};

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    CountEven func;
    for (auto num : vec) {
        func(num);
    }

    cout << "调用次数" << func.getCallCount() << endl;
    cout << "偶数个数" << func.getCount() << endl;

    return 0;
}
