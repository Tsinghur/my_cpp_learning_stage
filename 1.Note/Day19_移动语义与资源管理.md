# Day19_移动语义与资源管理

## 一、移动语义

1. **为什么要使用移动语义**

   回顾之前的String.cc

   ```cpp
   #include <string.h>
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class String {
   public:
       // default no arg constructor
       String()
       /* : m_pstr(nullptr) */
       : m_pstr(new char[1]())
       {
           cout << "String()" << endl;
       }
   	// args constructor
       String(const char* pstr)
       : m_pstr(new char[strlen(pstr) + 1]{})
       {
           cout << "String(const char*)" << endl;
           strcpy(m_pstr, pstr);
       }
   	// copy constructor
       String(const String& rhs)
       : m_pstr(new char[strlen(rhs.m_pstr) + 1]())
       {
           cout << "String(const String&)" << endl;
           strcpy(m_pstr, rhs.m_pstr);
       }
   	// operator =
       String& operator=(const String& rhs) {
   		cout << "String &operator=(const String&)" << endl;
           if (this != &rhs) {
               if (m_pstr) {
                   delete [] m_pstr;
               }
               m_pstr = new char[strlen(rhs.m_pstr) + 1]();
               strcpy(m_pstr, rhs.m_pstr);
           }
           return *this;
       }
   	// length
       size_t length() const {
           size_t len = 0;
           if (m_pstr) {
               len = strlen(m_pstr);
           }
           return len;
   
       }
   	// c style string
       const char* c_str() const {
           if(m_pstr) {
               return m_pstr;
           } else {
               return nullptr;
           }
       }
   	// destructor
       ~String() {
           cout << "~String()" << endl;
           if(m_pstr) {
               delete [] m_pstr;
               m_pstr = nullptr;
           }
       }
       void print() const {
           if (m_pstr) {
               cout << "m_pstr = " << m_pstr << endl;
           } else {
               cout << endl;
           }
       }
   private:
       char* m_pstr;
   };
   
   void test0() {
       String s1("hello");
       //拷贝构造
       String s2 = s1;
       // 先构造，再拷贝构造，编译的时候需要加上才能看到结果：-fno-elide-constructors --std=c++11
       // 利用"hello"这个字符串创建了一个临时对象
       // 并复制给了s3
       // 这一步实际上new了两次
       String s3 = "hello";
   }
   ```

   **创建s3的过程中实际创建了一个临时对象，也会在堆空间上申请一片空间**，然后把**字符串内容复制给s3**的`pstr`，这一行结束时临时对象的生命周期结束，它申请的那片空间被回收。**在这个过程中，这片(临时)空间申请了又马上被回收**，实际上可以视作**一种不必要的开销**。我们希望能够少new一次，可以**直接让s3能够复用临时对象申请的空间**

   这就是要使用**移动语义的目的**，**移动语义**允许**资源的所有权从一个对象转移到另一个对象，而无需进行昂贵的额外拷贝操作**

