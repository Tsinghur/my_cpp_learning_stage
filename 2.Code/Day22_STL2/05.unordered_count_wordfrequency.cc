#include <cctype> // std::isalpha、std::tolower
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <chrono> // 计时核心头文件

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
/* using namespace std::chrono; */
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;


struct Record {
    string _word;
    int _frequency;
};

class Dictionary {
public:
    void read(const string& filename) {
        std::ifstream ifs(filename);
        string word;
        while (ifs >> word) {
            word = cleanWord(word);
            if (word.empty()) 
                continue;   // 跳过纯标点与非字母单词
            bool found = false;
            /* if (_dict.empty()) { */
            /*     _dict.push_back({word, 1}); */
            /*     continue; */
            /* } */
            for (auto& dict : _dict) {
                if (dict._word == word) {
                    found = true;
                    dict._frequency++;
                    break;
                }
            }
            if (found == false) {
                /* _dict.emplace_back(word, 1); // 注意：Record没有构造函数,不能用圆括号初始化 */
                _dict.push_back({word, 1});
                // push_back({...}) 可以，是因为函数参数类型已知，直接用花括号初始化临时对象
                // 而 emplace_back({...}) 要求先推导参数类型，花括号列表"无类型"导致推导失败
            } 
        }

        ifs.close();
    }
    void store(const string& filename) {
        std::ofstream ofs(filename);
        for (auto& elem : _dict) {
            ofs << elem._word << " " << elem._frequency << endl;
        }

        ofs.close();
    }
    string cleanWord(const string& raw) {
        string result;
        for (char c : raw) {
            if (std::isalpha(c))        // 只保留字母
                result += std::tolower(c); // 全转小写
        }
        return result;
    }
private:
    vector<Record> _dict;
};

class Dictionary2 {
public:
    void read(const string& filename) {
        std::ifstream ifs(filename);
        string word;
        while (ifs >> word) {
            word = cleanWord(word);
            if (word.empty()) 
                continue;   // 跳过纯标点与非字母单词
            _dict[word]++;
        }
    }
    void store(const string& filename) {
        std::ofstream ofs(filename);
        for (auto& e : _dict) {
            ofs << e.first  << " " << e.second << endl;
        }
    }
    string cleanWord(const string& raw) {
        string result;
        for (char c : raw) {
            if (std::isalpha(c))        // 只保留字母
                result += std::tolower(c); // 全转小写
        }
        return result;
    }
private:
    unordered_map<string,int> _dict;
};

int main() {
    // ========== 1. 记录开始时间 ==========
    auto start = high_resolution_clock::now();

    // vector
    /* Dictionary dictionary; */
    /* dictionary.read("/home/gzh/The_Holy_Bible.txt"); */
    /* dictionary.store("dict_vector.txt"); */
    /*
    for (auto& elem : dictionary._dict) {
        cout << elem._word << " " << elem._frequency << endl;
    }
    */
    // unordered_map
    Dictionary2 dictionary2;
    dictionary2.read("/home/gzh/The_Holy_Bible.txt");
    dictionary2.store("dict_unordered_map.txt");

    // ========== 2. 记录结束时间 ==========
    auto end = high_resolution_clock::now();
    // ========== 3. 计算时间差（支持秒/毫秒/微秒） ==========
    auto sec = duration_cast<seconds>(end - start);        // 秒
    auto ms  = duration_cast<milliseconds>(end - start);  // 毫秒
    auto us  = duration_cast<microseconds>(end - start);  // 微秒
    // 输出结果
    cout << "耗时: " << sec.count() << " 秒" << endl;
    cout << "耗时: " << ms.count()  << " 毫秒" << endl;
    cout << "耗时: " << us.count()  << " 微秒" << endl;

    return 0;
}
