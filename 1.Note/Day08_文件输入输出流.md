

# Day08_文件输入输出流

## ==一、文件输入输出流==

所谓“**文件**”，一般指存储**在外部介质上数据的集合**。一批*数据是以文件的形式存放在外部介质上的*。**操作系统以文件为单位对数据进行管理**。要向外部介质上存储数据也必须先建立一个**文件（以文件名标识）**，才能向它输出数据。外存文件包括磁盘文件、光盘文件和U盘文件。目前使用最广泛的是磁盘文件

**文件流**是以**外存文件为输入输出对象**的**数据流**

**文件输入流**是从外存文件流向内存的数据，**文件输出流**是从内存流向外存文件的数据。**每一个文件流都有一个内存缓冲区与之对应**。*文件流本身不是文件，而只是以文件为输入输出对象的流*。若要对磁盘文件输入输出，就必须通过文件流来实现

1. **C++ 对文件进行操作的流类型有三个:**

   -  ifstream（文件输入流）

   - ofstream（文件输出流）

   - fstream （文件输入输出流）

   他们的构造函数形式都很类似：

   ```cpp
   ifstream();
   explicit ifstream(const char* filename, openmode mode = ios_base::in);
   explicit ifstream(const string & filename, openmode mode = ios_base::in);
   
   ofstream();
   explicit ofstream(const char* filename, openmode mode = ios_base::out);
   explicit ofstream(const string & filename, openmode mode = ios_base::out);
   
   fstream();
   explicit fstream(const char* filename, openmode mode = ios_base::in|out);
   explicit fstream(const string & filename, openmode mode = ios_base::in|out);
   ```

2. **文件模式**

   根据不同的情况，对文件的读写操作，可以采用不同的文件打开模式。文件模式在 GNU GCC 7.4 源码实现中，是用一个叫做 **openmode 的枚举类型**定义的，它**位于 ios_base 类**中。**文件模式一共有六种**，它们分别是：

   - <font color=red>**in **</font>

      以读取模式打开文件（默认用于 `ifstream`）；如果文件不存在，打开失败

   - <font color=red>**out**</font> 

     以写入模式打开文件（默认用于 `ofstream`），如果文件存在覆盖文件内容；如果文件不存在，则直接创建一个

   - <font color=red>**app**</font>

     追加，写入将始终发生在文件的末尾

   - <font color=red>**ate**</font>

     打开文件后，将文件指针定位到文件末尾

   - trunc

     截断，如果打开的文件存在，其内容将被丢弃，其大小被截断为零

   - binary

     二进制，读取或写入文件的数据为二进制形式

   ![image-20241108093024482](..\0.TyporaPicture\image-20241108093024482.png)

   > 补充：
   >
   > **外公开给程序员使用的静态常量名是 `binary`**，而不是 `bin`。在同一头文件中会看到类似这样的定义：
   >
   > ```cpp
   > static const openmode app    = _S_app;
   > static const openmode ate    = _S_ate;
   > static const openmode binary = _S_bin;   // 公开名称为 binary
   > static const openmode in     = _S_in;
   > static const openmode out    = _S_out;
   > static const openmode trunc  = _S_trunc;
   > ```
   >
   > 所以：
   >
   > - **内部枚举值**叫 `_S_bin`（带下划线的保留名，表示“binary”的缩写）
   > - **给用户用的常量**是 `std::ios_base::binary`

