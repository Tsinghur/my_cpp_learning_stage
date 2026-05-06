# Day07_字符串&vector&CPP输入输出流

## 一、C++字符串

C++ 提供了 std::string （后面简写为 string ）类用于字符串的处理。 string 类定义在 C++ 头文件< string > 中，注意和头文件 < cstring > 区分， < cstring > 其实是对 C 标准库中的 <string.h> 的封装，其定义的是一些对 C 风格字符串的处理函数

尽管 C++ 支持 C 风格字符串，但在 C++ 程序中最好还是不要使用它们。这是因为 C 风格字符串不仅使用起来不太方便，而且极易引发程序漏洞，是诸多安全问题的根本原因。与 C 风格字符串相比， string不必担心内存是否足够、字符串长度，结尾的空白符等等。 string 作为一个类出现，其集成的成员操作函数功能强大，几乎能满足所有的需求。从另一个角度上说，<span style=color:red;background:yellow>**完全可以把 string 当成是 C++ 的内置数据类型，放在和 int 、 double 等内置类型同等位置上**</span>

> **`string` 就是 `basic_string<char>` 的别名**
>
> `basic_string` 是**模板基类**，`string` 是它针对**char 字符**的具体实现

1. **string对象的构造函数**

   > **`basic_string` 是一个类模板（Class Template）**，而 **`string` 是 `basic_string` 模板的一个具体实例（Concrete Instantiation）**
   >
   > basic_string的常用构造
   >
   > ```cpp
   > // 无参构造
   > basic_string(); 
   > // count + 字符
   > basic_string( size_type count,
   >               CharT ch，
   >               const Allocator& alloc = Allocator() );
   > // 接收一个basic_string对象
   > basic_string( const basic_string& other,
   >               size_type pos,
   >               size_type count,
   >               const Allocator& alloc = Allocator() ); 
   > // 接收一个C风格字符串
   > basic_string( const CharT* s,
   >               size_type count,
   >               const Allocator& alloc = Allocator() ); 
   > ```
   >
   > 在创建字符串对象时，我们可以直接使用std::string作为类名，如std::string str = "hello". 这是因为C++标准库已经为我们定义了std::string这个类型的别名

   1. 无参构造

      ```cpp
      string();
      // 生成一个空字符串
      ```

   2. 通过c风格字符串构造一个string对象

      ```cpp
      string(const char * rhs);
      ```

   3. 拷贝构造函数

      ```cpp
      string(const string & rhs);
      ```

   4. 通过string对象的一部分创建新的string

      ```cpp
      string(const string & rhs，size_t pos, size_t count);
      ```

   5. 生成一个string对象，该对象包含count个ch字符

      ```cpp
      string(size_type count, char ch);
      // string(97, 'a'); // "97个a...a"
      // 不等于string{97, 'a'}; // "aa"
      ```

   6. 以区间[first, last)内的字符创建一个string对象

      ```cpp
      string(InputIt first, InputIt last);
      // InputIt 输入迭代器 ≈ 指针
      // 在 C++ 中，指针（Pointer）本身就是天然的迭代器
      ```

