#include <iostream>
#include <string>
#include <set>
#include <utility> // pair

using std::cout;
using std::endl;
using std::string;

class Student {
public:
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {}
    // std::set 强制要求：必须为自定义类型提供「严格弱序」的比较规则
    // std::set强制要求：容器里的所有元素，都是const（只读不可修改）的
    /* bool operator<(const Student& rhs); // error：没有保证左操作数为只读，即this指针指向的本对象不为只读 */
    // 形式1：所以要是采用成员函数形式，则需要使用const成员函数
    bool operator<(const Student& rhs) const {
        return m_id < rhs.m_id;
    }
    // 形式2：使用友元函数形式
    /* friend bool operator<(const Student& s1, const Student& s2); */
    friend void visitSet(const std::set<Student>& box);
private:
    int m_id;
    string m_name;
    int m_age;
};

void visitSet(const std::set<Student>& box) {
    for (auto& x : box) {
        cout << x.m_id << " " << x.m_name << " " << x.m_age << endl;
    }
}

// 形式2：使用友元函数形式
/* bool operator<(const Student & s1, const Student & s2) { */
/*     /1* return s1.m_id < s2.m_id; *1/ */
/* } */

// set容器的构造
/*
关联容器初始化最好不要使用()
std::set<int> box(1); // error：set没有「接收单个数值」的构造，而vector(5)合法：vector有「指定元素个数」的构造
std::set<int> box({1}); // right
*/
void test1() {
    // 1.无参构造函数—— >空容器
    std::set<Student> box1;
    // 2.初始化列表方式
    /* std::set<Student> box2(Student{1, "zs", 18}); // error */
    /* std::set<Student> box2({Student{1, "zs", 18}}); // right */
    std::set<Student> box2{Student{1, "zs", 18}};
    // std::set<Student> box2{{1, "zs", 18}};
    std::set<Student> box{{1, "zs", 18}, {3, "ww", 20}, {2, "ls", 19}};
    // 3.拷贝构造
    std::set<Student> box3 = box2;
    // 4.迭代器方式
    std::set<Student> box4(box.begin(), box.end());

    visitSet(box1);
    visitSet(box2);
    visitSet(box3);
    cout << "-------------------" << endl;
    visitSet(box4);
}

// set容器的特点：升序、不重复
void test2() {
    std::set<int> box{3, 1, 1, 2, 5, 6, 4};
    for (auto& e : box) {
        cout << e << " ";
    }
    cout << endl;
    // 或
    auto it = box.begin();
    for (; it != box.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

// set容器的数据插入：insert
// 注意：调用插入成员函数则一定得使用(),不能像初始化时还可使用{}
void test3() {
    std::set<Student> box;
    // 1.单个数据插入
    box.insert(Student{2, "zs", 18});
    /* box.insert({2, "zs", 18}); */
    // 2.批量数据插入
    // 初始化列表方式
    /* box.insert({1, "ls", 19}, {"3", "ww", 20}); // error */
    box.insert({{1, "ls", 19}, {3, "ww", 20}}); // right
    visitSet(box);
    cout << "---------------" << endl;
    // 还可使用迭代器方式
    std::set<int> box1{10, 11, 12};
    std::set<int> box2;
    box2.insert(box1.find(11), box1.end());
    for (auto& e : box2) {
        cout << e << " ";
    }
    cout << endl;
}

// pair：存储一对数据，first、second
void test4() {
    std::pair<string, int> p{"age", 20};
    cout << p.first << endl;
    cout << p.second << endl;
    cout << "-------------" << endl;
    std::set<int> box;
    /* box.insert(100); // 重复插入就会插入失败 */
    std::pair<std::set<int>::iterator, bool> p2 = box.insert(100);
    if (p2.second) {
        cout << "insert success" << endl;
        cout << *p2.first << endl;
    } else {
        cout << "insert failed" << endl;
    }
}

// set容器的数据删除：erase
void test5() {
    std::set<int> box{1, 2, 3, 4, 5};
    for (auto& e : box) {
        cout << e << " ";
    }
    cout << endl;
    cout << "-------------" << endl;
    auto it = box.begin();
    it++;
    it++;
    box.erase(it);
    for (auto& e : box) {
        cout << e << " ";
    }
    cout << endl;
}

// set容器不能通过下标访问

int main() {
    /* test1(); */ 
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();

    return 0;
}