3. **文件输入流**

   1. **读取数据基本步骤**：

      - 创建 `ifstream` 对象并打开文件
      - 检查文件是否成功打开
      - 读取数据
      - 关闭文件

   2. **文件输入流对象的创建**

      首先要明确使用文件输入流的信息传输方向：
      **文件——>文件输入流对象的缓冲区——>程序中的数据结构**

      根据上述的说明，我们可以将输入流对象的创建分为两类：

      - 可以使用**无参构造**创建ifstream对象，**再使用open函数**将这个文件输入流对象与文件绑定（<font color=red>**若文件不存在，则文件输入流进入failbit状态**</font>）
      - 也可以使用**有参构造**创建ifstream对象，在创建时就将流对象与文件绑定，后续操作这个流对象就可以对文件进行相应操作

      通过参考文档中对ifstream的构造函数的描述，文件输入流对象的**有参构造需要输入文件名**，可以指定打开模式（不指定则默认使用in模式，为读打开）

      ```cpp
      #include <fstream>
      void test0(){
          // 无参构造，再使用open成员函数
          ifstream ifs;
          ifs.open("test1.cc");
          
          // 有参构造，直接创建时打开
          ifstream ifs2("test2.cc");
          string filename = "test3.cc";
          ifstream ifs3(filename);
      }
      ```

   3. **读取文件数据**

      1. 逐词读取

         ```cpp
         // 使用 >> 运算符，默认以换行符、空格作为间隔符，一次读取一个字符串
         string word;
         while (ifs >> word) { // 只要ifs是goodbit状态就会一直读取
         	cout << word << endl;
         }
         ifs.close(); // 规范操作, 使用完之后关闭流
         ```

         > 补充：`ifs >> word` 的返回值是 **流对象 `ifs` 本身的引用**，类型是 `std::ifstream&`
         >
         > 这样设计有两个常见用途：
         >
         > 1. **链式输入**：可以连写 `ifs >> a >> b >> c;`，因为每次 `>>` 都返回流的引用，下一个 `>>` 就能接着调用
         > 2. **条件判断**：在 `while(ifs >> word)` 中，`ifs >> word` 返回流引用后，`while` 需要一个布尔条件，于是编译器自动调用流的 **布尔转换运算符**（C++11 起是 `explicit operator bool()`，之前是 `operator void*()`）。该转换会检查流状态标志（`failbit`、`badbit`），如果流处于正常状态则返回 `true`，否则返回 `false`

      2. 按行读取

         - 法一：使用`ifstream`类中的成员函数`getline`，这种方式是兼容C的写法

           ```cpp
           #include <string.h>
           ifstream ifs("test.cc");
           //方法一，兼容C的写法，使用较少
           char buff[100] = {0};
           while(ifs.getline(buff,sizeof(buff))){
               cout << buff << endl;
               // 清空缓冲区
               memset(buff,0,sizeof(buff));
           }
           ```

           > ==补充：==
           >
           > | std::basic_istream<CharT,Traits>::getline                    |
           > | ------------------------------------------------------------ |
           > | basic_istream& getline( char_type* s, std::streamsize count ); |
           > | basic_istream& getline( char_type* s, std::streamsize count, char_type delim ); |
           >
           > - **`s`**：指向字符数组首地址的指针，用于存放读取到的字符串。函数会在读取结束后自动在末尾添加一个空字符 `\0`，使其成为一个合法的 C 风格字符串
           > - **`count`**：允许读取的**最大字符数**（包含结尾的 `\0`）。因此函数最多会从流中提取 **`count - 1`** 个字符，留出最后一个位置给空字符。如果输入行长度超过这个限制，读取会提前停止，剩余字符依然留在流中
           > - **`delim`**：**分隔符**，即指定一个字符作为“行”的结束标志。当从流中读取到此字符时停止读取（该分隔符会被读取并丢弃，**不会存入** `s` 中）。如果调用的是只有两个参数的重载版本，则分隔符默认为 **`'\n'`**（换行符）
           >
           > **简单来说**：从流中往 `s` 里读，最多读 `count-1` 个字符，遇到 `delim` 就停，分隔符不写入 `s`

         - 法二：使用`<string>`提供的`getline`方法，**工作中更常用**

           ```cpp
           // 传入输入流对象、string(、分隔符（默认换行符为分隔符, 也可以自己指定）)
           // 更方便，使用更多
           string line;
           while (getline(ifs,line)) {
               cout << line << endl;
           }
           ```

           > ==补充：==
           >
           > ![image-20241108094729774](..\0.TyporaPicture\image-20241108094729774.png)
           >
           > ```cpp
           > // 将一行的内容交给一个string对象去存储，不用再关心字符数了
           > void test4()
           > {
           >     using std::string; // 使用string中的getline
           >     ifstream ifs("aa.txt");
           >     string line;
           >     while(std::getline(ifs,line)){ // eof状态结束循环
           >         cout << line << endl;
           >     }
           > 
           >     ifs.close(); // 关闭流
           > }
           > ```

      3. 读取指定字节数的内容

         