2. **string的常用操作函数**

   ```cpp
   // 获取出C++字符串保存的字符串内容，返回指向字符串内部字符数组起始位置的指针
   const CharT* data() const; // 在C++11之前，data()返回的数组不保证以'\0'结尾；对于非 const std::string（读写场景，C++17 起）有区别：C++17 为 data() 引入了非 const 重载，而 c_str() 始终是 const 的
   const CHarT* c_str() const; // 以C风格字符串作为返回值
   
   // 判空
   bool empty() const; 
   
   // 获取字符数
   size_type size() const;
   size_type length() const;
   
   // 在字符串末尾添加字符
   void push_back(CharT ch);  
   
   // 在字符串末尾添加内容(字符串)，返回修改后的字符串
   basic_string& append(size_type count, CharT ch); // 添加count个字符
   basic_string& append(const basic_string& str); // 添加字符串
   basic_string & append(const basic_string& str, size_type pos,size_type count); // 添加str的从pos位置的count个字符
   basic_string& append(const charT* s); // 添加C风格字符串
   
   // 查找字符/子串
   size_type find( const basic_string& str, size_type pos = 0 ) const; // 从C++字符串的pos位开始查找C++字符串str
   size_type find( CharT ch, size_type pos = 0 ) const; // 从C++字符串的pos位开始查找字符ch
   size_type find( const CharT* s, size_type pos, size_type count ) const; // 从C++字符串的pos位开始，去查找C字符串的前count个字符
   ```

   **补充：两个basic_string字符串比较，可以直接使用==等符号进行判断**

   原理：basic_string对==运算符进行了默认重载（后续会学到）

   ```cpp
   // 非成员函数
   bool operator==(const string & lhs, const string & rhs);
   bool operator!=(const string & lhs, const string & rhs);
   bool operator>(const string & lhs, const string & rhs);
   bool operator<(const string & lhs, const string & rhs);
   bool operator>=(const string & lhs, const string & rhs);
   bool operator<=(const string & lhs, const string & rhs);
   ```

3. ==**string的遍历**==

   string实际上也可以看作是一种存储char型数据的容器，对string的遍历方法是之后对各种容器遍历的一个铺垫

   1. **下标操作符[]**

      ```cpp
      for(size_t idx = 0; idx < str.size(); ++idx){
          cout << str[idx] << " ";
      }
      cout << endl;
      ```

      **操作符[]并不检查索引是否有效**，如果索引超出范围，会引起未定义的行为。而**成员函数 at() 会检查**，如果使用 at()的时候索引无效，会抛出 out_of_range 异常

      ```cpp
      string str("hello");
      cout << str.at(4) << endl; // 输出o
      cout << str.at(5) << endl; // 运行时抛出异常
      ```

   2. **增强for循环**

      增强for循环经常和auto关键字一起使用，auto关键字可以自动推导类型

      ```cpp
      string str("hello"); // 把string视作一个存放char元素的容器
      for (auto& c : str) { // &意义在于对于容器中元素本身进行操作, 否则对其副本进行操作
      	cout << c;
      }
      cout << endl;
      ```

   3. **迭代器方式**

      ```cpp
      // 如指针一样，迭代器也有其固定的形式
      // 某容器的迭代器形式为 容器名::iterator
      // 此处auto推导出来it的类型为string::iterator
      // string::iterator itBegin = str.begin();
      // string::iterator itEnd = str.end();
      // 使用auto来简化操作
      auto it = str.begin(); // auto = string::iterator
      while(it != str.end()){
          cout << *it << " ";
      	++it;
      }
      cout << endl;
      ```

      **==补充：什么是迭代器==**

      **迭代器**是一种用于遍历容器中元素的对象，这里可以理解为是**广义的指针**。它**可以**像指针一样进行**解引用、移位**等操作。迭代器是容器用来访问元素的重要手段，容器都有相应的函数来获取特定的迭代器（此处可以简单理解为指向特定元素的指针，在STL的阶段，会对迭代器进行更详细的讲解）

      <font color=red>**begin函数返回首迭代器（指向首个元素的指针）**</font>

      <font color=red>**end函数返回尾后迭代器（指向最后一个元素的后一位的指针）**</font>

      ![image-20241203114859778](..\0.TyporaPicture\image-20241203114859778.png)

## 二、C++动态数组——vector

C++中，**std::vector**（向量）是一个**动态数组容器**，能存放任意类型的数据

其动态性体现在以下几个方面：

- 动态大小：`std::vector` 可以根据需要自动调整自身的大小。它在内部管理一个动态分配的数组，可以根据元素的数量进行自动扩容或缩减。当元素数量超过当前容量时，`std::vector` 会重新分配内存，并将元素复制到新的内存位置。这使得 `std::vector` 能够根据需要动态地增长或缩小容量，而无需手动管理内存
- 动态插入和删除：`std::vector` 允许在任意位置插入或删除元素，而不会影响其他元素的位置。当插入新元素时，`std::vector` 会自动调整容量，并将后续元素向后移动以腾出空间。同样地，当删除元素时，`std::vector` 会自动调整容量，并将后续元素向前移动以填补空缺
- 动态访问：`std::vector` 提供了随机访问元素的能力。可以通过索引直接访问容器中的元素，而不需要遍历整个容器。这使得对元素的访问具有常数时间复杂度（O(1)），无论容器的大小如何

