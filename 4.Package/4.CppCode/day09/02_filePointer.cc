#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;

void test1()
{
    ifstream ifs { "data.txt" };
    // 获取文件指针的位置 tellg()
    int pos = ifs.tellg();
    cout << "pos : " << pos << endl; 

    // 读取字符数据
    char ch1 = ifs.get();
    cout << ch1 << endl;

    pos = ifs.tellg();
    cout << "pos : " << pos << endl; 

    char ch2 = ifs.get();
    cout << ch2 << endl;

    pos = ifs.tellg();
    cout << "pos : " << pos << endl; 

    cout << "---------" << endl;
    // 移动文件指针到指定位置
    // 可以使用绝对位置 / 相对位置
    /* ifs.seekg(0); //使用的是绝对位置 */
    // 使用相对位置, 指明相对的是谁
    ifs.seekg(1,std::ios::beg);
    pos = ifs.tellg();
    cout << "pos : " << pos << endl; 
    char ch3 = ifs.get();
    cout << ch3 << endl;

    pos = ifs.tellg();
    cout << "pos : " << pos << endl; 

    ifs.close();

}

void test2()
{
    ifstream ifs {"data.txt"};
    // 文件指针移动到末尾
    ifs.seekg(0, std::ios::end);
    // 获取文件指针的位置
    int size = ifs.tellg();
    // 创建一个数组用来存储读取的文件的数据
    char buf[size + 1];
    // 注意!! 还要移动指针到文件开头
    ifs.seekg(0);
    ifs.read(buf, size);
    cout << buf << endl;
    ifs.close();

}

void test3()
{
    // 可以修改打开模式: in ---> ate
    ifstream ifs {"data.txt",std::ios::ate};
    // 获取文件指针的位置
    int size = ifs.tellg();
    // 创建一个数组用来存储读取的文件的数据
    char buf[size + 1];
    // 注意!! 还要移动指针到文件开头
    ifs.seekg(0);
    ifs.read(buf, size);
    cout << buf << endl;
    ifs.close();

}

int main(int argc, char * argv[])
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

