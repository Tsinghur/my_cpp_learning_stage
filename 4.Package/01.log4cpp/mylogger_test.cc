#include "mylogger.hh"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

void test1() {
    // C++标准[预定义宏]
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;
    // C++11标准的预定义标识符，C++11 标准规定：编译器在每个函数内部自动生成的const char[]常量
    cout << __func__ << endl; // 等价于——编译器非标准扩展：__FUNCTION__
    cout << ADD_PREFIX("abc") << endl;
}

int main() {
    /* test1(); */
    LOG_ERROR("test: warn...");
    LOG_WARN("test: warn...");
    LOG_NOTICE("test: warn...");
    LOG_INFO("test: warn...");
    LOG_DEBUG("test: warn...");

    Mylogger::destroyInstance();
    return 0;
}