1. **vector的构造**

   vector常用的几种构造形式：

   1. 无参构造，仅指明vector存放元素的种类，没有存放元素

      ```cpp
      vector<int> numbers;
      // 此时无数据
      ```

   2. 传入一个参数，指明vector存放元素的种类和数量，参数是存放元素的数量，每个元素的值为该类型对应的默认值

      ```cpp
      vector<long> numbers2(10); // 存放10个0
      // 注意：！！！此时已经有了10个数据，均为0
      ```

   3. 传入两个参数，第一个参数为vetor存放元素的数量，第二个参数为每个元素的值（相同）

      ``` cpp
      vector<long> numbers2(10，20); // 存放10个20
      ```

   4. 通过列表初始化vector，直接指明存放的所有元素的值

      ```cpp
      vector<int> number3{1,2,3,4,5,6,7};
      ```

   5. (范围初始化)迭代器方式初始化vector，传入两个迭代器作为参数，第一个为首迭代器，第二个为尾后迭代器

      ```cpp
      vector<int> number3{1,2,3,4,5,6,7};
      vector<int> number4(number3.begin(),number3.end() - 3); // number4 = {1, 2, 3, 4}		begin = [0]-"1" end = [7]-""
      // 迭代器类似指针使用的vector构造方式为：左闭右开区间 [first, last) 
      ```

2. **vector的常用操作**

   ```cpp
   iterator begin();  				// 返回首位迭代器
   iterator end();  				// 返回尾后迭代器
   bool empty() const; 			// 判空
   size_type size() const; 		// 返回容器中存放的元素个数
   size_type capacity() const; 	// 返回容器容量（最多可以存放元素的个数）
   void push_back(const T& value); // 在最后一个元素的后面再存放元素
   void pop_back(); 				// 删除最后一个元素
   void clear(); 					// 清空所有元素，但不释放空间
   void shrink_to_fit();  			// 释放多余的空间（可以存放元素但没有存放元素的空间=capacity-size）
   void reserve(size_type new_cap);// 预留空间≠扩容，请求 vector 分配至少 new_cap 大小的连续内存空间，如果当前容量不足，则重新分配更大内存，只扩容、不新增元素、不改变 size，新分配的内存空间不初始化
   // 1.已有的元素完全保留，不受影响
   // 2.不会新增任何元素（即只增加空的空间）
   // 3.新开辟的内存空间不初始化（保持未定义状态）
   // 4.不会缩小空间（如果你给的 new_cap 比当前容量小，reserve 什么都不做）
   // !!!reserve () 绝对不会在原有空间后面扩容！要么什么都不做，要么必须开辟全新空间！
   ```

3. **vector的遍历(以int型数据举例)**

   ```cpp
   vector<int> nums{1,2,3,4,5,6,7};
   ```

   - 增强for循环

     ```cpp
     for (auto & element : nums) {
         cout << element << " ";
     }
     cout << endl;
     ```

   - 下标方式

     ```cpp
     for (size_t i = 0; i < nums.size(); ++i) {
         cout << nums[i] << " ";
     }
     cout << endl;
     ```

   - 迭代器方式

     ```cpp
     auto it = nums.begin();
     while(it != nums.end()){
         cout << *it << " ";
         ++it;
     }
     cout << endl;
     ```

4. **vector的动态扩容**

   当vector存满后，仍然追加存放数据时，vector会进行自动扩容

   GCC(gcc、g++)中vector是2倍的容量扩容机制：当vector存满后再添加新的元素，容量就会变成2倍，把新的元素存入其中；而MSVC是1.5倍的扩容

   > 很多技术上具体的实现，在不同的平台上细节不同。C++标准给出功能的要求，各个编译器只需要实现此功能

   - **工作步骤：**

   （1）**(必然会)开辟(新)空间**

   （2）Allocator分配（后面STL阶段学习）

   （3）复制，再添加新元素

   （4）**回收原空间**

   ![image-20250225092256556](..\0.TyporaPicture\image-20250225092256556.png)

