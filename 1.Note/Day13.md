# Day13

## 一、std::string的底层实现-写时复制原理探究

1. **std::string的实现方式**

   一个std::string对象占据的内存空间有多大，即sizeof(std::string)的值为多大？如果我们在不同的编译器（VC++, GCC, Clang++）上去测试，可能会发现其值并不相同；即使是GCC，不同的版本，获取的值也是不同的

   虽然历史上的实现有多种，但基本上有三种方式：

   - Eager Copy（**立即深拷贝**）
   - COW（Copy-On-Write **写时复制**）
   - SSO(Short String Optimization **短字符串优化**)

   > <font color=red>**std::string的底层实现是一个高频考点**</font>，虽然**目前std::string是根据SSO(短字符串优化)的思想实现**的，但是最好能够掌握其发展过程中的不同设计思想，在回答时会是一个非常精彩的加分项

2. **写时复制COW的基本原理**

   > 简单的就是深拷贝，无论什么情况，都是采用拷贝字符串内容的方式解决，这种实现方式，在不需要改变字符串内容时，对字符串进行频繁复制，效率比较低下。所以需要对其实现进行优化，之后便出现了COW的实现方式

   - **共享数据**

     当多个对象（如字符串变量）引用同一份数据时，它们共享底层内存，而非立即复制

   - **延迟复制**

     只有在某个对象尝试修改数据时，系统才会创建该数据的独立副本，确保修改不影响其他共享对象

   - 一些问题的探究

     1. 当字符串对象进行复制时，可以优化为指向同一个堆空间的字符串，接下来的问题就是何时回收堆空间的字符串内容呢？

        -  引用计数refCount, 当字符串对象进行复制操作时，引用计数+1；
        -  当字符串对象被销毁时，引用计数-1；
        -  只有当引用计数减为0时，才真正回收堆空间上字符串   

        ![image-20241204155449617](..\0.TyporaPicture\image-20241204155449617.png)

        补充：如果是如下创建对象，不能共用空间

        ```cpp
        string s1("hello");
        string s2("hello");
        // 在创建s2之前可能有很多String对象
        // 不可能遍历这些对象，看看哪个对象保存的内容是hello
        // 只有在复制或赋值时且确保内容一致时，s2才能去共用s1的空间
        ```

        即单独创建对象没有优化的空间，每一个string对象需要一片独立的空间存放自己的字符串

     2. 引用计数应该放到哪里？

        - 方案1——不合理

          需要改变str1的数据成员

          ![image-20250225093746344](..\0.TyporaPicture\image-20250225093746344.png)

        - 方案2——不合理

          静态数据成员被该类所有对象共享，但此时str1和str2的引用计数应该都是2，但是str3的引用计数应该是1

          ![image-20250225093837965](..\0.TyporaPicture\image-20250225093837965.png)

        - 方案3——可行，还可以继续优化

          ![image-20250225093942262](..\0.TyporaPicture\image-20250225093942262.png)

          按常规的思路，需要使用两次new表达式（字符串、引用计数）；可以优化成只用一次new表达式，因为申请堆空间的行为一定会涉及系统调用，程序员要尽量少使用系统调用，提高程序的执行效率

          **优化方向：**

          **把引用计数和字符串内容保存到一起**，<font color=red>**引用计数保存到字符串内容的前面，方便访问**</font>

          ![image-20241204094210678](..\0.TyporaPicture\image-20241204094210678.png)

## 二、std::string的底层实现-写时复制方式实现

1. **CowString的基础结构**

   CowString对象初始化时，为字符数组指针分配空间时，前部分用来存储int类型的引用计数，后部分用来存储实际的字符数据，通过指针移动进行操作

   ```cpp
   class CowString {
   public:
       // no arg constructor
       CowString();
       // arg constructor
       CowString(const char* pStr);
       // copy constructor
       CowString(const CowString& rhs);
       // operator =
       CowString& operator=(const CowString& rhs);
       // destructor
       ~CowString();
       // operator << 
       friend
       ostream& operator<<(ostream& os, const CowString& rhs);
       // operator []
       char& operator[](int index);
       // 用于获取字符串长度的方法
       int size() {
           return strlen(m_pStr);
       }
       // 返回C风格字符串
       char* c_str() {
           return m_pStr;
       }
   private:
       // pointer to char array
       char* m_pStr;
   };
   ```

