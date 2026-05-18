#include <iostream>
#include <set>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::pair;

/*
 * set容器: 底层是红黑树
 * 特点:
 * 1.存储的数据是单列数据  一个一个 
 * 2.元素不能重复 元素是有序的 默认按照升序排列
 *
 * 使用场景:
 * 1.去重
 * 2.排序
 *
 * map容器: 存储的是双列数据(一对一对)
 * key-value数据, 键值对数据
 * 属性名 = 属性值
 * name = "zs"
 * city = "BJ"
 * age = 20
 *
 *
 * set的使用, 存储数据时 像vector类似 需要指明数据的类型是啥
 * set<int>
 * set<Student>
 * set<string>
 *
 */
// set容器的构建
void test1()
{
    // 无参构造函数---->空容器
    set<int> box1;
    // 初始化列表方式
    set<int> box2 { 3,1,2,5,4 };
    // 迭代器方式
    set<int> box3{ box2.begin(), box2.end() };
    // 拷贝构造
    /* set<int> box4 = box3; */
    set<int> box4 { box3 };

}

// 验证set容器的特点
void test2()
{
    /* set<int> box { 3,1,2,5,4 }; */
    set<int> box { 3,1,1,2,5,5,4 };
    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
    // 数据是有序的 升序  元素不能重复
}

// 元素查找 count / find
void test3()
{
    
    set<int> box { 3,1,2,5,4 };
    // cout(目标元素) 
    // 如果找到了 返回1
    // 没找到 返回0
    /* int result = box.count(3); */
    int result = box.count(6);
    if(result){
        cout << "find success!" << endl;
    }else{
        cout << "not found!" << endl;
    }
    cout << "-------" << endl;
    // find(目标元素)
    // 如果找到了 返回指向目标元素的迭代器
    // 没找到 返回end()
    // set<int>::iterator 
    /* auto it = box.find(3); */
    auto it = box.find(6);
    if(it != box.end()){
        cout << "find success" << endl;
        cout << *it << endl;
    }else{
        cout << "not found" << endl;
    }

}

// 增强for循环
void visitSet(set<int> & box)
{
    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}
// 迭代器循环
void visitSet2(set<int> & box)
{
    auto it  = box.begin();
    for(; it != box.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}

// 数据的插入 单个数据插入 / 批量数据插入
void test4()
{
   set<int> box; 
   // 单个数据插入
   box.insert(1);
   box.insert(2);
   visitSet(box);
   // 批量 
   // 初始化列表方式
   box.insert({5,4,3});
   visitSet(box);
   // 还可以使用迭代器
    set<int> box2{10, 11, 12};
    box.insert(box2.find(11), box2.end());

   visitSet(box);
   cout << "----------" << endl;
   pair<set<int>::iterator,bool> p = box.insert(100);
   if(p.second){
       cout << "insert success!" << endl;
       cout << *(p.first) << endl;
   }else{
       cout << "insert fail!" << endl;
   }
}

// pair: 存储一对数据 first second
void test5()
{
    // 使用时指明pair<first的类型,second的类型>
    pair<string,int> p{"age", 20};
    cout << p.first << endl;
    cout << p.second << endl;
}

// erase删除
void test6()
{
     set<int> box{1,2,3,4,5};
     visitSet(box);
     auto it = box.begin();
     ++it;
     ++it;
     box.erase(it);
     visitSet(box);
}

// set不能通过下标访问
void test7()
{
     set<int> box{1,2,3,4,5};
     /* cout << box[0] << endl; */
     // error 没有operator[]
}

void test8()
{
    set<string> box{"zs","ls","aa"};
    for(auto & e : box){
        cout << e << " ";
    }
    cout << endl;
}

// 如果存自定义类型的数据
class Student
{
public:
    Student(int id, string name, int age)
    : m_id(id)
    , m_name(name)
    , m_age(age)
    {}
    void print()
    {
        cout << m_id << " " << m_name << " "<< m_age << endl;
    }
    int m_id;
    string m_name;
    int m_age;
};

bool operator<(const Student & s1, const Student & s2)
{
    // 制定比较规则
    // 按照id比较
    /* return s1.m_id < s2.m_id; */
    return s1.m_age < s2.m_age;
}

void test9()
{
    set<Student> box;
    box.insert(Student{2,"zs",18});
    box.insert(Student{1,"ls",20});
    box.insert(Student{3,"ww",19});
    for(Student  e : box){
        e.print();
    }
}
int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    /* test3(); */
    /* test4(); */
    /* test5(); */
    /* test6(); */
    /* test8(); */
    test9();
    return 0;
}