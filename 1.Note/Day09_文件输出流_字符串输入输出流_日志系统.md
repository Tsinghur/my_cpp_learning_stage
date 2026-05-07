# Day09_文件输出流&字符串输入输出流&日志系统

## 一、文件输出流

文件输出流的作用是将流对象保存的内容传输给文件

> **基本步骤**：
>
> 1. 创建 `ofstream` 对象并打开文件
> 2. 检查文件是否成功打开
> 3. 写入数据
> 4. 关闭文件

1. **文件输出流对象的创建**

   ![image-20241108114843218](..\0.TyporaPicture\image-20241108114843218.png)

   ofstream对象的创建与ifstream对象的创建类似

   ```cpp
   #include <fstream>
   void test0(){
       // 法一
       ofstream ofs;
       ofs.open("test1.cc");
       
   	// 法二
       ofstream ofs2("test2.cc");
       // 或
       string filename = "test3.cc";
       ofstream ofs3(filename);
   }
   // 如果文件输出流对象绑定的文件不存在，则会自动创建
   ```

2. **写入数据到文件**

   1. ==通过 输出流运算符<< 写内容==

      ```cpp
      // ofstream对象绑定文件后，可以往该文件中写入内容
      string filename = "test.txt";
      ofstream ofs(filename);
      
      string line("hello,world!\n");
      ofs << line; 
      
      ofs.close();
      // 内容传输的过程是string中的内容传给ofs对象，再传给这个对象绑定的文件
      ```

      但是我们会发现运行此代码，并没有保留下多次的内容，因为这种创建方式会使打开模式默认为`std::ios::out`，<font color=red>**每次都会清空文件的内容**</font>

      为了实现**在文件流结尾追加写入内容**的效果，可以在创建流对象时指定打开模式为<span style=color:red;background:yellow>**std::ios::app**</span>（追加模式）

      ```cpp
      string filename = "test.txt";
      ofstream ofs(filename, std::ios::app);
      ```

   2. 通过`write`函数写内容

      除了使用输出流运算符<< 将内容传输给文件输出流对象（传给`ofstream`对象就是将内容传到其绑定的文件中），还可以使用write函数进行传输

      ![image-20241108142946333](..\0.TyporaPicture\image-20241108142946333.png)

3. <span style=color:red;background:yellow>**动态查看指令**</span>

   为了更方便地查看多次写入的效果（动态查看文件的内容）可以使用指令，需要2个会话

   ```shell
   tail 文件名 -F   //动态查看文件内容
   ctrl + c        //退出查看
   ```

## 二、字符串输入输出流——==包含在头文件<sstream>中==

1.  **字符串输入输出流**

   字符串I/O是内存中的**字符串对象**与**字符串输入输出流对象**之间做内容传输的数据流，通常用来做格式转换

   C++ 对字符串进行操作的流类型有三个: 

   - istringstream （字符串输入流）
   - ostringstream （字符串输出流）
   - stringstream （字符串输入输出流）

   它们的构造函数形式都很类似:

   ```cpp
   istringstream()
       : istringstream(ios_base::in) 
       { }
   explicit istringstream(openmode mode = ios_base::in);
   explicit istringstream(const string& str, openmode mode = ios_base::in);
   
   ostringstream()
       : ostringstream(ios_base::out) 
       { }
   explicit ostringstream(openmode mode = ios_base::out);
   explicit ostringstream(const string& str, openmode mode = ios_base::out);
   
   stringstream()
       : stringstream(in|out) 
       { }
   explicit stringstream(openmode mode = ios_base::in|ios_base::out);
   explicit stringstream(const string& str, openmode mode = ios_base::in|ios_base::out);
   ```

