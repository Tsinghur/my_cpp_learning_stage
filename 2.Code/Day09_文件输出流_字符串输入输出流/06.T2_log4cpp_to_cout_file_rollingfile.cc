#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>

using std::cout;
using std::endl;
using namespace log4cpp;
  
// 将日志信息输出到控制台
void test1() {
    // 创建输出器对象
    OstreamAppender* appender1 = new OstreamAppender("console", &cout);
    // 给输出器绑定格式化对象
    PatternLayout* layout1 = new PatternLayout();
    layout1->setConversionPattern("%d [%p] %c : %m%n"); // 设置输出格式
    appender1->setLayout(layout1); // 绑定

    // 获取根记录器
    Category& root = Category::getRoot();
    // 给记录器设置优先级
    root.setPriority(Priority::INFO); 
    // 给记录器添加输出器
    root.addAppender(appender1);

    // 产生日志信息
    root.debug("debug msg...");
    root.info("info msg...");
    root.notice("notice msg...");
    root.warn("warn msg...");

    // 释放资源
    Category::shutdown();
}

// 输出到文件
void test2() {
    // 创建输出器对象
    FileAppender* appender1 = new FileAppender("file", "log.txt");
    // 给输出器绑定格式化对象
    PatternLayout* layout1 = new PatternLayout();
    layout1->setConversionPattern("%d [%p] %c : %m%n"); // 设置输出格式
    appender1->setLayout(layout1); // 绑定

    // 获取根记录器
    Category& root = Category::getRoot();
    // 给记录器设置优先级
    root.setPriority(Priority::INFO); 
    // 给记录器添加输出器
    root.addAppender(appender1);

    // 产生日志信息
    root.debug("debug msg...");
    root.info("info msg...");
    root.notice("notice msg...");
    root.warn("warn msg...");

    // 释放资源
    Category::shutdown();
}

// 输出到回卷文件
void test3() {
    // 创建输出器对象
    // 第三、四个参数分别为：单个日志文件达到此大小后触发滚动(单位字节)、日志"备份文件"数量(总数量为n+1) 
    // 这里是：留5个备份，最多共6个日志文件，触发滚动的阈值为100字节
    RollingFileAppender* appender1 = new RollingFileAppender("roll", "rolling_file_log.txt", 100, 5);
    // 给输出器绑定格式化对象
    PatternLayout* layout1 = new PatternLayout();
    layout1->setConversionPattern("%d [%p] %c : %m%n"); // 设置输出格式
    appender1->setLayout(layout1); // 绑定

    // 获取根记录器
    Category& root = Category::getRoot();
    // 给记录器设置优先级
    root.setPriority(Priority::INFO); 
    // 给记录器添加输出器
    root.addAppender(appender1);

    // 产生日志信息
    root.debug("debug msg...");
    root.info("info msg...");
    root.notice("notice msg...");
    root.warn("warn msg...");

    // 释放资源
    Category::shutdown();
}

int main() {
    /* test1(); */
    /* test2(); */
    test3();

    return 0;
}
