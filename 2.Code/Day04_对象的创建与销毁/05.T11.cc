#include <string.h>
#include <iostream>

using namespace std;

class Student {
public:
    Student(const char* name, int num, int age) 
    : m_name(new char[strlen(name) + 1]{})
    , m_num(num)
    , m_age(age)
    {
        strcpy(m_name, name);
    }
    ~Student() {
        delete[] m_name;
    }
private:
    char* m_name; // 不能为const char*，应该允许写入，否则无法初始化
    int m_num;
    int m_age;
};

int main() {
    Student s1("zs", 1, 20);
    Student s2("ls", 2, 21);
    Student s3("ww", 3, 22);

    return 0;
}