2. **左值与右值**

   - 左值和右值是针对表达式而言的

     - **左值**是指表达式执行结束后依然存在的持久对象
     - **右值**是指表达式执行结束后就不再存在的临时对象

   - 如何区分

     <span style=color:red;background:yellow>**能对表达式取地址的，称为左值**</span>
     <span style=color:red;background:yellow>**不能取地址的，称为右值**</span>

     > 在实际使用过程中，字面值常量、临时对象（匿名对象）、临时变量（匿名变量），都称为右值。**右值又被称为即将被销毁的对象**
     >
     > **字面值常量**，也就是10， 20这样的数字，属于**右值**，不能取地址
     >
     > **字符串常量**，“world"，是属于**左值**的，**位于内存中的文字常量区**

   - 存储位置

     1. 右值的存储位置

        关于右值的存储位置，它们可以存储在内存中，也可以仅存在于寄存器中，这取决于具体的实现和上下文。编译器优化策略在很大程度上影响了这一点：

        - **在内存中存储：** 尽管**右值**通常被视为临时的，但它们可以在内存中创建并存储，尤其是当它们**是较大的对象或者编译器决定这样做更高效时**。例如，一个复杂的右值对象（比如一个大的临时结构体或对象）可能**会在内存中分配空间，以便存储其状态**（与内存相对的，就是存储在CPU寄存器中）
        - **仅存在于寄存器中：** **对于简单的右值**（如基本数据类型的算术表达式结果），**编译器可能会选择将其存储在寄存器中以优化性能**。寄存器的使用减少了内存访问的需要，可以加快程序的执行速度。*当一个右值用于简单表达式或作为函数参数传递时，这种情况更常见*

     2. 优化和存储决策

        **C++标准并没有具体规定对象必须存储在内存还是寄存器中**，这留给了编译器作为实现细节。现代编译器使用复杂的优化策略来决定何时在内存中分配空间以及何时使用寄存器。这些决策基于减少程序的总运行时间和内存使用，同时还要满足程序的语义要求

        因此，是否一个右值会短暂存储在内存中或只会存在寄存器中，取决于多种因素，包括但不限于右值的类型、大小、上下文以及编译器的优化策略。在**实际编程中，除非在性能调优阶段需要深入了解这些细节，否则开发者通常不需要过分关注这一点**

   - 验证如下取址操作和引用绑定操作是否可行

     ```cpp
     void test1() {
     	int a = 1, b = 2;
     	&a;  
     	&b;
     	&(a + b); // error
     	&10; // error
     	&String("hello"); // error
         
         //非const引用绑定 ——> 左值
     	int& r1 = a;
     	int& r2 = 1; // error
         
         //const引用绑定 ——> 左值/右值
     	const int & r3 = 1;
     	const int & r4 = a;
         
     	String s1("hello");
     	String s2("wangdao");
     	&s1;
     	&s2;
     	&(s1 + s2); // error
     }
     ```

     如上定义的`int & r1 ` 和 `const int & r3` 分别叫作**左值引用**与**const左值引用**，**非const左值引用只能识别出左值**，const左值引用既可以绑定到左值，也可以绑定到右值，即**const左值引用不能区分是左值还是右值**

3. **右值引用**

   为了实现String s3 = "hello"的空间复用需求，则希望能够区分出右值，并且还要进行绑定，所以，C++11提出了新特性<span style=color:red;background:yellow>**右值引用**</span>，使用双重引用符号`&&`表示，它允许程序员将资源从一个对象“移动”到另一个对象，而不是进行资源的拷贝，从而提高效率

   ```cpp
   // 非const左值引用不能绑定右值
   int& r1 = a;
   int& r2 = 1; // error
   
   // const左值引用既可以绑定左值，又可以绑定右值
   const int& r3 = a;
   const int& r4 = 1;
   
   // 右值引用只能绑定右值
   int&& rRef = a; // error
   int&& rRef2 = 1;
   ```

   对rRef取地址是可行的，rRef2本身是一个左值。但这并不代表右值引用本身一定是左值

   <span style=color:red;background:yellow>**实际上，右值引用既可以是左值（比如：作为函数的参数、有名字的变量），也可以是右值（函数的返回类型）**</span>