5. ==**vector的底层实现**==

   利用**sizeof()查看vector对象**的大小时，发现无论存放的元素类型、数量如何，其**大小始终为24个字节**（64位环境）

   - **vector对象由三个指针组成：**

     - <span style=color:red;background:yellow>**_start指向当前数组中第一个元素存放的位置**</span>

     - <span style=color:red;background:yellow>**_finish指向当前数组中最后一个元素存放的下一个位置**</span>

     - <span style=color:red;background:yellow>**_end_of_storage指向当前数组能够存放元素的最后一个空间的下一个位置**</span>

   - **可以推导出：**

     - **size() = _finish - _start**

     - **capacity() = _end_of_storage - start**

   - **扩容时的底层行为：**

     **逻辑上确实是 `size() == capacity()`，但绝大多数标准库源码不会写成直接比较两个函数返回值，而是用指针相等判断**

     但实际源码如下：

     ```cpp
     if (_M_finish == _M_end_of_storage) {
         // 需要扩容
     }
     ```

     这等价于 `size() == capacity()`，但**避免了两次指针减法**，而且指针比较指令通常更轻量

## 三、C++输入输出流

- **输入输出的含义**

  以前所用到的输入和输出，都是以终端为对象的，即从键盘输入数据，运行结果输出到显示器屏幕上。从操作系统的角度看，每一个与主机相连的输入输出设备都被看作一个**文件**。除了以终端为对象进行输入和输出外，还经常用磁盘(光盘)作为输入输出对象，磁盘文件既可以作为**输入文件**，也可以作为**输出文件**

  在编程语言中的输入输出含义有所不同。**程序的输入**指的是从输入文件将数据传送给程序(内存)，**程序的输出**指的是从程序(内存)将数据传送给输出文件

- **C++输入输出流机制**

  C++ 的 I/O 发生在流中，==**流是字节序列**==。如果字节流是从设备（如键盘、磁盘驱动器、网络连接等）流向内存，这叫做**输入操作**。如果字节流是从内存流向设备（如显示屏、打印机、磁盘驱动器、网络连接等），这叫做**输出操作**

  就 C++ 程序而言，**I/O 操作可以简单地看作是从程序移进或移出字节**，程序只需要关心是否正确地输出了字节数据，以及是否正确地输入了要读取字节数据，特定 I/O 设备的细节对程序员是隐藏的

- **C++常用流类型**

  1. **标准I/O(流)**

     对系统指定的标准设备的输入和输出。即从键盘输入数据，输出到显示器屏幕。这种输入输出称为标准的输入输出，简称**标准** I/O

  2. **文件I/O(流)**

     以外存磁盘文件为对象进行输入和输出，即从磁盘文件输入数据，数据输出到磁盘文件。以外存文件为对象的输入输出称为文件的输入输出，简称**文件** I/O

  3. **字符串I/O(流)**

     对内存中指定的空间进行输入和输出。通常指定一个字符数组作为存储空间（实际上可以利用该空间存储任何信息）。这种输入和输出称为字符串输入输出，简称**串** I/O

  常用的输入输出流如下：

  | 类名              | 作用             | 头文件       |
  | ----------------- | ---------------- | ------------ |
  | **istream**       | **通用输入流**   | **iostream** |
  | **ostream**       | **通用输出流**   | **iostream** |
  | iostream          | 通用输入输出流   | iostream     |
  | **ifstream**      | **文件输入流**   | **fstream**  |
  | **ofstream**      | **文件输出流**   | **fstream**  |
  | fstream           | 文件输入输出流   | fstream      |
  | **istringstream** | **字符串输入流** | **sstream**  |
  | **ostringstream** | **字符串输出流** | **sstream**  |
  | stringstream      | 字符串输入输出流 | sstream      |

  ![image-20241105111010178](..\0.TyporaPicture\image-20241105111010178.png)

