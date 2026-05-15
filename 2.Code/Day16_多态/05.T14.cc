#include <cstring>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Person {
public:
    Person(const char* name, int age)
    : m_name(new char[strlen(name) + 1]{})
    , m_age(age)
    {
        strcpy(m_name, name);
    }
    Person(const Person& p)
    : m_name(new char[strlen(p.m_name) + 1]{})
    , m_age(p.m_age)
    {
        strcpy(m_name, p.m_name);
    }
    Person& operator=(const Person& p) {
        if (this != &p) {
            if (m_name) {
                delete[] m_name;
                m_name = nullptr;
            }
            m_name = new char[strlen(p.m_name) + 1]{};
            strcpy(m_name, p.m_name);
            m_age = p.m_age;
        }
        return *this;
    }
    ~Person() {
        if (m_name) {
            delete[] m_name;
            m_name = nullptr;
        }
    }
    void func() const {
        display();
    }
    virtual void display() const = 0;
    const char* getName() const { // display为const成员函数，即const this指针，即const对象要能调用这个函数，所以改为const成员函数版本        return m_name;
        return m_name;
    }
    int getAge() const {
        return m_age;
    }
private:
    char* m_name;
    int m_age;
};

class Employee : public Person {
public:
    Employee(const char* m_name, int age, const char* division, double salary)
    : Person(m_name, age)
    , m_division(new char[strlen(division) + 1]{})
    , m_salary(salary)
    {
        strcpy(m_division, division);
    }
    Employee(const Person& p, const char* division, double salary)
    : Person(p)
    , m_division(new char[strlen(division) + 1]{})
    , m_salary(salary)
    {
        strcpy(m_division, division);
    }
    Employee(const Employee& e)
    : Person(e) // 值拷贝创建基类子对象，然后通过这个子对象来拷贝基类部分
    , m_division(new char[strlen(e.m_division) + 1]{})
    , m_salary(e.m_salary)
    {
        strcpy(m_division, e.m_division);
    }
    Employee& operator=(const Employee& e)
    {
        /* Person::operator=(e); // 放在外面是多余的 */
        if (this != &e) {
            Person::operator=(e);
            if (m_division) {
                delete[] m_division;
                m_division = nullptr;
            }
            m_division = new char[strlen(e.m_division) + 1]{};
            strcpy(m_division, e.m_division);
            m_salary = e.m_salary;
        }
        return *this;
    }
    ~Employee() {
        if (m_division) {
            delete[] m_division;
            m_division = nullptr;
        }
    }
    void display() const override {
        cout << "姓名：" << getName() << endl;
        cout << "年龄：" << getAge() << endl;
        cout << "部门：" << m_division << endl;
        cout << "工资：" << m_salary << endl;
        cout << "--------------" << endl;
    }
    friend void printInfo(vector<Employee>& es);
    friend double getAverageSalary(vector<Employee>& es);
private:
    char* m_division;
    double m_salary;
};

void printInfo(vector<Employee>& es) {
    for (auto& e : es) {
        Person& p = e;
        p.func();
        /* e.display(); // 根本用不到多态，因为 */
    }
}

double getAverageSalary(vector<Employee>& es) {
    double res = 0;
    for (auto& e : es) {
        res += e.m_salary;
    }
    // 需要做空容器保护
    return es.size() == 0 ? 0 : res / es.size();
}

void test1() {
    // 1. 创建 Employee 对象（直接利用 Employee 作为 Person 的引用）
    Employee e1("张三", 30, "研发部", 8000.0);
    Employee e2("李四", 25, "市场部", 6000.0);
    Employee e3("王五", 28, "研发部", 7500.0);

    // 2. 测试拷贝构造
    Employee e4(e1);                // 拷贝 e1
    e4 = Employee("张三副本", 30, "研发部", 9000.0); // 修改 e4 内容（通过赋值）

    // 3. 测试赋值运算符
    Employee e5("赵六", 35, "管理部", 10000.0);
    e5 = e2;                        // e5 变为 e2 的副本，两者独立
    e2 = Employee("李四", 25, "市场部", 6500.0); // 修改 e2，验证 e5 不受影响

    // 4. 测试自赋值（不会崩溃）
    e3 = e3;

    // 5. 放入 vector
    vector<Employee> staff;
    staff.push_back(e1);
    staff.push_back(e2);
    staff.push_back(e3);
    staff.push_back(e4);
    staff.push_back(e5);

    // 6. 测试打印（多态展示）
    cout << "===== 员工信息 =====" << endl;
    printInfo(staff);

    // 7. 测试平均工资
    cout << "平均工资: " << getAverageSalary(staff) << endl;

    // 8. 测试空容器
    vector<Employee> empty_staff;
    cout << "空容器平均工资: " << getAverageSalary(empty_staff) << endl;
}

int main() {
    test1();

    return 0;
}
