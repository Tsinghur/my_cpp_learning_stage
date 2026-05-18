#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

int main(int argc, char** argv) {

    // 创建了一个往控制台输出的输出器对象OstreamAppender
    // 应该使用OstreamAppender* 接收该对象,
    // 但是这里使用了Appender * , 使用了父类型接收 --> 多态
	log4cpp::Appender *appender1 =
        new log4cpp::OstreamAppender("console", &std::cout);

    // 给输出器绑定了一个格式化器 采用BasicLayout布局方式
	appender1->setLayout(new log4cpp::BasicLayout());


    // 创建了一个FileAppender对象 往目标文件中输出记录
    // 还是使用的多态,用父类指针Appender *
	log4cpp::Appender *appender2 = 
        new log4cpp::FileAppender("default", "program.log");
    // 给appender2输出器对象 绑定了格式化器对象
    // 采用的还是基础布局
	appender2->setLayout(new log4cpp::BasicLayout());


    // getRoot()是个静态函数 获取根记录器对象
	log4cpp::Category& root = log4cpp::Category::getRoot();

    // 设置日志级别,优先级Warn >= Warn保留
	root.setPriority(log4cpp::Priority::WARN);
    // 为记录器添加了一个输出器
	root.addAppender(appender1);

    // getInstance() : 获取子记录器对象sub1
	log4cpp::Category& sub1 =
        log4cpp::Category::getInstance(std::string("sub1"));
    // 为子记录器对象添加输出器
	sub1.addAppender(appender2);

    // 产生日志信息
	// use of functions for logging messages
    // root产生的
	root.error("root error");
	root.info("root info");
    // sub1产生的
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}