## ==四、流的四种状态==

IO 操作与生俱来的一个问题是可能会发生错误，一些错误是可以恢复的，另一些是不可以的。在C++ 标准库中，用 iostate 来表示流的状态，不同的编译器 iostate 的实现可能不一样，不过都有四种状态：

1. <span style=color:red;background:yellow>**badbit **</span>表示发生**系统级的错误**，如不可恢复的读写错误。通常情况下一旦 badbit 被置位，流就无法再使用了
2. <span style=color:red;background:yellow>**failbit **</span>表示发生**可恢复的错误**，如期望读取一个int数值，却读出一个字符串等错误。这种问题通常是可以修改的，流还可以继续使用

3. <span style=color:red;background:yellow>**eofbit**</span>表示**到达流结尾位置**， 流在正常输入输出的情况下结束，会被置为eofbit状态

4. <span style=color:red;background:yellow>**goodbit **</span>表示流处于**有效状态**。流在有效状态下，才能正常使用。如果 badbit 、 failbit 和 eofbit 任何一个被置位，则流无法正常使用

这四种状态都定义在类 ios_base 中，作为其数据成员存在。在 GNU GCC7.4 的源码中，流状态的实现如下：

![image-20241105180158154](D:\Typora Picture\image-20241105180158154.png)

通过流的状态函数实现：

```cpp
bool good() const 	// 流是goodbit状态，返回true，否则返回false
bool bad() const	// 流是badbit状态，返回true，否则返回false
bool fail() const	// 流是failbit状态，返回true，否则返回false
bool eof() const	// 流是eofbit状态，返回true，否则返回false
```

## 五、标准输入输出流

对系统指定的标准设备的输入和输出。即从键盘输入数据，输出到显示器屏幕。这种输入输出称为标准输入输出，简称**标准** I/O

C++标准库定义了三个预定义的标准输入输出流对象:

- **标准输入流 (`std::cin`)**：从键盘（或其他输入设备）读取数据
- **标准输出流 (`std::cout`)**：向标准输出设备(屏幕)（或其他输出设备）输出数据
- **标准错误流 (`std::cerr`)**：用于向屏幕输出错误信息，不缓冲

标准输入、输出的内容包含在头文件==<iostream>==中

> 有时候会看到**通用输入输出流**的说法，这是一个更广泛的概念，可以与各种类型的输入输出设备进行交互，包括标准输入输出设备、文件、网络等

