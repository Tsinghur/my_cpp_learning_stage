# Day12

## 一、可调用实体-函数指针与成员函数指针

1. **函数指针**

   - 声明

     ```cpp
     返回类型 (*指针名称)(参数类型列表)
     ```

   - 示例

     ```cpp
     void print(int x) {
         cout << "print:" << x << endl;
     }
     
     void display(int x) {
         cout << "display:" << x << endl;
     }
     
     int main(void) {
         //省略形式
         void (*p)(int) = print;
         p(4);
         p = display;
         p(9);
         //完整形式
         void (*p2)(int) = &print;
         (*p2)(4);
         p2 = &display;
         (*p2)(9);
     }
     ```

   - 补充

     - 定义函数指针p后，可以指向print函数，也可以再指向display函数，并通过函数指针调用函数

       > 那么其实可以抽象出一个函数指针类，这个类的对象就是这个特定类型的函数指针
       >
       > p和p2可以抽象出一个函数指针类型**void(*)(int)**  —— <font color=red>**逻辑类型，不能在代码中直接以这种形式写出**</font>

     - 使用typedef可以定义类型别名，这段程序中函数指针p、p2的类型是void (*) (int)，但是C++中是没有这个类的，所以**可以使用typedef定义这样的一个新类型**

       > 可以理解为是给void ( * ) (int) 取类型别名为Function
       >
       > ```cpp
       > typedef void(*Function)(int);
       > ```

     - Function类的“对象”可以这样使用，这个类的“对象”都是特定类型的函数指针，只能指向一种函数（这种函数的类型在定义函数指针类时就决定了）

       ```cpp
       Function f;
       // 指向print函数
       f = print;
       // 调用print函数
       f(19);
       // 指向display函数
       f = display;
       // 调用display函数
       f(27);
       ```

2. **成员函数指针**

   从函数指针的用法可知，成员函数应该也可以使用这种形式

   - 形式

     > 比如有这样一个类FFF，包含两个成员函数
     >
     > ```cpp
     > class FFF {
     > public:
     >     void print(int x) {
     >         cout << "FFF::print:" << x << endl;
     >     }
     >     void display(int x) {
     >         cout << "FFF::display:" << x << endl;
     >     }
     > };
     > ```

     定义一个函数指针要明确指针指向的函数的返回类型、参数类型，那么<span style=color:red;background:yellow>**定义一个成员函数指针还需要确定的是这个成员函数是哪个类的成员函数（类的作用域）**</span>

     ```cpp
     // 声明成员函数指针:
     返回类型 (类名::*指针名称)(参数列表);
     // 将成员函数指针指向特定的成员函数：
     指针名称 = &类名::成员函数;
     ```

   - 形式解析

     - **返回类型**：成员函数的返回类型
     - **类名**：成员函数所属的类
     - **指针名称**：成员函数指针的名称0
     - **参数列表**：成员函数的参数类型

   - 注意

     - 与普通函数指针不一样的是，<font color=red>**成员函数指针的定义和使用都需要使用完整写法**</font>，**不能使用省略写法**，定义时要完整写出指针声明，使用时要完整写出解引用（解出成员函数后接受参数进行调用）

     - 成员函数需要通过对象来调用，<font color=red>**成员函数指针也需要通过对象来调用**</font>

       ```cpp
       (对象.*指针名称)(参数);     // 对于具体对象
       (对象指针->*指针名称)(参数); // 对于对象指针(指向堆上的对象)
       ```

       ```cpp
       // 示例
       void (FFF::*p)(int) = &FFF::print;
       FFF ff;
       (ff.*p)(4);
       ```

       > **类比来写，也可以使用typedef来定义这种成员函数指针类，见下面成员指针运算符的两种形式**

   - ==**成员指针运算符**的两种形式==

     1. `.*`

        - 要求：<font color=red>**成员函数指针指向的成员函数需要是FFF类的公有成员函数**</font>

        - 示例

          ```cpp
          typedef void (FFF::*MemberFunction)(int); // 定义成员函数类型MemberFunction
          MemberFunction mf = &FFF::print; // 定义成员函数指针
          FFF fff;  
          (fff.*mf)(15); // 通过对象调用成员函数指针
          ```

          > - `typedef void (FFF::*MemberFunction)(int);` 定义了一个类型
          > - `&FFF::成员函数名` 是该类型的一个值
          > - 之所以`&`放在类名之前`*`放在成员函数名之前，，是因为 C++ 规定**通过 `&` + `限定名` 获取非静态成员函数指针是唯一合法途径**；而`typedef` 只是给了这个指针类型一个别名，丝毫不影响获取指针的语法

     2. `->*`

        ```cpp
        // 无要求，以FFF类对象是一个堆上的对象为例
        typedef void (FFF::*MemberFunction)(int); // 定义成员函数类型MemberFunction
        MemberFunction mf = &FFF::print; // 定义成员函数指针
        FFF* fp = new FFF{};
        (fp->*mf)(65); // 通过指针调用成员函数指针
        ```

   - 成员指针的意义

     1. 回调函数：<font color=red>**将成员函数指针作为参数传递给其他函数**</font>，使其他函数能够在特定条件下调用该成员函数
     2. 事件处理：将成员函数指针存储在事件处理程序中，以便在特定事件发生时调用相应的成员函数
     3. 多态性：通过将成员函数指针存储在基类指针中，可以实现多态性，在运行时能够去调用相应的成员函数

