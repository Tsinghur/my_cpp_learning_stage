#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

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

int main() {
    Dictionary dictionary;
    dictionary.read("/home/gzh/The_Holy_Bible.txt");
    /* for (auto& elem : dictionary._dict) { */
    /*     cout << elem._word << " " << elem._frequency << endl; */
    /* } */
    dictionary.store("dict2.txt");

    return 0;
}
