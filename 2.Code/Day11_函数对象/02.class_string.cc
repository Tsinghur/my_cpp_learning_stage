#include <iostream>
#include <cstring>   

class String {
public:
    String() 
    : _pstr(new char[1]{'\0'}) 
    {}

    String(const char *str) 
    : _pstr(new char[std::strlen(str) + 1]) 
    {
        std::strcpy(_pstr, str);
    }

    String(const String &str) 
    : _pstr(new char[std::strlen(str._pstr) + 1]) 
    {
        std::strcpy(_pstr, str._pstr);
    }

    ~String() {
        delete[] _pstr;
    }

    String &operator=(const String &str) {
        if (this != &str) {
            char *tmp = new char[std::strlen(str._pstr) + 1];
            std::strcpy(tmp, str._pstr);
            delete[] _pstr;
            _pstr = tmp;
        }
        return *this;
    }

    String &operator=(const char *str) {
        char *tmp = new char[std::strlen(str) + 1];
        std::strcpy(tmp, str);
        delete[] _pstr;
        _pstr = tmp;
        return *this;
    }

    String &operator+=(const String &str) {
        size_t newLen = std::strlen(_pstr) + std::strlen(str._pstr);
        char *tmp = new char[newLen + 1];
        std::strcpy(tmp, _pstr);
        std::strcat(tmp, str._pstr);
        delete[] _pstr;
        _pstr = tmp;
        return *this;
    }

    String &operator+=(const char *str) {
        size_t newLen = std::strlen(_pstr) + std::strlen(str);
        char *tmp = new char[newLen + 1];
        std::strcpy(tmp, _pstr);
        std::strcat(tmp, str);
        delete[] _pstr;
        _pstr = tmp;
        return *this;
    }

    char &operator[](std::size_t index) {
        return _pstr[index];
    }

    const char &operator[](std::size_t index) const { // 常量对象只能调用这个版本
        return _pstr[index];
    }

    std::size_t size() const {
        return std::strlen(_pstr);
    }

    const char* c_str() const {
        return _pstr;
    }

    friend bool operator==(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) == 0;
    }

    friend bool operator!=(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) != 0;
    }

    friend bool operator<(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) < 0;
    }

    friend bool operator>(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) > 0;
    }

    friend bool operator<=(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) <= 0;
    }

    friend bool operator>=(const String &lhs, const String &rhs) {
        return std::strcmp(lhs._pstr, rhs._pstr) >= 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &s) {
        os << s._pstr;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, String &s) {
        char buf[1024];
        if (is >> buf) {
            s = buf; // 使用operator=(const char*)
        }
        return is;
    }

private:
    char *_pstr;
};

// 标准做法：+ 通过 += 来实现
String operator+(const String &lhs, const String &rhs) {
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}

String operator+(const String &lhs, const char *rhs) {
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}

String operator+(const char *lhs, const String &rhs) {
    String tmp(lhs);
    tmp += rhs;
    return tmp;
}

int main() {

    return 0;
}