2. **对象创建**

   - 无参构造函数

     ![image-20241204195737724](..\0.TyporaPicture\image-20241204195737724.png)

     1. 构造函数初始化列表中对字符数组指针进行初始化，4字节存储引用计数, 1**字节存**字符串结束字符**‘\0’**
     2. 并将字符数组**指针移动到**实际的**字符**数据位置
     3. 通过**强转与解引用**，将引用**计数初始化为1**

   - C风格字符串构造

     ![image-20241204151347589](..\0.TyporaPicture\image-20241204151347589.png)

     1. 构造函数初始化列表中对字符数组指针进行初始化，4字节存储引用计数，1字节存储字符串结束字符，C风格字符串的长度个字节存储有效字符数组
     2. 通过强转与解引用,将引用计数初始化为1
     3. 字符数据复制

   - 源代码

     ```cpp
     // no arg constructor
     CowString::CowString()
     : m_pStr(new char[4+1]{} + 4)
     {
         // 操作指针初始化引用计数为1
         *(int*)(m_pStr - 4) = 1;
     }
     
     // arg constructor
     CowString::CowString(const char* pStr)
     : m_pStr(new char[4 + strlen(pStr) + 1]{} + 4)
     {
         // 操作指针初始化引用计数为1
         *(int*)(m_pStr - 4) = 1;
         // 字符数据copy
         strcpy(m_pStr, pStr);
     }
     ```

3. **为了方便操作与使用, 代码复用, 可以将重复代码抽取到方法中, 封装一些操作**

   1. 获取引用计数：`int getRefCount()`
   2. 初始化引用计数：`void initRefCount()`
   3. 引用计数+1：`int incrementRefCount() `
   4. 引用计数-1：`int decrementRefCount()`
   5. 初始化列表中分配字符数组指针空间：`char * allocate(const char* pStr = nullptr)`

   ```cpp
   // 引用计数相关操作
   // 获取引用计数
   int getRefCount() {
       return *(int*)(m_pStr - 4);
   }
   // 初始化引用计数
   void initRefCount() {
       *(int*)(m_pStr - 4) = 1;
   }
   // 引用计数+1
   int incrementRefCount() {
       return ++*(int*)(m_pStr - 4);
   }
   // 引用计数-1
   int decrementRefCount() {
       return --*(int*)(m_pStr - 4);
   }
   // 初始化列表中分配字符数组指针空间
   char* allocate(const char* pStr = nullptr) {
       if (!pStr) { // 无参构造中使用
           return new char[4 + 1]{} + 4;
       } else {
           // C风格字符串构造中使用
           return new char[4+ strlen(pStr) + 1]{} + 4;
       }
   }
   ```

4. **对象复制**

   ![image-20241204151938136](..\0.TyporaPicture\image-20241204151938136.png)

   1. 调用拷贝构造函数, 在初始化列表中进行浅拷贝, 共享字符数组
   2. 引用计数+1

   ```cpp
   // copy constructor
   CowString::CowString(const CowString& cowSting)
   : m_pStr(cowSting.m_pStr)
   {
       cout << "copy constructor" << endl;
       // 引用计数+1
       incrementRefCount();
   }
   ```

5. **对象销毁**

   ![image-20241204153922228](..\0.TyporaPicture\image-20241204153922228.png)

   1. 调用析构函数 
   2. 引用计数-1
   3. 只有当引用计数为0的时候进行空间释放

   ```cpp
   // destructor
   CowString::~CowString() {
       cout << "destructor" << endl;
       // 引用计数-1
       decrementRefCount();
       // 如果引用计数为0，说明已无共享，回收空间
       if (getRefCount() == 0) {
           // 回收引用计数+字符数据部分的总空间
           delete [] (m_pStr - 4);
           cout << "==>release heap" << endl;
       }
       m_pStr = nullptr;
   }
   
   // 可以将析构函数中内容抽取到CowString类的release方法中，进行复用
   void release() {
       // 引用计数-1
       decrementRefCount();
       if (getRefCount() == 0) {
           // 引用计数为0 删除空间 
           delete [] (m_pStr - 4);
           cout << "release heap" << endl;
       }
       m_pStr = nullptr;
   }
   ```