4. **移动构造函数**

   **有了右值引用后，再接收临时对象作为参数时就可以分辨出来**

   之前`String str1 = String("hello");`这种操作调用拷贝构造函数时：

   1. 形参为`const String& `类型，其既能绑定右值又能绑定左值，这是为了确保通过右值拷贝时即对右值的接收不出错而特意为之的
   2. 为了确保进行左值的复制时不出错，一律采用重新开辟空间的方式

   有了能够分辨出右值的右值引用之后，就可以定义一个新的构造函数——<span style=color:red;background:yellow>**移动构造函数**</span>

   - 基本语法

     ```cpp
     class MyClass {
     public:
         // 移动构造函数
         MyClass(MyClass&& other) {
     		// ...
         }
     };
     ```

     ![image-20250123145016684](..\0.TyporaPicture\image-20250123145016684.png)

     给String类加上移动构造函数，在**初始化列表中完成浅拷贝**，使s3的m_pstr指向临时对象的m_pstr所指向的空间（复用），还不能忘记要将右操作数（临时对象）的m_pstr设为空指针，因为这个**临时对象会马上销毁**（**要避免临时对象销毁时调用析构函数回收掉这片堆空间,否则可能出现double free**）

     ```cpp
     String(String&& rhs)
     : m_pstr(rhs.m_pstr)
     {
         cout << "String(String&&)" << endl;
         rhs.m_pstr = nullptr;
     }
     ```

     <font color=red>**编译时加上编译器的去优化参数 -fno-elide-constructors**</font>，再运行代码String s3 = "hello";

     发现没有再调用拷贝构造函数，而是调用了移动构造函数

   - 对比函数形参的三种写法

     ![image-20250123144821592](..\0.TyporaPicture\image-20250123144821592.png)

   - 移动构造函数的特点

     1. 如果没有显式定义构造函数、拷贝构造、赋值运算符函数、析构函数，编译器会自动生成移动构造，**对右值的复制会调用移动构造**
     2. 如果显式定义了拷贝构造，而没有显式定义移动构造，那么对右值的复制会调用拷贝构造
     3. 如果显式定义了拷贝构造和移动构造，那么对右值的复制会调用移动构造

   - <span style=color:red;background:yellow>**总结：移动构造函数优先级高于拷贝构造函数**</span>

     可以理解为：如果显式定义了拷贝构造和移动构造，利用一个已存在的对象创建一个新对象时，会先尝试调用移动构造，如果这个对象是右值，就使用移动构造函数创建出新对象，如果这个对象是左值，移动构造使用不了，就会调用拷贝构造

5. **移动赋值运算符函数**

   - 原理及语法

       有了移动构造函数的成功经验，很容易想到原本的赋值运算符函数

       比如，进行如下操作时

       ```cpp
       String s3("hello");
       s3 = String("wangdao");
       ```

       原本赋值运算符函数的做法

       ![image-20250123152213648](..\0.TyporaPicture\image-20250123152213648.png)

       我们希望复用临时对象申请的空间，那么也同样需要赋值运算符函数能够分辨出接收的参数是左值还是右值，同样可以利用右值引用

       ![image-20250123152530601](..\0.TyporaPicture\image-20250123152530601.png)

       所以移动赋值运算符函数可以写为

       ```cpp
       String& operator=(String&& rhs){
           if(this != &rhs){
               delete [] m_pstr;
               // 浅拷贝
               m_pstr = rhs.m_pstr;
               rhs.m_pstr = nullptr;
               cout << "String& operator=(String&&)" << endl;
           }
           return *this;
       }
       /*
       rhs和传入的原始右值生命周期完全绑定
       既然生命周期一致，为什么不会出问题？
       关键：对象 ≠ 资源
       临时对象（右值）会销毁，但它持有的资源已经被我们偷走了
       我们用 rhs.m_pstr = nullptr 把临时对象和资源切断了联系
       （即资源是由对象的指针所指向的，而不是对象本身，而临时对象销毁时只是其本身被销毁了，但是其所持有的资源不会仅因此而销毁）
       */
       ```

   - 移动赋值函数的特点

        1. 如果**没有显式定义构造函数、拷贝构造、赋值运算符函数、析构函数，编译器会自动生成移动赋值函数**。**使用右值**的内容进行**赋值会调用移动赋值函数**。

        2. 如果**显式定义了赋值运算符函数，而没有显式定义移动赋值函数**，那么**使用右值**的内容进行**赋值会调用赋值运算符函数**。
        3. 如果**显式定义了移动赋值函数和赋值运算符函数**，那么**使用右值**的内容进行**赋值会调用移动赋值函数**。

        <span style=color:red;background:yellow>**移动赋值函数优先级也是高于赋值运算符函数**</span>

   - **注意：移动赋值函数中的自赋值判断有没有必要？**

       ```cpp
       String s1("hello");
       // 右值给左值赋值，肯定不是同一个对象
       s1 = String("world");
       // 创建了两个内容相同的临时对象，也不是同一对象
       String("wangdao") = String("wangdao");
       ```

       似乎去掉自复制判断不会造成问题，但是c++11提出了一种方式，将左值转为右值，就是std::move函数，其会导致移动赋值函数的自复制情况出现问题

   **总结**

          1. 将**拷贝构造函数**和赋值运算符函数称为具有**复制控制语义的函数**
          2. 将**移动构造函数**和**移动赋值函数**称为具有**移动语义的函数**<span style=color:red;background:yellow>**(移交控制权)**</span>
          3. <font color=red>**具有移动语义的函数优于具有复制控制语义的函数执行**</font>

