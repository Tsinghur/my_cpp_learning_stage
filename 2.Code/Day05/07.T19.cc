#include <string.h>
#include <iostream>

using namespace std;

class Student {
public:
    Student(int num, const char* name, int age) 
        : m_num(num)
          , m_name(new char[strlen(name) + 1]{})
          , m_age(age)
          {
              strcpy(this->m_name, name);
              cout << "Student num " << this->m_num << endl;
          }
    // 构造函数的初始化列表阶段，只有基类和已经在列表中初始化完成的成员才是可用的
    // 对于当前类中尚未被初始化的成员，通过 this 去访问它们（哪怕只读取）是未定义行为
    Student(const Student& s) // 初始化列表中不能使用this指针
        : m_num(s.m_num)
          , m_name(new char[strlen(s.m_name) + 1]{})
          , m_age(s.m_age)
          {
              strcpy(this->m_name, s.m_name);
              cout << "copy Student num " << this->m_num << endl;
          }
    Student& operator=(const Student& s) {
        if (this == &s) // 防止自我赋值
            return *this;
        if (this->m_name) {
            delete [] this->m_name;
            this->m_name = nullptr;
        }
        this->m_num = s.m_num;
        this->m_name = new char[strlen(s.m_name) + 1]{};
        strcpy(this->m_name, s.m_name);
        this->m_age = s.m_age;
        cout << "operator= Student num " << this->m_num << endl;
        return *this;
    }
    ~Student() {
        if (this->m_name) {
            delete [] this->m_name;
            this->m_name = nullptr;
        }
        cout << "~Student num " << this->m_num << endl;
    }
    void print() {
        cout << "Student num " << this->m_num << endl;
        cout << "Student name " << this->m_name << endl;
        cout << "Student age " << this->m_age << endl;
    }
private:
    int m_num;
    char* m_name;
    int m_age;
};

int main() {
    Student s1(1, "zs", 20);
    cout << "s1:" << endl;
    s1.print();

    cout << endl;

    /* Student s2(s1); // 显式调用拷贝构造函数 */
    Student s2 = s1; // 这种"拷贝初始化"语法要求隐式转换，如果用 explicit 修饰拷贝构造函数这种拷贝初始化就不合法
    cout << "s2:" << endl;
    s2.print();

    cout << endl;

    Student s3(3, "ls", 21);
    cout << "s3 before = :" << endl;
    s3.print();
    s3 = s1;
    cout << "s3 after = :" << endl;
    s3.print();

    cout << endl;

    return 0;
}
