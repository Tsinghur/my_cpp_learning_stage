#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class PersonInfo {
public:
    PersonInfo() = default;
    void setName(string& name) {
        m_name = name;
    }
    void setPhones(vector<string>& phones) {
        m_phones = phones;
    }
    void print() {
        cout << m_name << " ";
        for (auto& phone : m_phones) {
            cout << phone << " ";
        }
        cout << endl;
    }
private:
    string m_name;
    vector<string> m_phones;
};

int main() {
    std::ifstream ifs("phone.txt");
    int lines = 0;
    string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) // 跳过空行
            continue;  
        lines++;
    }
    /* cout << lines << endl; */

    vector<PersonInfo> users;
    users.reserve(lines);
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    while (std::getline(ifs, line)) {
        if (line.empty()) // 跳过空行
            continue;  

        PersonInfo user;
        vector<string> phones;
        std::istringstream iss(line);
        string word;
        int count = 0;
        while (iss >> word) {
            if (count == 0) {
                user.setName(word);
            }
            else {
                phones.push_back(word);
            }
            count++;
        }
        user.setPhones(phones);
        users.push_back(user);
    }

    for (auto& user : users) {
        user.print();
    }

    ifs.close();
    return 0;
}