3. **空指针的使用**

   - 示例——==**即可以“不通过对象”强行调用非静态成员函数吗**==

     ```cpp
     // Class类型的指针指向nullptr 通过该指针->调用该类型的成员函数
     typedef void (FFF::*MemberFunction)(int); // 定义成员函数类型MemberFunction
     MemberFunction mf = &FFF::print; // 定义成员函数指针
     FFF* fp = nullptr;
     (fp->*mf)(34);
     ```

   - 示例结果

     可以通过并能输出正常的结果

   - 结果分析

     因为空指针去调用成员函数也好、成员函数指针也好，只要不涉及到访问该类数据成员，都是可以的

     ```cpp
     class Bar {
     public:
         void test0() {
             cout << "Bar::test0()" << endl; 
         }
         void test1(int x) { 
             cout << "Bar::test1(): " << x << endl; 
         }
         void test2() { 
             cout << "Bar::test2(): " << m_data << endl; 
         }
         int m_data = 10;
     };
     
     void test0() {
         Bar* fp = nullptr;
         fp->test0(); // ok
         fp->test1(3); // ok
         fp->test2(); // error，设计到数据成员，需要有一个对象
     }
     ```

   - 内存图分析

     空指针没有指向有效的对象。

     **对于不涉及数据成员的成员函数，不需要实际的对象上下文**，因此就算是空指针也可以调用成功。对于涉及数据成员的成员函数，空指针无法提供有效的对象上下文，因此导致错误

     ![image-20241120112331410](..\0.TyporaPicture\image-20241120112331410.png)

4. **总结**

   <span style=color:red;background:yellow>**C++中普通函数、函数指针、成员函数、成员函数指针、函数对象，可以将它们概括为可调用实体**</span>

## 二、类型转换函数

普通变量的类型转换：int 型转换为 long 型， double 型转换为 int 型

接下来讨论类对象与其他类型的转换，转换方向有:**（1）由其他类型向自定义类型转换（2）由自定义类型向其他类型转换**

- **由其他类型向自定义类型转换——隐式转换-构造函数**

  由构造函数来实现，有当类中定义了合适的构造函数时，转换才能通过。这种转换，一般称为**隐式转换**

  示例

  ```cpp
  class A
  {
  public:
      // explicit // 使用这个限定词可禁止隐式转换
      A(int num)
      : m_num(num)
      {
          cout << "A constructor" << endl;
      }
  private:
      int m_num;
  };
  
  void test(){
      // 隐式转换 使用int数据创建出了一个A类型对象
      A a = 1;
  }
  ```

  > 这种隐式转换是比较奇怪的，一般情况下，不希望这种转换成立，所以可以在相应的构造函数之前加上`explicit`关键字，禁止这种隐式转换
  >
  > 而有些隐式转换使用起来很自然，比如：
  >
  > ```cpp
  > string s1("hello,world");
  > string s1 = "hello,world";
  > ```
  >
  > 这行语句其实也是隐式转换，利用C风格字符串构造一个临时的string对象，再调用string的拷贝构造函数创建s1

