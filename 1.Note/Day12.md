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

   - 示例

     ```cpp
     // Class类型的指针指向nullptr 通过该指针->调用该类型的成员函数
     typedef void (FFF::*MemberFunction)(int); // 定义成员函数类型MemberFunction
     MemberFunction mf = &FFF::print; // 定义成员函数指针
     FFF* fp = nullptr;
     (fp->*mf)(34);
     ```

   - 示例结果

     

4. **总结**

   <span style=color:red;background:yellow>**C++中普通函数、函数指针、成员函数、成员函数指针、函数对象，可以将它们概括为可调用实体**</span>

```
可以“不通过对象”强行调用非静态成员函数吗？
技术上可以通过一些非法/未定义行为的方式让代码通过编译并执行（例如将空指针转型后调用），但这属于危险的奇技淫巧，绝不是语言的正确用法，在任何严肃代码中都不应该出现：

cpp
MyClass* p = nullptr;
p->hello();             // 若函数未使用成员变量，可能“碰巧”不崩，但UB！
虽然有时看到这种写法能跑，根本原因是该函数没有访问任何成员数据，编译器生成的代码恰好不依赖 this。一旦函数内有成员访问，程序就会崩溃。不要这样做
```

## 二、类型转换函数



## 三、嵌套类



## 四、单例对象自动释放



## 五、补充

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

3. 