2. **字符串输入流**

   - 先字符串的内容传输给字符串输入流对象（即流对象的创建），再通过这个对象进行字符串的处理（解析，即**数据从流对象到变量**）

     创建字符串输入流对象时传入c++字符串，字符串的内容就被保存在了输出流对象的缓冲区中。之后可以通过输入流运算符将字符串内容输出给不同的变量，起到了字符串分隔的作用

     ![image-20250305153127869](D:\Typora Picture\image-20250305153127869-17781528097712.png)

   - 示例：将字符串s的内容传给了两个int型数据

     ```cpp
     void test0() {
         string s("123 456");
         int num = 0;
         int num2 = 0;
         // 将字符串内容传递给了字符串输入流对象  
         istringstream iss(s);
         iss >> num >> num2;
         cout << "num:" << num << endl;
         cout << "num2:" << num2 << endl;
     }
     ```

     因为**输入流运算符会默认以空格符作为分隔符**，所以编译器会以int型数据来理解缓冲区释出的内容，将num和num2赋值为123和456

   - ==**字符串输入流通常用来处理字符串内容，比如读取配置文件**==

     ```cpp
     // myserver.conf
     ip 192.168.0.0
     port 8888
     dir ~HaiBao/53th/day06
     
         
     // readConf.cc
     void readConfig(const string & filename) {
         ifstream ifs(filename);
         if (!ifs.good()) {
             cout << "open file fail!" << endl;
             return;
         }
         
         string line;
         string key, value;
         while (getline(ifs,line)) {
             istringstream iss(line);
             iss >> key >> value;
             cout << key << " -----> " << value << endl; 
         }
     }
     
     void test0() {
         readConfig("myserver.conf");
     }
     ```

3. **字符串输出流**

   通常的用途就是**将各种类型的数据转换成字符串类型（即数据从变量到流对象）**

   ```cpp
   void test0() {
       int num = 123, num2 = 456;
       ostringstream oss;
       // 把所有的内容都传给了字符串输出流对象
       oss << "num = " << num << " , num2 = " << num2 << endl;
       // str()用于返回构造好的字符串（整个字符串的所有内容，不止一行）
       cout << oss.str() << endl;
   }
   ```

   将字符串、int型数据、字符串、int型数据统统传给字符串输出流对象，存在其缓冲区中，然后**利用它的`str()`函数**，全部**转为`string`类型**以此完成拼接

   ==注：字符串并非只有一行，换行符在字符串中只是一个普通的字符==

## 三、日志系统

1. **日志系统简介**

   - 日志系统在整个系统架构中的重要性可以称得上基础的基础，但是这一点，都容易被大多数人所忽视。因为日志在很多人看来只是printf，在系统运行期间，很难一步一步地调试，只能根据系统的运行轨迹来推断错误出现的位置，而日志往往也是最重要的参考资料

   - 日志系统主要解决的问题就是记录系统的运行轨迹，在这个基础上，进行跟踪分析错误，审计系统运行流程。一般在高可靠的系统中，是不允许系统运行终止的，所以也会产生海量的日志


   - 日志系统的内容可以分为两类：

     1. 业务级别的日志，主要供终端用户来分析他们业务过程
     2. 系统级别的日志，供开发者维护系统的稳定
   - 由于日志系统的数据输出量比较大，所以不能不考虑对整个系统性能的影响。从另外一方面来看，海量的日志内容有时候并不件好事，因为，很容易覆盖真实问题的蛛丝马迹，也增加日志阅读者信息检索的困难。所以日志系统的设计需要挑选一个合适的工具，并进行合理的设计

2. **日志系统的设计**

   日志系统的设计，一般而言要抓住最核心的一条，就是**日志从产生到到达最终目的地期间的处理流程**。一般而言，为了设计一个灵活可扩展，可配置的日志库，**主要将日志库分为4个部分去设计**，分别是：**记录器**、**过滤器**、**格式化器**、**输出器**四部分

   1. **记录器（日志来源）**

      负责产生日志记录的原始信息，比如（原始信息，日志优先级，时间，记录的位置）等等信息。

   2. **过滤器（日志系统优先级）**

      负责按指定的过滤条件过滤掉我们不需要的日志

      > log4cpp 采用了一种**混合过滤机制**，主要过滤功能由**输出器（Appender）** 承载，而**记录器（Category）** 也包含内置规则，二者共同作用
      >
      > 而一般可看作：log4cpp将过滤器嵌入于记录器之中，通过log4cpp::Category::setPriority函数来设置优先级（常使用）

   3. **输出器（日志目的地）**

      负责将将要进行记录的日志（一般经过过滤器及格式化器的处理后）记录到日志目的地（例如：输出到文件中）。

   4. **格式化器（日志布局）**

      负责对原始日志信息按照我们想要的格式去格式化。

3. **以一条日志的生命周期为例说明日志库如何工作**

   一条日志的生命周期：

   1.  产生：info(“log information.”)

   2.  经过记录器，记录器去获取日志发生的时间、位置、线程信息等等信息

   3.  经过过滤器，决定是否记录

   4.  经过格式化器处理成设定格式后传递给输出器。

       例如输出“2018-3-22 10:00:00 [info] log information.”这样格式的日志到文件中。

       日志的输出格式由格式化器实现，输出目的地则由输出器决定

   5.  这条日志信息生命结束