- **由自定义类型向其他类型转换——类型转换函数**

  **形式固定**

  ```cpp
  operator 目标类型() {}
  ```

  **特征要求**

  - 必须是成员函数
  - 没有返回类型
  - 没有参数
  - 在函数执行体中必须要返回目标类型的变量

  1. <font color=red>**自定义类型向内置类型转换**</font>

     - 示例

       ```cpp
       class Point {
       public:
       // ...
       operator int() {
         cout << "operator int()" << endl;
         return m_x + m_y;
       }
       	// ...
       };
       ```

     - 使用（与隐式转换的方向相反）

       ```cpp
       Point pt(1,2);
       int a = 10;
       // 将Point类型对象转换成int型数据
       a = pt;
       cout << a << endl;
       ```

  2. <font color=red>**自定义类型向自定义类型转换**</font>

     - ==使用类型转换函数==——<span style=color:red;background:yellow>**需要注意将类型转换函数设为谁的成员函数**</span>

         ```cpp
         Point pt(1,2);
         Complex cx(3,4);
         pt = cx;
         cx.print();
         ```
         
         如上，想要**让Complex对象转换成Point对象**，并对pt赋值，**应该在Complex类中添加目标类型的类型转换函数**
         
         ```cpp
         class Complex {
         // ...
         operator Point() {
           cout << "operator Complex()" << endl;
           return Point(m_real,m_image);
         }
         };
         
         pt = cx;
         ```
         
     - 使用隐式转换（即特定形式的构造函数）
  
         ```cpp
         Point::Point(const Complex& rhs)
         : m_x(rhs.m_real)
         , m_y(rhs.m_image)
         {
             cout << "Point的特殊构造函数" << endl;
         }
         ```
  
     - 赋值运算符函数
  
         ```cpp
         Point& Point::operator=(const Complex& rhs) {
             m_x = rhs.m_real;
             m_y = rhs.m_image;
             cout << "Point& operator=(const Complex&)" << endl;
             return *this;
         }
         ```
  
     **总结**
  
     三种方式同时存在时，会**优先调用赋值运算符函数**（**赋值操作本身就支持**），其次**类型转换**的优先级高于**隐式转换**
  
     ```cpp
     operator=(const Complex&) > oprator Point() > Point(const Complex&)
     ```

## 三、C++运算符优先级排序与结合性

![image-20231128114539734](..\0.TyporaPicture\image-20231128114539734.png)

<img src="..\0.TyporaPicture\image-20250225095240219.png" alt="image-20250225095240219" style="zoom: 58%;" />

## 四、嵌套类

1. **前置**

   1. **类作用域（Class Scope）**

       类作用域是指在类定义内部的范围。在这个作用域内定义的成员（包括变量、函数、类型别名等）可以被该类的所有成员函数访问。类作用域开始于类定义的左花括号，结束于类定义的右花括号。**在类作用域内，成员可以相互访问，==无论它们在类定义中的声明顺序如何==**

       ```cpp
       class A {
           // 类作用域
       }
       ```

   1. **类名作用域（Class Name Scope）**

       类名作用域指的是**可以通过类名**访问的作用域

       这主要用于访问类的**静态成员**、**嵌套类型**。**==类名==必须用于访问静态成员或嵌套类型**，除非在类的成员函数内部，因为**它们不依赖于类的任何特定对象**

       以静态成员为例：

       ```cpp
       class MyClass {
       public:
           void func() {
               m_b = 100; // 类的成员函数内访问_b
           }
           static int m_a;
           int m_b;
       };
       int MyClass::m_a = 0;
       
       void test0() {
           MyClass::m_a = 200; // 类外部访问_a
       }
       ```

   1. **全局类**

       在函数和其他类定义的外部定义的类称为**全局类(即定义在全局作用域中的类)**，绝大多数的 C++ 类都是全局类。我们在前面定义的所有类都在全局作用域中，全局类具有全局作用域

2. **嵌套类定义**

   与全局类相对应，一个类A还可以定义在另一类B的定义中，这就是<span style=color:red;background:yellow>**嵌套类**</span>结构。A类被称为B类的<font color=red>**内部类**</font>，B类被称为A类的<font color=red>**外部类**</font>

   ```cpp
   class Global {
       
   };
   
   // 外部类
   class Outer {
     // 内部类
     class Nested{
          
     };
   };
   ```

