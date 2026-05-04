#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    string id;    
    string name;  
    int age;      

public:
    // 默认构造函数
    Student() : id(""), name(""), age(0) {
        cout << "默认构造，学号：" << id << endl;
    }

    // 带参构造函数
    Student(const string& sid, const string& sname, int sage)
        : id(sid), name(sname), age(sage) {
        cout << "带参构造，学号：" << id << "，姓名：" << name << "，年龄：" << age << endl;
    }

    // 拷贝构造函数
    Student(const Student& other)
        : id(other.id), name(other.name), age(other.age) {
        cout << "拷贝构造，复制学号：" << other.id << endl;
    }

    // 拷贝赋值运算符
    Student& operator=(const Student& other) {
        if (this != &other) {
            id = other.id;
            name = other.name;
            age = other.age;
            cout << "赋值运算，目标学号：" << id << endl;
        }
        return *this;
    }

    // 析构函数
    ~Student() {
        cout << "析构，学号：" << id << "，姓名：" << name << endl;
    }

    // 输出学生信息
    void print() const {
        cout << "学生信息 -> 学号：" << id 
             << "，姓名：" << name 
             << "，年龄：" << age << endl;
    }

    // 设置年龄
    void setAge(int newAge) { age = newAge; }
};

int main() {
    cout << "===== 1. 创建两个学生对象 =====" << endl;
    Student s1("2024001", "张三", 20);
    Student s2("2024002", "李四", 21);

    cout << "\n===== 2. 输出 s1 和 s2 =====" << endl;
    s1.print();
    s2.print();

    cout << "\n===== 3. 拷贝构造 s3（从 s1）=====" << endl;
    Student s3(s1);   // 或 Student s3 = s1;

    cout << "\n===== 4. 将 s2 赋值给 s1 =====" << endl;
    s1 = s2;

    cout << "\n===== 5. 输出赋值后的 s1 =====" << endl;
    s1.print();

    cout << "\n===== 程序结束，对象将依次析构 =====" << endl;
    return 0;
}
