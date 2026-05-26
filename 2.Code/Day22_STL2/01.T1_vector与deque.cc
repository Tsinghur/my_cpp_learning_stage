#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using std::cout; 
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::sort;

class Person {
public:
    Person(string name, double score = 0)
    : m_name(name)
    , m_score(score)
    {}

    friend void print(vector<Person>&);

    /* friend void test1(); */
    string getName() {
        return m_name;
    }

    double getScore() {
        return m_score;
    }

    void setScore(double score) {
        m_score = score;
    }
private:
    string m_name;
    double m_score;
};

void print(vector<Person>& v) {
    for (auto& e : v) {
        cout << "姓名：" << e.m_name << "   成绩：" << e.m_score << endl;
    }
}

void test1() {
    vector<Person> persons{
        {"aaa"},
        {"bbb"},
        {"ccc"},
        {"ddd"},
        {"eee"}
    };

    for (auto& person : persons) {
        deque<double> scores;
        cout << "分别输入" << person.getName() << "的所有成绩：" << endl; 
        for (int i = 0; i < 10; ++i) {
            cout << "评委" << i + 1 << "的打分：";
            double score;
            std::cin >> score;
            scores.push_back(score);
        }

        sort(scores.begin(), scores.end(), std::less<double>());
        scores.pop_front();
        scores.pop_back();
        person.setScore(0);
        for (auto& e : scores) {
            person.setScore(person.getScore() + e);
        }
        person.setScore(person.getScore() / scores.size());
    }

    print(persons);
}

int main() {
    test1();

    return 0;
}