3. **示例**

   ```cpp
   // 外部类
   class Line {
   public:
       // 内部类
       class Point {
       public:
           Point(int x,int y)
           : m_ix(x)
           , m_iy(y)
           {}
       private:
           int m_ix;
           int m_iy;
       };
   public:
       Line(int x1, int y1, int x2, int y2)
       : m_pt1(x1,y1)
       , m_pt2(x2,y2)
       {}
   private: 
       Point m_pt1;
       Point m_pt2;
       double length = 10;
   };
   ```

   - **注意**

     - Point类是定义在Line类中的内部类，无法直接创建Point对象，需要在Line类名作用域中才能创建

       ```cpp
       Point pt(1,2); // error
       Line::Point pt2(3,4); // ok
       ```

     - Point类是Line类的内部类，并不代表Point类的数据成员会占据Line类对象的内存空间，<span style=color:red;background:yellow>**在存储关系上并不是嵌套的结构**</span>

     - 只有**当Line类有Point类类型的对象成员时**，Line类对象的**内存布局中才会包含Point类对象（成员子对象）**

       > 如果Line类中没有Point类的对象成员，sizeof(Line) = 8;（此时只有一个double型数据成员）
       >
       > 如果Line类中有两个Point类的对象成员，sizeof(Line) = 24;（此时有1个double型数据成员 + 2*2个int型(对象成员中的)数据成员）

   - 使用输出流运算符<<输出Line对象的实现

     ```cpp
     // 为了使用<<输出Line对象,其中访问了Line中私有数据成员m_p1, m_p2  需要将重载函数设置为友元
     std::ostream& operator<<(std::ostream& os,const Line & line) {
      os << line.m_p1 << "---" << line.m_p2 << endl; // 复用Point自己重载的输出流运算符函数 —— 封装思想
      return os;
     }
     ```

     ```cpp
     // Point中同理, 将重载函数设置为友元，同时还需要加上!!!Line的类名作用域!!!
     // 如果Point为Line中私有成员, 则还需要将重载函数声明为Line的友元
     std::ostream& operator<<(std::ostream & os,const Line::Point & p) {
      os << p.m_x << "," << p.m_y;
      return os;
     }
     ```

4. **嵌套类结构的访问权限**

   - 外部类对内部类的成员进行访问

   - 内部类对外部类的成员进行访问


   ![image-20250226094255903](..\0.TyporaPicture\image-20250226094255903.png)

   **内部类相当于是定义在外部类中的外部类的友元类**
   类A定义在类B中，那么类A访问类B的成员时，就相当于默认的是类B的友元类

5. **Pimpl模式**

   不是设计模式之一，Pimpl（Pointer to Implementation）模式是一种常用的 C++ 编程技巧，用于**隐藏类的实现细节**，提高编译时间效率，并帮助维护代码的封装性。在 Pimpl 模式中，类的接口（即公共部分）与其实现（即私有成员）是分开的

   通常做法是**将类的实现（数据成员、私有成员函数等）放到一个单独的内部类中**，并**通过指针将其与外部类关联**

   - 结构

     1. **外部类（接口类）**：只包含公有的接口（方法声明），不包含实现细节（即不包含私有成员的定义）
     2. **内部类（实现类）**：该类定义了所有的实现细节（私有数据成员、私有成员函数等）。它通常是一个封装类，且通常在 `.cpp` 文件中定义，不在头文件中暴露
     3. **指针**：外部类通过一个指向内部实现类的指针来访问实现细节

   - 示例

     - 需求

       希望Line的实现全部隐藏，在源文件中实现，再将其打包成库文件，交给第三方使用

     - 源代码

       1. 头文件只给出接口

          ```cpp
          // Line.hpp
          class Line {
          public:
              Line(int x1, int y1, int x2, int y2);
              ~Line();
              void printLine() const; // 打印Line对象的信息
          private:
              class LineImpl; // 类的前向声明
              LineImpl * m_pimpl; // 需要上一行的前向声明
          };
          ```

       2. 在实现文件中进行具体实现，使用嵌套类的结构（LineImpl是Line的内部类，Point是LineImpl的内部类），Line类对外公布的接口都是使用LineImpl进行具体实现的

          在测试文件中创建Line对象（最外层），使用Line对外提供的接口，但是不知道具体的实现，而具体实现位于LineImpl.cc中

          ```cpp
          // LineImpl.cc
          #include "Line.hpp"
          #include <iostream>
          
          using std::cout;
          using std::endl;
          
          // 内部实现类
          class Line::LineImpl {
              // 给出具体实现类，使用内部类
              class Point {
              public:
                  Point(int x, int y)
                  : m_x(x)
                  , m_y(y)
                  {}
                  void print() const {
                      cout << m_x << " " << m_y;
                  }
              private:
                  int m_x;
                  int m_y;
              };
          public:
              LineImpl(int x1, int y1, int x2, int y2)
              : m_pt1(x1,y1)
              , m_pt2(x2,y2)
              {}
              void print() const {
                  m_pt1.print();
                  cout << endl;
                  m_pt2.print();
                  cout << endl;
              }
          private:
              Point m_pt1;
              Point m_pt2;
          };
          
          
          Line::Line(int x1 ,int y1, int x2, int y2)
          : m_pimpl(new LineImpl(x1,y1,x2,y2))
          {}
          
          Line::~Line() {
              if (m_pimpl) {
                  delete m_pimpl;
                  m_pimpl = nullptr;
              }
          }
          
          void Line::printLine() const {
              m_pimpl->print();
          }
          
          //testLine.cc
          void test0() {
              Line line(10,20,30,40);
              line.printLine();
          }
          ```

       3. 打包库文件，将库文件和头文件交给第三方

          ```cpp
          sudo apt install build-essential
          g++ -c LineImpl.cc
          ar rcs libLine.a LineImpl.o
          
          生成libLine.a库文件
          编译：g++ Test.cc(测试文件) -L(加上库文件地址) -lLine(就是库文件名中的lib缩写为l，不带后缀)
          此时的编译指令为 g++ Test.cc -L. -lLine
          ```

     - 内存结构

       ![image-20250225093601534](..\0.TyporaPicture\image-20250225093601534.png)

       pimpl模式是一种减少代码依赖和编译时间的C++编程技巧，其基本思想是将一个**外部可见类的实现细节**（一般是**通过私有**的非虚成员）放在一个单独的实现(**私有**)类中，**在可见类中通过一个==私有==指针来间接访问该类型**

   - 优点

     - 实现信息隐藏
     - 只要头文件中的接口不变，实现文件可以随意修改，修改完毕只需要将新生成的库文件交给第三方即可
     - 可以实现库的平滑升级

