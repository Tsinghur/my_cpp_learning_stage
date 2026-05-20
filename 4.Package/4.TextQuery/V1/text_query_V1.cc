#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::map;

class Dictionary {
public:
    void read(const string& fileName) {
        ifstream ifs(fileName);
        string word;
        while (ifs >> word) {
            word = cleanWord(word);
            if (word.empty()) {
                continue; // 跳过纯标点与非字母单词
            } // else
            m_dict[word]++;
        }
        /* ifs.close(); // 析构时自动关闭 */
        // 显式close()仅在需要提前释放文件句柄时有用
    }
    void store(const string& fileName) {
        ofstream ofs(fileName);
        for (auto& p : m_dict) {
            // '\n' 本身永远不会主动刷新缓冲区
            // 但输出到终端时，可能由于“行缓冲模式”而自动刷新，这取决于实现
            ofs << p.first << " " << p.second << "\n";
        }
        /* ofs.close(); // 析构时自动关闭 */
    }
    string cleanWord(const string& raw) {
        string res;
        for (char c : raw) {
            if (std::isalpha(c)) {
                res += std::tolower(c);
            }
        }
        return res;
    }
private:
    map<string,int> m_dict;
};

int main() {
    Dictionary dictionary;
    dictionary.read("/home/gzh/The_Holy_Bible.txt");
    dictionary.store("dict2.txt");

    return 0;
}
