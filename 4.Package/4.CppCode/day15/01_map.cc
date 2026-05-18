#include <iostream>
#include <map>
#include <utility>

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
/*
 * 使用场景: 一般情况适合数据统计使用
 *
 * 举例:
 * 班级里面不同省份的同学有多少个
 * 河南:3
 * 湖北:5
 * key:省份 
 * value:个数
 * map<string,int>
 *
 *
 * 班级里面考试情况, 优良差的同学有多少个
 *
 * 班级里面不同省份的同学都是谁?
 * key:省份
 * value: vector<string>
 * map<string,vector<string> 
 *
 * map<string,vector<Student>>
 *
 */
void visitMap(map<string,int> & m)
{
    for(auto & p : m){
        cout << p.first << "=" << p.second << endl;
    }
}

// map的operator[]
void test1()
{
    map<string,int> m; 
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});
    visitMap(m);
    cout << "-----" << endl;
    // 还可以通过operator[key]添加元素
    m["two"] = 20;
    m["five"] = 5;
    visitMap(m);
}

// 删除元素erase
void test2()
{
    map<string,int> m; 
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});
    visitMap(m);
    cout << "--------" << endl;
    auto it = m.begin();
    ++it;
    // 参数为迭代器
    m.erase(it);
    visitMap(m);
}


int main(int argc, char * argv[])
{
    /* test1(); */
    test2();
    return 0;
}

