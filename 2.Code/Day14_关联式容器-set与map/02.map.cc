#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

// map容器的遍历
void visitMap(std::map<int,string>& map) {
    // 1.容器遍历
    for (auto& p : map) { // 因为map中存储的是pair对象即一对数据
        cout << p.first << "=" << p.second << endl;
    }
    cout <<"重复遍历" << endl;
    // 2.迭代器遍历
    auto it = map.begin();
    for (; it != map.end(); it++) {
        /* cout << (*it).first << "=" << (*it).second << endl; */
        // 或
        cout << it->first << "=" << it->second << endl;
    }
    cout << endl;
}

// map的构建
void test1() {
    // 1.无参构造
    std::map<int, string> m1;
    // 2.通过初始化列表方式构造
    std::map<int, string> m2({
        std::pair<int, string>{2, "zs"}, 
        std::pair<int, string>{1, "ls"},
        std::pair<int, string>{3, "ww"}
    }); // ()可省略，在初始化时即构造函数中{}有()的功效
        // ！但是，不能外层是{}内层是()，这样的话只能成功插入{3, "ww"}
    // 初始化列表方式的简写形式
    std::map<int, string> m3{
        {2, "zs"}, 
        {1, "ls"},
        {3, "ww"}
    };
    // 3.通过make_pair创建一个pair对象，其为函数—— 所以{}替换为()
    std::map<int, string> m4{
        std::make_pair(2, "zs"), 
        std::make_pair(1, "ls"),
        std::make_pair(3, "ww")
    };
    // 4.通过拷贝构造函数
    /* std::map<int,string> m5 = m4; */
    /* std::map<int,string> m5(m4); */
    std::map<int,string> m5{m4};
    // 5.通过迭代器方式构建
    /* std::map<int,string> m6{(m5.begin(), m5.end())}; // error */
    /* std::map<int,string> m6({m5.begin(), m5.end()}); // right */
    /* std::map<int,string> m6{m5.begin(), m5.end()}; // right */
    std::map<int,string> m6(m5.begin(), m5.end()); // 最标准做法

    visitMap(m1);
    visitMap(m2);
    visitMap(m3);
    visitMap(m4);
    visitMap(m5);
    visitMap(m6);
}

// map的特点：按key升序排序 且 key不能重复value无所谓

// map容器的数据插入
void test2() {
    std::map<int, string> m;
    // 1.单个数据的插入
    /* m.insert(3, "ww"); // error */
    /* m.insert{3, "ww"}; // error */
    /* m.insert(pair<int,string>{3, "ww"}); // right */
    m.insert({3, "ww"}); // 上一行简写
    // 2.批量插入
    /* m.insert({1, "zs"}, {2, "ls"}); // error */
    /* m.insert{{1, "zs"}, {2, "ls"}}; // error */
    m.insert({{1, "zs"}, {2, "ls"}}); // right
    visitMap(m);
    // 还可以使用迭代器方式
    std::map<int, string> m2;
    m2.insert(m.begin(), m.end());
    visitMap(m2);

}

// map支持下标访问
// operator[]：通过key获取value
void test3() {
    std::map<int,string> m{
        {2, "zs"},
        {5, "zs"},
        {1, "ls"},
        {3, "ww"}
    };
    m[2] = "zss";
    cout << m[2] << endl;

    std::map<string,string> m2{
        {"city", "BJ"},
        {"name", "zs"},
        {"gender", "male"}
    };
    cout << m2["city"] << endl;
    cout << m2["name"] << endl;
    cout << "----------" << endl;
    // 还可以通过下标的方式进行数据插入
    m2["age"] = "20";
    for (auto& p : m2) {
        cout << p.first << "=" << p.second << endl;
    }
    cout << "----------" << endl;
    m2["class"];
    // map对象[不存在的键];
    // 1.插入这个新键（key）
    // 2.给对应的值（value）赋默认值
    //      string 的默认值 = 空字符串 ""
    //      int 的默认值 = 0
    for (auto& p : m2) {
        cout << p.first << "=" << p.second << endl;
    }
}

int main() {
    /* test1(); */
    test2();
    /* test3(); */

    return 0;
}
