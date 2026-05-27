#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::vector;

class wordConvert {
public:
    wordConvert(const string& filePath, const string& mapFilePath) {
        // 初始化转换规则文件容器
        ifstream ifsMapFile(mapFilePath);
        if (!ifsMapFile) {
            throw std::runtime_error("无法打开规则文件: " + mapFilePath);
        }
        string line;
        while (getline(ifsMapFile, line)) {
            istringstream iss(line);
            string key, value;
            // while (iss >> key) {
            if (iss >> key) { // 因为每行固定是一对“键+值”，所以改为一个确定性的读取逻辑，避免多余的while造成误解
                iss >> std::ws; // 空白跳过符
                // string value(iss.str()); // error: 会将整个iss中的内容拷贝进value
                // 使用getline是根据当前流的指针位置读取的
                getline(iss, value);
                m_convertRules[key] = value;
            }
        }
        // 初始化转换后的文件容器
        ifstream ifsFile(filePath);
        if (!ifsFile) {
            throw std::runtime_error("无法打开规则文件: " + mapFilePath);
        }
        while (getline(ifsFile, line)) {
            istringstream iss(line);
            string newLine;
            string key;
            while (iss >> key) {
                if (!newLine.empty())
                    newLine += ' '; // 单词间加空格
                if (m_convertRules.find(key) != m_convertRules.end())
                    newLine += m_convertRules[key];
                else
                    newLine += key;
            }
            // if (!newLine.empty())
                m_file.push_back(newLine); // 保留空行
        }
    }
    // unordered_map<string,string>& getConvertRules() {
    //     return m_convertRules;
    // }
    // vector<string>& getFile() {
    //     return m_file;
    // }
    void printResult() const {
        for (const auto& s : m_file)
            cout << s << endl;
    }
private:
    unordered_map<string, string> m_convertRules;
    vector<string> m_file;
};

void test1() {
    wordConvert wc("file.txt", "map.txt");
    // for (auto& e : wc.getConvertRules()) {
    //     cout << e.first << " " << e.second << endl;
    // }
    wc.printResult();
}

int main() {
    test1();

    return 0;
}