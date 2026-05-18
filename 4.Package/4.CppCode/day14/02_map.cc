#include <iostream>
#include <map>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::vector;


/*
 * map: 存储的是双列数据(一对数据)的容器
 * key-value(键值对数据), 具有自我描述性的数据
 * name = "zs"
 * city = "BJ"
 *
 * 底层采用红黑树
 * 特点:
 * 1.key不能重复
 * 2.按key升序进行排序
 *
 * map的使用: 指明key是个什么类型 value是个什么类型
 * 
 * map<key的类型,value的类型>
 */

// map的构建
void test1()
{
    // 无参构造 ---> 空容器
    map<int,string> m1; // pair<int,string>

    // 通过初始化列表构建 存的是pair对象
    map<int,string> m2{
        pair<int,string>{2,"zs"},        
        pair<int,string>{1,"ls"},        
        pair<int,string>{3,"ww"}        
    };
    // 简写
    map<int,string> m3{
        {2,"zs"},        
        {1,"ls"},        
        {3,"ww"}        
    };
    // 通过make_pair函数创建一个pair对象
    map<int,string> m4{
        std::make_pair(2,"zs"),
        std::make_pair(1,"ls"),
        std::make_pair(3,"ww")
    };
    // 可以通过迭代器方式构建
    map<int,string> m5{ m4.begin(), m4.end() };

    // 可以通过拷贝构造函数构建
    map<int,string> m6{ m4 };


    // 更换一下类型
    map<string,string> m7;
    map<string,int> m8;
    map<string,vector<int>> m9;
    
}

// 容器的遍历
void visitMap(map<int,string>& m)
{
    for(auto & p : m){
        cout << p.first << " = " << p.second<<endl;
    }
    cout << endl;
}

// 迭代器遍历
void visitMap2(map<int,string>& m)
{
    auto it = m.begin();
    for(; it != m.end(); ++it){
        /* cout << (*it).first << endl; */
        /* cout << (*it).second << endl; */
        cout << it->first << endl;
        cout << it->second << endl;
    }
    cout << endl;
}

// 验证map的特点
void test2()
{
    map<int,string> m{
        {2,"zs"},        
        {2,"zs"},        
        {5,"zs"},        
        {1,"ls"},        
        {3,"ww"}        
    };

    visitMap(m);
    // key不能重复 value无所谓可以重复
    // 按照key升序排序
}

// map的查找
void test3()
{
    map<int,string> m{
        {2,"zs"},        
        {5,"zs"},        
        {1,"ls"},        
        {3,"ww"}        
    };
    // count(目标元素的key)
    // 找到了返回1
    // 没找到返回0
    int result = m.count(3);
    if(result){
        cout << "find success!" << endl;
    }
    cout << "-------" << endl;
    // find(目标元素的key)
    // 找到了返回 指向该元素的迭代器
    // 没找到返回end()
    auto it = m.find(3);
    if(it != m.end()){
        cout << "find success!" << endl;
        cout << it->first << endl;
        cout << it->second << endl;
    }
}

// insert
void test4()
{

    map<int,string> m;
    // 单个数据的插入
    m.insert(pair<int,string>{1,"zs"});
    m.insert(std::make_pair(2,"ww"));
    m.insert({3,"ls"});

    // 批量的插入方式
    m.insert({
        {5,"zs"},
        {4,"ww"},
        {3,"ls"},
     });
    visitMap(m);
}

// operator[]
void test5()
{
    // map支持下标访问
    // 通过key获取value
    map<int,string> m{
        {2,"zs"},        
        {5,"zs"},        
        {1,"ls"},        
        {3,"ww"}        
    };
    m[2] = "zss";
    cout << m[2] << endl;

    map<string,string> m2{
        {"city", "BJ"},
        {"name", "zs"},
        {"gender", "male"},
    };
    cout << m2["city"] << endl;
    cout << m2["name"] << endl;
    cout << "------" << endl;
    //还可以通过下标的方式进行插入
    m2["age"] = "20";
    for(auto & p : m2){
        cout << p.first << "=" << p.second<< endl;
    }
    cout << "------" << endl;
    m2["class"];
    for(auto & p : m2){
        cout << p.first << "=" << p.second<< endl;
    }

}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    test5();
    return 0;
}

