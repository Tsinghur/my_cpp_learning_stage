#include <iostream>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::list;

class Student {
public:
    Student(string name, double chineseScore, double mathScore, double englishScore)
    : m_name(name)
    , m_chineseScore(chineseScore)
    , m_mathScore(mathScore)
    , m_englishScore(englishScore)
    , m_totalScore(chineseScore + mathScore + englishScore)
    {}

    /* friend void print(list<Student>& box); */

    string getName() const {
        return m_name;
    }

    double getTotalScore() const {
        return m_totalScore;
    }

    double getChineseScore() const {
        return m_chineseScore;
    }
private:
    string m_name;
    double m_chineseScore;
    double m_mathScore;
    double m_englishScore;
    double m_totalScore;
};

void print(const list<Student>& box) {
    for (const auto& e : box) {
        /* cout << e.getName() << " " << e.getTotalScore() << " " << e.getChineseScore() << endl; */
        cout    << "姓名："     << e.getName()
            << "  总成绩：" << e.getTotalScore()
            << "  语文："   << e.getChineseScore() << endl;
    }
}

struct Compare {
    bool operator()(const Student& lhs, const Student& rhs) const {
        if (lhs.getTotalScore() != rhs.getTotalScore())
            return lhs.getTotalScore() > rhs.getTotalScore();
        else
            return lhs.getChineseScore() > rhs.getChineseScore();
    }
};

void test1() {
    list<Student> students{
        {"aaa", 2, 3, 3},
        {"bbb", 2, 2, 2},
        {"ccc", 3, 3, 2},
        {"ddd", 4, 4, 4},
        {"eee", 5, 5, 5}
    };

    students.sort(Compare());

    print(students);
}

int main() {
    test1();

    return 0;
}
