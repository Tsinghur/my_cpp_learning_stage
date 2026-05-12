#include <cstring>
#include <iostream>
#include <algorithm> // std::swap
#include <cassert>

using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    // 构造函数
    String(const char* pStr = "") {
        _size = strlen(pStr);
        if (_size < 16) {
            // 小字符串：直接放在内部数组，最多15字符 + '\0'
            strcpy(_buffer._local, pStr);
            _capacity = 15;   // 有效容量15
        } else {
            _buffer._pointer = new char[_size + 1];
            strcpy(_buffer._pointer, pStr);
            _capacity = _size;
        }
    }

    // 析构函数
    ~String() {
        if (_size >= 16) {
            delete[] _buffer._pointer;
        }
        // SSO时无需清理，或可保留memset用于调试：
        // else { memset(_buffer._local, 0, 16); }
    }

    // 拷贝构造函数
    String(const String& rhs) {
        _size = rhs._size;
        _capacity = rhs._capacity;
        if (_size < 16) {
            strcpy(_buffer._local, rhs._buffer._local);
        } else {
            _buffer._pointer = new char[_size + 1];
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        }
    }

    // 拷贝赋值运算符（copy-and-swap）
    String& operator=(String rhs) {
        swap(rhs);
        return *this;
    }

    // 交换函数
    void swap(String& other) noexcept {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_buffer, other._buffer);  // 直接交换union
    }

    // 下标访问
    char& operator[](size_t idx) {
        // 简单模拟：越界时断言，便于调试
        assert(idx < _size && "String index out of range");
        return _size < 16 ? _buffer._local[idx] : _buffer._pointer[idx];
    }

    // 常量版本（方便 const 对象使用）
    const char& operator[](size_t idx) const {
        assert(idx < _size && "String index out of range");
        return _size < 16 ? _buffer._local[idx] : _buffer._pointer[idx];
    }

    // 获取大小
    size_t size() const { return _size; }

    // 友元输出运算符
    friend ostream& operator<<(ostream& os, const String& rhs);

private:
    union Buffer {
        char* _pointer;
        char _local[16];
        Buffer() { memset(this, 0, sizeof(Buffer)); }
        ~Buffer() {} // 无操作，由外部类管理资源
    };

    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};

// 输出运算符实现
ostream& operator<<(ostream& os, const String& rhs) {
    if (rhs._size < 16) {
        os << rhs._buffer._local;
    } else {
        os << rhs._buffer._pointer;
    }
    return os;
}

// ---------- 测试代码 ----------
void test0() {
    // 测试小字符串（SSO）
    String ss1("Hello");
    String ss2 = ss1;            // 拷贝构造
    String ss3;
    ss3 = ss1;                  // 拷贝赋值

    cout << "--- SSO strings ---\n";
    cout << "ss1: " << ss1 << ", size = " << ss1.size() << endl;
    cout << "ss2: " << ss2 << endl;
    cout << "ss3: " << ss3 << endl;

    // 修改不会相互影响
    ss1[0] = 'Y';
    cout << "After ss1[0] = 'Y':\n";
    cout << "ss1: " << ss1 << endl;
    cout << "ss2: " << ss2 << endl;

    // 测试长字符串（堆分配）
    String ls1("This is a very long string that does not fit in SSO buffer.");
    String ls2 = ls1;
    cout << "\n--- Heap strings ---\n";
    cout << "ls1: " << ls1 << ", size = " << ls1.size() << endl;
    cout << "ls2: " << ls2 << endl;

    ls1[10] = 'X';
    cout << "After ls1[10] = 'X':\n";
    cout << "ls1: " << ls1 << endl;
    cout << "ls2: " << ls2 << endl;

    // 混合赋值
    String mix;
    mix = ss1;   // 短 -> 短
    mix = ls1;   // 短 -> 长
    cout << "\nAfter mix = ls1:\n";
    cout << "mix: " << mix << endl;
}

int main() {
    test0();
    return 0;
}