## 四、log4cpp

> **安装**
>
> 下载地址：https://sourceforge.net/projects/log4cpp/files/
>
> - 安装步骤
>
>   ```shell
>   $ tar xzvf log4cpp-1.1.4rc3.tar.gz
>   $ cd log4cpp
>   $ ./configure  //进行自动化构建，自动生成makefile
>   $ make
>   $ sudo make install //安装  把头文件和库文件拷贝到系统路径下
>       
>   # 安装完后：
>   # 默认头文件路径：/usr/local/include/log4cpp
>   # 默认lib库路径：/usr/local/lib
>   ```
>
> - 测试
>
>   打开log4cpp官网[Log for C++ Project (sourceforge.net)](https://log4cpp.sourceforge.net/)
>
>   拷贝simple example的内容，编译运行
>
>   ```shell
>   # 编译指令：
>   g++ log4cppTest.cc -llog4cpp -lpthread
>   ```
>
> - 报错：找不到动态库
>
>   ![image-20231124114253211](..\0.TyporaPicture\image-20231124114253211.png)
>
>   ![image-20260507195511572](..\0.TyporaPicture\image-20260507195511572.png)
>
>   ```shell
>   cd  /etc
>   sudo vim ld.so.conf
>   # 再将默认的lib库路径 "/usr/local/lib" 写入，再重新加载
>   sudo ldconfig # 让动态链接库为系统所共享
>   # ld.so.cache 执行了sudo ldconfig之后，会更新该缓存文件，会将所有动态库信息写入到该文件。当可执行程序需要加载相应动态库时，会从这里查找
>   ```

1. **log4cpp的核心组件**

   1. **日志目的地（Appender）—— 输出器**

      通过log4cpp官网查看常用类的信息

      ![image-20231124150134123](..\0.TyporaPicture\image-20231124150134123.png)

      主要关注三个目的地**类**，点开查看构造函数

      | 类名                | 释义                           |
      | ------------------- | ------------------------------ |
      | OstreamAppender     | 写到C++**通用输出流**(如 cout) |
      | FileAppender        | 写到**本地文件**中             |
      | RollingFileAppender | 写到**回卷文件**中             |

      ![image-20231124150108405](..\0.TyporaPicture\image-20231124150108405.png)

      - **OstreamAppender**

        构造函数传入两个参数：目的地名(即别名，随便写)、输出流指针

      - **FileAppender**

        构造函数传入两个参数：目的地名(别名)、保存日志的文件名
        (后面两个参数使用默认值即可，分别表示以结尾附加的方式的保存日志，当前用户读写-其他用户只读)

      - **RollingFileAppender**

        > 稍复杂一些，如果没有回卷文件，将所有的日志信息都保存在一个文件中，那么随着系统的运行，产生越来越多的日志，本地日志文件会越变越大，若不加限制，则会大量占用存储空间。所以通常的做法是使用回卷文件，比如只给日志文件1G的空间，对于这1G的空间可以再次进行划分，比如使用10个文件存储日志信息，每一个文件最多100M

        构造函数的参数如上图，其中要注意的是回卷文件个数，如果这一位传入的参数是9，那么实际上会有10个文件保存日志

        > 回卷的机制是：
        >
        > 先生成一个wd.log文件，该文件存满后接着写入日志，那么wd.log文件改名为wd.log.1，然后再创建一个wd.log文件，将日志内容写入其中，wd.log文件存满后接着写入日志，wd.log.1文件改名为wd.log.2，wd.log改名为wd.log.1，再创建一个wd.log文件，将最新的日志内容写入。以此类推，直到wd.log和wd.log.1、wd.log.2、... wd.log.9全都存满后再写入日志，wd.log.9（其中实际上保存着最早的日志内容）会被舍弃，编号在前的回卷文件一一进行改名，再创建新的wd.log文件保存最新的日志信息

   2. **日志布局（Layout）—— 格式化器**

      - 示例代码中使用的是BasicLayout，也就是默认的日志布局，这样一条日志最开始的信息就是日志产生时距离1970.1.1的秒数，不方便观察

      - 实际使用时可以用<span style=color:red;background:yellow>**PatrrenLayout**</span>类对象来定制化格式，类似于printf的格式化输出

        ![image-20231124164249912](..\0.TyporaPicture\image-20231124164249912.png)

          ```cpp
          PatternLayout * ptn1 = new PatternLayout();
          ptn1->setConversionPattern("%d %c [%p] %m%n"); 
          ```

      - setConversionPattern函数接收一个string作为参数，格式化字符的意义如下：
   
        ```cpp
         %d   %c   [%p]   %m     %n
        时间 模块名 优先级 消息本身 换行符
        ```
   
        > `%c` 就是在日志内容里**打印出这条日志来自哪个 Category**
        >
        > 根Category（`Category::getRoot()`）的名称固定为 `root`
        >
        > 自定义Category 的名称就是你 `getInstance()` 时传入的字符串
        > 比如`log4cpp::Category::getInstance("MyApp.UserModule")`
   
      - <span style=color:red;background:yellow>**注意（极易出错）：**</span>
   
        当日志系统有多个日志目的地时，每一个目的地Appender都需要设置一个布局Layout（一对一关系）
   
   3. **日志记录器（Category）—— 记录器(处理器)**
   
      **创建Category对象**
   
      - 方式一：
   
        可以用getRoot先创建root模块对象，对root模块对象设置优先级和目的地；再用getInstance创建叶模块对象，叶模块对象会继承root模块对象的优先级和目的地，**也可以**再去修改优先级、目的地
   
        ```cpp
        // 官网示例代码——Category对象的创建：
        // 先创建根对象
        log4cpp::Category& root = log4cpp::Category::getRoot(); // 命名空间::类::静态成员函数
        root.setPriority(log4cpp::Priority::WARN); // 设置优先级——即过滤器
        root.addAppender(appender1); // 添加输出器1到根记录器
        // 再创建叶对象
        log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1")); // 传入的字符串sub1就会是日志中记录的日志来源即%c
        sub1.addAppender(appender2); // 添加输出器2到子记录器
        ```
   
      - 方式二：
   
        也可以一行语句创建叶对象
   
        ```cpp
        log4cpp::Category& sub1 = log4cpp::Category::getRoot().getInstance("salesDepart"); // 记录的日志来源会是salesDepart
        sub1.setPriority(log4cpp::Priority::WARN); // 设置优先级——即过滤器
        sub1.addAppender(appender1); // 添加输出器1到子记录器
        ```
   
        > 这里需要注意的是，例子中:
        >
        > sub1本质上是绑定**Category对象的引用**，在代码中利用sub1去进行设置优先级、添加目的地、记录日志等操作；
        >
        > getInstance的参数salesDepart表示的是日志信息中记录的Category名称，也就是日志来源 —— **对应了布局中的%c**
        >
        > 所以一般在使用时这两者的名称取同一个名称，统一起来，能够更清楚地知道该条日志是来源于salesDepart这个模块 —— **即应该把引用名改为salesDepart与记录来源名相同**
   
      > 补充：如果没有创建根对象，直接使用getInstance创建叶对象，会先隐式地创建一个Root对象
      >
      > **子Category可以继承父Category的信息：优先级、目的地**
      >
      > ![image-20231124171810154](..\0.TyporaPicture\image-20231124171810154.png)
   
   4. **日志优先级（Priority）—— 过滤器**
   
      对于 log4cpp 而言，有两个优先级需要注意：
   
      - 一个是日志记录器的优先级：
   
        Category对象就是日志记录器，在使用时须设置好其优先级
   
      - 另一个就是某一条日志的优先级：
   
        某一行日志的优先级，就是Category对象在调用某一个日志记录函数时指定的级别，如 logger.debug("this is a debug message") ，这一条日志的优先级就是DEBUG级别的
   
        简言之：
        **日志系统(记录器)有一个优先级A，日志信息有一个优先级B**
        **只有B高于或等于A(>=)的时候，这条日志才会被输出（或保存），当B低于A的时候，这条日志会被过滤**
   
        ```cpp
        // 枚举类型属于类，不属于对象，所以可直接使用
        // 使用方式：log4cpp::Priority::INFO(或其他)
        class LOG4CPP_EXPORT Priority {
        public:
        	typedef enum {
        			EMERG = 0,
        			FATAL = 0,
        			ALERT = 100,
        			CRIT = 200,
        			ERROR = 300,
        			WARN = 400,
        			NOTICE = 500,
        			INFO = 600,
        			DEBUG = 700,
        			NOTSET = 800 // 不可使用
        	} PriorityLevel;
        	// ......
        }; // 数值越小，优先级越高；数值越大，优先级越低
        ```
   
        
