#include <iostream>
#include <string>
#include <vector>

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
    Student s3{3, "ww", 100};
    vector<Student> students{s1, s2, s3};
    
    for (auto& s : students) {
        s.print();
    }
    cout << "----------------------------------" << endl;
    auto it = students.begin();
    while (it != students.end()) {
        (*it).print();
        it++;
    }
    cout << "----------------------------------" << endl;
    /* Student s4(4, "gzh", 99); */
    /* students.push_back(s4); */
    students.emplace_back(4, "gzh", 99);
    auto its = students.begin();
    while (its != students.end()) {
        (*its).print();
        its++;
    }

    return 0;
}