## ==五、单例对象自动释放==

- **之前实现的单例模式：**单例对象由静态指针ms_instance保存，最终通过**手动**调用destroy函数进行**释放**

  **现实工作中，单例对象是需要进行自动释放**。程序在执行的过程中 ，需要判断有哪些地方发生了内存泄漏 ，此时需要工具valgrind的使用来确定。
  假设单例对象没有进行自动释放 ，那么valgrind工具会认为单例对象是内存泄漏。程序员接下来还得再次去确认到底是不是内存泄漏 ，增加了程序员的额外的工作

- 如何实现单例对象的自动释放——看到自动就应该想到当**对象被销毁时**，**析构函数会被自动调用**

**四种方式**

1. **利用另一个对象的声明周期管理资源**

   - 原理

       ![image-20250225100753372](..\0.TyporaPicture\image-20250225100753372.png)

       利用对象的生命周期管理资源——析构函数（在析构函数中会执行delete m_p），当**对象被销毁时会自动调用**

   - 注意

       1. 如果还手动调用了Singleton类的destroy函数，会导致double free问题，所以**可以删掉destroy函数**，将**回收**堆上的单例对象的**工作完全交给AutoRelease对象**
       2. 不能用多个AutoRelease对象托管同一个堆上的单例对象
       3. 需要将控制类AutoRelease设置为所托管的单例类的友元类, 这样可以调用单例类中的private权限的析构函数

   

2. ==**嵌套类 + 静态对象**==

   

3. **`atexit + destroy`**

   

4. **`atexit + pthread_once + destroy`**

   

## 六、补充