1. **标准输入流**

   - istream 类定义了一个全局输入流对象，即 cin , 代表的是**标准输入**，它从标准输入设备(键盘)获取数据，程序中的变量通过**流提取符 “>>”（输入流符号）** 从流中提取数据

   - 流提取符 “>>” 从流中提取数据时通常跳过输入流中的空格、tab 键、换行符等空白字符，会把这些**空白字符作为分隔符**，只有在输入完数据再按回车键后，该行数据才被送入键盘<font color=red>**缓冲区**</font>，形成输入流，提取运算符 “>>” 才能从中提取数据

   - 流提取符 “>>” 从流中提取数据时通常跳过输入流中的空格、tab 键、换行符等空白字符，会把这些**空白字符作为分隔符**，只有在输入完数据再按回车键后，该行数据才被送入键盘<font color=red>**缓冲区**</font>，形成输入流，提取运算符 “>>” 才能从中提取数据

     下面来看一个例子，每次从 cin 中获取一个字符：

     ```cpp
     void printStreamStatus(std::istream & is){ 
         cout << "is's goodbit:" << is.good() << endl;
         cout << "is's badbit:" << is.bad() << endl;
         cout << "is's failbit:" << is.fail() << endl;
         cout << "is's eofbit:" << is.eof() << endl;
     }
     
     void test0(){
         printStreamStatus(cin);  // goodbit状态
         int num = 0;    
         cin >> num;   
         cout << "num:" << num << endl;
         printStreamStatus(cin);  // 进行一次输入后再检查cin的状态
     }
     ```

   - 如果没有进行正确的输入，输入流会进入failbit的状态，无法正常工作，需要恢复流的状态，查看C++参考文档，需要利用<span style=color:red;background:yellow>**clear和ignore**</span>函数配合，实现这个过程：

     ```cpp
     if(!cin.good()){
         // 恢复流的状态
         cin.clear();
         // 清空缓冲区，才能继续使用 
         cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // 忽略缓冲区的所有剩余字符 
     }
     ```

     ```cpp
     void test()
     {
         int num = 10;
         cout << "执行输入操作前流的状态:" << endl;
         printStreamStatus(cin);
         
         cin >> num;
         cout << "执行输入操作后流的状态:" << endl;
         printStreamStatus(cin);
         
         if(!cin.good()){
             // 恢复流的状态
             cin.clear();
             // 清空缓冲区 后才能使用
             // 忽略当前输入流中的所有字符，直到遇到换行符为止. 这种方法适用于清空缓冲区，因为它可以跳过所有字符。
             cin.ignore(std::numberic_limits<std::streamsize>::max(), '\n');
             printStreamStatus(cin);    
         }
         // 没有正常输入 num被设置为0
         cout << "num=" << num << endl;
         string line;
         cin >> line;
         cout << "line:" << line << endl;
     }
     ```

   - 实例：输入整型数据的具体实现（要求如果是非法输入则继续输入）

     ```cpp
     void readInt(int & num) {
         /*具体实现*/
     }
     void test() {
     	int num = 0;
     	readInt(num);
     }
     ```

     - 形式1

       ```cpp
       void readInt(int & num) {
       	cout << "input a num:" << endl;
       	cin >> num;
       	while(!cin.eof()) {
       		if(cin.bad()) {
       			cout << "cin has broken!" << endl;
                   return;
       		} else if (cin.fail()) {
                   // 重置流状态
                   cin.clear();
                   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                   cout << "input a num again:" << endl;
                   cin >> num;
       		} else {
                   cout << "num: " << num << endl;
                   break;
               }
       	}
       }
       ```

     - 形式2

       ```cpp
       /*
       逗号运算符','
       顺序执行左边所有表达式，最终只返回最右边表达式的值作为循环条件
       */
       void inputInteger(int num) {
           cout << "input a num:" << endl;
           while(cin >> num, !cin.eof()){
               // 逗号运算符，将 cin >> num 和 !cin.eof() 组合在一起
               if (cin.bad()) {
                   cout << "cin has broken!" << endl;
                   return;
               } else if (cin.fail()) {
                   // 重置流状态
                   cin.clear();
                   cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                   cout << "input a num again:" << endl;
       		} else {
                   // 输入合法
                   cout << "num: " << num << endl;
                   break;
       		}
       	}
       }
       ```

     补充：注意cin表达式的返回值:

     - cin对象作为条件时,隐式转换为布尔类型

     - cin对象完成一次输入后,返回值为自身对象,可以进行连续链式的输入

       ```cpp
       cin >> a >> b >> c;
       // 第一步：cin >> a，返回 cin
       // 第二步：用返回的 cin 继续 >> b，又返回 cin
       // 第三步：再用 cin >> c
       // 即( (cin >> a) >> b ) >> c;
       ```

