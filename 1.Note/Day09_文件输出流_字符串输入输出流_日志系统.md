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