6. **`std::move`函数**

      - 为什么需要`std::move`

        在一些使用移动语义的场景下，有时需要将左值转为右值，std::move函数的作用是**显式的将一个左值转换为右值**，<span style=color:red;background:yellow>**其实现本质上就是一个强制转换**</span>
      
        - 修改`std::move`返回值导致的问题
      
          当**将一个左值转换为右值后**，如果**利用右值引用绑定std::move的返回值**，并**进行修改操作**，**那么原来的左值对象也会随之修改**，可能无法正常工作了，所以**原对象必须要重新赋值才可以继续使用**
      
          ```cpp
          void test() {
              int a = 1;
              &(std::move(a)); // error，左值转成了右值
              
          	String s1("hello");
          	s1.print();
              // 如果经历了std::move的强转后没有进行修改操作，之后s1对象还是可以正常使用的
              std::move(s1); // 没有使用返回值
              s1.print(); // 原左值对象仍能正常使用
              
              // 若是使用std::move的返回值调用移动赋值运算符函数，在移动赋值运算符函数中形参String&& rhs = std::move(s1)即使用右值引用，在移动赋值函数中：rhs.m_pstr = nullptr; 进行了修改操作，会使得s1对象本身的m_pstr变成空指针 再进行print操作时会出现问题
              String s2("abc");
              s2 = std::move(s1);
              s1.print(); // 这里程序中断
              s2.print();
          }
          ```
      
      - **移动赋值函数**在使用`std::move`时**需要考虑自复制问题**
      
          如果将移动赋值函数的自赋值判断去除，如下情况依然会调用移动赋值函数，但是s1的pstr所指向的空间被回收，且被设为了空指针，会出错
      
          ```cpp
          String s1("hello");
          s1 = std::move(s1);
          s1.print();
          ```
      
          - **验证**
      
            去掉移动赋值函数中的浅拷贝，移动赋值函数中：先让左操作数s1 的 `m_pstr`**重新指向一片空间**，再将右操作数rhs的 `m_pstr`设为空指针
      
            ```cpp
            String& operator=(String&& rhs){
                delete [] m_pstr;
                m_pstr = new char[1]();
                rhs.m_pstr = nullptr;
                cout << "String& operator=(String&&)" << endl;
                return *this;
            }
            ```
      
            即使这样，但通过输出流运算符输出s1的 `m_pstr`仍然造成了程序的中断，所以说明对std::move(s1)的内容进行修改，会导致s1的内容也被修改
      
            > `std::move`的返回值是右值引用
            >
            > std::move(s1).m_pstr = nullptr;——合法，但是不推荐，因为会内存泄漏、破坏对象，不要手动修改 move 后的对象成员，交给移动构造 / 移动赋值处理
      
      - **`std::move`原理**
      
        `std::move`的本质是在底层做了类型转换来标记一个对象为右值（它本身并**不移动数据或资源**，只是**为移动操作提供条件**，使得移动构造函数和移动赋值运算符函数能够被调用）
      
        `std::move()` 的关键作用是告诉编译器，“我不再需要这个对象的资源，你可以安全地转移它”，所以==**移动赋值函数的自赋值判断不应该省略**==