2. **缓冲机制**

   在标准输入输出流的测试中发现，流有着缓冲机制。**缓冲区**又称为缓存，它是内存空间的一部分。也就是说，在内存空间中预留了一定的存储空间，这些存储空间用来缓冲输入或输出的数据，这部分预留的空间就叫做**缓冲区**。缓冲区根据其对应的是输入设备还是输出设备，分为**输入缓冲区**和**输出缓冲区**

   - 为什么要引入缓冲区

     比如我们从磁盘里取信息，我们先把读出的数据放在缓冲区，计算机再直接从缓冲区中取数据，等缓冲区的数据取完后再去磁盘中读取，这样就**可以减少磁盘的读写次数**，再加上**计算机对缓冲区的操作大大快于对磁盘的操作**，故应用缓冲区可大大提高计算机的运行速度

     又比如，我们使用打印机打印文档，由于打印机的打印速度相对较慢，我们先把文档输出到打印机相应的缓冲区，打印机再自行逐步打印，这时我们的 CPU 可以处理别的事情。因此缓冲区就是一块内存区，它用在输入输出设备和 CPU 之间，用来缓存数据。它**使得低速的输入输出设备和高速的CPU能够协调工作，避免低速的输入输出设备占用CPU，解放出CPU，使其能够高效率工作**

   - 缓冲区要做哪些工作

     从上面的描述中，不难发现缓冲区**向上连接了程序的输入输出请求**，**向下连接了真实的 I/O 操作**。作为中间层，==必然需要分别处理好与上下两层之间的接口，以及要处理好上下两层之间的协作==

     输入或输出的内容会存在流对象对应的缓冲区，在特定情景下会从缓冲区释出

   - ==**缓冲机制**==

     缓冲机制分为三种类型：<span style=color:red;background:yellow>**全缓冲、行缓冲和不带缓冲**</span>

     - 全缓冲

       在这种情况下，当**填满缓冲区后**才进行实际 I/O 操作。全缓冲的典型代表是**对磁盘文件的读写**

     - 行缓冲

       在这种情况下，当**在输入和输出中遇到换行符时**，执行真正的 I/O 操作。这时，我们输入的字符先存放在缓冲区，等按下回车键换行时才进行实际的 I/O 操作。典型代表是**cin**

     - 不带缓冲

       也就是不进行缓冲，**有多少数据就刷新多少**。**标准错误流cerr**是典型代表，这使得出错信息可以直接尽快地显示出来

3. **标准输出流**

   ostream 类定义了全局输出流对象 cout，即标准输出，在缓冲区刷新时将数据输出到终端

   如下几种情况会导致输出缓冲区内容被刷新：

   1. <font color=red>**程序正常结束**</font>

      ```cpp
      // 马上输出了1025个a
      void test1(){
          for(int i = 0; i < 1025; ++i){
              cout << 'a';
          }
      }
      ```

   2. <font color=red>**缓冲区满**</font>

      **GCC中标准输出流的默认缓冲区大小就是1024个字节**

      ```cpp
      // 马上输出了1024个a,等待2秒后输出了最后一个a
      // 在实验环境中cout对象的默认缓冲区大小是1024个字节，缓冲区满了还继续传输内容，就会刷新出了当前缓冲区中所有内容，后面还有一个字符，就要等程序正常结束时刷新出来
      #include <unistd.h> // linux专属，提供操作系统底层功能
      
      void test1(){
          for(int i = 0; i < 1025; ++i){
              cout << 'a';
          }
          sleep(2); // <unistd.h>
      }
      ```

   3. 使用<font color=red>**操纵符**</font>显式地刷新输出缓冲区，如endl

      ```cpp
      // 加上endl这种操作符，直接输出了5个a，等待2秒程序结束；如果不加endl，等待2秒程序结束时才会输出5个a
      void test()
      {
          for(int i = 0; i < 5; ++i){
              //cout << 'a' << endl;
              cout << 'a';
          }
          sleep(2);
      }
      ```

      > 查看ostream头文件中endl的定义（刷新缓冲区 + 换行）
      >
      > ```
      > cd /usr/include/c++/11
      > vim ostream
      > ```
      >
      > ![image-20241107104337240](..\0.TyporaPicture\image-20241107104337240.png)
      >
      > 如果在使用cout时，没有使用endl函数，键盘输入的内容会存在输出流对象的缓冲区中，当缓冲区满或遇到换行符时，将缓冲区刷新，内容传输到终端显示。可使用sleep函数查看缓冲的效果，如果不用sleep函数，即使没有endl或换行符，所有内容依然是直接输出——因为**程序执行完时也会刷新缓冲区**

   **关于操作符**

   endl : 用来完成换行，并刷新缓冲区

   flush : 用来直接刷新缓冲区的——cout.flush();

   **标准错误流**

   ostream 类还定义了全局输出流对象 cerr，标准错误流（不带缓冲，立即输出默认到终端）

