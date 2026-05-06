#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    Student(int num, string name, double score) 
    : m_num(num)
    , m_score(score)
    {
        m_name.append(name);
        cout << "Student(string&, int, double)" << endl;
    }
    void print() {
        cout << "学号：" << m_num << "   " << "姓名：" << m_name << "   " << "成绩：" << m_score << endl;
    }
private:
    int m_num;
    string m_name;
    double m_score;
};

int main() {
    Student s1{1, "zs", 80};
    Student s2{2, "ls", 90};
    s1.print();
    s2.print();

    return 0;
}