7. **右值引用本身的性质**

   定义一个返回值是右值引用的函数

   ```cpp
   int gNum = 10;
   
   int&& func() {
       return std::move(gNum);
   }
   
   void test1() {
       // &func(); // 无法取址，说明返回的右值引用本身也是一个右值
       int&& ref = func();
       &ref; // 可以取址，此时ref是一个右值引用，其本身是左值
   }
   ```

   **右值引用本身是左值还是右值，取决于是否有名字，==有名字就是左值，没名字就是右值==**

   > **==补充：==**
   >
   > 值得一提的是，如果我们写出如下的代码，func的返回值是一个匿名右值引用，其绑定的内容是一个即将销毁的右值，这是一个不安全的操作，因为func的返回值，这个**没有名字的右值引用无法持续有效地延长**这个**临时变量的生命周期**，这个临时变量本体销毁后，**返回值真实的性质是一个”悬空引用“**。接下来**虽然还能用右值引用绑定这个返回值**，但是**任何(对于悬空引用的右值引用)尝试访问的行为都可能导致未定义的错误**
   >
   > ```cpp
   > int&& func(int a,int b) {
   > 	return a + b;
   > }
   > 
   > void test1() {
   >     // &func(1,2); // 无法取址
   >     int&& ref = func(1,2);
   >     &ref; 
   >     // cout << ref << endl; // error
   > }
   > ```

8. ==**拷贝构造函数调用时机的补充**==

      - **函数返回值是一个将亡值时**

          ```cpp
          String func2(){
              String str1("wangdao");
           str1.print();
              return str1; // 这里返回的是对象而非引用
          }
          
          void test2(){
              func2();
              // &func2(); // error,右值
               String&& ref = func2(); // 这个ref跟func2中的str1没有关系，因为str1在函数结束时已经销毁了，ref绑定的是函数返回的临时对象，但由于ref是右值引用，所以能延长这个临时对象的生命周期
              &ref; // 右值引用本身为左值
          }
          // 若是将返回类型与返回值改为右值引用与右值，ref不但仍旧与str1没有关系，反而还会出现问题，这就是上述"7.右值引用本身的性质"中补充的例子
          // 原因在于ref没有直接绑定str1，而是返回值即一个临时右值引用直接绑定的str1
          ```

          在这里func2的调用按以前的理解会调用拷贝构造函数，但是发现**结果是调用了移动构造函数**

          这是因为<font color=red>**当返回的对象其本身生命周期即将结束，就不再调用拷贝构造函数，而是调用移动构造函数**</font>
          
          ![image-20250124104555895](..\0.TyporaPicture\image-20250124104555895.png)
          

      - <font color=red>**如果返回的对象其本身生命周期大于函数生命周期时，执行return语句时还是调用拷贝构造函数**</font>
        
          ```cpp
                String str1("beijing");
                String func3() {
                    str1.print();
                    return str1;
                }
                
                void test3() {
                    func3(); // 调用拷贝构造函数
                }
          ```
          
          ![image-20250124104716862](..\0.TyporaPicture\image-20250124104716862.png)
          

      **总结：**当类中同时定义移动构造函数和拷贝构造函数，需要对以前的规则进行补充，<span style=color:red;background:yellow>**调用哪个函数还需要取决于返回的对象本体的生命周期**</span>

## 二、资源管理

C语言在进行资源管理的时候，比如文件指针，由于分支较多，或者由于写代码的人与维护的人不一致，导致分支没有写的那么完善，从而导致文件指针没有释放

```cpp
void UseFile(char const* fn) {
    // 1. 获取资源
    FILE* f = fopen(fn, “r”);
    // 2.使用资源
    // ... 
    // 3.回收资源有很多分支
    if (!g()) { fclose(f); return; }
    // ...
    if (!h()) { fclose(f); return; }
    // ...
    // 4.释放资源
    fclose(f); 
}
```

根据之前单例对象(AutoRelease)自动释放的经验，我们可以想到**利用对象的生命周期去管理资源**。那么就可以尝试**实现一个安全回收文件的程序**了

```cpp
class SafeFile {
public:
    // 在构造函数中初始化资源（托管资源）
    SafeFile(FILE* fp)
    : m_fp(fp)
    {
        cout << "SafeFile(FILE*) " << endl;
    }
    // 提供方法访问资源
    void write(const string& msg) {
        fwrite(msg.c_str(), 1, msg.size(), m_fp);
    }
    // 利用析构函数释放资源
    ~SafeFile() {
        cout << "~SafeFile()" << endl;
        if (m_fp) {
            fclose(m_fp); 
            cout << "fclose(m_fp)" << endl;
        }
    }
private:
    FILE* m_fp;
};

void test0() {
    string msg = "hello,world";
    SafeFile sf(fopen("wd.txt", "a+"));
    sf.write(msg);
}
```

