#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void test1() {
    vector<char> v{'h', 'e', 'l', 'l', 'o'};
    // 法一：使用增强for循环的循环构建
    string s1;
    for (auto& e : v) {
        s1.push_back(e);
    }
    cout << s1 << endl;
    // 法二：使用迭代器范围的构造函数
    string s2(v.begin(), v.end());
    cout << s2 << endl;
    // 法四：使用C风格字符串首地址与字符个数的构造函数
    string s3(v.data(), v.size());
    cout << s3 << endl;
    // 法五：使用vector返回的C风格字符串的构造函数
    string s4(v.data());
    cout << s4 << endl;
}
int main() {
    test1();
    
    return 0;
}

