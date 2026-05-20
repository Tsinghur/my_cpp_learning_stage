#include <cctype> // isalpha, tolower
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::shared_ptr;
using std::make_shared;

class QueryResult {
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string word, int count, shared_ptr<set<int>> sp, shared_ptr<vector<string>> file)
    : m_word(word)
    , m_count(count)
    , m_spLineNumbers(sp)
    , m_file(file)
    {}
private:
    string m_word;
    int m_count;
    shared_ptr<set<int>> m_spLineNumbers;
    shared_ptr<vector<string>> m_file;
};

class TextQuery {
public:
    /* using line_no = std::vector<std::string>::size_type; // C++11引入，等价typedef std::vector<std::string>::size_type line_no; */

    // 构造初始化同时生成其数据成员的内容，因为设计上这个类的每个对象只对应一个文件，所以直接就在构造函数中完成所有的构建
    TextQuery(ifstream& ifs)
    /* : m_file(new vector<string>) */
    : m_file(make_shared<vector<string>>()) // make_shared更安全、更高效（一次内存分配），Modern C++的惯用法
    {
        string line;
        int lineNumber = 0;
        while (std::getline(ifs, line)) {
            lineNumber++;
            m_file->push_back(line);
            istringstream iss(line);
            string word;
            while (iss >> word) {
                word = cleanWord(word); // 构造函数中可以调用成员函数
                if (word.empty())
                    continue;
                shared_ptr<set<int>>& lineNumbers = m_wordLineNumbers[word]; // 返回插入的新值即shared_ptr(若是不存在则将新值初始化为默认值，指针就是nullptr)
                                                                     // 单纯的引用不会增加计数
                if (!lineNumbers) // 智能指针仍未空，即没有管理资源
                    lineNumbers = make_shared<set<int>>(); // 则给其分配一个新的set<int>对象
                    // 或 numbers.reset(new set<int>())
                lineNumbers->insert(lineNumber);
                m_wordCounts[word]++;
            }
        }
    }

    QueryResult query(const string& word) const {
        // 如果没有找到word，则返回一个空的set<int>
        /* static shared_ptr<set<int>> nodata(new set<int>()); */
        static shared_ptr<set<int>> nodata(make_shared<set<int>>());
        // 使用find而不是[]来查找单词是因为避免将word加入到m_wordLineNumbers中
        /* map<string,shared_ptr<set<int>>>::const_iterator lineNumbers = m_wordLineNumbers.find(word); // const成员函数中容器返回的迭代器类型是const_iterator，不能隐式转换成iterator，在这里m_wordLineNumbers被视为const map<...> */ 
        auto lineNumbers = m_wordLineNumbers.find(word); // 使用auto才是现代C++风格
        if (lineNumbers == m_wordLineNumbers.end())
            /* return QueryResult(word, m_wordCounts[word], nodata, m_file); // const成员函数中不能使用非const成员函数即operator[] */
            return QueryResult(word, 0, nodata, m_file);
        else
            return QueryResult(word, m_wordCounts.at(word), lineNumbers->second, m_file);
    }

    static string cleanWord(const string& raw) {
        string res;
        for (char c : raw) {
            if (std::isalpha(c) || c == '-') { // 保留类似state-of-the-art风格的单词
                res += std::tolower(c);
            }
        }
        return res;
    }
private:
    /* vector<string> m_lines; // 存储每一行的内容 */
    shared_ptr<vector<string>> m_file;
    /* map<string, set<int>> m_wordLineNumbers; // 存储对应单词出现过的所有行号 */
    map<string,shared_ptr<set<int>>> m_wordLineNumbers;

    map<string, int> m_wordCounts; // 存储对应单词出现的次数
                             // 纯值类型的容器，天生就安全，根本用不到智能指针
    // 什么时候用智能指针？
    // 管理堆上创建的对象（new出来的），或需要跨对象共享生命周期的数据
};

ostream& print(ostream& os, const QueryResult& qr) {
        os << qr.m_word << " occurs " << qr.m_count  << " times." << endl;
        for (int lineNumber : *qr.m_spLineNumbers) {
            os << "(line " << lineNumber << ") " << (*qr.m_file)[lineNumber - 1] << endl;
        }
    os << "---------------------------------------------" << endl;
    return os;
}

void runQuries(ifstream& ifs) {
    TextQuery tq(ifs);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string word;
        if (!(cin >> word) || word == "q")
            break;
        print(cout, tq.query(word));
    }
}

void test1(const string filePath) {
    ifstream ifs(filePath);
    if (!ifs) {
        std::cerr << "Error: cannot open file " << filePath << std::endl;
        return;
    }
    runQuries(ifs);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    test1(argv[1]);

    return 0;
}
