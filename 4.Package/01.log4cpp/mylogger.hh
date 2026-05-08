#ifndef MYLOGGER_HH
#define MYLOGGER_HH

#include <log4cpp/Category.hh>
#define ADD_PREFIX(msg) string("[").append(__FILE__)\
                        .append(":").append(__func__)\
                        .append(":").append(std::to_string(__LINE__))\
                        .append("]").append(msg).c_str()

// 若是单独使用一次ADD_PREFIX宏函数，然后再使用LOG_WARN则会导致未定义行为
// 因为前者的string是个临时值，在LOG_WARN使用时，前者返回的c_str指针已经变成了野指针
// 如果想要兼容这种情况，则可将.c_str()移到LOG_WARN中的(msg)之后
// 但是在我的这个日志封装中保证只同时组合使用二者，则不会出现问题，因为这个临时字符串会在整条语句也就是一系列函数调用结束之后才会销毁
#define LOG_ERROR(msg) Mylogger::getInstance()\
                      ->error(ADD_PREFIX(msg))
#define LOG_WARN(msg) Mylogger::getInstance()\
                      ->warn(ADD_PREFIX(msg))
#define LOG_NOTICE(msg) Mylogger::getInstance()\
                      ->notice(ADD_PREFIX(msg))
#define LOG_INFO(msg) Mylogger::getInstance()\
                      ->info(ADD_PREFIX(msg))
#define LOG_DEBUG(msg) Mylogger::getInstance()\
                      ->debug(ADD_PREFIX(msg))

using namespace log4cpp;

// 单例模式
class Mylogger {
public:
    // 静态方法获取、摧毁实例
    static Mylogger* getInstance();
    static void destroyInstance();
    // 删除复制函数
    Mylogger(const Mylogger&) = delete;
    Mylogger& operator=(const Mylogger&) = delete;

	void error(const char *msg);
    void warn(const char *msg);
	void notice(const char *msg);
	void info(const char *msg);
	void debug(const char *msg);
private:
    // 将构造函数设置为私有(析构非必须设置私有)
    Mylogger();
    ~Mylogger();
    Category& m_category;
    static Mylogger* ms_instance;
};

#endif
