#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>

using std::cout;
using std::endl;
using std::string;
using namespace log4cpp;

/*
 * 使用日志工具时, 一般都会做封装处理
 * 对底层的log4cpp进行包装, 套个外壳
 *
 */

// 自定义日志工具类
class MyLogger
{
public:
    MyLogger()
    : m_category(Category::getRoot())
    {
        // 完成初始化操作
        // 给记录器配置一下
        OstreamAppender * appender = new OstreamAppender("console", &cout);
        PatternLayout * layout = new PatternLayout();
        layout->setConversionPattern("%d [%p] %c : %m%n");
        appender->setLayout(layout);

        m_category.setPriority(Priority::INFO);
        m_category.addAppender(appender);
    }

    void info(const string & msg)
    {
        // 底层使用log4cpp
        m_category.info(msg);
    }
     void debug(const string & msg)
    {
        // 底层使用log4cpp
        m_category.debug(msg);
    }
   void error(const string & msg)
    {
        // 底层使用log4cpp
        m_category.error(msg);
    }

private:
    // 把记录器作为数据成员
    Category &  m_category;
};

// 创建一个全局对象
MyLogger logger;

void test1()
{
    // 模拟数据库连接
    logger.error("数据库连接出错...");
}

int main(int argc, char * argv[])
{
    logger.info("程序启动了....");
    test1();
    // 获取文件名 行号 函数名
    cout << __FUNCTION__ << endl;
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;
    logger.info("程序结束了....");
    return 0;
}

