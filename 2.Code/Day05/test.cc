#include <iostream>

using namespace std;

// ========== 1. const 数据成员的初始化 ==========
// const 数据成员必须在构造函数的初始化列表中初始化，不能在构造函数体内赋值
class ConstMember {
public:
    ConstMember(int val)
    : m_const(val)  // const成员只能在初始化列表中初始化
    {
        // m_const = val;  // 错误！const成员不能在函数体内赋值
        cout << "ConstMember(" << val << ")" << endl;
    }

    // 无参构造时给默认值
    ConstMember()
    : m_const(0)
    {
        cout << "ConstMember() default" << endl;
    }

    void print() const {
        cout << "m_const = " << m_const << endl;
    }

    int getValue() const {
        return m_const;
    }

private:
    const int m_const;
};

// ========== 2. const 成员函数 ==========
// const成员函数承诺不修改对象的数据成员（mutable除外）
class ConstFunc {
public:
    ConstFunc(int x, int y)
    : m_x(x)
    , m_y(y)
    , m_counter(0)
    {}

    // const成员函数：不能修改普通数据成员，可以修改mutable成员
    int getX() const {
        // m_x = 10;  // 错误！const成员函数不能修改普通成员
        ++m_counter;  // OK，mutable成员可以被修改
        return m_x;
    }

    int getY() const {
        ++m_counter;
        return m_y;
    }

    // 非const成员函数
    void setX(int x) {
        m_x = x;
    }

    void setY(int y) {
        m_y = y;
    }

    int getCallCount() const {
        return m_counter;
    }

private:
    int m_x;
    int m_y;
    mutable int m_counter;  // mutable成员可以在const函数中被修改
};

// ========== 3. const对象只能调用const成员函数 ==========
class ConstObject {
public:
    ConstObject(int val)
    : m_val(val)
    {}

    // const重载：根据对象的const属性自动选择
    void print() const {
        cout << "const print: " << m_val << endl;
    }

    void print() {
        cout << "non-const print: " << m_val << endl;
    }

    void modify(int val) {
        m_val = val;
    }

private:
    int m_val;
};

// ========== 4. static const 数据成员 ==========
// static const整型成员可以在类内直接初始化（C++11之前也支持）
class StaticConst {
public:
    static const int MAX_SIZE = 100;    // 类内初始化（整型常量）
    static const char FLAG = 'Y';       // char类型也可以

    // static constexpr 是C++11推荐的写法，支持更多类型
    static constexpr double PI = 3.14159;

    void print() const {
        cout << "MAX_SIZE = " << MAX_SIZE << endl;
        cout << "FLAG = " << FLAG << endl;
        cout << "PI = " << PI << endl;
    }
};

// 非整型的static const成员仍需类外定义（如果没有constexpr）
class StaticConstStr {
public:
    static const string DEFAULT_NAME;  // 只能在类外定义
    static const int ID = 999;         // 整型可类内初始化
};

const string StaticConstStr::DEFAULT_NAME = "hello";

// ========== 5. 引用数据成员（也是const的，必须在初始化列表中初始化） ==========
class RefMember {
public:
    RefMember(int& ref)
    : m_ref(ref)
    {}

    void print() const {
        cout << "m_ref = " << m_ref << endl;
    }

    int getRef() const {
        return m_ref;
    }

private:
    int& m_ref;  // 引用成员，必须在初始化列表中绑定
};

// ========== 6. 综合测试 ==========
class Complex {
public:
    Complex(int val, int& ref, const string& name)
    : m_const(val)        // const成员
    , m_ref(ref)          // 引用成员
    , m_name(name)        // const对象成员
    , m_id(++s_nextId)    // 可以在初始化列表中做简单运算
    {}

    void print() const {
        cout << "m_const = " << m_const
             << ", m_ref = " << m_ref
             << ", m_name = " << m_name
             << ", m_id = " << m_id
             << endl;
    }

    int id() const { return m_id; }
    static int nextId() { return s_nextId; }

private:
    const int m_const;
    int& m_ref;
    const string m_name;
    const int m_id;

    static int s_nextId;  // static 非const成员类外初始化
};

int Complex::s_nextId = 0;

// ========== 测试函数 ==========

void test_const_member() {
    cout << "===== const 数据成员测试 =====" << endl;
    ConstMember cm1(42);
    cm1.print();

    ConstMember cm2;
    cm2.print();

    const ConstMember cm3(100);  // const对象
    cout << "cm3.getValue() = " << cm3.getValue() << endl;
    // cm3 只能调用const成员函数
}

void test_const_func() {
    cout << "\n===== const 成员函数测试 =====" << endl;
    ConstFunc cf(10, 20);
    cout << "x = " << cf.getX() << ", y = " << cf.getY() << endl;
    cout << "call count = " << cf.getCallCount() << endl;

    const ConstFunc ccf(1, 2);  // const对象
    cout << "x = " << ccf.getX() << ", y = " << ccf.getY() << endl;
    // ccf.setX(5);  // 错误！const对象不能调用非const成员函数
}

void test_const_overload() {
    cout << "\n===== const重载测试 =====" << endl;
    ConstObject obj(99);
    obj.print();          // 调用非const版本

    const ConstObject cobj(88);
    cobj.print();         // 调用const版本
    // cobj.modify(10);   // 错误！const对象不能调用非const函数
}

void test_static_const() {
    cout << "\n===== static const 测试 =====" << endl;
    StaticConst sc;
    sc.print();

    // 直接通过类名访问
    cout << "StaticConst::MAX_SIZE = " << StaticConst::MAX_SIZE << endl;
    cout << "StaticConst::PI = " << StaticConst::PI << endl;

    StaticConstStr scs;
    cout << "StaticConstStr::ID = " << StaticConstStr::ID << endl;
    cout << "StaticConstStr::DEFAULT_NAME = " << StaticConstStr::DEFAULT_NAME << endl;
}

void test_ref_member() {
    cout << "\n===== 引用数据成员测试 =====" << endl;
    int value = 55;
    RefMember rm(value);
    rm.print();

    value = 66;  // 修改原值，引用成员看到的值也会变
    rm.print();
}

void test_complex() {
    cout << "\n===== 综合测试 =====" << endl;
    int external = 77;
    Complex c1(10, external, "obj1");
    c1.print();

    external = 88;
    c1.print();  // m_ref 会跟随 external 变化

    Complex c2(20, external, "obj2");
    c2.print();
    cout << "c1.id() = " << c1.id() << ", c2.id() = " << c2.id() << endl;
}

int main() {
    test_const_member();
    test_const_func();
    test_const_overload();
    test_static_const();
    test_ref_member();
    test_complex();

    return 0;
}
