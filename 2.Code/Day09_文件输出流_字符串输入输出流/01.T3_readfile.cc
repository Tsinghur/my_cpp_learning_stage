#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// 按单词读取
void test1(ifstream& ifs1) { // C++ 标准库中，所有流对象（ifstream、ofstream、fstream 等）的拷贝构造函数都是被删除的
                             // 所以，只要需要传递流对象，必须使用引用（或指针），永远不要尝试按值传递
    string word;
    /* while ((ifs1 >> word).good()) { */
    while (ifs1 >> word) { // 判断条件直接使用流对象本身(什么状态都不用)才是最佳做法
                           // 用到了流对象中定义的一个隐式类型转换运算符operator bool,直接把流对象当成一个布尔值来判断
        cout << word << endl;
    }
}

// 按行读取
void test2(ifstream& ifs2) {
    // 若是继续读取test1读取之后的文件流，则不会读取到数据
    // 因为此时已经到达流末尾了，所以要重新打开一个流 或 重置偏移
    ifs2.clear(); // 因为上次读取最终进入到错误状态(eof)，所以先重置流的状态
    ifs2.seekg(0, std::ios::beg);
    string line;
    while (std::getline(ifs2, line)) { // <string>的全局函数，不是ifstream类的成员函数getline
        cout << line << endl;
    }
}

int main() {
    ifstream ifs("test.txt", std::ios::in);
    test1(ifs);
    cout << "--------------" << endl;;
    /* ifstream ifs2("test.txt", std::ios::in); */
    test2(ifs);

    ifs.close();
    return 0;
}