6. **对象赋值**

   除了复制操作，赋值操作也可以确定两个string对象保存的字符串内容是相同的，也可以复用空间，引用计数随之改变

   但相比复制操作，**还需要考虑**string对象**原**本用来保存字符串的**堆空间是否需要回收**

   ![image-20241204190631758](..\0.TyporaPicture\image-20241204190631758.png)

   1. 原本空间的引用计数-1，引用计数减到0，才真正回收堆空间
   2. 让自己的指针指向新的空间，并将新空间的引用计数+1

   ```cpp
   // operator=
   CowString& CowString::operator=(const CowString& cowSting) {
       // 自赋值判断
       if (this != &cowSting) {
           // 引用计数-1
           decrementRefCount();
           // 判断引用计数是否为0
           if (getRefCount() == 0) {            // 释放原本空间
               delete [] (m_pStr - 4);
               cout << "release heap" << endl;
           }
           m_pStr = nullptr;
           // 指针指向新空间
           m_pStr = cowSting.m_pStr;
           // 新空间引用计数+1
           incrementRefCount();
       }
       // 返回自身对象
       return *this;
   }
   ```

7. ==**operator[]重载实现**==

   1. **直接重载的隐患**

      如下，若是直接返回对应位置的字符的引用

      ```cpp
      // operator []
      char& CowString::operator[](size_t index) {
       // 判断index合法
          if (index >= size()) {
              cout << "illegal index" << endl;
              static char nullChar = '\0'; // 静态局部变量只初始化一次，后续每次调用都是同一个实例
              return nullChar;
          } else {
              return m_pStr[index];
          }
      }
      
      void test() {
          CowString s1("abc");
          CowString s2 = s1;
          s1[0] = 'A'
      }
      // 因为s1,s2共享底层字符数据, 此时s1,s2中的内容都变成了Abc
      ```

      ![image-20241205094223084](..\0.TyporaPicture\image-20241205094223084.png)

   2. **第一次改进——深拷贝**

      - 改进

          如果多个对象共享了同一片空间，**一个对象通过下标访问运算符修改了字符串中的某个字符**，不应该影响到其他使用这片空间的string对象，所以**应当进行深拷贝操作，在新分配的空间中进行修改而不影响其他对象**

          所以，**多个对象共享空间，某个对象通过下标修改字符时：**

          1. 判断引用计数是否大于1，**大于1说明共享**
          2. 原空间的引用计数-1
          3. **深拷贝**
          4. 修改指针指向新空间
          5. 初始化新空间的引用计数

          ```cpp
          char& CowString::operator[](size_t index) {
           // 判断index
              if (index >= size()) {
                  cout << "index is illegal!" <<endl;
                  static char nullChar = '\0'; // 静态局部变量只初始化一次，后续每次调用都是同一个实例
                  return nullChar;
              } else {
                  // 判断引用计数是否大于1
                  if (getRefCount() > 1) {
                      // 说明共享了 需要开辟新空间
                      // 原来的引用计数-1
                      decrementRefCount();
                      char* temp = new char[4 + strlen(m_pStr)+1]() + 4;
                      // 复制
                      strcpy(temp, m_pStr);
                      // 更改指向
                      m_pStr = temp;
                      // 初始化新空间引用计数
                      initRefCount();
                  }
                  // 返回下标对应字符
                  return m_pStr[index];
              }
          }
          ```

      - 又引入一个<span style=color:red;background:yellow>**新的问题：**</span>

          经过对下标访问运算符operator[]的修改，当多个对象共享同一空间，某个对象通过下标修改字符时，不会影响到其他对象了，但是产生了一个新的问题，**下标访问进行读操作会产生影响**

          ```cpp
          CowString s1{"abc"};
          CowString s2 = s1;
          CowString s3 = s1;
          //下标访问
          cout << "========" << endl;
          cout << "s2[0]: " << s2[0] << endl;
          cout << "s1 cout: " << s1.getRefCount() << endl; // 2
          cout << "s2 cout: " << s2.getRefCount() << endl; // 1
          cout << "s3 cout: " << s3.getRefCount() << endl; // 2
          printf("s1 address: %p\n", s1.c_str()); // s1 address: 0x58a0d31aeeb4
          printf("s2 address: %p\n", s2.c_str()); // s2 address: 0x58a0d31af2e4
          printf("s3 address: %p\n", s3.c_str()); // s3 address: 0x58a0d31aeeb4
          
          // 1.引用计数发生了修改
          // 2.地址发生了改变
          ```

          即虽然**s2的内容没有变化，但是引用计数与地址都发生了变化**，然而：

          - **下标访问**

            **读操作** `cout << str1[0] << endl;` `cout << char字符`，只返回相应下标位置的字符即可，**不需要复制**，不修改引用计数

          - **下标修改**

            **写操作** `str1[0] = 'A';` `char字符 = char字符`，**需要进行申请新空间进行深拷贝**，修改引用计数，修改字符

      - 问题分析

        - 需要找到一种更好的方案去区分读写操作，首先想到 << 与 = 运算符重载，但是对于这里的 << 与 = 运算符来说，它们的操作数CowString[i]即char型字符、ostream都是基本类型，没有自定义类型对象，不符合重载的要求（**class类型或枚举**），所以**无法通过重载来解决**
        - 而CowString的**下标访问运算符[]**的操作数是`CowString`对象和`size_t`类型的下标，**也没办法判断取出来的内容接下来要进行读操作还是写操作**

        由此引入设计模式之一——**代理模式**

   3. **第二次改进——代理模式**

      - **思路**

        1. 创建一个CowString类的内部类
        2. 让CowString的operator[]函数返回是这个新类型的对象
        3. 然后在这个新类型中对 << 和 = 进行重载，让这两个运算符能够处理新类型对象，从而分开了处理逻辑，区分读写操作

        ![image-20241205102923993](..\0.TyporaPicture\image-20241205102923993.png)

      - **CowString中operator[]重载——服务于operator<< 与 operator=，==即[]是<<与=的前提==**

        根据分析过程，将CowString中下标访问运算符operator[]返回结果修改为内部类对象CharProxy

        为了能够在内部类对象CharProxy中处理字符数组中字符的读写操作, 需要2个参数（即CharProxy中的两个数据成员）

        ```cpp
        // operator[]-->返回内部类对象CharProxy
        CowString::CharProxy CowString::operator[](size_t index) {
            // 无论是读还是写都需要下标index
            // 还需能访问到外部类CowString中的字符数组指针成员-->CowString对象
            // 如何传递CowString对象?---->this
            // 将参数通过构造函数传递 才能在内部类对象中进行处理
            return CharProxy(*this, index);
        	// 返回CharProxy对象副本
        }
        ```

      - **内部类CharProxy定义**

        1. 根据operator[]推导出内部类CharProxy中需要2参构造函数：即**CowString对象**与**下标index**
        2. 进而推导出CharProxy中需要2个数据成员：`CowString & m_self `, `size_t m_index`
        3. **重载operator<<**用于处理**读操作**
        4. **重载operator=**用于处理**写操作**

        ```cpp
        // CharProxy定义
        class CowString {
        private:
            // 内部类--->处理下标访问运算符的读写逻辑
            class CharProxy {
            public:
                CharProxy(CowString& cowString, size_t index)
                : m_self(cowString)
                , m_index(index)
                {}
                // operator<< 读操作：out << s1[0] --> charProxy --> CowString --> m_pStr --> char
                // 友元函数方式进行重载
                friend
                ostream& operator<<(ostream& os, const CharProxy& proxy);
        
                //operator=写操作：s[0]='A'	   char = char
                // [] --> proxy --> cowString --> m_pStr --> char = char
                // 成员函数重载
                char& operator=(const char& ch);
            private:
                CowString& m_self;
                size_t m_index;
            };
            // ......
        }
        ```

      - **(CharProxy中)operator<<重载实现——读操作**

        因为定义的是私有的内部类CharProxy且在其之中还要访问CowString的私有成员，为了让输出流运算符能够处理CharProxy对象，所以需要将operator<<重载函数，**分别在CharProxy和CowString进行两次友元声明**

        ```cpp
        // operator<<友元函数重载，从而可以访问私有成员
        ostream& operator<<(ostream& os, const CowString::CharProxy& proxy) {
            if (proxy.m_index < 0 || proxy.m_index >= proxy.m_self.size()) {
                os << "index is illegal" << endl;
            } else {
                os << proxy.m_self.m_pStr[proxy.m_index];
            }
            return os;
        }
        ```

        > 对于读操作，还可以给CharProxy类定义类型转换函数来进行处理——即CharProxy --> char
        >
        > 在CowString中的operator[]中直接将返回的CharProxy对象转换为对应下标的char，稍稍达到了一定的简化效果，**可以避免双友元(可以去掉双友元)**
        >
        > ```cpp
        > class CowString {
        >     class CharProxy {
        > 	public:
        >         // 类型转换函数: charProxy ---> char
        >         operator char() const {
        >             cout << "operator cast" << endl;
        >             return m_self.m_pStr[m_index];
        >         }
        > 	private:
        >         CowString& m_self;
        >         size_t m_index;
        >     };
        >     // ......
        > };
        > ```

      - **(CharProxy中)operator=重载实现——写操作**

        ```cpp
        // operator= CharProxy的成员函数重载 存在this指向当前CharProxy对象
        char& CowString::CharProxy::operator=(const char& ch) {
            // index判断
            if (m_index < 0 || m_index >= m_self.size()) {
                cout << "index is illegal" << endl;
                static char nullChar = '\0';
                return nullChar;
            } else {
                // index合法，进行写操作
                // 判断引用计数是否大于1
                if (m_self.getRefCount() > 1) {
                    // 说明存在共享，需要开辟空间进行深拷贝
                    // 原空间引用计数-1
                    m_self.decrementRefCount();
                    // 开辟新空间
                    char* temp = new char[4 + m_self.size() + 1]() + 4;
                    // 深拷贝
                    strcpy(temp, m_self.m_pStr);
                    // 修改指针指向新空间
                    m_self.m_pStr = temp;
                    // 初始化新空间引用计数
                    m_self.initRefCount();
                }
                // 修改字符内容（若是引用计数为1，则直接在字符串上修改，无需复制）
                m_self.m_pStr[m_index] = ch;
                // 返回目标index位置的char
                return m_self.m_pStr[m_index]; // 为了支持连续赋值
            }
        };
        ```

   4. **总结**

      - 当运算符需要处理自定义类型对象时，先看一看这个自定义类型有没有相应的运算符重载函数，如果有，那么这个运算符就可以处理这个自定义类型对象

      - 如果没有运算符重载，就无法直接处理，需要进行转换
        - 先看看这个自定义类型中有没有类型转换函数，转换成一个该运算符可以直接处理的类型的数据
        - 如果没有类型转换函数，会再看看有没有隐式转换的途径（一般，大多数情况谨慎使用隐式转换）


## 三、std::string的底层实现-短字符串优化与最佳策略

1. **短字符串优化（SSO）**

   - 当字符串的字符数小于等于15时：buffer直接存放整个字符串
   - 当字符串的字符数大于15时：buffer 存放的就是一个指针，指向堆空间的区域

   这样做的好处是，当字符串较小时，直接拷贝字符串，放在 string内部，不用获取堆空间，开销小

   ![image-20241206102314843](..\0.TyporaPicture\image-20241206102314843.png)

   ```cpp
   // union表示共用体，允许在同一内存空间中存储不同类型的数据
   // 共用体的所有成员共享一块内存，但是每次只能使用一个成员
   class string {
   	union Buffer {
   		char* _pointer;
   		char _local[16];
   	};
   	size_t _size;
   	size_t _capacity;
       Buffer _buffer;
   };
   ```

2. **最佳策略**

   Facebook提出的最佳策略，将三者进行结合，因为以上三种方式，都不能解决所有可能遇到的字符串的情况，各有所长，又各有缺陷。综合考虑所有情况之后，facebook开源的folly库中，实现了一个fbstring，它根据字符串的不同长度使用不同的拷贝策略，**最终每个fbstring对象占据的空间大小都是24字节**