1. **嵌套类的初始化**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class Line {
   public:
       class Pointer {
       public:
           Pointer(int x, int y)
           : m_x(x)
           , m_y(y)
           {}
           friend class Line;
       private:
           int m_x;
           int m_y;
       };
       Line(const Pointer& pt1, const Pointer& pt2)
       : m_pt1(pt1.m_x, pt1.m_y)
       , m_pt2(pt2.m_x, pt2.m_y)
       {}
       Line(int x1, int y1, int x2, int y2)
       : m_pt1(x1, y1)
       , m_pt2(x2, y2)
       {}
   private:
       Pointer m_pt1;
       Pointer m_pt2;
   };
   
   void test1() {
       // 先定义构造函数,否则无法有参初始化
       Line line1({1, 2}, {3, 4});
       Line line2{{1, 2}, {3, 4}};
   
       Line line3(1, 2, 3, 4);
       Line line4{1, 2, 3, 4};
   }
   
   int main() {
       test1();
   
       return 0;
   }
   ```

2. **静态成员函数与回调**

   `pthread_once` 的第二个参数要求是 `void (*)(void)` 类型。非静态成员函数因为隐含 `this` 指针，类型不匹配，不能直接当作普通函数指针传递。而**静态成员函数没有 `this` 指针，本质上就是一个全局函数，只是受类作用域保护**，所以必须（且只能）传递 `Singleton::initRoutine` 这样的静态函数地址。加上类名限定，还能让编译器准确找到这个静态函数定义，即使它在类外定义，限定名也是必需的

   **==即问题的本质在于普通成员函数多了一个参数this指针，而不在于是否为成员函数还是普通函数==**

   > **回调（Callback）**，简单说就是：**把一个函数（或可调用对象）作为参数传递给另一个函数，约定在某个特定时刻（如事件发生、任务完成），由那个函数反过来调用这个传入的函数**

3. **两个自定义类型之间(赋值)转换的3种方式**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class Complex;
   class Point {
   public:
       Point(int x, int y)
       : m_x(x)
       , m_y(y)
       {}
       Point(const Complex& rhs); // 需要Complex类前置声明
       Point& operator=(const Complex& rhs);
       void print() const {
           cout << "(" << m_x << "," << m_y << ")" << endl;
       }
   private:
       int m_x;
       int m_y;
   };
   
   class Complex {
   public:
       Complex(int x = 0, int y = 0)
       : m_real(x)
       , m_image(y)
       {}
       operator Point() {
           cout << "类型转换函数operator Pointer被调用" << endl;
           return Point(m_real, m_image);
       }
       void print() const {
           cout << "(" << m_real << "," << m_image << ")" << endl;
       }
       friend class Point; // 使Point中通过Complex的构造函数可以访问Complex的私有成员
   private:
       int m_real;
       int m_image;
   };
   
   Point::Point(const Complex& rhs)
   : m_x(rhs.m_real)
   , m_y(rhs.m_image)
   {
       cout << "Point的特殊构造函数" << endl;
   }
   
   Point& Point::operator=(const Complex& rhs) {
       m_x = rhs.m_real;
       m_y = rhs.m_image;
       cout << "Point& operator=(const Complex&)" << endl;
       return *this;
   }
   
   // operator=(const Complex&) > oprator Point() > Point(const Complex&)
   void test1() {
       Point pt(1, 2);
       Complex cx(3, 4);
       pt = cx;
       pt.print();
       cx.print();
   }
   
   int main() {
       test1();
   
       return 0;
   }
   ```

4. **嵌套类的访问问题**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   // 外部类
   class Line
   {
   public:
       // 内部类
       class Point{
       public:
           Point(int x,int y)
           : m_ix(x)
           , m_iy(y)
           {}
           static void func() {
               cout << "Line::Point::func()" << endl;
           }
           void func2() {
               func();
               /* cout << Line::a << endl; // error:因为内部类不知道这个a是哪一个外层类对象的 */
               /*                          // 外层可以直接使用是因为隐含一个this指针，其永远指向调用函数的对象 */
               /*                          // 而内层类而言，而编译器不会凭空给你一个 Line 对象，所以 Line::a 这样的写法毫无意义，直接报错 */
           }
       private:
           int m_ix;
           int m_iy;
       };
   public:
       int a;
       Line(int x1, int y1, int x2, int y2)
       : m_pt1(x1,y1)
       , m_pt2(x2,y2)
       {}
       void func3() {
           /* func(); // error */
           /* Line::Point::func(); // right */
           Point::func();
       }
       friend void test1();
   private:
       Point m_pt1;
       Point m_pt2;
       double length = 10;
   };
   
   void test1() {
       Line line(1, 2, 3, 4);
       line.func3();
       line.m_pt1.func();
       line.m_pt1.func2();
   }
   // 外部类访问内部类
   void test2() {
       /* Point::func(); // error */
       Line::Point::func();
       /* Point pt(1, 2); // error */
       Line::Point pt(1, 2); // error
       pt.func();
       pt.func2();
   }
   
   int main() {
       test1();
       cout << "------------" << endl;
       test2();
   
       return 0;
   }
   ```

5. 

