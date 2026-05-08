#include "mylogger.hh"
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;

Mylogger::Mylogger() 
: m_category(Category::getRoot())
{
    cout << "constructor" << endl;
    m_category.setPriority(Priority::DEBUG);
    // 创建输出器
    auto appender1 = new OstreamAppender("console", &cout);
    auto appender2 = new FileAppender("file", "mylogger.log");
    // 创建格式化器
    auto layout1 = new PatternLayout();
    auto layout2 = new PatternLayout();
    // 设置格式
    layout1->setConversionPattern("%c %d [%p] %m%n");
    layout2->setConversionPattern("%c %d [%p] %m%n");
    // 绑定
    appender1->setLayout(layout1);
    appender2->setLayout(layout2);
    // 为记录器添加输入器
    m_category.addAppender(appender1);
    m_category.addAppender(appender2);
}

Mylogger::~Mylogger() {
    cout << "destructor" << endl;
    Category::shutdown();
}

Mylogger* Mylogger::ms_instance = nullptr;

Mylogger* Mylogger::getInstance() {
    if (!ms_instance) {
        ms_instance = new Mylogger();
    }
    return ms_instance;
}

void Mylogger::destroyInstance() {
    if (ms_instance) {
        delete ms_instance;
        ms_instance = nullptr;
    }
}

void Mylogger::error(const char *msg) {
    m_category.error(msg);
}
void Mylogger::warn(const char* msg) {
    m_category.warn(msg);
}
void Mylogger::notice(const char *msg) {
    m_category.notice(msg);
}
void Mylogger::info(const char *msg) {
    m_category.info(msg);
}
void Mylogger::debug(const char *msg) {
    m_category.debug(msg);
}
