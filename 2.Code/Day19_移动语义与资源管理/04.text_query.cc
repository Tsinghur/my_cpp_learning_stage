#include <cstdlib> // exit
#include <cctype> // isalpha, tolower
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <utility>

#define FILE_PATH "/home/gzh/china_daily.txt"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;

class TextQuery {
public:
    void readFile(const string& fileName) {
        // 为智能指针分配资源
        m_lines = std::make_shared<vector<string>>();

        std::ifstream ifs(fileName);
        if (!ifs.is_open()) {
            std::cerr << "Error: cannot open file \"" << fileName << "\"\n";
            exit(EXIT_FAILURE);   // 需要 #include <cstdlib>
        }

        string line;
        int lineNumber = 0;
        /* while (ifs >> line) { */
        while (std::getline(ifs, line)) {
            lineNumber++;
            m_lines->push_back(line); // std::move(lineNumber) 对 int 无效且无意义

            std::istringstream iss(line);
            string word;
            while (iss >> word) {
                word = cleanWord(word);
                if (word.empty()) {
                    continue; // 跳过纯标点与非字母单词
                } // else
                auto &sp = m_wordNumbers[word]; // 返回插入新值的引用(若是不存在则将新值初始化为默认值，指针就是nullptr)
                if (!sp) {
                    sp = std::make_shared<set<int>>();
                }
                /* m_wordNumbers[word]->insert(std::move(lineNumber)); */
                sp->insert(std::move(lineNumber));
                m_dict[word]++;
            }
        }
    }
    void query(const string& word) {
        /* cout << "---------------------------------------------" << endl; */
        /* cout << word << " occurs " << m_dict[word] << " times." << endl; */
        /* for (auto& e : m_wordNumbers[word]) { */
        /*     cout << "(line " << e << ") " << m_lines[e - 1] << endl; */
        /* } */
        /* cout << "---------------------------------------------" << endl; */
        cout << "---------------------------------------------" << endl;
        auto it = m_dict.find(word);
        if (it == m_dict.end()) {
            cout << "\"" << word << "\" does not appear in the file." << endl;
        } else {
            cout << word << " occurs " << it->second << " times." << endl;
            // 此时 m_wordNumbers[word] 一定存在
            for (int lineNo : *m_wordNumbers.at(word)) {
                cout << "(line " << lineNo << ") " << (*m_lines)[lineNo - 1] << endl;
            }
        }
        cout << "---------------------------------------------" << endl;
    }
    static string cleanWord(const string& raw) {
        string res;
        for (char c : raw) {
            if (std::isalpha(c)) {
                res += std::tolower(c);
            }
        }
        return res;
    }
private:
    /* vector<string> m_lines; // 存储每一行的内容 */
    std::shared_ptr<vector<string>> m_lines;
    /* map<string, set<int>> m_wordNumbers; // 存储对应单词出现过的所有行号 */
    map<string,std::shared_ptr<set<int>>> m_wordNumbers;
    map<string, int> m_dict; // 存储对应单词出现的次数
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <word>" << endl;
        return 1;
    }

    /* string queryWord("is"); */
    TextQuery tq;
    /* tq.readFile("argv[1]"); */
    /* tq.readFile("FILE_PATH"); // error: 宏出现在字符串字面量里不会展开 */
    /* tq.readFile(FILE_PATH); // right */
    tq.readFile(argv[1]);
    /* tq.query(queryWord); */
    tq.query(argv[2]);

    return 0;
}
