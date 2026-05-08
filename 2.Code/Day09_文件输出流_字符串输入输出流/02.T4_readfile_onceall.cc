#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    ifstream ifs("test.txt");
    ifs.seekg(0, std::ios::end);
    int size = ifs.tellg(); // 不能使用auto，因为真正返回值为std::streampos类
    ifs.seekg(0, std::ios::beg);
    char buf[size + 1] = {}; // 数组大小要求为整型int，std::streampos不可作为数组大小
    /* ifs.read(buf, size); */
    ifs.read(buf, size - 1); //这样可不读取换行 
    cout << buf << endl; // 文件末尾存在隐式换行,若是也读取进来则结果末尾打印2个换行

    ifs.close();
    return 0;
}
