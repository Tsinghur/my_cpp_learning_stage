#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char* pStr) {
        _size = strlen(pStr);
        if (_size < 16) {
            strcpy(_buffer._local, pStr);
            _capacity = 16;
        } else {
            _buffer._pointer = new char[_size + 1]{};
            strcpy(_buffer._pointer, pStr);
            _capacity = _size + 1;
        }
    }
    ~String() {
        if (_size >= 16) {
            delete[] _buffer._pointer;
            _buffer._pointer = nullptr;
        } else {
            bzero(_buffer._local, 16);
        }
    }
    
    char& operator[](size_t idx) {
        if (idx >= _size) {
            cout << "idx is illegal" << endl;
            static char nullChar = '\0';
            return nullChar;
        }
        if (_size < 16) {
            return _buffer._local[idx];
        } else {
            return _buffer._pointer[idx];
        }
    }

    friend
    ostream& operator<<(ostream& os,const String& rhs);
private:
	union Buffer{
		char * _pointer;
		char _local[16];
	};
	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};

ostream& operator<<(ostream& os,const String& rhs) {
    if (rhs._size < 16) {
        os << rhs._buffer._local;
    } else {
        os << rhs._buffer._pointer;
    }
    return os;
}

void test1() {
    String str1("hello");
    String str2("hello,world!!!!!");
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str2[6] : " << str2[6] << endl;
    str1[0] = 'w';
    str2[6] = 'h';
    cout << "after str1[0] = 'w' and str2[6] = 'h' : " << endl;
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str2[6] : " << str2[6] << endl;
}

int main() {
    test1();

    return 0;
}
