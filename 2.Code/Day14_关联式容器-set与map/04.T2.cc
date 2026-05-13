#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;

void test1() {
    std::map<string,int> m;
    m.insert({
        {"张三", 20}, 
        {"李四", 21}, 
        {"赵六", 22}}
    );
    cout << "张三的年龄是：" << m.find("张三")->second << endl;
    cout << "----------------" << endl;
    m["李四"] = 19;
    m["王五"] = 23;
    for (auto& p : m) {
        cout << p.first << "的年龄是：" << p.second << endl;
    }
}

int main() {
    test1();

    return 0;
}
