#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
	virtual void print() {
		cout << "Base::print()" << endl;
		}
	virtual void display() {
		cout << "Base::display()" << endl;
	}
	virtual void show() {
		cout << "Base::show()" << endl;
	}
private:
	long m_base = 10;
};

class Derived : public Base {
public:
	virtual void print() {
		cout << "Derived::print()" << endl;
	}
	virtual void display() {
		cout << "Derived::display()" << endl;
	}
	virtual void show() {
		cout << "Derived::show()" << endl;
	}
private:
	long m_derived = 100;
};

void test1() {
    Derived derived{};

    long* pDerived = reinterpret_cast<long*>(&derived); // 将派生类对象地址转换为long指针
    cout << pDerived[0] << endl; // 拿到派生类对象的第一个8字节内容—— 虚表基地址
    cout << pDerived[1] << endl; // 拿到派生类对象的第二个8字节内容—— 基类子对象的数据成员m_base=10
    cout << pDerived[2] << endl; // 拿到派生类对象的第三个8字节内容—— 派生类子对象的数据成员m_derived=100

    cout << "----------------" << endl;

    // 将虚函数指针强制为long类型指针数组
    long* pVTable = reinterpret_cast<long*>(pDerived[0]); // 将虚表基地址转换为long指针
    cout << pVTable[0] << endl; // 虚表中第一个8字节内容—— 即第一个成员函数print()的地址的long型解释
    cout << pVTable[1] << endl; // 虚表中第二个8字节内容—— 即第二个成员函数display()的地址的long型解释
    cout << pVTable[2] << endl; // 虚表中第三个8字节内容—— 即第三个成语函数show()的地址的long型解释
                                //
    cout << "----------------" << endl;

    // 强转为void(*)()类型函数指针
    void (*func1)() = reinterpret_cast<void (*)()>(pVTable[0]); // Derived::print()的地址转换为函数指针
    void (*func2)() = reinterpret_cast<void (*)()>(pVTable[1]); // Derived::display()的地址转换为函数指针
    void (*func3)() = reinterpret_cast<void (*)()>(pVTable[2]); // Derived::show()的地址转换为函数指针
    /* cout << func1 << endl; // error: 函数指针通过cout输出为1 */
    printf("%p\n", func1);
    printf("%p\n", func2);
    printf("%p\n", func3);
    func1(); // 访问的函数中用不到数据成员时能正常运行
    func2();
    func3();
    cout << "----------------" << endl;
    // 规范调用方式
    void (*func)(Derived*) = reinterpret_cast<void (*)(Derived*)>(pVTable[0]);
    func(&derived);

    cout << "----------------" << endl;

    // 或者使用typedef
    typedef void (*Function)();
    Function f = (Function)pVTable[0];
    printf("%p\n", f);
    f();
    f = (Function)pVTable[1];
    printf("%p\n", f);
    f();
    f = (Function)pVTable[2];
    printf("%p\n", f);
    f();
}

int main() {
    test1();

    return 0;
}