## 三、RAII(资源获取即初始化)技术

以上例子其实已经用到了RAII的技术。所谓RAII，是**C++提出的资源管理的技术**，全称为Resource Acquisition Is Initialization，由C++之父Bjarne Stroustrup提出

其**本质是利用对象的生命周期来管理资源**（内存资源、文件描述符、文件、锁等），**因为当对象的生命周期结束时，会自动调用析构函数**

1. **常见特征**

   - 在构造函数中托管资源（在给构造函数传参时初始化资源）

   - 在析构函数中释放资源

   - 一般不允许进行复制或者赋值（对象语义）

   - 提供若干访问资源的方法（如：读写文件）

2. **对象语义与值语义**

   - **对象语义：不允许复制或者赋值**

     就像全世界不会有两个完全一样的人，程序世界中也不会有两个完全一样的对象

     **实现常用手段：**

     1. 将拷贝构造函数与赋值运算符函数设置为私有的

     2. 将拷贝构造函数与赋值运算符函数 = delete

     3. 使用继承的思想，将基类的拷贝构造函数与赋值运算符函数删除（或设为私有），让派生类继承基类

        > - 派生类无法自动生成拷贝构造 / 赋值运算符
        >
        >   编译器**只会在「所有基类、所有成员变量都支持拷贝 / 赋值」的前提下**，才会为派生类自动生成：默认拷贝构造函数、默认拷贝赋值运算符
        >
        >   如果**基类的拷贝 / 赋值被禁用（delete / 私有）**，编译器**绝对不会**为派生类生成这两个函数
        >
        > - 并且也无法手动定义
        >
        >   因为派生类的**拷贝构造函数 / 拷贝赋值运算符**，有一个**强制性义务**：必须先初始化 / 赋值「基类子对象」，而基类 `Base` 已经把**拷贝构造、拷贝赋值**都 `= delete` 了 → **基类根本不允许拷贝**
        >
        >   所以：手动写派生类的拷贝函数 → 必须调用基类的拷贝函数 → 基类拷贝函数被删除 → **编译直接报错**

   - **值语义：可以进行复制或赋值**（两个变量的值可以相同）

     与对象语义相反

     ```cpp
     int a = 10;
     int b = a;
     int c = 20;     
     
     c = a; // 赋值
     int d = c; // 复制
     ```

3. **模拟实现**

   可以实现一个类模板，模拟RAII的思想

   ```cpp
   template <class T>
   class RAII {
   public:
       // 1.在构造函数中初始化资源（托管资源）
       RAII(T* data)
       : m_data(data)
       {
           cout << "RAII(T*)" << endl;
       }
   
       // 2.在析构函数中释放资源
       ~RAII() {
           cout << "~RAII()" << endl;
           if (m_data) {
               delete m_data;
               m_data = nullptr;
           }
       }
       // 3.提供若干访问资源的方法
       T* operator->() {
           return m_data;
       }
       T& operator*() {
           return *m_data;
       }
       T* get() const {
           return m_data;
       }
       void set(T* data) {
           if (m_data) {
               delete m_data;
               m_data = nullptr;
           }
           m_data = data;
       }
       // 4.不允许复制或赋值
       RAII(const RAII& rhs) = delete;
       RAII& operator=(const RAII& rhs) = delete;
   private:
       T* m_data;
   };
   ```

   如下，**raii不是一个指针，而是一个对象**，但是它的**使用已经和指针完全一致**了。**此对象可以托管堆上的Point对象，而且不用考虑delete**

   ```cpp
   void test0() {
   	Point* pt = new Point(1, 2);
   	// 智能指针的雏形
   	RAII<Point> raii(pt);
   	raii->print();
   	(*raii).print();
   }
   ```

4. <span style=color:red;background:yellow>**RAII技术的本质**</span>

   利用**栈对象**的生命周期管理资源，因为栈对象在离开作用域时候，会执行析构函数
