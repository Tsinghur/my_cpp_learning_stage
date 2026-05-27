# CPP阶段笔记# Day02_C++与C

## 一、命名空间namespace

1. **什么是命名空间**

   - **命名空间又名字空间，是程序员命名的内存区域**，程序员根据需要指定一些有名字的空间域，把一些全局实体分别存放到各个命名空间中，从而与其他全局实体分隔开
      **命名空间是一种将全局作用域划分为更小的、可管理的部分的机制**

   - 命名空间中可以存放：变量、常量、函数、结构体、引用、类、对象、模板、命名空间等，它们都称为**实体**。
      每个名字空间都是一个名字空间域，存放在名字空间域中的全局实体只在本空间域内有效。名字空间对全局实体加以域的限制，从而合理的解决命名冲突

   - 名字冲突就是在同一个作用域中有两个或多个同名的实体，C语言中避免名字冲突，只能进行起名约定

      ```cpp
      int hw_cpp_tom_num = 100;
      int wd_cpp_bob_num = 200;
      ```

      C++为了**解决命名冲突** ，引入了**命名空间**，所谓命名空间就是一个**可以由用户自己定义的作用域**，在**不同的作用域中可以定义相同名字的变量，互不干扰，系统能够区分它们**

      ```cpp
      // C++中定义命名空间的基本格式如下：
      namespace wd
      {
      int val1 = 0;
      char val2;
      }// end of namespace wd
      ```

2. **命名空间的使用方式**

   - **作用域限定符**

      每次要使用某个命名空间中的实体时，都直接加上<span style=color:red;background:yellow>**作用域限定符: :**</span>

      ```CPP
      namespace wd
      {
      int number = 10;
      void display()
      {
      	//cout,endl都是std空间中的实体，所以都加上'std::'命名空间
      	std::cout << "wd::display()" << std::endl;
      }
      }//end of namespace wd
      
      void test0()
      {
      	std::cout << "wd::number = " << wd::number << endl;
      	wd::display();
      }
      ```


   - **using编译指令**

      ```cpp
      #include <iostream>
      using namespace std; //using编译指令
      
      int main(int argc, char * argv[]){
       cout << "hello,world" << endl;
       return 0;
      }
      ```

      ==using声明与using编译指令的区别==

      - **using 声明（using 声明机制）**：**只把某个名字引进来**（精准导入）
      - **using 编译指令（using 指令）**：**把整个命名空间的所有名字都引进来**（批量导入）


   - **using声明机制**

      ```cpp
      #include <iostream>
      using std::cout; // using声明
      using std::endl; // using声明
      
      int number = 100;
      
      namespace wd
      {
      int number = 10;
      void display()
      {
      	cout << "wd::display()" << endl;
      }
      }//end of namespace wd
      
      
      int main(void)
      {
      	using wd::number; // using声明
      	using wd::display; // **只写函数名** using声明
      	cout << "wd::number = " << number << endl;   //ok，访问到wd::number，全局位置实体int number被屏蔽，！！！但是不能写using namespace wd会报错
      	display();
      	return 0;
      }
      ```

3. **using编译指令与using声明机制的注意事项**

   (1)using编译指令尽量写在局部作用域

   (2)采用using编译指令使用命名空间中的实体时，要注意避免命名空间中实体与全局位置实体同名。

   (3)在不清楚命名空间中实体的具体情况时，尽量不使用using编译指令

   (4)在同一作用域内用using声明机制, 不同的命名空间的实体，不能是同名的，否则会发生冲突。

   - **using编译指令尽量写在局部作用域——建议：将using编译指令写在局部作用域**

      ```cpp
      namespace cpp{
      int number = 100;
      }//end of namespace cpp
      
      namespace wd
      {
      int number = 10;
      void display()
      {
      	cout << "wd::display()" << endl;
      }；
      }//end of namespace wd
      
      using namespace wd; // wd中存在实体int number
      void test0()
      {
      	cout << number << endl; 
      }
      
      using namespace cpp; // cpp中也存在实体int number
      void test1()
      {
      	cout << number << endl; // error，有冲突
      }
      ```

   - **⭐采用using==编译指令==使用命名空间中的实体时，==要注意避免命名空间中实体与全局位置实体同名==**

      | 写法                  | 本质                           | 对同名外层变量             | 结果           |
      | :-------------------- | :----------------------------- | :------------------------- | :------------- |
      | `using wd::number;`   | 在当前作用域**声明引入**       | **隐藏**外层同名变量       | 无冲突，能编译 |
      | `using namespace wd;` | 将整个命名空间**作为备选范围** | **不会隐藏**，导致两个候选 | 歧义，编译报错 |

      ```cpp
      int number = 100; // 全局变量int number
      
      namespace wd
      {
      int number = 10;
      void display()
      {
      	cout << "wd::display()" << endl;
      }
      }//end of namespace wd
      
      
      void test0()
      {
      	using wd::number;
        	/* 报错：using namespace wd; // wd中存在于全局位置实体同名的实体int number */
      	cout << number << endl; // error,有冲突
      }
      ```

   - **在不清楚命名空间中实体的具体情况时，尽量不使用using编译指令**

      ```cpp
      #include <iostream>
      using namespace std;
      
      double cout() // 不知道std中有cout这个实体，又去定义了一个cout函数
      {
      	return 1.1;
      }
      
      int main(void)
      {
      	cout();
      	return 0;
      }
      ```

   - **在同一作用域内用using声明机制, 不同的命名空间的实体，不能是同名的，否则会发生冲突——using声明机制的特点是：需要哪个实体的时候就引入到程序中，不需要的实体就不引入，尽可能减小犯错误的概率**

      ```cpp
      namespace wd
      {
      int number = 10;
      void display()
      {
      	cout << "wd::display()" << endl;
      }
      }//end of namespace wd
      
      namespace wd2
      {
      void display()
      {
      	cout << "wd2::display()" << endl;
      }
      }//end of namespace wd2
      
      void test0(){
      	using wd::display; // 声明了实体dispaly
      	using wd2::display; // 也声明了实体dispaly
      	display(); //冲突
      	wd::display();
      	wd2::display();
      }
      ```

4. **命名空间的嵌套使用**

   ```CPP
   namespace wd
   {
   int num = 100;
   
   void func() {
       cout << "func" << endl;
   }
   
   namespace cpp
   {
   int num = 200;
   
   void func() {
       cout << "cpp::func" << endl;
   }
   }//end of namespace cpp
   
   }//end of namespace wd
   
   //方式一：使用作用域限定符精确访问实体
   void test0() {
       cout << wd::cpp::num << endl;
       wd::cpp::func();
   }
   
   //方式二：using编译指令一次性引入cpp的实体
   void test1() {
       using namespace wd::cpp;
       cout << num << endl;
       func();
   }
   
   //方式三：using声明语句，引入部分cpp中的实体
   void test2() {
       using wd::cpp::num;
       using wd::cpp::func;
       cout << num << endl;
       func();
   }
   ```

5. **不定义名字的命名空间称为匿名命名空间（简称匿名空间）**，如果我们希望一部分实体只在本文件中起作用，那么可以将它们定义在匿名空间中

   ```CPP
   namespace {
   int val = 10;
   void func(){
   cout << "func()" << endl;
   }
   } // end of anonymous namespace
   
   // 以下用法均ok
   void test0(){
   cout << val << endl;
   cout << ::val << endl;
   func();
   ::func();
   }
   ```

   **注意：**如果匿名空间中定义了和全局位置中同名的实体，会有冲突，**即使使用作用域限定符: :，也无法访问到匿名空间中重名的实体，==只能访问到全局的实体==**

   ```CPP
   int val = 100;
   void func(){
       cout << "g_func()" << endl;
   }
   
   namespace {
   int val = 10;
   void func(){
       cout << "func()" << endl;
   }
   } // end of anonymous namespace
   
   void test0(){
       cout << val << endl; // 冲突
       cout << ::val << endl; // 全局的val
       func(); // 冲突
       ::func(); // 全局的func
   }
   ```

   **注意事项：**

   1. 匿名空间不要定义与全局空间中同名的实体

   1. 匿名空间中的实体不能跨模块调用

6. **跨模块调用**

   **一个.c / .cc / .cpp的文件可以称为一个模块**

   - `全局变量和函数`是可以跨模块调用的

     ```cpp
     //externA.cc
     int num = 100;
     
     void print(){
     cout << "print()" << endl;
     }
     // ------------------------
     //externB.cc
     extern int num;//外部引入声明
     extern void print();
     void test0(){
     cout << num << endl;
     print();
     }
     ```


   - `有名命名空间中的实体`可以跨模块调用

     ```cpp
     //externA.cc
     namespace wd
     {
     int val = 300;
     void display(){
     cout << "wd::display()" << endl;
     }
     }//end of namespace wd
     // -----------------------------
     //externB.cc
     // 定义与要引入模块的同名命名空间
     namespace wd
     {
     // 通过extern引入
     extern int val;
     extern void display();
     }
     
     void test0(){
     // 访问实体
     cout << wd::val << endl;
     wd::display();
     }
     ```
     
     **易错点：如果在externA.cc中有同名的命名空间实体与全局实体，并且同时在externB.cc中做外部引入,直接访问的是全局实体, 通过: :访问的是命名空间中实体**
     
     **使用规则：==如果需要跨模块调用命名空间中的实体，要尽量避免它们与全局位置的实体重名，在使用时尽量采取作用域限定的方式==**
     
     ```CPP
     // externA.cc
     #include "3.externA.hpp"
     #include <iostream>
     using namespace std;
     
     // 全局变量 & 函数定义
     int val = 100;
     void display() {
         cout << "全局 display()" << endl;
     }
     
     // 命名空间 wd 定义
     namespace wd
     {
         int val = 300;
         void display() {
             cout << "wd::display()" << endl;
         }
     }
     ```
     
     ```CPP
     // externB.cc
     #include "3.externA.hpp"   // 必须包含头文件！
     #include <iostream>
     using namespace std;
     
     // 全局变量、函数声明
     extern int val;
     void display();
     
     // 命名空间声明
     namespace wd
     {
         extern int val;
         void display();
     }
     // test0：直接访问 → 全局
     void test0() {
         cout << "test0:" << val << endl;
         display();
     }
     
     // test1：加命名空间限定 → wd 里的实体
     void test1() {
         cout << "\ntest1:" << wd::val << endl;
         wd::display();
     }
     
     // test2：using namespace 会冲突（编译报错）
     void test2() {
         using namespace wd;
         // cout << val << endl;  // 报错：二义性
         // display();            // 报错：二义性
     }
     
     // test4：局部 using 声明 → 屏蔽全局，使用 wd
     void test4() {
         using wd::val;
         using wd::display;
         /* 报错： using namespace wd; */
     
         cout  << "\ntest4:" << val << endl;   // 300
         display();             // wd::display()
     }
     
     int main() {
         test0();
         test1();
         /* test2(); */
         test4();
         return 0;
     }
     ```


## 二、==引用&==

1. **引用的本质**

   **C++中的引用本质上是一种被限制的指针**。类似于线性表和栈的关系，栈是被限制的线性表，底层实现相同，只不过逻辑上的用法不同而已

   由于<font color=red>**引用是被限制的指针**</font>，所以**引用是占据内存的**，占据的大小就是一个指针的大小。有很多的说法，都说引用不会占据存储空间，其只是一个变量的别名，但这种说法并不准确。引用变量会占据存储空间，存放的是一个地址，但是编译器阻止对它本身的任何访问，从一而终总是指向初始的目标单元。在**汇编里，引用的本质就是“间接寻址”**

   可以尝试**对引用取址**，发现获取到的地址**就是引用所绑定变量的地址**

2. **引用和指针的联系与区别**

   这是一道非常经典的面试题，请尝试着回答一下：

   **联系：**

   1. 引用和指针都有地址的概念，都是用来间接访问变量；

   1. 引用的底层还是指针来完成，可以把引用视为一个受限制的指针。（const pointer）


   **区别：**

      - 引用必须初始化，指针可以不初始化；
      - 引用不能修改绑定，但是指针可以修改指向；
      - 在代码层面对引用本身取址取到的是变量本体的地址，但是对指针取址取到的是指针变量的地址

3. **常引用:使用const修饰的引用**

   如果不希望函数体中通过引用改变传入的变量，那么可以使用<span style=color:red;background:yellow>**常引用作为函数参数**</span>

   - 不会修改值
   - ==不会复制（不会造成不必要的开销）==

   **注: Google编程规范中要求对于引用作为函数参数,必须使用const**

   ```cpp
   // 常引用基本特点
   void test1(){
       int num = 10;
       // 定义引用绑定num 并使用const修饰
       const int & ref = 10;
       // 既不能修改指向,也不能通过这个引用修改变量的值
       // ref = 100; // error read only
       num = 100;
       cout << "num = " << num << endl;
       cout << "ref = " << ref << endl;
       // 不能通过引用常引用修改 但是可以通过变量自身修改
   }
   
   // 函数不希望通过引用改变变量的值的时候可以使用常引用
   // 形参为常引用 
   void func(const int & x){
       cout << x << endl;
      //  x = 100; //error read only  无法通过常引用修改
   }
   
   void test(){
       int num = 1;
       func(num);
       cout << num << endl;
   }
   ```

4. **引用在函数返回值场景的应用**

   **要求：**当以引用作为函数的返回值时，<span style=color:red;background:yellow>**返回的变量其生命周期一定是要大于函数的生命周期**</span>的，即当函数执行完毕时，返回的变量还存在

   **目的：** ==避免复制==，节省开销；**特点：不复制、函数内部可以直接修改外部变量、语法上和普通变量一样，不用解引用**

   ```cpp
   int a = 1;
   // 返回值为int类型
   int  func(){
       //...
       return a;   //在函数内部，当执行return语句时，会发生复制 
   }   
   
   // 返回值为int类型的引用
   int & func2(){
        //...
       return b;   //在函数内部，当执行return语句时，不会发生复制
   }  
   ```

   ```cpp
   // 全局变量
   int a  = 100;
   int func(){
       // func函数返回的是a的一个副本,一个临时变量
       return a;
   }
   
   // 全局变量
   int b = 200;
   // 函数返回值为引用
   int & func2(){
       // return时不会发生复制
       return b; // 返回的实际是一个绑定到b的引用  
       // 要注意返回的引用所绑定的变量的生命周期要比函数更长
   }
   
   void test(){
       cout << func() << endl;
       cout << &a << endl;
       // cout << &func() << endl;// error 
       // func()返回的是一个临时变量值,不允许对一个临时变量取地址,一个临时值没有地址返回给调用者
       
       cout << func2() << endl;
       cout << &func2() << endl; // OK func2 返回的是引用不是值.
   }
   ```

5. **为什么 `int& ref = a;` 可以？为什么 `int& ref = test();`（返回 int 时）不可以？**
   因为 `a` 是一个**有名字的变量，可以取地址**；返回类型是 `int`，编译器会生成一个**临时的 `int` 值**（拷贝了 `a` 的内容）。这个临时值没有名字、不可取地址，是一个右值

   > | 类型              | 简单理解                                 | 关键特征                                           |
   > | :---------------- | :--------------------------------------- | :------------------------------------------------- |
   > | **左值 (lvalue)** | 有名字、能取地址、持续存在的**对象**     | 可以出现在等号左边（但不是绝对）                   |
   > | **右值 (rvalue)** | 没有名字、不能取地址、用完即弃的**数据** | 通常出现在等号右边，是临时值、字面量或计算中间结果 |

   函数按值返回时，**它给出的不是原来的那个变量，而是一个立刻生成的、临时的、没有名字的副本**

6. **注意事项**

   - **不要返回局部变量的引用**。因为局部变量会在函数返回后被销毁，被返回的引用就成为了"无所指"的引用，程序会进入未知状态

   - <span style=color:red;background:yellow>**不要轻易**</span>返回一个堆空间变量的引用，非常容易造成内存泄漏

     如果函数返回的是一个堆空间变量的引用，那么这个函数调用一次就会new一次，非常容易造成内存泄露，所以谨慎使用这种写法，并且要有完善的回收机制

     ```cpp
     int & func3(){
         int *p = new int{10};
         return *p;
     }
     
     void test(){
         // func3调用1次就会new一次, 如果不释放就会内存泄漏
         // cout << func3() << endl;
         // delete &func3();
         // 调用2次func3,释放一次,仍然泄露
         
         // 完善写法,使用**引用接收**之后再处理
         int &ref = func3();
         cout << ref << endl;
         // delete
         delete &ref; 
     }
     ```

## 三、强制转换

C++引进了4个新的类型转换操作符:

- **static_cast** 

  ```cpp
  目标类型 转换后的变量 = static_cast<目标类型>(要转换的变量)
  ```

  最常用的类型转换符，在正常状况下的类型转换, 用于将一种数据类型转换成另一种数据类型，如把int转换为float

  1. 用于基本数据类型之间的转换

     ```cpp
     int iNumber = 100；
     float fNumber = 0；
     fNumber = static_cast<float>(iNumber);
     ```

  2. ==把void指针==转换成目标类型的指针，但不安全(可能因为指向的实际数据类型和期望类型不一致导致未定义行为,编译器不会检查)

     ```cpp
     void * pVoid = malloc(sizeof(int));
     // void * ---> int *
     int * pInt = static_cast<int*>(pVoid);
     *pInt = 1;
     ```

     注意: <span style=color:red;background:yellow>**不能完成任意两个指针类型间的转换**</span>

     ```cpp
     int iNumber = 1;
     int * pInt = &iNumber;
     float * pFloat = static_cast<float *>(pInt);//error
     ```

  3. 用于类层次结构中基类和子类之间指针或引用的转换（后面学）

- const_cast

- dynamic_cast

- reinterpret_cast(了解)

## 四、函数重载

1. **什么是函数重载**

   <font color=red>**在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。**</font>重载函数通常**用来命名一组功能相似的函数**，**使得同一函数名可以作用于不同的数据类型或者参数组合,**适用于处理相似功能,但是输入类型不同的情况,这样做**减少了函数名的数量**，对于程序的可读性有很大的好处

2. **实现函数重载的条件**

   **函数名相同, 参数列表不同可以构成重载。**

   1. 函数参数的数量
   2. 数量相同,类型不同
   3. 数量,类型都相同,参数的顺序不同

   **注意:** 只有返回类型不同，**参数完全相同，是不能构成重载的**，若是返回类型与参数都完全相同，那也是如下的非法重复定义，属于编译错误

   ```cpp
   // 编译错误
   int add(int x, int y) {
       return x + y;
   }
   // 只有返回值类型不同, 不能构成重载
   void add(int x, int y) {
      cout << x + y << endl;
   }// 不是重载
   ```

3. **函数重载的实现原理**

   **名字改编(name mangling)**——当函数名称相同时 ，编译器会根据参数的类型、顺序、个数进行改编

   - g++ -c Overload.cc

   - nm Overload.o

   ![image-20241014164716694](../0.TyporaPicture\image-20241014164716694.png)

4. **extern "C"**

```cpp
extern "C" void func() //用 extern"C"修饰单个函数
{

}

//如果是多个函数都希望用C的方式编译
//或是需要使用C语言的库文件
//都可以放到如下{}中
extern "C"
{
//……
}


```

## 五、函数默认参数

1. 在C++中，**函数默认参数**是指在定义函数时为一个或多个参数提供的**默认值**，当调用函数时如果没有为这些参数传递具体的值，则使用默认值，**目的是：**

   - 函数调用时进行缺省调用
   - 减少函数重载

2. **函数提供默认参数可以进行缺省调用**

   给函数参数赋默认值后就可以进行缺省调用，但是<span style=color:red;background:yellow>**传入的参数优先级高于默认参数。**</span>

   ```cpp
   void func(int x = 0, int y = 0){
       cout << "x = " << x << endl;
   	cout << "y = " << y << endl;
   }
   
   void test0(){
       // 如果传参,实际参数就是传递的参数, 如果不传,那么参数就是默认参数
       func(24,30);
       func(100);
       func();
   }
   ```

3. **减少函数重载**

   默认参数可将一系列简单的重载函数合成为一个，例如：

   ```cpp
   void func3();
   void func3(int x);
   void func3(int x, int y);
   //上面3个函数其实是函数重载 
   //上面三个函数可以合成下面这一个带默认参数的函数 
   void func3(int x = 0, int y = 0);
   ```

   **注意:**如果一组重载函数（可能带有默认参数）都允许相同实参个数的调用，将会引起调用的二义性

   ```cpp
   void func4(int x);
   void func4(int x, int y = 0);
   
   func4(1);//error,编译器无法确定调用的是哪种形式的func4 
   ```

   <span style=color:red;background:yellow>**所以在函数重载时，要谨慎使用默认参数。**</span>重载是允许的，**但是缺省调用时**会产生冲突。**应避免在同一个范围内定义带有默认参数的重载函数**，否则编译器可能会因为无法确定合适的调用而报错

4. **默认参数的声明**

   **一般默认参数是在函数声明中提供，**若在定义时而不是在声明时设置默认值，那么函数定义一定要在函数的调用之前 

5. **默认参数的顺序规定**

   如果一个函数中有**多个默认参数**，则形参分布中，**默认参数应从右至左逐渐定义**

   因为当调用函数时，只能从左向右匹配参数，如：

   ```cpp
   void func2(int a = 1, int b, int c = 0, int d);//error
   void func2(int a, int b, int c = 0, int d = 0);//ok
   ```

   若给**某一参数设置了默认值**，那么在参数表中**其后所有的参数都必须也设置默认值**，否则，由于函数调用时可不列出已设置默认值的参数，编译器无法判断在调用时是否有参数遗漏

   完成函数默认参数的设置后，该函数就可以按照相应的缺省形式进行调用，<span style=color:red;background:yellow>**即函数参数赋默认值从右向左（严格）,保证在缺省调用时完成准确的匹配**</span>

## 六、内联(inline)函数

1. **什么是内联函数**

   - 定义函数时，在函数的最前面以关键字“inline”声明函数，该函数即可称为内联函数（内联声明函数），这个行为是对编译器提出了内联的**建议(并不是强制性的，可能会失效)**，如果建议通过即有效，就会在编译时进行内联展开
   - 当内联函数收到编译器的指示时，即可发生**内联**：编译器将使用函数的定义体来**替代**函数调用语句，**这种替代行为发生在编译阶段而非程序运行阶段**
   - 函数体内容如果太长或者有循环之类的结构，不建议inline，以免造成代码膨胀；**比较短小并且比较常用的代码适合用inline，**比如函数体中有循环结构，那么执行函数体的开销比调用函数的开销大得多，设为内联函数只能减少函数调用的开销，没有太大意义

2. **宏 VS 内联函数**

   | 特性               | 内联函数 (`inline`)                  | 宏 (`#define`)                     |
   | ------------------ | ------------------------------------ | ---------------------------------- |
   | 类型安全           | 提供类型安全，编译器进行类型检查     | 没有类型检查，可能产生不匹配的错误 |
   | 编译期替换         | **编译器决定是否内联（有优化机制）** | 预处理器简单文本替换               |
   | 代码可读性和调试性 | 支持断点调试，可读性和普通函数相似   | 调试困难，无法跟踪宏的展开过程     |
   | 副作用             | 参数只求值一次，不会有多次求值副作用 | 参数会多次求值，可能导致副作用     |
   | 代码膨胀           | 函数被多次内联可能导致代码膨胀       | 频繁替换也会导致代码膨胀           |
   | 灵活性             | **适用于明确类型的函数**             | 可以处理不同类型的参数             |
   | 性能               | **小型函数可以避免函数调用开销**     | 无函数调用开销                     |

3. **适用场景**

   - **内联函数**适用于需要提高性能的小型、频繁调用的函数，特别是需要进行类型检查和避免副作用的场景。对于需要安全性和封装性的代码段，应优先使用内联函数
   - **宏**适用于简单的文本替换、条件编译、或者需要通用计算而不考虑类型的情况下。然而，应该尽量避免使用宏函数来实现复杂的逻辑

   总体而言，**内联函数**比宏更安全、更易读、更易于调试；在现代C++开发中，宏更多用于**常量定义**和**条件编译**，而逻辑操作和计算应尽量使用**内联函数**以确保代码的健壮性和可维护性

4. **注意事项**

   1. 调用一个函数时，是采取内联函数的方式还是普通函数的方式，<font color=red>**取决于该函数的实现**</font>

      ```cpp
      // 两种写法都会按照内联函数的方式展开
      inline int add1(int x ,int y);
      
      inline int add1(int x ,int y){
          return x + y;
      }
      // ----------------------------
      int add2(int x ,int y);
      
      inline int add2(int x ,int y){
          return x + y;
      }
      ```

   2. <font color=red>**如果要把inline函数声明在头文件中，则必须把函数定义也写在头文件中。**</font>若头文件中只有声明没有实现，被认为是没有定义替换规则，<font color=red>**即inline函数在头文件必须有定义**</font>

   3. **递归函数**不适合、也不能真正被内联，主流编译器（GCC/Clang/MSVC）都会**忽略 inline 请求，当作普通递归函数处理**

      ==原因：==**编译期无法确定递归深度、会==无限展开==、破坏递归栈帧**。

      **不适合：**

      - 递归函数
      - 大函数、带循环 /switch 的函数
      - 虚函数（多态时）

## 七、补充

1. **const关键字**

   const修饰的变量称为const常量，之后不能修改其值(本质还是变量，使用时也是当成变量使用，只是被赋予只读属性)

   整型、浮点型数据都可以修饰，它们被称为const常量，<span style=color:red;background:yellow>**const常量在定义时必须初始化。**</span>

   ```cpp
   const int number1 = 10;
   int const number2 = 20;
   
   const int val;//error 常量必须要进行初始化
   // -------------------------------------
   int b = 20;
   const int a = b; // 变量也可赋值给const常量
   b = 10;
   cout << "a = " << a << endl;
   cout << "b = " << b << endl;
   return 0;
   ```

2. <span style=color:red;background:yellow>**const常量和宏定义常量的区别(面试常考)**</span>

   1. <font color=red>**发生的时机不同**</font>：

      C语言中的宏定义发生时机在**预处理时**，做字符串的替换；

      const常量是在**编译时**（const常量本质还是一个变量，只是用const关键字限定之后，赋予只读属性，使用时依然是以变量的形式去使用）

   2. <font color=red>**类型和安全检查不同**</font>：

      宏定义没有类型，**不做任何类型检查**；

      **const常量有具体的类型**，在**编译期会执行类型检查**；在使用中，应尽量以const替换宏定义常量，可以减小犯错误的概率

3. **指向常量的指针**和**常量指针**

   1. 指向常量的指针：pointer to const 
      - const int *p **或** int const *p
      - const在*左边，即为指向常量的指针，不能通过指针改变其指向的值，但是可以改变这个指针的指向
   2. 常量指针：const pointer
      - int * const p
      - const在*右边，即为常量指针，不能改变这个指针的指向，但是可以通过指针改变其指向的值

4. **数组指针**和**指针数组**

   1. **数组指针**
      - 指向数组的指针 pointer to array , 本质是指针, 指向数组首地址的指针
      - int (*p)[3]
   2. **指针数组**
      - 元素都是指针类型的数组 array of pointers , 本质是数组,其元素是指针
      - int *p[3]

5. **函数指针**和**指针函数**

   1. **函数指针**
      - 指向函数的指针 pointer to function ,本质是指针
      - 可以通过函数指针调用函数 
      - 定义方式: return_type (*pointer_name)(parameter_list)
   2. **指针函数**
      - 返回值为指针类型的函数 function return a pointer , 本质为函数
      - 定义方式 return_type* function_name(parameter_list) { }

6. **==new/delete==与==malloc/free==的区别(面试常考)**=

   1. malloc/free是库函数
      new/delete是运算符，后两者使用时不是函数的写法
   2. malloc返回值是void*
      new表达式的返回值是相应类型的指针
   3. malloc申请的空间不会进行初始化，获取到的空间是有脏数据的
      但new表达式申请空间时可以直接初始化
   4. malloc的参数是字节数
      new表达式不需要传递字节数，会根据相应类型自动获取空间大小

7. **程序模拟**

   **27(√)，81(×)**

   ```cpp
   int foo(int x,int y)
   {
   if(x <= 0 ||y <= 0)
   return 1;
   return 3 * foo(x-1, y/2);
   }
   
   cout << foo(3,5) << endl;
   ```# Day03_类与对象

## 一、异常处理

1. **异常**是程序在执行期间产生的问题，比如尝试除以零的操作

   **异常处理**是用于处理运行时错误的机制，允许开发者在程序中检测错误并采取相应的补救措施，从而使程序能够**优雅地处理**错误并继续运行C++

2. C++ 异常处理涉及到三个关键字：try、catch、throw

   ```cpp
   throw 表达式;
   
   try {
   //语句块
   } catch(异常类型) {
   //具体的异常处理...
   } ...
   catch(异常类型) {
   //具体的异常处理...
   }
   ```

   1. 先定义抛出异常的规则（throw）,异常是一个表达式，它的值可以是基本类型，也可以是类类型

   2. try-catch语句块的catch可以有多个，至少要有一个，否则会报错

      - 执行 try 块中的语句，如果执行的过程中没有异常拋出，那么执行完后就执行最后一个 catch块后面的语句，所有 catch 块中的语句都不会被执行
      - 如果 try 块执行的过程中拋出了异常，那么拋出异常后立即跳转到第一个“异常类型”和拋出的异常类型匹配的 catch 块中执行（称作异常被该 catch 块“捕获”），执行完后再跳转到最后一个catch 块后面继续执行

      注意：<font color=red>**catch的是类型，不是具体信息**</font>

      ```cpp
      double division(double x,double y){
          if(y == 0){
              throw "Deivision by zero";
          }
          return x/y;
      }
      
      void test0(){
          double x = 100, y = 0;
          try{
              cout << "before" << endl;
              cout << division(x,y) << endl;//异常行后的代码不会执行
              cout << "after" << endl;
          }catch(const char * msg){ //catch的小括号里是类型
          	cout << "hello" << endl;
              cout << "hello," << msg << endl;
          }catch(double x){
              cout << "double" << endl;
          }catch(int x){
              cout << "int" << endl;
          }
          cout << "end test" << endl;
      }
      
      ```

## ==二、内存布局==

1. 栈区：操作系统控制，由高地址向低地址生长，编译器做了优化，显示地址时栈区和其他区域保持一致的方向

2. 堆区：程序员分配，由低地址向高地址生长，堆区与栈区没有明确的界限

3. 全局/静态区：读写段（数据段），存放全局变量、静态变量

4. 文字常量区：只读段，存放程序中直接使用的常量，如const char * p = "hello";  hello这个内容就存在文字常量区

5. 程序代码区：只读段，存放函数体的二进制代码

   ![image-20241015175642417](..\0.TyporaPicture\image-20241015175642417.png)

6. **注意：**

   - 因为编译器的优化, 局部变量的地址分配通常是：
     ==虽然 **栈是从高地址向低地址生长的**（即每次函数调用时，栈指针减小），但在一个函数的**同一个栈帧内部**，多个局部变量的分配顺序是完全由编译器决定的。==
     - 后创建的变量分配高地址
     - 先创建的变量分配低地址

   - C++ 的 cout 没有专门处理 “函数指针” 的 operator<< 重载，于是把它隐式转成 bool，非空就是 true，输出为 1，如果**想打印出函数指针**的内容即指向的地址，则**需要使用C中的printf(“%p”, f);**

## 三、面向对象思想

1. **过程论**

   数据和逻辑是分离的、独立的，程序世界本质是过程，数据作为过程处理对象，逻辑作为过程的形式定义，世界就是各个过程不断进行的总体

2. **对象论**

   数据和逻辑不是分离的，而是相互依存的。相关的数据和逻辑形成个体，这些个体叫做对象，世界就是由一个个对象组成的

   **对象论更有助于分析规模较大的事物**

## 四、类

1. C++用**类**来描述对象，类是对现实世界中相似事物的抽象，比如同是“双轮车”的摩托车和自行车，有共同点，也有许多不同点。“车”类是对摩托车、自行车、汽车等相同点的提取与抽象。

   类的定义分为两个部分：

   - 数据，相当于现实世界中的属性，称为<font color=red>**成员变量**</font>

   - 对数据的操作，相当于现实世界中的行为，称为<font color=red>**成员函数**</font>

   从程序设计的观点来说，**类就是数据类型**，是用户定义的数据类型，对象可以看成某个类的实例（某类的变量），所以说**类是对象的抽象，对象是类的实例**

   <span style=color:red;background:yellow>**由对象抽象出类，由类实例化出对象**</span>

   C++中用关键字class来定义一个类，其基本形式如下：类的定义和声明

   ```cpp
   // 类名采用大驼峰命名
   class MyClass{//类的定义
       //……
       void myFunc(){}  //成员函数 采用小驼峰命名
       int m_a;          //数据成员
   };//一定要有分号
   
   
   //类也可以先声明，后完成定义
   class MyClass2;//类的声明
   
   class MyClass2{//类的定义
       //……
   };//分号不能省略
   ```

2. **访问修饰符**

   1. <span style=color:red;background:yellow>**public：**</span> 公有的访问权限，在类外可以通过对象直接访问公有成员

   2. <span style=color:red;background:yellow>**protected：**</span>保护的访问权限，在本类中和派生类中可以访问，在类外不能通过对象直接访问（后面学）

   3. <span style=color:red;background:yellow>**private：**</span>私有的访问权限，在本类之外不能访问，比较敏感的数据设为private，类定义中可以访问

      ![image-20241212155514035](..\0.TyporaPicture\image-20241212155514035.png)

      **注意：**

      - 类定义中访问修饰符的管理范围从当前行到下一个访问修饰符或类定义结束

      - class定义中如果在成员定义（或声明）之前没有任何访问修饰符，其<font color=red>**默认的访问权限为私有private**</font>

      - **public的成员函数**也可以称为**接口**，就是该类提供给外界使用的路径，在类外可以直接通过对象进行访问

        ```cpp
        class Computer {
        public:
        	void setBrand(const char * brand)
        	{
        		strcpy(m_brand, brand);
        	}
        	void setPrice(float price)
        	{
        		m_price = price;
        	}
        private:
        	char m_brand[20];
        	float m_price;
        }；
        
        int main(void){
            Computer pc;
            pc.setPrice(10000); //ok
            pc.m_price; //error,因为_price是私有的
        }
        
        ```

3. **struct 与 class的对比**

   - C中的struct只能是一些变量的集合体，可以封装数据但不能隐藏数据，而且成员不能是函数

   - C++中的struct对C中的struct做了拓展，可以定义函数，基本等同于class，默认访问权限是public

   - class默认访问权限是private

4. **成员函数的定义**

   1. **成员函数定义的三种形式**

      - 成员函数**定义在类内部**

        默认情况下是**内联函数**

        ```cpp
        class Computer {
        public:
        	void setBrand(const char * brand)
        	{
        		strcpy(m_brand, brand);
        	}
        	void setPrice(float price)
        	{
        		m_price = price;
        	}
        private:
        	char m_brand[20];
        	float m_price;
        }；
        ```

      - 成员函数在**类内部只进行声明**，在**类外部完成定义**

        类外定义的成员函数默认不是内联函数，除非使用 inline 来显式声明它为内联函数

        ```cpp
        class Computer {
        public:
        	//成员函数
        	void setBrand(const char * brand)；//设置品牌
        
        	void setPrice(float price)；//设置价格
                
            void print();//打印信息
        private:
        	//数据成员
        	char m_brand[20];
        	float m_price;
        };
        
        // 定义成员函数的时候结合作用域限定符一起使用 
        void Computer::setBrand(const char * brand)
        { 
            strcpy(m_brand, brand); 
        }
        void Computer::setPrice(float price)
        { 
            m_price = price;
        }
        ```

      - 成员函数在类中**声明使用头文件(.hpp)**，成员函数的**定义使用实现文件(.cc)**

        在头文件中定义一个函数时，如果多个源文件都包含了该头文件，那么在联合编译时会出现重定义错误

        ```cpp
        // 头文件 computer.h
        #ifndef __COMPUTER_H__
        #define __COMPUTER_H__
        class Computer{
        private:
            char m_brand[20];
            int m_price;
        public:
            // 在类中声明成员函数
            void setBrand(const char * brand);
            void setPrice(int price);
            void printInfo();
        };
        // -----------------
        
        // 实现文件computer.cc
        #include "computer.h"
        #include <iostream>
        #include <cstring>
        using std::cout;
        using std::endl;
        void Computer::setBrand(const char* brand){
            strcpy(m_brand, brand);
        }
        
        void Computer::setPrice(int price){
            m_price = price;
        }
        
        void Computer::printInfo(){
            cout << "computer info: brand: " << m_brand
                << ", price: " << m_price << endl;
        }
        // ---------------------------------
        
        // 测试文件 testComputer.cc
        #include "computer.h"
        #include <iostream>fs
        #include <cstring>
        
        int main(int argc, char *argv[])
        {
            Computer com;
            com.setBrand("Lenovo");
            com.setPrice(3999);
            com.printInfo();
            return 0;
        }
        ```

## 五、对象
# Day04_对象的创建与销毁

## 一、对象的创建

通过自定义的公共成员函数 setBrand 和 setPrice 实现了对数据成员的初始化（严格意义上是**赋值**）

C++ 为类提供了一种<span style=color:red;background:yellow>**特殊的成员函数——构造函数**</span>来完成真正的**初始化**

1. **构造函数**

   - 形式

     ```
     类名(形参列表) {
     	
     }
     ```

   - 作用：初始化数据成员

   - 注意

     - **没有返回值**，即使是void也不能有； 
     - **函数名与类名相同**，再加上函数参数列表。
     - 构造函数在对象创建时<font color=red>**自动调用**</font>，用以完成对象成员变量等的初始化及其他操作(如为指针成员动态申请内存等)

2. **对象的创建规则**

   - 类中没有显式定义构造函数时，编译器会**自动生成**一个**默认  (无参)  构造函数** ，但不会初始化数据成员

     当Point pt; 创建对象后，其数据成员没有被初始化，输出的会是不确定的值

   - 类中显式提供了构造函数时 ，编译器就**不会再自动生成**默认的**无参**构造函数

   - 构造函数可以重载，以提升代码的灵活性（可以用多种不同的数据来创建出同一类的对象）

     ```cpp
     class Point {
     public:
         // 无参构造
         Point() {
             cout << "Point()" << endl;
         }
     	// 两参构造
         Point(int x, int y) {
             cout << "Point(x,y)" << endl;
             m_x = x;
             m_y = y;
         }
         // 一参构造
         Point(int x) {
             cout << "Point(x)" << endl;
             m_x = x;
         }
         void print() {
             cout << "(x,y) = " << "("
                 <<m_x << "," << m_y << ")"
                 << endl;
         }
     private:
         int m_x;
         int m_y;
     };
     
     void test() {
         Point p;// 调用无参构造
         p.print();
         
         Point p2(1,2);// 调用两参构造
         p2.print();
         
         Point p3(10);// 调用一参构造
         p3.print();
     }
     ```

   - 如果在显示提供了构造函数时还希望通过无参构造函数创建对象，则必须要手动提供一个无参构造函数

3. **对象的数据成员初始化**

   在构造函数的函数体中对数据成员进行赋值，其实严格意义上**不算初始化**（而算是**赋值**）

   在C++中，对于类中数据成员的初始化，**推荐**使用<span style=color:red;background:yellow>**初始化列表**</span>完成

   ```cpp
   class Point {
   public:
   	//...
   	Point(int x = 0, int y = 0)
   	: m_x(ix)
       , m_y(iy)
   	{
   		cout << "Point(int,int)" << endl;
   	}
   	//...
   };
   ```

   **细节注意：**

   - 如果没有在构造函数的初始化列表中显式地初始化成员**(即构造函数中不存在初始化列表 ==或== 某个具体的成员变量没有被写在初始化列表里)**，则该成员将在构造函数体之前执行默认初始化

   - 数据成员的初始化并不取决于其在初始化列表中的顺序，而是取决于声明时的顺序（与声明顺序一致）

     ```cpp
     // 正例：列表顺序与声明顺序一致（推荐做法）
     class Point {
         int m_x;   // 声明顺序：m_x 先，m_y 后
         int m_y;
     public:
         Point(int x, int y) : m_x(x), m_y(y) {}   // 列表顺序也是 m_x, m_y，清晰安全
     };
     ```

     ```cpp
     // 反例：列表顺序与声明顺序相反（危险陷阱）
     class Bad {
         int a;   // 声明顺序：a 先
         int b;   //            b 后
     public:
         // 初始化列表写成了 b, a，但实际初始化顺序还是 a, b
         Bad(int val) : b(val), a(b + 1) { }
         // 意图：先用 val 初始化 b，再用 b+1 初始化 a
         // 实际：先初始化 a，但此时 b 尚未初始化，a = 未定义的b + 1 → 未定义行为！
     };
     ```

     ```cpp
     // 其他例子：没有依赖问题，所以不会出错
     class Example {
         int x;
         int y;
         int z;
     public:
         Example() : y(1), z(2), x(3) {}
         // 列表顺序：y, z, x
         // 实际初始化顺序：x, y, z（按声明顺序）
     };
     ```

   - 构造函数的参数也可以按从右向左规则赋默认值，同样的，如果构造函数的**声明和定义分开写**，**只用在声明或定义中的一处设置参数默认值**，**一般建议**在声明中设置默认值

     ```cpp
     class Point {
     public:
     	Point(int ix, int iy = 0); // 默认参数设置在声明时
     	// ...
     };
     
     Point::Point(int ix, int iy)
     : m_x(ix)
     , m_y(iy)
     {
     	cout << "Point(int,int)" << endl;
     }
     
     void test0(){
         Point pt(10);
     }
     ```

   - C++11之后，普通的数据成员也可以在声明时就进行初始化<font color=red>**（类似于默认值的性质）**</font>

     ```cpp
     class Point {
     public:
     	// ...
         int m_x = 0; // C++11
         int m_y = 0;
     };
     ```

     但一些特殊的数据成员初始化只能在初始化列表中进行，故一般情况下统一推荐在初始化列表中进行数据成员初始化

4. **对象所占空间大小**

   - 内存对齐规则（与结构体内存对齐规则相同）

     ```cpp
       规则						说明	
     成员对齐		每个成员的偏移量必须是其自身大小的整数倍	
     结构体对齐		结构体总大小必须是其最大成员大小的整数倍	
     补齐填充		不满足上述条件时，插入填充字节
     ```

   - **特殊情况**

     如果定义了一个空类，这个类依然是可以创建对象的；**空类对象所占空间为1个字节**，这仅仅是编译器的一种占位机制

     ```c++
     class A{};
     
     A a;
     ```

5. **指针数据成员**

   类的数据成员中有指针时，意味着创建该类的对象时要进行指针成员的初始化，需要申请堆空间

   **在初始化列表中申请空间，在函数体中复制内容**

   ```cpp
   class Computer {
   public:
   	Computer(const char * brand, double price)
   	: m_brand(new char[strlen(brand) + 1]())
   	, m_price(price)
   	{
           strcpy(m_brand,brand);
       }
       
   private:
   	char * m_brand;
   	double m_price;
   };
   
   void test0(){
       Computer pc("Apple",12000);
   }
   ```

   代码运行没有报错，但使用memcheck工具检查发现发生了内存泄漏；有new表达式被执行，就要想到通过delete表达式来进行回收；如果没有对应的回收机制，**对象被销毁时，它所申请的堆空间不会被回收，就会发生内存泄漏**

   若是想要进行妥善的内存回收——则需要交给**析构函数**来完成↓↓↓

## 二、对象的销毁

1. **析构函数**

   - 基本语法

     ```cpp
     ~类名() {
     	
     }
     ```

   - 执行特点：<span style=color:red;background:yellow>**对象被销毁时 ，一定且会自动调用析构函数【非常重要】**</span>

   - 作用：**清理资源**

     - 释放动态内存：使用 `new` 分配的堆空间内存需要在析构函数中使用 `delete` 释放
     - 关闭文件句柄：如果在对象的生命周期中打开了文件，析构函数可以确保在对象销毁时关闭文件
     - 断开网络连接：在网络编程中，析构函数可以确保在对象销毁时关闭套接字连接

   - 形式：**特殊的成员函数**

   - **析构函数只有一个**（不能重载）

   - **析构函数默认情况下 ，系统也会自动提供一个**

2. **自定义析构函数**

   没有显式定义出析构函数，系统会自动提供一个默认的析构函数

   <span style=color:red;background:yellow>**析构函数作为一个清理数据成员申请的堆空间的接口存在**</span>

   ```cpp
   class Computer {
   private:
   	char * m_brand;
   	double m_price;
   public:
   	Computer(const char * brand, double price)
   	: m_brand(new char[strlen(brand) + 1]())
   	, m_price(price)
   	{}
   	~Computer()
   	{	
           if(m_brand){
               delete [] m_brand;
           	m_brand = nullptr; //设为空指针，安全回收
           }
   		cout << "~Computer()" << endl;
   	}
   };
   ```

   **注：**

   - 如果没有进行安全回收

     ```cpp
     if(m_brand){
         	delete [] m_brand;
             //_brand = nullptr//设为空指针，安全回收
            }
     ```

     第一次手动调用析构函数时已经回收了这片堆空间，但是m_brand存的地址值依然有效，当对象销毁时自动调用析构函数，依然会进入if语句，再一次试图回收这片空间，发生double free错误

   - 如果没有对指针成员的判断，可能会有delete一个空指针的情况，在其他的一些平台这样做可能会导致风险

   - **对象被销毁，一定会调用析构函数；**<font color=red>**调用了析构函数，对象并不会被销毁**</font>

     当一个有析构函数的对象生命周期结束时，编译器**保证**调用其析构函数来清理资源

     这里的**“销毁”通常指释放该对象占用的内存**（即便内存被回收了）。显式调用析构函数只会执行析构逻辑（如关闭文件、释放锁等），**不会释放对象本身所占的存储空间**

   - 所以，<font color=red>**不建议手动调用析构函数，因为容易导致各种问题，应该让析构函数自动被调用**</font>

   > **注：析构函数是可以通过对象来调用，而构造函数不同**

3. ==**析构函数的调用时机**==

   - 对于**全局对象**，在<font color=red>**整个程序结束时**</font>**自动**调用全局对象的析构函数

   - 对于**局部对象**，在<font color=red>**程序离开局部对象的作用域时**</font>**自动**调用对象的析构函数

   - 对于**静态对象**，在<font color=red>**整个程序结束时**</font>**自动**调用析构函数

   - 对于 **堆对象**，   在<span style=color:red;background:yellow>**使用 delete 删除该对象时**</span>**手动**调用析构函数

     ```cpp
     void test(){
         // 堆对象
         Computer *pc = new Computer("apple",6500);
         delete pc; // 调用析构函数
         cout << "after delete" << endl;
     }
     ```

     ![image-20250212154926766](D:\Typora Picture\image-20250212154926766.png)

     通过 **`new`** 操作符在堆上创建对象时，如果该对象的某些**数据成员**本身也是通过 `new` 在堆上动态分配的内存，那么在回收这些资源时，需要确保**所有动态分配的内存都被正确释放**，以避免内存泄漏。通过在对象的**析构函数**中对**数据成员**的**显式释放**

4. **析构函数的顺序/优先级**

   1. 手动 `delete` 的**堆对象**
   2. **普通局部栈对象**（出作用域就没了）
   3. **局部 static 静态对象**
   4. **全局对象**（全场最晚析构）

   > 局部静态对象是在程序结束时析构，且先于全局对象# Day05

## 一、同类型对象的复制——拷贝构造函数

1. **拷贝构造函数**

   **—— C++ 里一种==特殊的构造函数==，==用一个已存在的同类型对象，去创建并初始化一个新对象==**

   对于语言内置类型而言，使用一个变量初始化另一个变量是很常见的操作

   ```cpp
   int x = 1;
   int y = x;
   ```

   对于自定义类型，也希望有这样的效果

   ```cpp
   Point pt1(1,2);
   Point pt2 = pt1;
   pt2.print();
   ```

   这种操作也是可以通过的，执行 Point pt2 = pt1; 语句时， pt1 对象已经存在，而 pt2 对象还不存在，所以也是这句创建了 pt2 对象，既然涉及到对象的创建，就必然需要调用构造函数，而**这里会调用**的就是**拷贝构造函数(复制构造函数**)

2. **拷贝构造函数的定义**

   - 1·形式

     <font color=red>**<类名>(const <类名> & ) {}**</font>

     ```cpp
     // 该函数是一个构造函数 —— 拷贝构造也是构造
     // 该函数用一个已经存在的同类型的对象，来初始化新对象，即对'对象'本身进行复制
     ```

   - 没有显式定义拷贝构造函数，复制语句依然可以通过，即**编译器自动提供**了**默认的拷贝构造函数**

     ```cpp
     Point(const Point & rhs)
     : m_x(rhs.m_x)
     , m_y(rhs.m_y)
     {}
     ```

3. **浅拷贝与深拷贝**

   ```cpp
   Computer pc("Acer",4500);
   Computer pc2 = pc;//调用拷贝构造函数
   
   // 拷贝构造函数
   Computer(const Computer & rhs) : m_brand(rhs.m_brand) , m_price(rhs.m_price){
       cout << "Computer(const Computer &)" << endl;
   }
   ```

   可以编译通过，但运行报错

   - 如果是默认的拷贝构造函数，pc2会对pc的_brand进行<font color=red>**浅拷贝**</font>，指向同一片内存；pc2被销毁时，会调用析构函数，将这片堆空间进行回收；pc再销毁时，析构函数中又会试图回收这片空间，出现double free问题

   - 所以，如果**拷贝构造函数需要显式写出**时（该**类有指针成员申请堆空间**），在**自定义的拷贝构造函数中要换成<font color=red>深拷贝</font>的方式**，先申请空间，再复制内容

     ```cpp
     Computer::Computer(const Computer & rhs)
     : m_brand(new char[strlen(rhs.m_brand) + 1]())
     , m_price(rhs.m_price)
     {
     	strcpy(m_brand, rhs.m_brand);
     }
     ```

   - 浅拷贝对比深拷贝

     | **特性**     | 浅拷贝 (Shallow Copy) | 深拷贝 (Deep Copy)        |
     | :----------- | :-------------------- | :------------------------ |
     | **复制内容** | 只复制指针地址        | 复制指针指向的实际数据    |
     | **内存关系** | 新旧对象共享同一内存  | 新旧对象有独立内存        |
     | **修改影响** | 修改一方会影响另一方  | 修改一方不影响另一方      |
     | **资源释放** | 双重释放风险（崩溃）  | 可安全释放                |
     | **实现方式** | 编译器默认生成        | 需手动实现                |
     | **性能开销** | 低（仅复制指针）      | 高（需分配内存+复制数据） |

4. ==**拷贝构造函数的调用时机**==

   - 当使用**一个已经存在的对象**初始化**另一个同类型的新对象**时

     ```cpp
     void test0(){
         Point pt(10,8);
         // 利用一个已经存在的对象用复制的方式创建新的对象
         // 调用拷贝构造, 用=连接是为了跟内置类型保持一致
         Point pt2 = pt;
         pt2.print();
     }
     ```

   - 对象作为函数参数（**实参和形参的类型都是对象**），形参与实参结合时（**实参初始化形参**）

     **—— 为了避免这次不必要的拷贝，可以使用引用作为参数==（使用引用&原因）==**

     ```cpp
     // 当函数的实参和形参都是对象时,利用实参初始化形参,相当于值传递,会发生复制
     // 为了避免这次多余的复制,可以将参数改为引用
     /* void func1(Point & p) */
     void func1(Point p)
     {
         p.print();
     }
     
     void test1()
     {
         Point p(1,1);
         func1(p);
     }
     ```

   - 对象作为函数的返回值，执行return语句时（编译器有优化）

     **—— 为了避免这次多余的拷贝，可以使用引用作为返回值，但一定保返回值的生命周期大于函数的生命周期**

     ```cpp
     MyClass func() {
         MyClass obj;  // 局部对象
         return obj;   // 返回对象
     }
     
     int main() {
         MyClass res = func();  // 调用方变量
     }
     /*
     无优化时，真实执行流程（两次拷贝）
     1.func() 里创建局部对象 obj（栈上）；
     2.第一次拷贝：return obj 时，把 obj 拷贝到函数的返回值临时空间（编译器为返回值准备的匿名内存）；
     3.函数销毁局部 obj；
     4.第二次拷贝：把返回值临时空间里的对象，再拷贝给 main 里的变量 res；
     5.销毁临时空间对象。
     中间那两次拷贝，全是为了把局部对象安全转移到调用方变量而产生的过渡拷贝。
     */
     ```

5. **拷贝构造函数的形式探究**

   1. <span style=color:red;background:yellow>**拷贝构造函数为什么不能去掉引用符号**</span>

      即形式：**<类名>(const <类名> )** 为什么不行

      - 首先，**编译器**不允许这样写，直接**报错**
      - 其次，进行拷贝时调用拷贝构造函数的过程中会发生“实参和形参都是对象，用实参初始化形参”（**拷贝构造函数的第二种调用时机**），会再一次调用拷贝构造函数。形成递归调用，直到栈溢出，导致程序崩溃

      ```cpp
      // 如果拷贝构造函数的形式是Pointer(const Pointer rhs)
      // Point pt2(pt)
      // 形参的初始化const Point rhs = pt; 会触发拷贝构造的第二种时机 会对pt进行复制
      // const Point rhs = pt;
      // ......
      // 如此会导致拷贝构造函数递归调用,直到栈溢出,程序崩溃
      ```

   2. <span style=color:red;background:yellow>**拷贝构造函数为什么不能去掉const**</span>

      即形式：**<类名>( <类名> & ) **为什么不行

      编译器不会报错，而加const的目的：

      - 确保原始对象的数据成员不被改变
      - 为了能够复制临时对象的内容，因为**非const**引用**不能绑定临时变量（右值）**

      ```cpp
      // 如果不加const，那么如下操作是可以通过的——不合理
      Point(Point & rhs)
      : m_ix(rhs.m_ix)
      , m_iy(rhs.m_iy)
      {
       rhs.m_ix = 0; // 修改源对象
       rhs.m_iy = 0;
       cout << "Point(const Point &)" << endl;
      }
      ```

      ```cpp
      // 如果拷贝构造函数中去掉const
      void test()
      {
          // Computer("apple",12000) 是一个临时变量/对象(匿名对象),是右值 
          // 非const引用不能绑定右值
      	Computer & rhs = Computer("apple",12000); //error    
      }
      ```

6. ==**补充：左值与右值**==

   - 左值 : **一个占据内存并可以取地址的对象**

     简单来说，左值是表达式**可以放在赋值运算符 `=` 左侧**的内容，是可以被**引用**的、持久存在的内存位置

     - 左值有**确定的内存地址**
     - 左值是可以被赋值的，即可以放在 `=` 左边
     - 左值通常表示一个变量或对象，可以通过引用来获取它的内存地址

     ```cpp
     int x = 5;    	// x是一个变量 是左值, 占据内存，有具体的地址
     x = 10;       	// x 可以被赋值，因此 x 是左值
     int & ref = x; 	// 非const引用只能绑定左值 
     ```

   - 右值 : **没有明确存储位置的临时对象**

     通常用于表达式的结果。右值是**不能取地址**的，通常表示临时的、短暂存在的值

     - 右值是**临时的值**，没有明确的内存地址，不能取地址
     - 右值通常是**字面常量**或**表达式计算的结果**

     - 右值只能放在赋值运算符的右边，不能作为左值（因为没有存储位置）

     ```cpp
     int y = 5 + 3; 			// 5 + 3 是右值，表达式的结果是一个临时值
     int z = 10;    			// 10 是一个字面常量，也是右值
     // int & ref2 = 10; error 非const引用不能能绑定右值 
     const int & ref = 10; 	// const引用既可以绑定左值, 也可以绑定右值
     ```

   ```cpp
   void test()
   {
       // num为左值可以取地址  1为右值不能取地址
       int num = 1;
       &num;
       // &1 // 字面常量1 没有存在内存中
       int & ref = num; // 非const常量只能绑定左值, 不能绑定右值
       // int & ref2 = 10; 
       // const引用既能够绑定左值,又能绑定右值
       const int & ref3 = 10;
       const int & ref4 = num;
   }
   ```

## 二、同类型对象的复制——赋值运算符函数

赋值运算符函数（常叫**拷贝赋值运算符** `operator=`）是 C++ 的**==特殊成员函数==**，用来==**把一个已存在对象的数据，拷贝给另一个已存在的同类型对象**==

```cpp
// 内置类型的赋值运算
int x = 1, y = 2;
x = y;
```

```cpp
// 自定义类型的赋值运算
Point pt1(1, 2), pt2(3, 4);
pt1 = pt2;//赋值操作
```

在执行 pt1 = pt2; 该语句时， **pt1 与 pt2 都存在**，所以**不存在对象的构造**，这要与 Point pt2 =pt1; 语句区分开

1. **赋值运算符函数的形式**

   当 = 作用于对象时，其实是把它当成一个函数来看待的。在执行 pt1 = pt2; 该语句时，需要调用的是<span style=color:red;background:yellow>**赋值运算符函数**</span>

   - **形式**

     <span style=color:red;background:yellow>**<类名>& operator=(const <类名>&)**</span>

     > 类名 &  : 返回值类型是对当前对象的引用
     >
     > const 类名 & : 参数是常量引用

   - 如果类中没有显式定义赋值运算符函数时，编译器会自动提供一个赋值运算符函数。对于 Point 类而言，其实现如下:

     ```cpp
     Point & Point::operator=(const Point & rhs)
     {
     	m_ix = rhs.m_ix;
     	m_iy = rhs.m_iy;
     }
     ```

   - ==为什么赋值运算符函数的声明里只看到一个参数==

     因为**赋值运算符必须是类的非静态成员函数**，不能是全局函数。
     当我们写 `a = b;` 时，编译器会把它翻译成：

     ```cpp
     a.operator=(b);   // a 是调用者，b 是参数
     ```

     左操作数 `a` 就是调用这个函数的对象，它由隐含的 `this` 指针指向，所以不需要写进参数列表。你看到的函数声明里，只显式声明了右操作数：

     ```cpp
     class MyClass {
     public:
         MyClass& operator=(const MyClass& right);  // 只有 1 个显式参数
     };
     ```

     实际上，这里的“完整签名”可以理解为：

     ```cpp
     MyClass& operator=(MyClass* this, const MyClass& right); // 伪代码，不可手写
     ```

     - `this` 是隐式的，指向左操作数 `a`
     - `right` 是显式的，对应右操作数 `b`

     所以从**操作数的角度来看，赋值运算符确实需要两个东西**：左边和右边。但从**函数定义的角度，你只需要写右操作数那个参数**

   - ==赋值运算符函数的返回值==

     赋值运算符函数返回类型是Point&，它的返回值是——==this指针的解引用即***this**==，所以函数返回给外界的不是指针本身还是当前对象的引用即*this

     `*this` 是对象本身，但**通过返回引用的函数返回它**，外界拿到的是**这个对象的引用**，就像一个别名，直接操作原对象，没有拷贝。**`return` 机制配合返回类型，把对象变成了引用传递。** 这就是 C++ 设计上的精妙之处

2. **this指针**

   **`this` 永远指向==正在==执行成员函数的那个对象。** 不是某个全局的、会变来变去的指针

   - this指针的本质

     - this指针的本质是一个常量指针  `Type* const pointer`

     - this指针指向本对象

     - 它储存了调用它的对象的地址，不可被修改
       这样成员函数才知道自己修改的成员变量是哪个对象的

     - this是一个隐藏的指针，可以在类的成员函数中使用，它可以用来指向调用对象
       当一个对象的成员函数被调用时，编译器会隐式地传递该对象的地址作为 this 指针

       ```cpp
       // 返回值类型为Pointer&
       // 函数名operator=
       // this不能显示写在形参列表中，它是隐式传参，编译器会在形参中加入一个this作为**第一个参数**
       Point & operator=(const Point & p)
       {
           // 省略this的访问
           /* m_x = p.m_x; */
           /* m_y = p.m_y; */
           
           // 对this指针解引用后通过.访问对象中成员
           /* (*this).m_x = p.m_x; */
           /* (*this).m_y = p.m_y; */
           
           // 可以使用->箭头运算符来访问对象中成员 简化操作 
           this -> m_x = p.m_x;
           this -> m_y = p.m_y;
           return *this;
       }
       
       void print()
       {
           // this指针指向当前对象 即调用print函数的对象
           // 通过this + 箭头运算符来访问对象中成员
           cout << "x=" << this->m_x
               << ", y=" << this->m_y << endl;
       } 
       ```

   - this指针存储位置

     编译器在生成程序时加入了获取对象首地址的相关代码，将获取的首地址存放在了寄存器中，这就是this指针

   - this指针的生命周期

     **this 指针的生命周期开始于成员函数的执行开始。**当一个**非静态**成员函数被调用时，this 指针被自动设置为指向调用该函数的对象实例。在成员函数执行期间，this 指针一直有效。它可以被用来访问调用对象的成员变量和成员函数。<font color=red>**this指针的生命周期结束于成员函数的执行结束。**</font>当成员函数返回时，this指针的作用范围就结束了

     > 要注意，this指针的生命周期与它所指向的对象的生命周期虽然并不完全相同，但是是相关的
     >
     > this指针本身只在成员函数执行期间存在，但它指向的对象可能在成员函数执行前就已经存在，并且在成员函数执行后继续存在
     >
     > 如果**成员函数通过一个已经销毁或未初始化的对象调用**，==this指针将是悬空的，它的使用将会是未定义行为==

   - **总结：**

     - 对象调用函数时，是如何找到自己本对象的数据成员的？    —— 通过this指针

     - this指针代表的是什么？                                                           —— 指向本对象

     - this指针在参数列表中的什么位置？                                        ——  参数列表的第一位（默                   认自动加入，不要手动写出）

     - this指针的形式是什么？                                                           ——  <类名>* const this （常量指针）

       ```cpp
       Point & operator=(const Point & rhs){
           this->m_ix = rhs.m_ix;
           this->m_iy = rhs.m_iy;
           cout << "Point & operator=(const Point &)" << endl;
           return *this;
       }
       ```

       本对象通过this指针找到本对象的数据成员。但是**不要在参数列表中显式加上this指针**，因为编译器一定会在参数列表的第一位加上this指针，如果显式再给一个，参数数量就不对了

3. **赋值运算符函数的定义**

   默认的赋值运算符函数

   ```cpp
   Computer & operator=(const Computer & rhs){
       this->m_brand = rhs.m_brand;
       this->m_price = rhs.m_price;
       return *this;
   }
   ```

   如果对象的指针数据成员申请了堆空间，默认的赋值运算符函数就不够用了，因为这里的指针成员m_brand是进行的**浅拷贝**，会造成问题

   **直接进行深拷贝**，会有内存泄露，需要回收掉pc2.m_brand原本申请的空间
   如果用delete**回收**掉pc2.m_brand原本申请的空间，**再进行深拷贝**，也可能出现问题，所以还要考虑**自赋值：一个对象被赋值给它自己**

   所以<span style=color:red;background:yellow>**总结步骤—— 四步走（重点）：**</span>

   1. 考虑自赋值问题
   2. 回收左操作数的数据成员原本申请的堆空间
   3. 深拷贝（以及其他的数据成员的赋值）
   4. 返回*this（本对象）

   ```cpp
   Computer & operator=(const Computer & rhs){
       // 1.自赋值情况判断
       if(this != &rhs){
           delete [] m_brand; //回收当前对象中指针成员原来申请的堆空间
           m_brand = new char[strlen(rhs.m_brand)](); // 深拷贝
           strcpy(m_brand,rhs.m_brand);
           m_price = rhs.m_price; // 其他数据成员的简单赋值
       }
       return *this; // 返回当前对象
   }
   ```

4. **赋值运算符函数的形式探究**

   关于赋值运算符函数的形式探究也是面试中比较可能出现的问题，以下提出四个思考：

   1. 为什么赋值运算符函数返回的必须是一个引用

      ```cpp
      Computer operator=(const Computer & rhs)
      {
          ……
          return *this;
      }
      // 会造成一次多余的拷贝，增加不必要的开销
      ```

   2. 为什么赋值操作符函数的返回类型不可以是void

      ```cpp
      void operator=(const Computer & rhs)
      {
          ……
      }
      // 无法处理连续赋值
      ```

   3. 为什么赋值操作符函数的参数一定要是引用

      ```cpp
      Computer & operator=(const Computer rhs)   
      {
      	……
      	return *this;
      }
      // 会造成一次多余的拷贝，增加不必要的开销（拷贝构造函数的第二种调用时机）
      ```

      > 注意：此时讨论的是赋值运算符函数的参数形式，前提是拷贝构造是正常的。拷贝构造的参数依然是引用，才不会陷入拷贝构造递归调用

   4. 为什么赋值操作符函数的参数必须是一个const引用

      ```cpp
      Computer & operator=(Computer & rhs)   
      {
      	……
      	return *this;
      }
      // 无法避免在赋值运算符函数中修改右操作数的内容——不合理
      ```

      ```cpp
      // 而且不能处理通过右值属性的对象来进行赋值的情况
      pc = Computer("xiaomi",5999); // error
      即 pc.operator=(Computer("xiaomi",5999)) // error
      pc.print();
      ```

5. ==**三合成原则**==

   <span style=color:red;background:yellow>**三合成原则**</span>很容易在面试时被问到：

   **拷贝构造函数、赋值运算符函数、析构函数，如果需要手动定义其中的一个，那么另外两个也需要手动定义。**

## 三、特殊的数据成员(成员变量)

在 C++ 的类中，有4种比较特殊的数据成员，分别是==**常量成员**、**引用成员**、**类对象成员**和**静态成员**==，它们的初始化与普通数据成员有所不同，==前三种的初始化都要在初始化列表中进行初始化==

1. **常量成员**

   数据成员用 const 关键字进行修饰以后，就成为**常量成员**；一经初始化，该数据成员便具有“只读属性”，在程序中无法对其值修改

   在**构造函数体内**对**const 数据成员赋值**是**非法**的，<span style=color:red;background:yellow>**const数据成员需在初始化列表中进行初始化**</span>（C++11之后也允许在声明时就初始化）

   普通的const常量必须在声明时就初始化，初始化之后 就不再允许修改值；**const数据成员初始化后也不再允许修改值==（可以不用在声明时初始化）==**

   ```cpp
   class Point {
   public:
   	Point(int ix, int iy)
   	: m_ix(ix)
   	, m_iy(iy)
   	{}
   private:
   	const int m_ix;
   	const int m_iy;
   };
   ```

   ```cpp
   class Point {
   public:
   	Point(int ix, int iy)
   	: m_ix(ix)
   	, m_iy(iy)
   	{}
   private:
       // C++11后允许在声明时进行初始化
       // 在这里初始化的值理解为默认值
   	const int m_ix = 1;
   	const int m_iy = 1;
   };
   
   void test(){
       Point p1(10,20); // 初始化
       Point p2 = p1; // 拷贝初始化
       // p2 = p1; // error 不能进行赋值操作 
   }
   ```

2. **引用成员**

   <span style=color:red;background:yellow>**引用成员在初始化列表中进行初始化**</span>，C++11之后允许在声明时初始化（绑定）

   引用要绑定到已经存在的变量，引用数据成员同样如此

   ```cpp
   class Point {
   public:
   	Point(int ix, int iy)
   	: m_ix(ix)
   	, m_iy(iy)
   	, m_iz(m_ix)
   	{}
   private:
   	int m_ix;
   	int m_iy;
   	int & m_iz;
   };
   ```

   构造函数再接收一个参数，用这个参数初始化引用成员可以吗

   ```cpp
   class Point
   {
   public:
   	Point(int x,int y,int z)
   	: m_ix(x)
   	, m_iy(y)
   	, m_iz(z) //这样绑定可行吗
   	{}
       
   private:
   	int m_ix;
   	int m_iy;
   	int & m_iz;
       // int & m_iz = m_ix; C++11之后允许在声明时初始化（绑定)
   };
   /*
   语法上完全可行
   但是存在严重问题：z 是按值传递的参数，它是构造函数作用域内的局部变量。构造函数执行完毕后 z 就会被销毁，而 m_iz 却仍然持有对它的引用，成为悬空引用（dangling reference）。此后任何对 m_iz 的读写都是未定义行为
   */
   ```

   **引用成员需要绑定一个已经存在的、且在这个引用成员的生命周期内始终有效的变量（对象）**

   ```cpp
   class A
   {
   public:
       A(int & num) // 将变量型实参传给引用型形参
       : m_num(num) // 将引用型赋值给引用型
       {
           cout << "constructor" << endl;
       }
       void print()
       {
           cout << "m_num=" << m_num << endl;
       }
   private:
       int & m_num;
   };
   
   
   void test(){
       int num =100;
       A a{num};
       a.print();
       num = 200;
       a.print();
   }
   ```

3. **对象成员**

   有时候，一个类对象会作为另一个类对象的数据成员被使用；比如一个A类对象中包含B类对象和C类对象

   <span style=color:red;background:yellow>**对象成员在初始化列表中进行初始化**</span>

   **注意：**

   - **初始化列表中**写的是需要被初始化的**对象成员的名称**，而**不是**对象成员的**类名**
   - 不能在声明对象成员时直接使用有参构造去创建
   - **如果在A类的构造函数的初始化列表中没有显式地初始化B类和C类对象成员，编译器会自动去调用B/C类型的默认无参构造**
   - 如果不想用B/C的无参构造，那么必须在A类的初始化列表中对B/C类的对象成员进行初始化

   <font color=red>**一个A对象中包含两个其他类型对象，被包含的那个对象数据成员称为成员子对象。**</font>

   执行流程：

   1. 创建A对象会马上调用A的构造函数
   2. 在A的构造函数执行过程中调用B的构造函数和C的构造函数
   3. A对象要销毁，就会马上调用A的析构函数
   4. A析构函数执行完之后，再根据**对象成员声明的反序**
   5. 通过成员子对象调用B和C的析构函数
   6. m_c调用析构函数，执行完后，m_b再调用析构函数

   如果A中有数据成员申请堆空间，B类/C类对象也有数据成员申请堆空间，堆空间资源的回收顺序如下

   ![image-20241120093249147](D:\Typora Picture\image-20241120093249147-17775509399501.png)

4. **静态成员**

   C++ 允许使用 static （静态存储）修饰数据成员，这样的成员在**编译时**就被**创建并初始化**的（与之相比，对象是在运行时被创建的），且其实例只有一个

   - 静态数据成员和之前介绍的静态变量一样，当程序执行时，该成员已经存在，一直到程序结束，任何该类对象都可对其进行访问;
   - **静态数据成员存储在全局/静态区，==并不占据对象的存储空间==**
   - <span style=color:red;background:yellow>**静态数据成员被整个类的所有对象共享**</span>

   静态成员规则：

   - 在private中声明的静态成员无法在类之外直接访问（显然）

   - <span style=color:red;background:yellow>**对于静态数据成员的初始化，必须放在类外**</span>（一般紧接着类的定义，这是规则1的特殊情况）

   - 静态数据成员**初始化**时**不**能在数据类型前面**加static**，在**数据成员名前面**要**加上类名+作用域限定符（<类名>: :<数据成员名>）**

   - 如果有多条静态数据成员，那么它们的**初始化顺序需要与声明顺序一致**（规范）

   - 静态成员在访问时**可以**通过对象访问，**也可以**直接通过**类名::成员名**的形式（更常用）

     ```cpp
     // 定义一个学生类, 创建3个不同的学生, 张三, 李四, 王五. 他们是同一个班级的同学
     class Student
     {
     public:
         Student(int id, const char* name)
         : m_id(id)
         , m_name(new char[strlen(name)+ 1]{})
         {
             strcpy(m_name, name);
         }
         ~Student()
         {
             if(m_name){
                 delete [] m_name;
                 m_name = nullptr;
             }
         }
         void print()
         {
             cout << m_id << "," << m_name << endl;
         }
     
         // 静态成员作为班级ID
         static int ms_classID; // 静态的成员必须在类的外部进行初始化
     private:
         int m_id;
         char *m_name;
     };
     
     // 类外部 静态成员的初始化
     // 需要指明是在哪个类中定义的静态成员 类名::
     int Student::ms_classID = 2;
     ```

## 四、补充

1. 变量初始化的顺序、构造函数参数的初始化顺序、构造函数中数据成员的初始化顺序

   ```cpp
   #include <math.h>   // C
   #include <cmath>    // C++
   #include <iostream>
   using namespace std;
   class Point {
   public:
       Point(int xx = 0, int yy = 0) {
                   X = xx;
                   Y = yy;
                   cout << "point构造函数被调用" << endl;
           }
           Point(Point &p);
           int GetX() {
                   return X;
           }
           int GetY() {
                   return Y;
           }
   private:
           int X,Y;
   };
   Point::Point(Point &p) {
           X = p.X;
           Y = p.Y;
           cout << "X = " << X << " Y=" << Y << "Point拷贝构造函数被调用" << endl;
   }
   class Distance {
   public:
           Distance(Point xp1, Point xp2);
           double GetDis() {
                   return dist;
           }
   private:
           Point p1,p2;
           double dist;
   };
   Distance::Distance(Point xp1, Point xp2)
   : p1(xp1)
   , p2(xp2)
   {
           cout << "Distance构造函数被调用" << endl;
           double x = double(p1.GetX() - p2.GetX());
           double y = double(p1.GetY() - p2.GetY());
           dist = sqrt(x * x + y * y);
   }
   int main() {
           Point myp1(1,1), myp2(4,5);
           Distance myd(myp1, myp2);
           cout << "The distance is:" ;
           cout << myd.GetDis() << endl;
   
           return 0;
   }
   /*
   运行结果：
   point构造函数被调用
   point构造函数被调用
   X = 4 Y=5Point拷贝构造函数被调用
   X = 1 Y=1Point拷贝构造函数被调用 // 说明形参初始化顺序从右往左 编译器行为
   X = 1 Y=1Point拷贝构造函数被调用
   X = 4 Y=5Point拷贝构造函数被调用
   Distance构造函数被调用
   The distance is:5
   */
   ```

   - 声明语句中，逗号分隔的多个变量

     ```cpp
     Point myp1(1,1), myp2(4,5);
     ```

     这是**一条声明语句**中包含两个声明符，用逗号分隔
     标准规定：初始化顺序**严格从左到右**。
     所以输出首先是：

     ```cpp
     point构造函数被调用     ← myp1 构造
     point构造函数被调用     ← myp2 构造
     ```

   - 函数实参的初始化顺序（关键！）

     ```cpp
     Distance myd(myp1, myp2);
     ```

     这里调用了 `Distance` 的构造函数：

     ```cpp
     Distance::Distance(Point xp1, Point xp2)  // 按值传递
     ```

     按值传递意味着需要将实参 **拷贝** 给形参 `xp1` 和 `xp2`

     **C++ 标准规定：函数实参的求值顺序是“未指定的”（unspecified）。**
     也就是说，编译器可以决定先初始化 `xp1` 还是先初始化 `xp2`，常见实现中，很多编译器是**从右向左**处理的（这与 C 调用约定 `__cdecl` 从右向左压栈一致）

     ```cpp
     X = 4 Y=5Point拷贝构造函数被调用     ← 形参 xp2 先被拷贝构造
     X = 1 Y=1Point拷贝构造函数被调用     ← 形参 xp1 后被拷贝构造
     ```

     说明该编译器选择了**先右后左**的顺序。这完全是合法的，因为标准不强制顺序
     注意：参考答案里的注释“说明形参初始化顺序从右往左 编译器行为”指的就是这一点

   - 构造函数初始化列表中的成员初始化

     进入 `Distance` 构造函数体之前，会先执行**初始化列表**：

     ```cpp
     : p1(xp1)
     , p2(xp2)
     ```

     这里 `p1` 和 `p2` 是 `Distance` 的成员变量
     初始化列表中的顺序**不决定**实际初始化顺序
     **真正的顺序由成员在类中声明的顺序决定**：

     ```cpp
     private:	
         Point p1, p2;   // 先 p1，后 p2
     ```

     所以成员初始化是**先 `p1` 后 `p2`**，而且都是调用拷贝构造函数

     于是输出：

     ```cpp
     X = 1 Y=1Point拷贝构造函数被调用     ← 成员 p1 用 xp1 拷贝构造
     X = 4 Y=5Point拷贝构造函数被调用     ← 成员 p2 用 xp2 拷贝构造
     ```

     注意这里的参数是 xp1 和 xp2，值分别是 (1,1) 和 (4,5)）

     最后才执行构造函数的函数体，输出：

     ```cpp
     Distance构造函数被调用
     ```

   - **总结**

     - 一条声明语句中的多个变量/声明符 → 严格从左到右
     - 函数实参 → 求值顺序未指定，实践中常见从右向左
     - 成员初始化列表 → 严格按类声明顺序，与列表顺序无关

2. return返回的临时变量的生命周期

   ```cpp
   #include <iostream>
   using namespace std;
   class B {
   public:
           B() {
           cout << "B()" << endl;
       }
       ~B() {
           cout << "~B()" << endl;
       }
       B(const B &rhs) {
           cout << "B(const B&)" << endl;
       }
       B &operator=(const B &rhs) {
           cout << "B &operator=(const B &s)" << endl;
           return  *this;
       }
   };
   B func(const B &rhs) {
       cout << "B func(const B &)" << endl;
       return rhs;
   }
   int main(int argc, char **argv) {
           B b1,b2;
       b2=func(b1);//10#
           return 0;
   }
   /*
   B()
   B()
   B func(const B &)
   B(const B&) // func函数return时发生
   B &operator=(const B &s)
   ~B()
   ~B()
   ~B()
   */
   ```

   在 `b2 = func(b1);` 这条语句中，执行顺序是：

   1. 调用 `func(b1)`
      - 进入函数体，输出 `B func(const B &)`
      - `return rhs;` 时，用 `b1` 拷贝构造出一个**临时 `B` 对象**（输出 `B(const B&)`）
      - `func` 调用结束，该临时对象作为函数结果返回
   2. 进行赋值
      - `b2.operator=(临时对象)`，输出 `B &operator=(const B &s)`
   3. 赋值完成后，**临时对象在分号处析构**
      - 输出 `~B()`（如果扩展完整输出的话，会看到它紧接在赋值之后，但在 `main` 中后续代码之前）

   这个临时 `B` 对象在**当前完整表达式结束时销毁**，也就是 `b2 = func(b1);` 这一整条语句执行完毕后立即析构，因为：

   ++ 标准规定：==**临时对象的生命周期持续到创建它的完整表达式（full-expression）的末尾**==，除了极少数绑定到引用的情况；这里的完整表达式就是整个赋值语句 `b2 = func(b1);`，所以临时对象会在该语句结束时自动析构

3. 构造函数、拷贝构造函数、赋值运算符函数、析构函数的实战小练习

   ```cpp
   #include <string.h>
   #include <iostream>
   
   using namespace std;
   
   class Student {
   public:
       Student(int num, const char* name, int age)
           : m_num(num)
             , m_name(new char[strlen(name) + 1]{})
             , m_age(age)
             {
                 strcpy(this->m_name, name);
                 cout << "Student num " << this->m_num << endl;
             }
       // 构造函数的初始化列表阶段，只有基类和已经在列表中初始化完成的成员才是可用的
       // 对于当前类中尚未被初始化的成员，通过 this 去访问它们（哪怕只读取）是未定义行为
       Student(const Student& s) // 初始化列表中不能使用this指针
           : m_num(s.m_num)
             , m_name(new char[strlen(s.m_name) + 1]{})
             , m_age(s.m_age)
             {
                 strcpy(this->m_name, s.m_name);
                 cout << "copy Student num " << this->m_num << endl;
             }
       Student& operator=(const Student& s) {
           if (this == &s) // 防止自我赋值
               return *this;
           if (this->m_name) {
               delete [] this->m_name;
               this->m_name = nullptr;
           }
           this->m_num = s.m_num;
           this->m_name = new char[strlen(s.m_name) + 1]{};
           strcpy(this->m_name, s.m_name);
           this->m_age = s.m_age;
           cout << "operator= Student num " << this->m_num << endl;
           return *this;
       }
       ~Student() {
           if (this->m_name) {
               delete [] this->m_name;
               this->m_name = nullptr;
           }
           cout << "~Student num " << this->m_num << endl;
       }
       void print() {
           cout << "Student num " << this->m_num << endl;
           cout << "Student name " << this->m_name << endl;
           cout << "Student age " << this->m_age << endl;
       }
   private:
       int m_num;
       char* m_name;
       int m_age;
   };
   
   int main() {
       Student s1(1, "zs", 20);
       cout << "s1:" << endl;
       s1.print();
   
       cout << endl;
   
       /* Student s2(s1); // 显式调用拷贝构造函数 */
       Student s2 = s1; // 这种"拷贝初始化"语法要求隐式转换，如果用 explicit 修饰拷贝构造函数这种拷贝初始化就不合法
       cout << "s2:" << endl;
       s2.print();
   
       cout << endl;
   
       Student s3(3, "ls", 21);
       cout << "s3 before = :" << endl;
       s3.print();
       s3 = s1;
       cout << "s3 after = :" << endl;
       s3.print();
   
       cout << endl;
   
       return 0;
   }
   /*
   Student num 1
   s1:
   Student num 1
   Student name zs
   Student age 20
   
   copy Student num 1
   s2:
   Student num 1
   Student name zs
   Student age 20
   
   Student num 3
   s3 before = :
   Student num 3
   Student name ls
   Student age 21
   operator= Student num 1
   s3 after = :
   Student num 1
   Student name zs
   Student age 20
   
   ~Student num 1
   ~Student num 1
   ~Student num 1
   */
   ```
# Day06_特殊成员函数&对象的组织&单例模式

## 一、特殊的成员函数

C++ 类中还有两种特殊的成员函数：**静态成员函数**和 **const 成员函数**

1. **静态成员函数**

   某一个成员函数的前面加上static关键字，这个函数就是静态成员函数

   - **静态成员函数的特点：**

     - <span style=color:red;background:yellow>**静态成员函数不依赖于某一个对象**</span>

     - 静态成员函数可以通过对象调用，但更常见的方式是<font color=red>**通过类名加上作用域限定符调用**</font>

     - 静态成员函数没有this指针

     - <font color=red>**静态成员函数中无法直接访问非静态的成员**</font>，只能访问静态数据成员或调用静态成员函数（因为没有this指针）

       > 构造函数、拷贝构造函数、赋值运算符函数、析构函数比较特殊，可以在静态成员函数中调用

     > 注：
     >
     > - 但是非静态的成员函数可以访问静态成员
     > - 静态成员函数不能是构造函数/析构函数/赋值运算符函数/拷贝构造（因为这四个函数都会访问所有的数据成员，而static成员函数没有this指针）

2. **const成员函数**

   在成员函数的参数列表之后，函数执行体之前加上const关键字，这个函数就是const成员函数

   - ==**形式：void func( ) const {  }**==
   - **特点：**
     - const成员函数中，不能直接修改对象的非静态的普通数据成员
     - 当编译器发现该函数是const成员函数时，会自动将this指针设置为**双重const限定的指针**`const Type* const pointer`，所以可以进行函数重载，同名的非const版本的成员函数和const版本的成员函数

   > - const成员函数的作用：让 const 对象 /const 引用 /const 指针 能够安全调用成员函数，同时强制保证函数不修改对象的状态

## 二、对象的组织

有了自己定义的类，或者使用别人定义好的类创建对象，其机制与使用内置类型创建普通变量几乎完全一致，同样可以创建 const 对象、创建指向对象的指针、创建对象数组，还可使用 new(delete) 来创建(回收)堆对象

1. **const对象**

   类对象也可以声明为 const 对象
   一般来说，能作用于 const 对象的成员函数除了构造函数和析构函数，就只有 const 成员函数，因为 const 对象只能被创建、销毁和只读访问，写操作是不允许的

   - const对象与const成员函数的规则：

     - 当类中有**const成员函数和非const成员函数重载**时，**const对象会调用const成员函数，非const对象会调用非const成员函数**
     - 当类中**只有一个const成员函数时**，无论const对象还是非const对象**都可以调用**这个版本
     - 当类中**只有一个非const成员函数**时，**const对象就不能调用**非const版本

   - **总结：**<span style=color:red;background:yellow>**如果一个成员函数中确定不会修改数据成员，就把它定义为const成员函数**</span>

   - **补充**

     - 一个类中可以有参数形式“完全相同”的两个成员函数（const版本与非const版本），既然没有报错重定义，那么它们必然是构成了重载，为什么它们能构成重载呢？

       **第一个参数(this指针)的类型是不同的**

     - const成员函数中不允许修改数据成员，const数据成员初始化后不允许修改，其效果是否相同？

       对于普通类型的数据成员：
       const数据成员初始化后不允许修改，在const成员函数中无论是const数据成员还是非const数据成员，都不能修改值

       对于指针类型的数据成员：
       `const int * p`，初始化之后在任何地方都不能修改其指向的值（无论在const成员函数中还是在非const成员函数中），在非const成员函数中可以修改指向，在const成员函数中不能修改指向
       `int * p`,在非const成员函数中可以修改指向，也可以修改值，在const成员函数中不能修改指向，可以修改指向的值

2. **指向对象的指针**

   对象占据一定的内存空间，和普通变量一致，C++ 程序中采用如下形式声明指向对象的指针：

   ```cpp
   <类名> * <指针名> = [初始化表达式];
   // 初始化表达式是可选的，既可以通过取地址（&对象名）给指针初始化，也可以通过申请动态内存给指针初始化，或者干脆不初始化（比如置为 nullptr ），在程序中再对该指针赋值
   ```

   指针中存储的是对象所占内存空间的首地址。针对上述定义，则下列形式都是合法的：

   ```cpp
   Point pt(1, 2);
   Point * p1 = nullptr;
   Point * p2 = &pt;
   Point * p3 = new Point(3, 4); // 记得delete
   ```

   利用指针去调用Point类的成员函数print：

   ```cpp
   p2->print();
   // 等价于
   (*p2).print();
   ```

3. **对象数组**

   - 对象数组的声明

     ```cpp
     Point pts[2];
     ```

   -  对象数组的初始化

      ```cpp
          // 1.通过左值对象构建数组
          Point pt1{ 1, 1 };
          Point pt2{ 2, 2 };
          Point pt3{ 3, 3 };
          // 左值对象作为数组元素时 会调用copy
          Point pts[3] = { pt1, pt2, pt3 };
          /* pts[0].m_x = 10; */
          pts[0].print();
      
          // 2.通过右值对象构建数组
          Point pts[] = {
              Point{ 1, 1 },
              Point{ 2, 2 },
              Point{ 3, 3 }
          };
          pts[0].print();
      
          // 3.通过初始化列表简写构建数组
          // 使用初始化列表进行简写
          Point pts[] = {
              { 1, 1 },
              { 2, 2 },
              { 3, 3 }
          };
          pts[0].print();
      ```

   -  对象数组的遍历

      ```cpp
          // foreach遍历 增强for循环(迭代循环)
          for(Point pt : pts){
              pt.print();
          }
          cout << "----->" << endl;
          // 使用关键字auto进行类型的自动推导
          for(auto pt : pts){
              pt.print();
          }
      	// 省去拷贝操作
          cout << "----->" << endl;
          // Point & pt 
          for(auto & pt : pts){
              pt.print();
          }
      ```

4. **堆对象**

   和把一个简单变量创建在动态存储区一样，可以用 new 和 delete 表达式为对象分配动态存储区

   ```cpp
   void test()
   {
   	Point * pt1 = new Point(11, 12);
   	pt1->print();
   	delete pt1;
   	pt1 = nullptr;
       
   	Point * pt2 = new Point[5]();//注意
   	pt2->print();
   	(pt2 + 1)->print();
   	delete [] pt2;
       pt2 = nullptr;
   }
   ```

## 三、new/delete表达式的工作步骤(了解)

new/delete和malloc/free最本质区别 —— new/delete是表达式，而malloc/free是库函数，new/delete表达式的底层工作步骤：

> **`new/delete` 是表达式（操作符），`operator new/delete` 是函数**。
> `new` 表达式在执行时会**调用** `operator new` 函数来分配原始内存，`delete` 表达式会**调用** `operator delete` 函数来释放原始内存
>
> | 表达式     | 底层操作                         |
> | :--------- | :------------------------------- |
> | `new T()`  | `operator new` + 构造函数调用    |
> | `delete p` | 析构函数调用 + `operator delete` |
> | `malloc()` | 仅分配原始内存                   |
> | `free()`   | 仅释放原始内存                   |

> 注意：不能说new 与 delete 的本质是 malloc 与 free 
>
> `new/delete` 是**C++ 的关键字 / 运算符**，**==底层会调用== malloc/free 分配内存**，==但==**额外做了大量 C++ 专属工作**

1. **new表达式的工作步骤**

   对于**自定义类型**而言：

   <span style=color:red;background:yellow>**使用new表达式时发生的三个步骤**</span>：

   1. 调用operator new标准库函数申请未类型化的空间             

   2. 在该空间上调用该类型的构造函数初始化对象

   3. 返回指向该对象的相应类型的指针

2. **delete表达式的工作步骤**

   对于**自定义类型**而言：

   <span style=color:red;background:yellow>**使用delete表达式时发生的两个步骤**</span>：

   1. 调用析构函数,回收数据成员申请的资源(堆空间)

   2. 调用operator delete库函数回收本对象所在的空间

   ```cpp
   //默认的operator new
   void * operator new(size_t sz){
       void * ret = malloc(sz);
   	return ret;
   }
   
   //默认的operator delete
   void operator delete(void * p){
       free(p);
   }
   ```

   ```cpp
   // 完善new/delete过程
   class Student {
   public:
   	Student(int id, const char * name)
   	: m_id(id)
   	, m_name(new char[strlen(name) + 1]())
   	{
   		strcpy(m_name, name);
   		cout << "Student()" << endl;
   	}
   	~Student() {
   		delete [] m_name;
   		cout << "~Student()" << endl;
   	}
   	void * operator new(size_t sz) {
           cout << "operator new" << endl;
   		void * ret = malloc(sz);
   		return ret;
   	}
   	void operator delete(void * pointer) {
           cout << "operator delete" << endl;
   		free(pointer);
   	}
   	void print() const {
   		cout << "id:" << _id << endl
   			<< "name:" << _name << endl;
   	}
   private:
   	int m_id;
   	char * m_name;
   };
   ```

   ![image-20241104093024931](..\0.TyporaPicture\image-20241104093024931.png)

   ![image-20241104093038278](..\0.TyporaPicture\image-20241104093038278.png)

3. **创建对象的探究**

   定义一个类，即使什么成员函数也不定义，依然可以创建栈对象和堆对象，说明会自动提供默认的operator new / operator delete函数

   默认的operator new / operator delete函数实际上就是通过malloc / free 实现的申请 / 回收堆空间

   1. <font color=red>**创建堆对象需要什么条件？**</font>

      > 将创建、销毁对象过程中所调用到的函数一一设为私有，私有的成员函数在类外就无法被直接调用了

      需要公有的operator new、operator delete、构造函数，对析构函数没有要求；只有在销毁堆对象的时候，才会调用析构函数

      ```cpp
      //创建堆上的对象需要public的构造函数/ operator new / operator delete
      void test1(){
          Student *p = new Student{1, "zs"};
          p->print();
          // delete p;
      }
      ```

   2. <font color=red>**创建栈对象需要什么条件？**</font>

      需要公有的构造函数、析构函数，对operator new/operator delete没有要求

      ```cpp
      void test2()
      {
          // 创建栈对象需要public的构造函数 析构函数
          Student stu{2,"ls"};
          // 离开作用域会调用析构函数
      }
      ```

4. **根据探究得出的结论，仍以Student类为例，想要实现以下需求，应该怎么做**

   - ==只能生成栈对象 , 不能生成堆对象==

     可以将operator new/operator delete 设为私有

     > 因为编译器要调用 `operator new`

   - ==只能生成堆对象 ，不能生成栈对象==

     可以将析构函数设为私有

     > 因为编译器自动调用构造函数与析构函数

   > **总结：**我们需要了解new/delete表达式的工作步骤，以此为依据更合理地设计类的成员函数来进行对象的创建和回收
   >
   > <font color=red>**operator new/operator delete在平时不需要特别地写出，使用默认的即可。**</font>只在如上的特别的需求下，可以显式定义出来，实现不同的限制效果

## ==四、单例模式==

单例模式是23种常用设计模式中最简单的设计模式之一，它提供了一种维护对象(实例)的方式，确保每次获取的都是同一个唯一的对象。这个设计模式主要目的是想在**整个系统中只能出现类的一个实例，即一个类只有一个唯一对象**

1. **将单例对象创建在静态区**

   1. 将构造函数设为私有
   2. 通过静态成员函数getInstance创建局部静态对象，确保对象的生命周期和唯一性(即只初始化一次)
   3. getInstance的**返回值设为引用**，避免复制

   <font color=red>**隐患：如果单例对象所占空间较大，可能会对静态区造成内存压力**</font>

   ```cpp
   #include <iostream>
   
   using namespace std;
   
   class Singleton {
   public:
       static Singleton &getInstance() {
           static Singleton instance;
           return instance; // 返回一个唯一的对象
       }
       // 删除复制函数
       Singleton(const Singleton &) = delete;
       Singleton &operator=(const Singleton &) = delete;
   private:
       Singleton() {}
   };
   
   void test1() {
       /* Singleton s1; // error */
       cout << &Singleton::getInstance() << endl;
       cout << &Singleton::getInstance() << endl;
       cout << &Singleton::getInstance() << endl;
   }
   
   int main() {
       test1();
   
       return 0;
   }
   ```

2. ==**将单例对象创建在堆区**==

   <font color=red>**既然将单例对象创建在全局/静态区可能会有内存压力，那么为这个单例对象动态分配空间是比较合理的选择**</font>

   1. 构造函数设为私有
   2. 通过静态成员函数getInstance创建堆上的对象，**返回相应类型的指针**
   3. **通过静态成员函数完成堆对象的回收**

   ```cpp
   #include <iostream>
   
   using namespace std;
   
   class Singleton {
   public:
       static Singleton *getInstance() { // 提供一个静态方法返回静态对象
           if (ms_instance == nullptr) {
               ms_instance = new Singleton(); // 在堆上创建对象
           }
           return ms_instance;
       }
       static void destroyInstance() { // 提供一个静态方法来销毁对象 释放空间
           if (ms_instance != nullptr) {
               delete ms_instance;
               ms_instance = nullptr;
           }
       }
       void func() {
           cout << "func()" << endl;
       }
   private:
       static Singleton *ms_instance; // 提供静态的自身类型的指针 指向唯一的实例
       Singleton() { // 构造函数私有 确保不能在外部创建对象
           cout << "default constructor" << endl;
       }
       ~Singleton() { // 析构函数私有 避免外部删除对象
           cout << "destructor" << endl;
       }
       // C++11之前可以将拷贝构造和赋值运算符函数设置为private
       // C++11以后可以删除类中的成员函数来避免外部复制对象 保证单例
       Singleton(const Singleton &) = delete; // 删除拷贝构造函数
       Singleton &operator=(const Singleton &) = delete; // 删除赋值运算符函数
   };
   Singleton *Singleton::ms_instance = nullptr; // 类中静态成员指针初始化为nullptr
   
   int main() {
       Singleton *instance1 = Singleton::getInstance();
       cout << instance1 << endl;
       Singleton *instance2 = Singleton::getInstance();
       cout << instance2 << endl; // 地址相同
       Singleton::getInstance()->func(); // 单例对象的使用规范 避免多个指针拥有单例对象的管理权
   
       Singleton::destroyInstance();
       Singleton::destroyInstance(); // 多次destroy也不会double free
       return 0;
   }
   ```

   **规范：**

   1. 要使用单例对象时直接使用getInstance函数的返回值
   2. **析构函数**的访问权限一般比构造函数更严格，**也设置为私有**
   3. 为了确保只有一个对象（严格避免复制），C++11后可以将拷贝构造和赋值运算符函数从类中删除( [声明] = delete; )

   ![image-20241104144008414](..\0.TyporaPicture\image-20241104144008414.png)

   ![image-20241104144204481](..\0.TyporaPicture\image-20241104144204481.png)

3. **单例对象的数据成员申请堆空间**

   要求：实现一个单例的Computer类，包含品牌和价格信息

   ```cpp
   class Computer {
   public:
       // init
       void init(const char* brand, double price)
       {
           // 回收之前的空间
           delete [] m_brand;
           m_brand = new char[strlen(brand)+1]{};
           strcpy(m_brand, brand);
           m_price = price;
       }
       // 静态方法来返回实例
       static Computer * getInstance()
       {
           if(ms_pInstance == nullptr){
               ms_pInstance = new Computer{};
           }
           return ms_pInstance;
       }
       static void destroyInstance()
       {
           if(ms_pInstance != nullptr)
           {
               delete ms_pInstance;
               ms_pInstance = nullptr;
           }
       }
       Computer(const Computer & pc) = delete;
       Computer & operator=(const Computer & com) = delete;
       
   private:
       // constructor
       Computer(){}
       // destructor
   	~Computer()
   	{
           if(m_brand){
               delete [] m_brand;
           	m_brand = nullptr; //设为空指针，安全回收
           }
   		cout << "destructor" << endl;
   	}
   
   
   	char * m_brand;
   	double m_price;
       static Computer * ms_pInstance;
   };
   Computer * Computer::ms_pInstance = nullptr;
   void test1(){
       cout << Computer::getInstance() << endl;
       cout << Computer::getInstance() << endl;
       Computer::getInstance()->init("xiaomi",2999);
       Computer::getInstance()->init("huawei",3999);
       cout << Computer::getInstance() << endl;
      
       Computer::destroyInstance();
   }
   ```

   ![image-20241128143035002](..\0.TyporaPicture\image-20241128143035002-17778971206723.png)

   ![image-20241128143050644](..\0.TyporaPicture\image-20241128143050644.png)# Day07_字符串&vector&CPP输入输出流

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

# Day08_文件输出流

## ==一、文件输入输出流==——==包含在头文件<fstream>中==

所谓“**文件**”，一般指存储**在外部介质上数据的集合**。一批*数据是以文件的形式存放在外部介质上的*。**操作系统以文件为单位对数据进行管理**。要向外部介质上存储数据也必须先建立一个**文件（以文件名标识）**，才能向它输出数据。外存文件包括磁盘文件、光盘文件和U盘文件。目前使用最广泛的是磁盘文件

**文件流**是以**外存文件为输入输出对象**的**数据流**

**文件输入流**是从外存文件流向内存的数据，**文件输出流**是从内存流向外存文件的数据。**每一个文件流都有一个内存缓冲区与之对应**。*文件流本身不是文件，而只是以文件为输入输出对象的流*。若要对磁盘文件输入输出，就必须通过文件流来实现

1. **C++ 对文件进行操作的流类型有三个:**

   -  ifstream（文件输入流）

   -  ofstream（文件输出流）

   -  fstream （文件输入输出流）

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

## 二、**文件输入流**

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

   1. 逐字符读取

      ```cpp
      // 使用ifstream成员函数get
      
      int ch = ifs.get();
      // 或
      char ch;
      ifs.get(ch);
      ```

   2. 逐词读取

      ```cpp
      // 使用 输入流运算符>>，默认以换行符、空格作为间隔符，一次读取一个字符串
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

   3. 按行读取

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

        **将一行的内容交给一个string对象去存储，不用再关心字符数**

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
        > void test4()
        > {
        > using std::string; // 使用string中的getline
        >  ifstream ifs("aa.txt");
        >  string line;
        >  while(std::getline(ifs,line)){ // eof状态结束循环
        >      cout << line << endl;
        >  }
        > 
        > ifs.close(); // 关闭流
        > }
        > ```

   4. 按字节读取

      - read函数

        通过文件输入流对象读取到的内容交给字符数组，同时需要传入要读取的字符数

        ![image-20241108110205841](..\0.TyporaPicture\image-20241108110205841.png)

      - tellg函数

        要知道字符数就需要用上tellg函数了，可以这样理解，从文件中读取内容时存在一个文件游标，读取是从文件游标的位置开始读取的。tellg就是用来获取游标位置的，而seekg则是用来设置游标位置的。

        ![image-20241108110135500](..\0.TyporaPicture\image-20241108110135500.png)

      - seekg函数

        调用seekg时有两种方式:

        1. 绝对位置

           比如将游标设为流的开始位置，可以直接传参数0

        2. 相对位置

           传入偏移量和基准点

           第一个参数：相对基准点需要向前偏移则传入负数，不偏移则传入0，需要向后偏移则传入正数。
           第二个参数：格式为<span style=color:red;background:yellow>**std::ios::beg**</span>(以流的开始位置为例)

        ![image-20241108110343811](..\0.TyporaPicture\image-20241108110343811.png)

        ![image-20241108110410536](..\0.TyporaPicture\image-20241108110410536.png)

      - 示例：读取一个文件的全部内容

        > 还可以在创建输入流对象时指定ate模式，省去第一步将游标置于流末尾处的操作

        ```cpp
        void test0(){
            string filename = "test.cc";
            ifstream ifs(filename); 
        
            if(!ifs){
                cerr << "ifs open file fail!";
                return;
            }
            
            // 读取一个文件的所有内容先要获取文件的大小
            // 将游标放到了文件的最后（尾后）
            fs.seekg(0,std::ios::end);
            long length = ifs.tellg();//获取尾后下标，实际就是总的字符数
            cout << length << endl;
        
            char * pdata = new char[length + 1]();
            //需要将游标再放置到文件开头
            ifs.seekg(0,std::ios::beg);
            ifs.read(pdata,length);
        
            // 还可以使用string构造函数 根据内容创建string对象
            //content包含了文件的所有内容，包括空格、换行
            string content(pdata);
            cout << "content:" << content << endl;
            /* cout << pdata << endl; */
            
            // delete
            delete[] pdata;
            pdata = nullptr;
            // close
            ifs.close();
        }
        ```

## 三、补充——类与对象简答

1. **什么是构造函数？它有哪些特点？请说明构造函数的作用。**

   - **定义**：一种特殊的成员函数，函数名与类名相同，没有返回值。

   - **特点**：
     - 在对象创建时自动调用；
     - 可以重载；
     - 如果没有显式定义，编译器会自动生成一个默认无参构造函数（但不会初始化内置类型成员）；
     - 可以通过初始化列表对数据成员进行初始化。
   - **作用**：初始化对象的数据成员，申请资源等。

2. **什么是析构函数？它有哪些特点？请说明何时需要自定义析构函数。**

   - **定义**：一种特殊的成员函数，函数名为`~类名`，没有参数和返回值。
   - **特点**：
     - 在对象销毁时自动调用；
     - 不能重载，每个类只有一个析构函数；
     - 如果没有显式定义，编译器会自动生成一个默认析构函数（但不会释放动态分配的资源）。
   - **何时需要自定义析构函数**：当类中有指针成员且申请了堆空间（如`new`分配的内存），或者有其他需要清理的资源（如文件句柄、网络连接）时，需要自定义析构函数来释放这些资源，防止内存泄漏。

3. **简述浅拷贝与深拷贝的区别，并说明在什么情况下需要手动实现深拷贝。**

   - **浅拷贝**：
     - 只复制指针的值（地址），
     - 新旧对象指向同一片内存。（**不是两个对象本身占用同一片内存，这是对浅拷贝最常见的误区。两个完全独立的对象，各自占用独立的内存空间；==但它们内部的指针成员，指向了同一片堆内存==（对象管理的外部资源）。**）
     - 可能导致同一内存被多次释放（double free）或修改一方影响另一方。

   - **深拷贝**：
     - 复制指针指向的实际数据，
     - 为新对象分配独立的内存。
     - 新旧对象互不影响，可以安全释放。
   - **需要手动实现深拷贝的情况**：当类中有指针成员且指向动态分配的内存时，默认的拷贝构造函数和赋值运算符函数进行浅拷贝，会导致问题，因此需要手动实现深拷贝。

4. **简述拷贝构造函数和赋值运算符函数的区别（从调用时机、形式、实现等方面）。**

   | 特性           | 拷贝构造函数                   | 赋值运算符函数                                   |
   | :------------- | :----------------------------- | :----------------------------------------------- |
   | 调用时机       | 用一个已存在对象初始化新对象时 | 两个对象都已存在，将一个对象的值赋给另一个对象时 |
   | 形式           | `类名(const 类名&)`            | `类名& operator=(const 类名&)`                   |
   | 是否创建新对象 | 是                             | 否                                               |
   | 返回值         | 无                             | 通常返回`*this`的引用                            |
   | 处理自赋值     | 不涉及（新对象还不存在）       | 需要处理自赋值情况                               |

5. **简述this指针的作用，并说明它在const成员函数和非const成员函数中的类型有何不同。**

   - **作用**：指向调用成员函数的对象本身，在成员函数中通过`this`可以访问本对象的成员。

   - 在非const成员函数中，this指针的类型是`类名 * const`（常量指针，指向非常量）；

   - 在const成员函数中，this指针的类型是`const 类名 * const`（常量指针，指向常量），因此不能通过this修改对象的数据成员。

6. **简述静态数据成员和静态成员函数的特点，并说明为什么静态成员函数中不能直接访问非静态成员。**

   - **静态数据成员**：
     - 被所有对象共享，
     - 存储在全局/静态区，不占用对象空间，
     - 必须在类外初始化。
   - **静态成员函数**：
     - 不依赖于具体对象，
     - 没有this指针，
     - 只能访问静态成员（静态数据成员或其他静态成员函数），不能直接访问非静态成员（因为没有this指针，不知道访问哪个对象的成员）。

7. **简述单例模式的作用和实现要点，并说明将单例对象创建在静态区和堆区各自的优缺点。**

   - **作用**：确保一个类只有一个实例，并提供一个全局访问点。
   - **实现要点**：
     1. 构造函数私有化；（**不强制要求必须把析构函数设为私有**，它不是单例的语法必需项）
     2. 提供静态的`getInstance`方法返回唯一实例；
     3. 将拷贝构造和赋值运算符删除（或设为私有）；
     4. 静态成员指针保存唯一实例（堆区实现），或返回静态局部对象（静态区实现）。
   - **优缺点**：
     - **静态区实现**：
       - 简单，
       - 线程安全（C++11后局部静态变量初始化是线程安全的），
       - 但对象生命周期与程序相同，可能因占用静态区造成内存压力。
     - **堆区实现**：
       - 可以手动控制对象销毁，
       - 适合大对象，
       - 但需要处理线程安全和手动释放。

8. **简述C风格字符串与C++ `std::string`的区别，并说明为什么在C++中更推荐使用`std::string`。**

   - **C风格字符串**：
     - 字符数组，以'\0'结尾，
     - 需要手动管理内存，
     - 使用库函数（如`strcpy`、`strcat`）操作，容易出错（缓冲区溢出、忘记结尾空字符等）。

   - **C++ `std::string`**：
     - 类类型，
     - 自动管理内存，
     - 提供丰富的成员函数，支持直接赋值、拼接、比较等操作，更安全、更方便。

**推荐使用`std::string`**：因为它封装了内存管理，避免了许多C风格字符串的常见错误，提高了代码的安全性和可读性。

9. **简述`std::vector`的动态扩容机制，并说明`size()`和`capacity()`的区别。**

   1. 当`size() == capacity()`时，再添加元素会触发扩容。
   2. **扩容步骤**：
      1. 开辟一块更大的新空间（通常为原容量的2倍或1.5倍，取决于编译器）；
      2. 将原空间的所有元素复制（或移动）到新空间；
      3. 添加新元素；
      4. 释放原空间。

   - `size()`：当前实际存储的元素个数。
   - `capacity()`：当前已分配内存可以存储的元素个数（即容量），`capacity() >= size()`。

10. 分析下列程序，写出输出结果（假设构造函数和析构函数都有输出提示）。 c++

    ```cpp
    #include <iostream>
    using namespace std;
    
    class A {
    public:
        A() { cout << "A()" << endl; }
        ~A() { cout << "~A()" << endl; }
    };
    
    class B {
    public:
        B() { cout << "B()" << endl; }
        ~B() { cout << "~B()" << endl; }
    private:
        A a;
    };
    
    int main() {
        B b;
        return 0;
    }
    ```

    - ```cpp
      A()
      B()
      ~B()
      ~A()
      ```

    - **原因**：

      `B` 类包含一个 `A` 类型的成员对象 `a`。在 `main` 中创建 `B` 的对象 `b` 时：

      - 先初始化成员 `a`，调用 `A` 的构造函数，输出 `A()`；
      - 再执行 `B` 的构造函数体，输出 `B()`。

      程序结束时销毁 `b`：

      - 先执行 `B` 的析构函数体，输出 `~B()`；
      - 再销毁成员 `a`，调用 `A` 的析构函数，输出 `~A()`。

      因此==**整体遵循“先构造的后析构”原则**==# Day09_文件输出流&字符串输入输出流&日志系统

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
   
        
# Day10——友元&运算符重载

## 一、友元

1. **什么是友元**

   - 一般类的私有成员只能在类的内部访问，类之外是不能访问它们的。

     但如果**将其他类/函数设置为**类的**友元**，那么友元类/函数就可以在前一个类的类定义之外**访问其私有成员（数据成员与成员函数）**了

   - <span style=color:red;background:yellow>**用friend关键字声明友元**</span>

   > 将类比作一个家庭，类的private 成员相当于家庭的秘密，一般的外人当然不允许探听这些秘密的，只有 friend 才有资格探听这些秘密

2. **友元的三种形式：普通函数、成员函数、类**

   1. **友元的普通函数形式**

      在类中**将普通函数设置为友元**，通过该普通函数访问类中私有成员

      ```cpp
      class MyClass {
      public:
          //MyClass(int data) : ... {}
          // 声明友元函数
          friend void friendFunc(const MyClass& cls);
      private:
          int m_data;
          void privateFunc() {
              cout << "privateFunc" << endl;
          }
          // const函数由const对象访问
          void privateFunc() const {
              cout << "const privateFunc" << endl;
          }
      };
      
      // 使用了const
      void friendFunc(const MyClass& cls) {
          // 友元函数访问类中私有成员
          cout << cls.m_data << endl; // 私有数据成员
          cls.privateFunc(); // 私有成员函数
      }
      
      void test1() {
          const MyClass cls2 {1};
          friendFunc(cls2);
      }
      ```

   2. **友元的成员函数形式**

      假设类A有一个成员函数，该成员函数想去访问另一个类B类中的私有成员
      则可以在B类中，声明A类的那个成员函数为B类的友元函数
      这样A类的那个成员函数就可以访问B类的私有成员

      注意：

      1. 需要把B类前向声明，否则在A类中不知道B类的存在
      2. 需要在A类中给出成员函数的声明，**这个友元成员函数的定义即具体实现写在类外**，因为在声明时编译器只知道B类的存在，但是不知道具体实现
      3. <span style=color:red;background:yellow>**友元的声明要注意和函数的形式完全对应上**</span>

      ```cpp
      // 在这个场景中：
      // A类那个成员函数的函数体定义，一定要放在B类里的友元声明之后
      // 但A类中该函数的声明放在B类定义之前
      
      // B类声明
      class MyClass;
      // A类定义
      class FriendClass {
      public:
          void display(MyClass & cls); 
      };
      // B类定义
      class MyClass {
      public:
          MyClass() {}
          MyClass(int data)
          : m_data(data)
          {}
          // 成员函数作为友元的声明
          friend void FriendClass::display(MyClass& cls);
      private:
          int m_data;
          void privateFunc() {
              cout << "privateFunc" << endl;
          }
      };
      // 友元函数的定义
      void FriendClass::display(MyClass& cls) {
          cout << cls.m_data << endl;
          cls.privateFunc();
      }
      
      void test1() {
          FriendClass cls {};
          MyClass myClass {20};
          cls.display(myClass);
      }
      int main(int argc, char *argv[]) {
          test1();
          return 0;
      }
      ```

      > ==**补充**==
      >
      > 前向声明的用处：
      > 进行了**前向声明**的类，能**以引用或指针的形式作为函数的参数**，前提是**不涉及到对该类对象具体成员的访问**，编译器可以通过
      >
      > (让编译器认识这个类，但是注意如果只进行前向声明，这个类的**具体实现没有的话，无法使用这个类的对象**，无法创建)

   3. **友元的类形式**

      若是在上面场景的基础上，假设类A中还有其他成员函数也需要访问B类的私有成员，如果还像上面的方式一个一个设置友元就比较繁琐了，**可以直接将A类设置为B类的友元类**，在工作中这也是更常见的方法

      ```cpp
      class B {
      	//...
      	friend class A;
      	//...
      };
      ```

      在B类中声明A类是本类的友元类，那么A类中的所有成员函数中都可以访问B类的私有成员——一次声明，全部解决

      ```cpp
      // B类
      class MyClass {
      public:
          MyClass() {}
          MyClass(int data)
      	: m_data(data)
          {}
          // FriendClass类作为友元声明
          friend class FriendClass; 
      private:
          int m_data;
          void privateFunc() {
              cout << "privateFunc" << endl;
          }
      };
      // A类
      class FriendClass {
      public:
          void display(MyClass & cls) {
              cout << cls.m_data << endl;
              cls.privateFunc();
          }
          void display2(MyClass & cls) {
              cout << cls.m_data << endl;
              cls.privateFunc();
          }
      };
      
      void test1() {
          FriendClass cls{};
          MyClass myClass {20};
          cls.display(myClass); // 成员函数1能访问B的私有成员
          cls.display2(myClass); // 成员函数2也能访问B的私有成员
      }
      int main(int argc, char *argv[]) {
          test1();
          return 0;
      }
      ```

3. **友元的特点**

   > 不可否认，友元将类的私有成员暴露出来，在一定程度上破坏了信息隐藏机制，似乎是种“副作用很大的药”，但俗话说“良药苦口”，好工具总是要付出点代价的，拿把锋利的刀砍瓜切菜，总是要注意不要割到手指的
   >
   > 友元的存在，使得类的接口扩展更为灵活，使用友元进行运算符重载从概念上也更容易理解一些，而且C++ 规则已经极力地将友元的使用限制在了一定范围内

   1. **友元不受类中访问权限的限制**

      可访问私有成员

   2. **友元破坏了类的封装性**

   3. **不能滥用友元 ，友元的使用受到限制**

   4. **友元是单向的**

      A类是B类的友元类(B中声明A为friend class)，则A类成员函数中可以访问B类私有成员；但并不代表B类是A类的友元类，如果A类中没有声明B类为友元类，此时B类的成员函数中并不能访问A类私有成员

   5. **友元不具备传递性**

      A是B的友元类，B是C的友元类，无法推断出A是C的友元类

   6. **友元不能被继承**

      因为友元破坏了类的封装性，为了降低影响，设计层面上友元不能被继承

## 二、运算符重载

1. **什么是运算符重载**

   C++预定义中的运算符的操作对象只局限于基本的内置数据类型，但是对于自定义的类型是没有办法操作的

   当然我们可以定义一些函数来实现这些操作，但考虑到用运算符表达含义的方式很简洁易懂，当定义了自定义类型时，也希望这些**运算符能被自定义类类型使用**，以此提高开发效率，增加代码的可复用性

   为了实现这个需求，**C++提供了运算符重载**
   其指导思想是：<span style=color:red;background:yellow>**希望自定义类类型在操作时与内置类型保持一致**</span>

2. **能够重载与不能重载的运算符**

   - 能够重载的运算符有42个

     | +    | -    | *    | /      | %     | ^        |
     | ---- | ---- | ---- | ------ | ----- | -------- |
     | &    | \|   | ~    | !      | =     | <        |
     | >    | +=   | -=   | *=     | /=    | %=       |
     | ^=   | &=   | \|=  | >>     | <<    | >>=      |
     | <<=  | ==   | !=   | >=     | <=    | &&       |
     | \|\| | ++   | --   | ->*    | ->    | ,        |
     | []   | ()   | new  | delete | new[] | delete[] |

   - 不能重载的运算符有5个**（带点的运算符不能重载，再加上sizeof）**

     - `.` 成员访问运算符
     - `.*`成员指针访问运算符
     - `?:`三目运算符
     - `::`作用域限定符
     - `sizeof `长度运算符

3. ==**运算符重载的规则与形式**==

   - **规则**

     1. 运算符重载时，<font color=red>**操作数必须要有自定义类类型或枚举类型**</font>——不能全是内置类型

     2. 运算符重载的本质是函数重载，其优先级和结合性仍然不变——例如：a == b + c

     3. <font color=red>**操作符的操作数个数仍然保持不变**</font>

     4. <font color=red>**运算符重载时 ，不能设置默认参数**</font>——因为设置默认值，就改变了操作数的个数

     5. **逻辑与&&**和**逻辑或||**不再具备短路求值特性，因为进入函数体之前必须完成所有函数参数的计算——所以不推荐重载

     6. 不能臆造一个并不存在的运算符——例如：@ $ 、

   - **形式**

     运算符重载的形式有三种：

     - 采用普通函数的重载形式

     - <span style=color:red;background:yellow>**采用友元函数的重载形式**</span>

       > **用做运算符重载的友元函数**，几乎**一定是「全局非成员函数」**
       >
       > 虽然也可以用另一个类的成员函数充当运算符重载的友元，但没人这么用、工程完全不这么写，属于语法允许但无实际意义

     - <span style=color:red;background:yellow>**采用成员函数的重载形式**</span>

4. ==**重载形式的选择**==

   - ==友元函数方式重载适用场景==
     * **不会修改操作数的值**的运算符
     * 具有对称性的运算符可能转换任意一端的运算对象，例如相等性、位运算符等
   - ==成员函数方式重载适用场景==
     * **会修改操作数的值**的运算符
     * **赋值=、下标[ ]、调用()、成员访问->、成员指针访问->* 运算符==必须==是成员函数形式重载**
     * 与给定类型密切相关的运算符，如递增、递减和解引用运算符

5. **运算符重载的本质是定义一个运算符重载函数，定义的步骤如下——以+运算符为例**

   1. 先确定这个函数的返回值是什么类型（加法运算返回值应该是一个临时的Complex对象，所以此处返回类型为Complex）
   2. 再写上函数名（operator+ 运算符，此处就是**operator+**）
   3. 再补充参数列表（考虑这个运算符有几个操作数，此处加法运算应该有两个操作数，分别是两个Complex对象，因为加法操作不改变操作数的值，可以用const引用作为形参）
   4. 最后完成函数体的内容（此处直接调用Complex构造函数创建一个新的对象作为返回值）

   > 在定义的operator+函数中需要访问Complex类的私有成员，要进行友元声明
   >
   > <span style=color:red;background:yellow>**像加号这一类不会修改操作数的值的运算符，倾向于采用友元函数的方式重载**</span>

## ==三、输入输出流运算符 << >> 的重载==

1. **输出流运算符 <<**

   - 基本形式

     ```cpp
     std::ostream& operator<<(std::ostream& os, const MyClass& obj);
     ```

   - 返回类型

     `std::ostream&`，这样可以使输出支持链式调用

   - 参数

     - 第一个参数 `std::ostream& os`，表示输出流。
     - 第二个参数 `const MyClass& obj`，表示我们要输出的自定义类对象

     希望打印一个对象与打印一个整型数据在形式上没有差别，那就必须要重载 << 运算符

   - 示例

     - 需求

       对于Complex对象，希望像内置类型数据一样，使用输出流运算符可以对其进行输出

     - 分析

       - 输出流运算符有两个操作数，左操作数是输出流对象，右操作数是Complex对象。**如果将输出流运算符函数写成Complex的成员函数**，会带来一个问题，**成员函数的第一个参数必然是this指针**，也就是说Complex对象必须要作为左操作数。这种方式完成重载函数后，**只能cx << cout这样来使用**，与内置类型的使用方法不同，所以<span style=color:red;background:yellow>**输出流运算符的重载采用友元函数形式**</span>
       - cout << cx这个语句的返回值是`cout`对象，为了不必要的拷贝与支持链式调用，返回类型为`ostream&`
       - 参数列表中
         第一个是左操作数（`cout`对象），写出类型并给出形参名
         第二个是右操作数（`Complex`对象），因为不会在输出流函数中修改它的值，采用`const Complex &`
       - 将Complex的信息通过连续输出语句全部输出给os，最终返回os（注意，使用cout输出流时通常会带上endl，**那么在函数定义中就不加endl**，以免多余换行）

     - 源代码

       ```cpp
       class Complex {
       public:
           Complex(int real, int image)
           : m_real(real)
           , m_image(image)
           {}        
           // 为了和内置类型的使用方式保持一致
           // 利用友元函数实现 << 重载
           friend std::ostream& operator<<(std::ostream& os, const Complex & com);
       private:
           int m_real;
           int m_image;
       };
       
       // !!!std::ostream不支持拷贝构造 需要使用引用!!!
       std::ostream& operator<<(std::ostream& os, const Complex& com) {
           os << com.m_real << "+" << com.m_image << "i" ;
           return os;
       }
       
       void test1() {
           Complex com = Complex{1,2};
           cout << com << endl;
           // 本质形式
           operator<<(cout, com);
       }
       ```

2. **输入流运算符 >>**

   - 基本形式
   
     ```cpp
     std::istream& operator>>(std::istream& is, MyClass& obj);
     ```
   
   - 参数
   
     - `std::istream& is`：输入流对象（如 `std::cin`）
     - `MyClass& obj`：要将流中的数据存储到的对象,，要修改对象中数据成员，所以不能加const限定
   
   - 返回值
   
     返回输入流对象 `std::istream&`，这样可以**支持链式调用**
   
   - 示例
   
     - 需求
   
       对于Complex对象，希望像内置类型数据一样，使用输入流运算符可以对其进行输入
   
     - 分析
   
       - 如果不想分开输出实部和虚部，也可以直接连续输入，空格符、换行符都能作为分隔符
       - 使用输入流时需要判断是否是合法输入，可以封装一个函数判断接收到的是合法的int数据，在>>运算符重载函数中调用
   
     - 源代码
   
       ```cpp
       class Complex {
       public:
       	//...
       	friend istream& operator>>(istream& is, Complex& rhs);
       private:
       	int m_real;
       	int m_image;
       };
       
       istream& operator>>(istream& is, Complex& rhs) {
       	is >> rhs.m_real >> rhs.m_image; // 连续输入
       	return is;
       }
       
       // 输入并验证是否为整数
       std::istream& judgeInt(std::istream& is, int& number) {
           cout << "input a number: ";
           while (true) {
               if (is >> number) {
                   break; // 输入成功则跳出while循环
               } else {
                   // 清除流状态
                   is.clear();
                   is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                   cout << "Invalid input, please input again: ";
               }
           }
           return is;
       }
       ```

## 四、[] 运算符

C++ 中，`[]` 运算符重载通常用于实现类似数组访问的功能，可以让自定义类型的对象支持数组下标操作重载

- 形式

  ```cpp
  Type& operator[](size_t index); // size_t无符号整型
  ```

- 参数

  `index`：下标，用于指定访问的元素位置

- 返回值

  通常是返回某个元素的引用，可以是常量引用（`const Type&`）或非常量引用（`Type&`），以便支持修改元素的值或只读访问

- 示例

  - 需求

    定义一个CharArray类，模拟char数组，需要通过下标访问运算符能够对对应下标位置字符进行访问

  - 分析

    - 分析[ ]运算符重载函数的返回类型，因为通过下标取出字符后可能进行写操作，需要改变CharArray对象的内容，所以应该用char引用

    - [ ]运算符的操作数有两个，一个是CharArray对象，一个是下标，ch[0]的本质是ch.operator[] (0)

    - **函数体实现需要考虑下标访问越界情况**，若未越界则返回对应下标位置的字符，若越界返回终止符

  - 源代码

    ```cpp
    class CharArray {
    public:
        // constructor
        CharArray(const char * str)
        : m_capacity(strlen(str))
        , m_data(new char[strlen(str) + 1]{})
        {
            strcpy(m_data, str);
        }
        // destructor
        ~CharArray() {
            if (m_data) {
                delete [] m_data;
                m_data = nullptr;
            }
        }
        // operator[] 重载
        char& operator[](size_t index) {
            // 判断下标是否越界
            if (index >= m_capacity) {
                cout << "index out of range" << endl;
                static char nullChar = '\0';
                return nullChar; // nullChar（空字符/空终止符）是ASCII码值为0
            } else {
                // 返回下标位置的字符
                return m_data[index];
            }
        }
        void print() {
            cout << m_data << endl;
        }
    private:
        int m_capacity; // 数组容量
        char * m_data; // 数组指针
    };
    
    void test1() {
        CharArray ch {"hello"};
        cout << ch[0] << endl;
        ch[0] = 'H';
        cout << ch[0] << endl;
        ch.print();
    }
    ```

## 五、+ += ++ 运算符的重载

1. **+运算符**

   **需求**

   实现一个复数类，复数分为实部和虚部，重载+运算符，使其能够处理两个复数之间的加法运算（实部加实部，虚部加虚部）

   - 友元函数实现

     ```cpp
     class Complex {
         // ...
         friend Complex operator+(const Complex& lhs, const Complex& rhs);
         // ...
     };
     
     Complex operator+(const Complex& lhs, const Complex& rhs) {
         // ...
     }
     
     void test0(){
         Complex cx(1,2);
         Complex cx2(3,4);
         Complex cx3 = cx + cx2; // 看上去和内置类型的计算一样了
         // Complex cx3 = operator+(cx,cx2); // 本质上是调用了operator+函数
     }
     ```

   - 普通函数实现

     在一个普通函数中想要访问一个类的私有成员，也可以给这个类添加一些公有的get系列函数，因为这些成员函数是可以访问私有成员的，而在类外可以通过对象直接调用这些成员函数，也就能获取到私有成员了

     **实际工作中不推荐使用，因为这样做几乎完全失去了对私有成员的保护**

     ```cpp
     class Complex {
     public:
     	// ...
     	double getReal() const {
             return m_real; 
         }
     	double getImage() const {
             return m_image;
         }
     	// ...
     };
     
     Complex operator+(const Complex& lhs, const Complex& rhs) {
     	return Complex(lhs.getReal() + rhs.getReal(),
     			lhs.getImage() + rhs.getImage());
     }
     
     void test0() {
     	Complex c1(1, 2), c2(3, 4);
     	Complex c3 = c1 + c2; // ok
     }
     ```

   - 成员函数实现

     还可以将运算符重载函数定义为Complex类的成员函数

     ```cpp
     class Complex {
     public:
     	//...
     	Complex operator+(const Complex& rhs) {
     		return Complex(m_real + rhs.m_real, m_image + rhs.m_image);
     	}
     };
     ```

     **这种写法要注意的是，加法运算符的左操作数实际上就是this指针所指向的对象，在参数列表中只需要写上右操作数**

     ```cpp
     Complex cp1(1,2);
     Complex cp2(3,4);
     Complex cp = cp1 + cp2; // 本质是Complex cp = cp1.operator+(cp2)
     ```

   - **补充**

     如果写出了这样的代码，虽然可以通过，但是要避免

     ```cpp
     class Complex {
     public:
     	// ...
     	Complex operator+(const Complex& rhs) {
     		return Complex(m_real - rhs.m_real, m_image - rhs.m_image);
     	}
     };
     ```

     明明是加操作符，但函数内却进行的是减法运算，这是合乎语法规则的，不过却有悖于人们的直觉思维，会引起不必要的混乱

     所以，除非有特别的理由，**否则尽量使重载的运算符与其内置的、广为接受的语义保持一致**

2. **+=运算符**

   <span style=color:red;background:yellow>**像+=这一类会修改操作数的值的运算符，倾向于采用成员函数的方式重载。**</span>

   ```cpp
   class Complex {
   public:
       Complex(int real, int image)
       : m_real(real)
       , m_image(image)
       {}        
   
       Complex& operator+=(const Complex& com) {
           this->m_real = this->m_real + com.m_real;
           this->m_image = this->m_image+ com.m_image;
           return *this;
       }
       void print() {
           cout << m_real << "+" << m_image << "i" << endl;
       }
   private:
       int m_real;
       int m_image;
   };
   ```

3. **++运算符（分为前置与后置两个版本）**

   - 分析

     - 自增运算符有前置++和后置++两种形式，依然按照内置类型先分析计算逻辑，再类比这个计算逻辑去定义运算符重载函数

     - 例如：int a = 5; 
       a++的操作是使a的值增为6，但是这个表达式的返回值却是一个临时变量（a的值改变前的副本，即5）—— **返回值为右值**

       ++a则是使a的值增加到6，直接返回变量a本身 —— **返回值为左值**

     - 类比Complex，写出++运算符重载函数。按照我们目前的认知，前置++和后置++**都应该选择成员函数的形式进行重载**

       **但是前置形式和后置形式都是只有一个操作数（本对象）**，参数完全相同的情况下，**只有返回类型不同不能构成重载**。前置形式和后置形式的区分**只能通过设计层面人为地加上区分**

   - 具体实现

     > 后置++中参数列表中的 `int` 并不需要一个具体的变量名，它只是用来区分前置和后置运算符的。这个 `int` 参数的存在是为了符合运算符重载的语法要求，而它实际上并不被使用,这个参数的实际作用是作为一个占位符，告诉编译器这是后置版本的自增
     >

     ```cpp
     void test0() {
         // 以内置类型为参考
         int a = 1;
         &(++a); // OK 左值
         /* &(a++); error 右值 是个临时变量 */
     }
     
     // 前置++的形式
     Complex& operator++() {
         cout << "Complex & operator++()" << endl;
         ++m_real;
         ++m_image;
         return *this;
     }
     
     // 后置++的形式
     // 参数列表中要多加一个int，从而与前置形式进行区分（因为编译器会帮忙自动传入一个int参数）
     Complex operator++(int) {
         cout << "Complex operator++(int)" << endl;
         // 通过拷贝构造 把当前对象的数据成员初始化一个新对象
         Complex tmp(*this);
         ++m_real;
         ++m_image;
         // 返回新对象
         return tmp;
     }
     
     void test1() {
         Complex c1 = Complex{1,1};
         /* Complex c2 = ++c1; */
         Complex c2 = c1++;
         c2.print();
         c1.print();
     }
     ```

## 六、成员访问运算符 -> 的重载

1. **分析**

   - **成员访问运算符包括`.`和`->`，其中`.`这个运算符是不能重载的，`->`运算符是可以重载的**

   - 箭头访问运算符 -> 和解引用运算符 * ，它们是指针操作最常用的两个运算符

     **箭头运算符==只能以成员函数的形式重载==**，其**返回值必须是一个==指针==或者==重载了->运算符的对象==**

2. **两层结构实现**

   **==前置：自动释放资源的双层结构==**

   ```cpp
   class Data {
   public:
       Data() {}
       ~Data(){}
       int getData() const {
           return m_data;
       }
   private:
       int m_data = 10;
   };
   
   class MiddleLayer {
   public:
       MiddleLayer(Data * p)
       : m_pData(p)
       {}
   
       ~MiddleLayer() {
           if (m_pData) {
               delete m_pData;
               m_pData = nullptr;
           }
       }
   private:
       Data * m_pData;
   };
   ```

   > 注意
   >
   > 如果用这种方式创建MiddleLayer对象，我们发现不需要手动delet pdata，并没有发生内存泄露，反而手动delet pdata后会有double free的问题

   - 形式

     ```cpp
     // 成员访问运算符
     Type* operator->();
     // 解引用运算符
     Type& operator*();
     ```

   - 返回类型

     - `operator->` 必须返回一个指针，因为 `->` 运算符会继续对返回的指针进行成员访问, 编译器会自动递归调用`operator->()`直到得到原生指针

       ```cpp
       Data* operator->() {
           return m_pData;
       }
       ```

     - `operator*`的返回值通常是一个引用 (`Type&`)，这样可以允许对对象的直接修改

       ```cpp
       Data& operator*() {
           return *m_pData;
       }
       ```

   - 使用形式

     ```cpp
     void test4() {
         MiddleLayer obj = MiddleLayer{new Data()};
         // 通过MiddleLayer对象访问Data对象成员
         
         // 利用重载的->得到Data* 再利用基本的->访问Data成员
         cout << (obj.operator->())->getData()<< endl;
         // 上下等价
         cout << obj->getData() << endl;
         
         // 利用重载的*得到Data对象, 同过Data对象访问成员
         cout << obj.operator*().getData() << endl;
         // 上下等价
         cout << (*obj).getData() << endl;
         
         // 智能指针的雏形: 利用局部对象的生命周期来回收资源
     }
     ```

   - 总结

     - 重载 `*` 解引用运算符的目的是使类对象可以表现得像指针一样，通过解引用访问封装的对象

     - 重载 `*` 通常用于实现类似智能指针的类，返回内部封装对象的引用

     - 当我们完成了以上的需求后，还有一件“神奇”的事情，使用的语句中有new没有delete，但是检查发现并没有内存泄漏

       **原因：obj本身是一个局部对象，因为重载了箭头运算符和解引用运算符，所以看起来像个指针，也可以像指针一样进行使用，但是这个对象在栈帧结束时会自动销毁，自动调用析构函数回收了它的数据成员所申请的堆空间**

       **实际上，这就是智能指针的雏形：其思想就是通过对象的生命周期来管理资源**

3. ==**三层结构实现**==

   [跳转](#三层结构)

## 七、补充

1. **输出流运算符 << 重载中的问题**

   **包含对象成员的类 使用临时对象进行拷贝构造时 遇到的问题：**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class A {
   public:
       A(int a, int b)
           : m_a(a)
             , m_b(b)
       {}
       A(const A& A)
       : m_a(A.m_a)
       , m_b(A.m_b)
       {}
       friend std::ostream& operator<<(std::ostream& os, const A& a);
   private:
       int m_a;
       int m_b;
   };
   std::ostream& operator<<(std::ostream& os, const A& A) {
       os << A.m_a << " " << A.m_b;
       return os;
   }
   class B {
   public:
       B(const int& a,const A& A)
           : m_a(a)
             , m_A(A)
       {}
       friend std::ostream& operator<<(std::ostream& os, const B& B);
   private:
       int m_a;
       A m_A;
   };
   std::ostream& operator<<(std::ostream& os, const B& B) {
       os << B.m_a << " " << B.m_A;
       return os;
   }
   int main() {
       // {2, 3}是一个花括号初始化列表(列表初始化)
       // 在这里它被用来直接构造一个临时的 A 对象
       B B(1, {2, 3});
       // 为什么 B B(1, (2, 3)); 不行
       // (2, 3)是一个括号表达式，里面有一个逗号运算符。
       // 逗号运算符会依次计算2(丢弃)，然后计算3，整个表达式的值就是3
       // 所以这行代码实际上变成了：B b(1, 3);
       // 而 B 的构造函数要求第二个参数是 const A&
       cout << B << endl;
       cout << "--------" << endl;
       A A(2, 3);
       cout << A << endl;
   
       return 0;
   }
   ```

2. **运算符重载中编译器自动行为**

   **在自定义类型中遇到以下运算符就会触发的特殊操作**

   - 后置 `++`：编译器触发**传参特殊操作**（自动塞 `int`）

   - `->`：编译器触发**递归特殊操作**（自动反复调用 `operator->`）

3. **三层结构下的成员访问运算符重载，且保证资源自动回收**<a id="三层结构"></a>

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class Data {
   public:
       Data(int data)
       : _data(data)
       {}
       int getData() const {
           return _data;
       }
   private:
       int _data;
   };
   
   class MiddleLayer {
   public:
       MiddleLayer(Data * p)
       : _pdata(p)
       {}
       Data* operator->() { // 仅最内层返回对象指针
           return _pdata;
       }
       ~MiddleLayer() {
           if (_pdata) {
               delete _pdata;
               _pdata = nullptr;
           }
       }
   private:
       Data * _pdata;
   };
   
   class ThirdLayer {
   public:
       ThirdLayer(MiddleLayer * pm)
       : _pml(pm)
       {}
       MiddleLayer& operator->() { // 除了最内层其余层均返回对象而不是对象指针，
                                   // 这样能一直调用operator->()函数，而不是在当前层对象中通过->调用getData()，因为只有最内层才存在getData
           return *_pml;
       }
       ~ThirdLayer() {
           if (_pml) {
               delete _pml;
               _pml = nullptr;
           }
       }
   private:
       MiddleLayer * _pml;
   };
   
   void test() {
       /* Data* p = new Data(1); */
       /* MiddleLayer m(p); //这样的话，在ThirdLayer的析构函数中就会发生delete一个栈对象—— 未定义行为 */
       /* ThirdLayer t(&m); */
       // 除了最外层（ThirdLayer）是栈对象，其余内层对象（MiddleLayer、Data）都必须用new创建在堆上
       // 假如部分内层对象改为引用或不需要释放的指针（即析构不需要delete），则它们也可以不是堆对象，但必须保证被引用对象的生命周期长于使用它的对象
       ThirdLayer t(new MiddleLayer(new Data(111)));
       // 多层 operator-> 重载的链条中，只有"终点站"返回指针，中间的每一站都必须返回类类型的对象（或引用），才能让链条继续传递下去
       cout << t->getData() << endl;
   }
   
   int main() {
       test();
   
       return 0;
   }
   ```

   # Day11_函数对象

## 一、可调用实体

- 讲到调用这个词，我们首先能够想到**普通函数**和**函数指针**，在学习了类与对象的基础知识后，还增加了**成员函数**，那么它们都被称为<font color=red>**可调用实体**</font>。事实上，根据其他的一些不同的场景需求，**C++还提供了一些可调用实体，它们都是通过运算符重载来实现的**
- 普通函数执行时，有一个特点就是无记忆性。**一个普通函数执行完毕，它所在的函数栈空间就会被销毁，所以普通函数执行时的状态信息，是无法保存下来的**，这就让它**无法应用在那些需要对每次的执行状态信息进行维护的场景**。大家知道，我们学习了类与对象以后，**有了对象的存在，对象执行某些操作之后，只要对象没有销毁，其状态就是可以保留下来的**

## **二、函数对象**

1. **什么是函数对象**

   将重载了函数调用运算符（即以operator()**作为成员函数名**的）类创建的对象称为函数对象

   一个行为类似于函数的对象, 它的作用是在代码中能够像函数一样调用，但是它其实是一个类的实例

   ```cpp
   class FunctionObject {
       // ...
       // 重载函数调用运算符
       ReturnType operator()(ParameterList) {
           // do something....
       }
   };
   
   void test0() {
       FunctionObject fo{ };
       fo(); // 让对象像一个函数一样被调用
   }
   ```

2. **如何实现函数对象**
   上面的代码看起来很奇怪，如果我们从运算符的视角出发，就是函数调用运算符()要处理FunctionObject对象，只需要实现一个<font color=red>**函数调用运算符重载**</font>函数即可

   **函数调用运算符重载**，是一种允许对象像函数一样被调用的技术。它通过重载 `operator()` 运算符来实现，使得类的实例能够表现得像函数

   - 基本语法

     - **`ReturnType`**：函数调用返回的类型
     - **`ParameterList`**：可以是零个或多个参数，类似于普通函数
     - **函数调用运算符==必须以成员函数的形式进行重载==**

     ```cpp
     ReturnType operator()(ParameterList);
     ```

     ```cpp
     class FunctionObject {
         void operator()() {
             cout << "void operator()()" << endl;
         }
     };
     
     void test0() {
         FunctionObject fo;
         fo(); // ok
         // 本质如下
         fo.operator()();
     }
     ```

   - 形式

     <span style=color:red;background:yellow>**重载了函数调用运算符的类的对象称为函数对象**</span>，由于参数列表可以随意扩展 ，**所以可以有很多重载形式**（对应了普通函数的多种重载形式）

     ```cpp
     class FunctionObject {
     public:
         void operator()() {
             cout << "operator()" << endl;
         }
         int operator()(int x, int y) {
             cout << "operator(int, int)" << endl;
             return  x + y;
         }
         double operator()(double x, double y, double z) {
             cout << "operator(double, double, double)" << endl;
             return  x + y + z;
         }
     };
     
     void test1() {
         FunctionObject fo = FunctionObject{};
         // 函数调用运算符来处理fo对象的使用
         fo();
         cout << fo(1,2) << endl;
         cout << fo(1.1, 2, 3.3) << endl;
     }
     ```

3. **函数对象相比普通函数的优点**

   - **可以携带状态**（函数对象可以封装自己的数据成员、成员函数，具有更好的面向对象的特性）
   - **可以记录函数对象被调用的次数**，*而普通函数只能通过全局变量做到（全局变量不够安全）*
   - 除此之外，函数对象作为STL的六大组件之一而存在，可以做很多定制化的行为

   ```cpp
   class FunctionObject {
   public:
       void operator()() {
           cout << "FunctionObject operator()()" << endl;
           ++ m_count;
       }
       int operator()(int x, int y) {
           cout <<"operator()(int,int)" << endl;
           ++ m_count;
           return x + y;
       }
       int m_count = 0; // 携带状态
   };
   
   void test0(){
       FunctionObject fo;
     
       cout << fo() << endl;
       cout << fo.operator()() << endl; // 本质
   
       cout << fo(5,6) << endl;
       cout << fo.operator()(5,6) << endl; // 本质
   
       cout << "fo.m_count:" << fo.m_count << endl; // 记录这个函数对象被调用的次数
   }
   ```

   

# Day12——函数/成员函数指针&类型转换函数&嵌套类&单例对象自动释放

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
       3. 需要将控制类AutoRelease设置为所托管的单例类的友元类, 这样可以调用单例类中的private权限的析构函数——==**因为删除一个对象一定会触发它的析构函数**==

   - 源代码

       ```cpp
       // 管理者类
       class AutoRelease {
       public:
           AutoRelease(Singleton* p)
           : m_p(p)
           {
               cout << "AutoRelease(Singleton*)" << endl;
           }
           ~AutoRelease() {
               if (m_p) {
                   delete m_p; // 需要在Singleton类中将AutoReleas类声明友元类，因为Singleton类中析构函数是私有成员
                   m_p = nullptr;
               }
               cout << "~AutoRelease()" << endl;
           }
       private:
           Singleton* m_p;
       };
       ```

2. ==**嵌套类 + 静态对象**==

   - 原理

     ![image-20250225101010421](..\0.TyporaPicture\image-20250225101010421.png)

     AutoRelease类对象m_ar是Singleton类的对象成员，创建Singleton对象，就会自动创建一个AutoRelease对象（静态区），**它的成员函数可以直接访问 ms_pInstance** 或者通过类名作用域访问

     程序结束时会自动销毁全局静态区上的ms_ar，调用AutoRelease的析构函数，在这个析构函数执行delete ms_pInstance的语句，这样又会调用Singleton的析构函数，再调用operator delete，回收掉堆上的单例对象

     利用嵌套类实现了一个比较完美的方案，不用担心手动调用了destroy函数

   - 源代码

     ```cpp
     class Singleton {
         // 内部类
         class AutoRelease {
         public:
             AutoRelease() {
                 cout << "AutoRelease()" << endl;
             }
     
             ~AutoRelease() {
                 if (m_pInstance) { // 内部类中可直接访问外部类的静态成员
                     delete m_pInstance;
                     m_pInstance = nullptr;
                 }
                 cout << "~AutoRelease()" << endl;
             }
         };
     public:
         static Singleton* getInstance() {
             if (!m_pInstance) {
                 m_pInstance = new Singleton();
             }
             return m_pInstance;
         }
         Singleton(const Singleton&) = delete;
         Singleton& operator=(const Singleton&) = delete;
         // 管理类中删除Singleton单例对象时一定会触发~Single()，而它是私有成员
         friend class AutoRelease; // 本身就可以作为一个类的前向声明
     private:
         Singleton() {}
         ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                         // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
         static Singleton* m_pInstance;
         static AutoRelease m_autoRelease; // 内部类对象作为外部类成员 静态对象
     };
     Singleton* Singleton::m_pInstance = nullptr;
     Singleton::AutoRelease Singleton::m_autoRelease; // 调用了AutoRelease的无参构造函数
     ```

3. **`atexit + destroy`**

   - 原理

     - 很多时候需要在程序退出的时候做一些诸如释放资源的操作，但程序退出的方式有很多种，比如main()函数运行结束、在程序的某个地方用exit()结束程序、用户通过Ctrl+C操作来终止程序等等

     - 所以需要有一种与程序退出方式无关的方法来进行程序退出时的必要处理——用atexit函数来注册程序正常终止时要被调用的函数（C/C++通用）

     - **注册函数的调用顺序:** 如果注册了多个函数，先注册的后执行

       ![image-20241129171136336](..\0.TyporaPicture\image-20241129171136336.png)

     - atexit注册了destroy函数，相当于有了一次必然会进行的destroy（程序结束时)，即使手动调用了destroy，因为安全回收的机制，也不会有问题

   - 源代码

     ```cpp
     class Singleton {
     public:
         // 由于这是单例模式，所以构造函数是万万不能重载的
         /* Singleton() { */
         /*     cout << "Singleton()" << endl; */
         /* } */
         static Singleton* getInstance() {
             if (!m_pInstance) {
                 m_pInstance = new Singleton();
                 /* atexit(destroyInstance); // right */
                 atexit(&destroyInstance); // 注册几次，程序结束时调用几次
             }
             return m_pInstance;
         }
         static void destroyInstance() {
             if (m_pInstance) {
                 delete m_pInstance;
                 m_pInstance = nullptr;
             }
             cout << "destroyInstance()" << endl;
         }
         Singleton(const Singleton&) = delete;
         Singleton& operator=(const Singleton&) = delete;
     private:
         Singleton() {}
         ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                         // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
         static Singleton* m_pInstance;
     };
     Singleton* Singleton::m_pInstance = nullptr; // 懒加载
     /* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */
     ```

   > 但是还遗留了一个问题，就是以上几种方式都无法解决<font color=red>**多线程安全**</font>问题。
   >
   > 以方式三为例，当多个线程同时进入if语句时，会造成单例对象被创建出多个，但是最终只有一个地址值会由ms_pInstance指针保存，因此造成内存泄漏
   >
   > 可以使用<font color=red>**饿汉式解决**</font>，但同时也可能带来内存压力（即使不用单例对象，也会被创建）
   >
   > ```cpp
   > // 对于ms_pInstance的初始化有两种方式
   > // 饱汉式（懒汉式）—— 懒加载，不使用到该对象，就不会创建
   > Singleton* Singleton::ms_pInstance = nullptr; 
   > // 饿汉式 —— 最开始就创建（即使不使用这个单例对象）
   > Singleton* Singleton::ms_pInstance = Singleton::getInstance();
   > ```
   >
   > **饿汉式**可以确保getInstance函数的第一次调用一定是在ms_pInstance的初始化时，之后再调用getInstance函数的时候,都不会进入if分支创建出对象
   >
   > 同时，还有一个要考虑的问题——如果多线程环境下手动调用了destroy函数，那么又会让ms_pInstance变为空指针，之后再调用getInstance函数还是有可能造成内存泄露——**故而应该将destroy函数私有**

4. **`atexit + pthread_once + destroy`**

   Linux平台可以使用的方法（能够保证创建单例对象时的多线程安全）
   
   - 原理
   
     - pthread_once函数可以确保初始化代码只会执行一次, 无论在多少个线程中调用它
   
       ![image-20241129171227277](..\0.TyporaPicture\image-20241129171227277.png)
   
     - 传给pthread_once函数的参数：
       1. 第一个参数比较特殊，形式固定
       2. 第二个参数需要是一个`静态函数指针`，pthread_once可以确保这个函数只会执行一次
   
   - 注意
   
     - 如果手动调用initRoutine创建对象，没有通过getInstance创建对象，实际上绕开了pthread_once的控制，必然造成内存泄露 —— <span style=color:red;background:yellow>**需要将initRoutine私有**</span>
   
     - 如果手动调用了destroy函数，之后再使用getInstance来尝试创建对象，因为pthread_once的控制效果，不会再执行init函数，所以无法再创建出单例对象。所以不能允许手动调用destroy函数
   
       同时因为会使用atexit注册destroy函数实现资源回收，所以也不能将destroy删掉，应该<span style=color:red;background:yellow>**将destroy私有**</span>，避免在类外手动调用
   
   - 源代码
   
     ```cpp
     class Singleton {
     public:
         static Singleton* getInstance() {
             /* if (!m_pInstance) */
             pthread_once(&m_once_control, &initRoute); // pthread_once可以确保这个函数只会执行一次
             return m_pInstance;
         }
         Singleton(const Singleton&) = delete;
         Singleton& operator=(const Singleton&) = delete;
     private:
         static void initRoute() {
             // 初始化只会被执行一次
             m_pInstance = new Singleton();
             atexit(&destroyInstance);
         }
         static void destroyInstance() {
             if (m_pInstance) {
                 delete m_pInstance;
                 m_pInstance = nullptr;
             }
             cout << "destroyInstance()" << endl;
         }
         Singleton() {}
         ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                         // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
         static Singleton* m_pInstance;
         static pthread_once_t m_once_control;
     };
     Singleton* Singleton::m_pInstance = nullptr; // 懒加载
     /* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */
     pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;
     ```

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

5. **单例对象自动释放的四种方式**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   // 方式一: 利用栈对象的生命周期进行自动释放
   
   class Singleton {
   public:
       static Singleton* getInstance() {
           if (!m_pInstance) {
               m_pInstance = new Singleton();
           }
           return m_pInstance;
       }
       /* static void destroyInstance() { */
       /*     if (m_pInstance) { */
       /*         delete  m_pInstance; */
       /*         m_pInstance = nullptr; */
       /*     } */
       /* } */
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
       // 管理类中删除Singleton单例对象时一定会触发~Single()，而它是私有成员
       friend class AutoRelease; // 本身就可以作为一个类的前向声明
   private:
       Singleton() {}
       ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                       // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
       static Singleton* m_pInstance;
   };
   Singleton* Singleton::m_pInstance = nullptr;
   
   // 管理者类
   class AutoRelease {
   public:
       AutoRelease(Singleton* p)
       : m_p(p)
       {
           cout << "AutoRelease(Singleton*)" << endl;
       }
       ~AutoRelease() {
           if (m_p) {
               delete m_p;
               m_p = nullptr;
           }
           cout << "~AutoRelease()" << endl;
       }
   private:
       Singleton* m_p;
   };
   
   int main() {
       AutoRelease ar(Singleton::getInstance()); // 创建管理者对象(栈对象)
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
   
       return 0;
   }
   // ----------------------------------------------------------------------------
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   // 方式二: 利用嵌套类 + 静态的内部类对象
   
   class Singleton {
       // 内部类
       class AutoRelease {
       public:
           AutoRelease() {
               cout << "AutoRelease()" << endl;
           }
   
           ~AutoRelease() {
               if (m_pInstance) { // 内部类中可直接访问外部类的静态成员
                   delete m_pInstance;
                   m_pInstance = nullptr;
               }
               cout << "~AutoRelease()" << endl;
           }
       };
   public:
       static Singleton* getInstance() {
           if (!m_pInstance) {
               m_pInstance = new Singleton();
           }
           return m_pInstance;
       }
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
       // 管理类中删除Singleton单例对象时一定会触发~Single()，而它是私有成员
       friend class AutoRelease; // 本身就可以作为一个类的前向声明
   private:
       Singleton() {}
       ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                       // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
       static Singleton* m_pInstance;
       static AutoRelease m_autoRelease; // 内部类对象作为外部类成员 静态对象
   };
   Singleton* Singleton::m_pInstance = nullptr;
   Singleton::AutoRelease Singleton::m_autoRelease; // 调用了AutoRelease的无参构造函数
   
   int main() {
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
   
       return 0;
   }
   // ----------------------------------------------------------------------------
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   // 方式三: 利用atexit() + destroyInstance()
   /*
    * atexit(函数指针): 把函数指针指向的函数注册到atexit当中
    * 参数的这个函数是一个回调函数
    * 当程序结束时, 被注册到atexit当中的函数被自动调用
    *
    * 单例的两种模式:
    * 1.懒加载(懒汉模式): 不用的时候不创建, 用的时候再创建
    * 2.立即加载(饿汉模式) : 不管用不用这个单例对象, 先把这个单例对象
    * 创建出来,用的时候给你返回
    */
   
   class Singleton {
   public:
       // 由于这是单例模式，所以构造函数是万万不能重载的
       /* Singleton() { */
       /*     cout << "Singleton()" << endl; */
       /* } */
       static Singleton* getInstance() {
           if (!m_pInstance) {
               m_pInstance = new Singleton();
               /* atexit(destroyInstance); // right */
               atexit(&destroyInstance); // 注册几次，程序结束时调用几次
           }
           return m_pInstance;
       }
       static void destroyInstance() {
           if (m_pInstance) {
               delete m_pInstance;
               m_pInstance = nullptr;
           }
           cout << "destroyInstance()" << endl;
       }
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
   private:
       Singleton() {}
       ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                       // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
       static Singleton* m_pInstance;
   };
   Singleton* Singleton::m_pInstance = nullptr; // 懒加载
   /* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */
   
   
   int main() {
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
   
       return 0;
   }
   // ----------------------------------------------------------------------------
   #include <pthread.h>    // for pthread_once
   #include <cstdlib>      // for atexit
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   // 方式四: 利用atexit() + destroyInstance() + pthread_once
   // 线程安全
   
   class Singleton {
   public:
       static Singleton* getInstance() {
           /* if (!m_pInstance) */
           pthread_once(&m_once_control, &initRoute); // pthread_once可以确保这个函数只会执行一次
           return m_pInstance;
       }
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
   private:
       static void initRoute() {
           // 初始化只会被执行一次
           m_pInstance = new Singleton();
           atexit(&destroyInstance);
       }
       static void destroyInstance() {
           if (m_pInstance) {
               delete m_pInstance;
               m_pInstance = nullptr;
           }
           cout << "destroyInstance()" << endl;
       }
       Singleton() {}
       ~Singleton() {} // 其实非必要，但这是一种防御性设计：
                       // 禁止除 AutoRelease 之外的任何代码直接 delete 单例对象
       static Singleton* m_pInstance;
       static pthread_once_t m_once_control;
   };
   Singleton* Singleton::m_pInstance = nullptr; // 懒加载
   /* Singleton* Singleton::m_pInstance = new Singleton(); // 立即加载 */
   pthread_once_t Singleton::m_once_control = PTHREAD_ONCE_INIT;
   
   int main() {
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
       cout << Singleton::getInstance() << endl;
   
       return 0;
   }
   ```



# Day13_std::string的底层实现

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

      - **CowString中operator[]重载——服务于operator[]结果的operator<< 与 operator=，==即[]是[]结果的<<与=的前提==**

        根据分析过程，**将CowString中下标访问运算符的重载函数operator[]返回结果修改为内部类对象CharProxy**

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

        因为定义的是外部类中的私有的内部类CharProxy，为了让输出流运算符能够处理CharProxy对象，所以需要将operator<<重载函数，**分别在CharProxy和CowString进行两次友元声明**

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
        // operator=，CharProxy的成员函数重载，其中this指向当前CharProxy对象
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

   这样做的好处是：**当字符串较小时，直接拷贝字符串，放在 string内部，不用获取堆空间，开销小**

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





# Day14_关联式容器-set&map

## 一、关联式容器-set——底层为红黑树

1. **特点**

   - set中存放的元素是唯一的，不能重复
   - **默认按元素进行升序排列**

2. **使用场景**

   - 去重
   - 排序

3. **set的构造**

   包含在头文件< set >，打开C++参考文档，主要关注这样的几个构造函数

   ![image-20241206105537432](..\0.TyporaPicture\image-20241206105537432.png)

   ```cpp
   // set容器的构造
   /*
   关联容器初始化最好不要使用()
   std::set<int> box(1); // error：set没有「接收单个数值」的构造，而vector(5)合法：vector有「指定元素个数」的构造
   std::set<int> box({1}); // right
   */
   void test1() {
       // 1.无参构造函数—— >空容器
       std::set<Student> box1;
       // 2.初始化列表方式
       /* std::set<Student> box2(Student{1, "zs", 18}); // error */
       /* std::set<Student> box2({Student{1, "zs", 18}}); // right */
       std::set<Student> box2{Student{1, "zs", 18}};
       // std::set<Student> box2{{1, "zs", 18}};
       std::set<Student> box{{1, "zs", 18}, {3, "ww", 20}, {2, "ls", 19}};
       // 3.拷贝构造
       std::set<Student> box3 = box2;
       // 4.迭代器方式
       std::set<Student> box4(box.begin(), box.end());
   }
   ```

4. **set的查找操作**

   1. count成员函数

      ![image-20241206115827359](..\0.TyporaPicture\image-20241206115827359.png)

      **参数key**：要查找的数据元素

      **返回值(类型size_type)**：元素数，有就返回1，没有就返回0

   2. find成员函数

      ![image-20241206115853634](..\0.TyporaPicture\image-20241206115853634.png)

      **参数key**：要查找的数据元素

      **返回值(类型iterator)**：如果找到返回对应元素的迭代器，没找到返回end()获取的迭代器

5. **set的插入操作**

   - pair

       pair定义在头文件<utility>中，类似于结构体，可以存储两种不同类型的变量

       当然，C++中结构体已经演变为了类，所以可以认为一个特定的pair是一个类，包含两个对象成员(它们的类型在定义pair时给出)

       ==**pair的对象成员如何访问**==

       ```cpp
       // pair：存储一对数据，first、second
       std::pair<string, int> p{"age", 20};
       cout << p.first << endl;
       cout << p.second << endl;
       ```
       
   - 插入单个元素

     ![image-20231031163352909](..\0.TyporaPicture\image-20231031163352909.png)

     insert函数的第一种形式中：
     **参数：key**
     **返回值：pair类型(包含一个对应set的迭代器和一个bool值)**

     插入成功：返回<span style=color:red;background:yellow>**插入元素对应迭代器  **</span> 和 <font color=red>**true**</font>
     插入失败：返回<span style=color:red;background:yellow>**阻止插入的元素(原本就有的这个元素)对应迭代器**</span> 和 <font color=red>**false**</font>
     
     ```cpp
     std::set<Student> box;
     box.insert(Student{2, "zs", 18});
     /* box.insert({2, "zs", 18}); */
     
     std::set<int> box;
     /* box.insert(100); // 重复插入就会插入失败 */
     std::pair<std::set<int>::iterator, bool> p2 = box.insert(100);
     if (p2.second) {
         cout << "insert success" << endl;
         cout << *p2.first << endl;
     } else {
         cout << "insert failed" << endl;
     }
     ```
     
   - 插入多个元素

     ![image-20241206152508731](..\0.TyporaPicture\image-20241206152508731.png)

     1. 传入大括号列表，尝试插入列表中的元素
     2. 传入两个迭代器(首迭代器和尾后迭代器)，尝试插入这两个迭代器范围中的元素；**[ , )左闭右开区间**

     ```cpp
     // 批量数据插入
     // 1.初始化列表方式
     std::set<Student> box;
     /* box.insert({1, "ls", 19}, {"3", "ww", 20}); // error */
     box.insert({{1, "ls", 19}, {3, "ww", 20}}); // right
     // 2.还可使用迭代器方式
     std::set<int> box1{10, 11, 12};
     std::set<int> box2;
     box2.insert(box1.find(11), box1.end());
     ```

6. **set的删除操作**

  ```cpp
  // set容器的数据删除：erase成员函数
  std::set<int> box{1, 2, 3, 4, 5};
  auto it = box.begin();
  it++;
  it++;
  box.erase(it); // 3被删除
  ```

## 二、关联式容器-map——底层为红黑树

1. **特点**
   - **有序容器**：`std::map` 会按照键的大小顺序对元素进行排序，==**默认按键(key)升序排序**==。如果需要降序排序，可以使用自定义比较函数
   - **唯一的键**：`std::map` 中的==**每个键(key)必须是唯一的(value无所谓)**==。如果你尝试插入一个已有键的元素，插入操作将不会成功
   - **键和值**：**每个键都会关联一个值，类型为 `pair<const Key, T>`**，其中 `Key` 是键的类型，`T` 是值的类型——即**存的是pair对象(一对数据)**
   - **自动排序**：元素会根据键(key)的顺序自动排序, 也可以自定义排序(后面学)
   - **支持迭代器**：你可以通过迭代器遍历 `map` 中的元素

2. **应用场景**

   1. 数据是 **一个键对应一个值**

   2. 需要 **通过键快速找值**

   3. 需要 **键自动排序 / 去重**

   4. 需要 **方便地修改 / 新增键值对**

3. **map的构造**

   map中**存放的元素的类型是pair类型（键值对）**，构造map需要关注三种方式，也可以把它们结合到一起

   ```cpp
   // map的构建
   void test1() {
       // 1.无参构造
       std::map<int, string> m1;
       // 2.通过初始化列表方式构造
       std::map<int, string> m2({
           std::pair<int, string>{2, "zs"},
           std::pair<int, string>{1, "ls"},
           std::pair<int, string>{3, "ww"}
       }); // ()可省略，在初始化时即构造函数中{}有()的功效
           // ！但是，不能外层是{}内层是()，这样的话只能成功插入{3, "ww"}
       // 初始化列表方式的简写形式
       std::map<int, string> m3{
           {2, "zs"},
           {1, "ls"},
           {3, "ww"}
       };
       // 3.通过make_pair创建一个pair对象，其为函数—— 所以{}替换为()
       std::map<int, string> m4{
           std::make_pair(2, "zs"),
           std::make_pair(1, "ls"),
           std::make_pair(3, "ww")
       };
       // 4.通过拷贝构造函数
       /* std::map<int,string> m5 = m4; */
       /* std::map<int,string> m5(m4); */
       std::map<int,string> m5{m4};
       // 5.通过迭代器方式构建
       /* std::map<int,string> m6{(m5.begin(), m5.end())}; // error */
       /* std::map<int,string> m6({m5.begin(), m5.end()}); // right */
       /* std::map<int,string> m6{m5.begin(), m5.end()}; // right */
       std::map<int,string> m6(m5.begin(), m5.end()); // 最标准做法
   }
   ```

4. **map的查找操作**

   根据key值在map中进行查找

   - `count`函数的返回值：如果找到返回1，如果没找到返回0（size_t类型）
   - `find`函数的返回值：如果找到返回相应元素的迭代器，如果没找到返回end( )的结果

   ```cpp
   void checkFind(map<int,string>& rhs, int key) {
       // 完整类型
       // map<int,string>::iterator it = rhs.find(key);
       // auto简化
       auto it = rhs.find(key);
       if (it != rhs.end()) {
           cout << it->first << "=" << it->second << endl;
       } else {
           cout << "not stroe" << endl;
       }
   }
   ```

5. **map的插入操作**

   ![image-20241206175902177](..\0.TyporaPicture\image-20241206175902177.png)

   - 插入单个元素

     **返回值**是一个pair（第一个对象成员是map元素相应的迭代器，第二个对象成员是bool值）

     ```cpp
     std::map<int, string> m;
     // 单个数据的插入
     /* m.insert(3, "ww"); // error */
     /* m.insert{3, "ww"}; // error */
     /* m.insert(pair<int,string>{3, "ww"}); // right */
     m.insert({3, "ww"}); // 上一行简写
     ```

   - 插入多个元素

     1. 初始化列表方式
     2. 迭代器方式

     ```cpp
     // 批量插入
     // 1.初始化列表方式
     std::map<int, string> m;
     /* m.insert({1, "zs"}, {2, "ls"}); // error */
     /* m.insert{{1, "zs"}, {2, "ls"}}; // error */
     m.insert({{1, "zs"}, {2, "ls"}}); // right
     // 2.迭代器方式
     std::map<int, string> m2;
     m2.insert(m.begin(), m.end());
     ```

6. **map的下标操作operator[]——根据key获取对应value**

   - map下标操作**返回**的是map中元素(pair)的**value**

   - **下标访问运算符中的值代表key**，而**不是传统意义上的下标**

   - 如果进行下标操作时下标值传入一个不存在的key，那么会将这个key和空的value**（默认的value值）**插入到map中

     > ```cpp
     > // map对象[不存在的键];
     > // 1.插入这个新键（key）
     > // 2.给对应的值（value）赋默认值
     > //      string 的默认值 = 空字符串 ""
     > //      int 的默认值 = 0
     > ```

   - **下标访问可以进行写操作**（**只对value进行写操作**，**不影响排序**）

> map的元素是pair(key-value)，**key和value的类型可以自由选择**，但**要保证key的类型可以进行判重和排序**
>
> ```cpp
> // key:char  value:string
> map<char,string> container2{
>     {'a',"abc"},
>     {'c',"bcd"},
>     {'d',"eee"},                                          
>     {'b',"fff"}
> };
> // 根据key访问对应value
> cout << container2['a'] << endl;
> cout << container2['b'] << endl;
> cout << container2['d'] << endl;
> ```
>
> 只有key为自定义类型时，才需要对operator<重载

## 三、补充

1. **关于[]下标访问**
   - map 是「查字典」（拼音→汉字），所以需要下标 `[]`
   - set 是「花名册」（只有名字），下标没用，所以不支持# Day15_继承

## 一、继承的基本概念

学习类和对象时，对象是基本，从对象上抽象出类。但是，世界并不是一层对象一层类那么简单，对象抽象出类，**在类的基础上可以再进行抽象，抽象出更高层次的类**

C++ 中模拟这种结构发展的方式就是**继承**，它也是**代码重用**的方式之一。通过继承，我们可以用原有类型来定义一个新类型，定义的新类型既包含了原有类型的成员，也能自己添加新的成员，而不用将原有类的内容重新书写一遍。原有类型称为**“基类”或“父类”**，在它的基础上建立的类称为**“派生类”或“子类”**

1. **基本语法**

   ```cpp
   class DerivedClass : access_specifier BaseClass {
       // Derived class members (fields and methods)
   };
   ```

   - **`DerivedClass`**：派生类（子类），继承自基类
   - **`BaseClass`**：基类（父类），提供要继承的属性和方法(即父类中成员)
   - **`access_specifier`**：访问控制符，决定基类成员在派生类中的访问权限，常见的有 `public`、`protected` 和 `private`

2. **三种继承方式**

   公有继承被称为**接口继承**

   保护继承、私有继承称为**实现继承**

   ```cpp
   class 基类
   {}；
   
   class 派生类
   : public/protected/private 基类 // 继承方式
   {};
   // 注意: 如果不写继承方式, 默认的继承方式是私有的
   ```

   如上述代码所示，有三种继承方式，其“继承效果”如图：

   ![image-20241209095350419](..\0.TyporaPicture\image-20241209095350419.png)

3. **定义一个派生类的过程**

   1. 吸收基类的成员
   2. 添加新的成员（非必须）
   3. 隐藏基类的成员（非必须）

   例如：定义一个Point3D类继承之前的Point类

   ```cpp
   class Point3D
   : public Point
   {
   public:
       Point3D(int x, int y, int z)
       : Point(x,y)
       , m_z(z)
       {
           cout << "Point3D(int*3)" << endl;
       }
   
       void display() const { // 添加新的成员函数
          	print();
           cout << m_z << endl;
       }
   private:
       int m_z; // 添加新的数据成员
   };
   ```

   如果**定义一个派生类只写了继承关系**，没有写任何的自己的内容，那么也会吸收基类的成员，这个情况叫做**空派生类**（其目的是在特定的场景建立继承关系，为将来的拓展留出空间）

4. **三种继承方式的访问权限**

   ![image-20241209152750803](..\0.TyporaPicture\image-20241209152750803.png)

   - 总结

     1. 不管什么继承方式，**==派生类内部==都不能访问基类的私有成员**，其他的**都可以访问(公有成员与保护成员)**
     2. 不管什么继承方式，**派生类**对象**在==类外==只能访问公有继承基类中的公有成员**，其他的都不能访问

   - <span style=color:red;background:yellow>**保护继承protected和私有继承private之间有什么区别呢？**</span>

     - protected：无限继承
     - private：继承一次就终止

     ```cpp
     class A { 
     public: 
         int m_a;
     };
     
     class B
     : private A
     {
         public:
         int m_b;
     };
     
     class C
     : private B
     {
         void func() {
             m_a; // error，底层派生类无法访问最顶层基类的成员m_a
             m_b; // Ok     底层派生类可以访问直接基类的非private成员m_b
         }
     };
     ```

5. **继承关系的局限性（即什么不能被继承）**

   - 创建、销毁的方式不能被继承——**构造、析构**

   - 复制控制的方式不能被继承——**拷贝构造函数、赋值运算符函数**

   - 友元不能被继承（**友元**破坏了封装性，为了降低影响，不允许继承）

## 二、单继承

1. **简单的单继承结构**

   ```cpp
   class A {
   public:
       int m_num1;
   private: 
       int m_num2;
   };
   
   class B
   /* : public A */
   : private A
   {
   public:
       int m_num3;
   };
   void test1() {
       B b{};
       cout << "size="<< sizeof(b) << endl; // 12
   }
   ```

   - **由上述代码可以推断出：**

     派生类对象中有基类数据成员部分和派生类自己定义的数据成员部分

   - **可以得到派生类对象的内存结构：**

     ![image-20241209152903966](..\0.TyporaPicture\image-20241209152903966.png)

2. <span style=color:red;background:yellow>**派生类对象的创建**</span>

   派生类继承基类后，可以通过派生类对象去访问基类中的成员，实现成员的复用，而成员是依赖于对象的，所以**(派生类对象创建)在这个过程中一定有基类对象的创建**

   但是，创建派生类对象时，先调用基类构造函数，再调用派生类构造函数，这样的说法是错误的，而是**先调用派生类构造函数，然后再先调用默认无参的基类构造函数**

   ```cpp
   class Base {
   public:
       // no args constructor
   	Base() {
           cout << "Base()" << endl;
       }
       // arg constructor
       Base(long num)
       : m_base(num)
       {
           cout << "Base arg constructor" << endl;
       }
   private:
   	long m_base;
   };
   
   class Derived : public Base {
   public:
   	Derived(long derived)
       /* : Base()  //显式调用Base的默认无参构造 */
   	/* , m_derived(derived) */
       /* ： Base(derived) //显式调用Base的有参构造函数*/
       : m_derived(derived) // 默认自动调用Base的无参构造函数
   	{ 
           cout << "Derived(long)" << endl; 
       }
   	long m_derived;
   };
   
   void test1() {
       Derived d{1};
   }
   ```

   - <span style=color:red>**创建派生类对象时调用基类构造的机制**</span>

     1. 当**派生类中没有显式调用基类构造函数时**，会**自动调用基类的默认无参构造**（**或者所有参数都有默认值的有参构造**）
     2. **此时如果基类中没有默认无参构造**，Derived类的构造函数的初始化列表中**也没有显式调用基类构造函数**，编译器**会报错**
     3. 当派生类对象调用基类构造时，**希望使用非默认的基类构造函数**，**必须显式地在初始化列表中写出**

     > ==**注意**==
     >
     > - **显式调用基类构造函数**，写的是**基类类名**
     > - **显式调用对象成员的构造函数**，写的是**对象成员的名字**

   - <font color=red>**创建派生类对象时, 构造函数的调用顺序：**</font>

     创建派生类对象会立刻调用派生类的构造函数，但在初始化列表的最开始调用的是基类的构造函数

     1. 完成**派生类对象所占空间的开辟**，由*系统在调用构造函数时自动完成*
     2. **调用基类的构造函数**，完成从基类继承的数据成员的初始化
     3. 若**派生类中含对象成员，const成员或引用数据成员，则必须在初始化列表中完成其初始化初始化**
     4. **执行派生类构造函数的函数体**

3. <span style=color:red;background:yellow>**派生类对象的销毁**</span>

   当**派生类析构函数执行完毕之后**，会**自动调用基类析构函数**，完成基类部分所需要的销毁（回收数据成员申请的堆空间资源），**这和执行构造函数时的顺序正好相反(创建时则是先执行基类构造函数，再执行派生类构造函数)**

   考虑对象成员时，继承机制下<font color=red>**销毁派生类对象时, 析构函数的调用顺序：**</font>

   1. 先调用派生类的析构函数
   2. 再调用派生类中对象成员的析构函数
   3. 最后调用基类的析构函数

4. **基类成员的隐藏**

   - 基类数据成员的隐藏

     - 派生类中声明了和基类的数据成员同名的数据成员，就会对基类的这个数据成员**形成隐藏**，无法通过派生类对象**直接**访问基类的这个数据成员

         ```cpp
         class Base {
         public:
             Base(long x)
             : m_base(x)
             {
                 cout << "Base()" << endl; 
             }
         
             long m_data = 100;
         private:
             long m_base;
         };
         
         class Derived : public Base {
         public:
             Derived(long base,long derived)
             : Base(base)//创建基类子对象
             , m_derived(derived)
             {
                 cout << "Derived()" << endl;
             }
         
             long m_data = 19;
         private:
             long m_derived;
         
         };
         
         void test0() {
             Derived dd(1,2);
             cout << dd.m_data << endl; // 直接访问
             // 使用基类类名+作用域限定符进行访问
             cout << dd.Base::m_data << endl; // 间接访问
         }
         ```

     - <span style=color:red;background:yellow>**隐藏不代表改变了基类的这个数据成员**</span>

         从内存的角度上也能验证：

         ![image-20241209170336940](..\0.TyporaPicture\image-20241209170336940.png)
   
         如果一定要访问基类的这个数据成员，需要加上作用域——`派生类对象.基类::同名数据成员`
         <font color=red>**但是这种写法不符合面向对象的原则，不推荐实际使用**</font>
   
   - 基类成员函数的隐藏
   
     **当派生类声明了与基类同名的成员函数时**，只要名字相同，**即使参数列表不同，也只能看到派生类部分的**，无法通过派生类对象**直接调用**基类的同名函数
   
     <span style=color:red;background:yellow>**派生类对基类的成员函数构成隐藏，只需要派生类中定义一个与基类中成员函数同名的函数即可（函数的返回类型、参数情况都可以不同，依然能隐藏）**</span>
   
     如果一定要调用基类的这个成员函数，需要加上作用域——`派生类对象.基类::同名成员函数()`
     但是这种写法不符合面向对象的原则，不推荐实际使用

## 三、多继承

C++ 除了支持单继承外，还支持多重继承

因为在客观现实世界中，我们经常碰到一个人身兼数职的情况，如在学校里，一个同学可能既是一个班的班长，又是学生中某个部门的部长；在创业公司中，某人既是软件研发部的 CTO ，又是财务部的 CFO ；一个人既是程序员，又是段子手。诸如此类的情况出现时，单一继承解决不了问题，就可以采用多基继承，例如：

![image-20241209181049480](..\0.TyporaPicture\image-20241209181049480.png)

1. **多重继承的派生类对象的构造和析构**

   - **多继承的定义方式**

       ~~~cpp
       class A {
       public:
           A() {
               cout << "A()" << endl; 
           }
           ~A() {
               cout << "~A()" << endl; 
           }
           void print() const {
               cout << "A::print()" << endl;
           }
       };
       
       class B {
       public:
           B()
           {
               cout << "B()" << endl; 
           }
           ~B()
           {
               cout << "~B()" << endl; 
           }
           void show() const
           {
               cout << "B::show()" << endl;
           }
       };
       
       class C {
       public:
           C() {
               cout << "C()" << endl; 
           }
           ~C() {
               cout << "~C()" << endl; 
           }
           void display() const {
               cout << "C::display()" << endl;
           }
       };
       
       class D
       : public A
       , B
       , C
       {
       public:
           D() {
               cout << "D()" << endl;
           }
           ~D() {
               cout << "~D()" << endl;
           }
           //void print() const {
           //    cout << "D::print()" << endl;
           //}
       };
       
       void test() {
           D d;
           d.print();
           //d.show(); //error
           //d.display(); // error
       }
       ~~~

       <font color=red>**如果这样定义，那么D类公有继承了A类，但是对B/C类采用的继承方式是默认的private**</font>，如果想要公有继承A/B/C三个类，则：

       ```cpp
       class D
       : public A
       , public B
       , public C
       {
       public:
           D() { 
               cout << "D()" << endl;
           }
           ~D() {
               cout << "~D()" << endl;
           }
       };
       ```
       
   - **此结构下创建D类对象时，这四个类的构造函数调用顺序：**

       立刻调用D类的构造函数，在此过程中会根据继承的声明顺序，依次调用A、B、C的构造函数，创建出这三个类的基类子对象

   - **D类对象销毁时，这四个类的析构函数调用顺序：**

       立刻调用D类的析构函数，析构函数执行完后，按照继承的声明顺序的逆序，依次调用C、B、A的析构函数

2. **多重继承可能引发的问题**

   - 成员名冲突的**访问二义性**

      ![image-20231102131820080](..\0.TyporaPicture\image-20231102131820080.png)

      ```cpp
      class A {
      public:
          A() {
              cout << "A Constructor" << endl;
          }
          ~A() {
              cout << "A Destructor" << endl;
          }
          void print() const {
              cout << "A print()" << endl;
          }
      };
      
      class B {
      public:
          B() {
              cout << "B Constructor" << endl;
          }
          ~B() {
              cout << "B Destructor" << endl;
          }
          
          void print() const {
              cout << "B print()" << endl;
          }
      };
      
      class C {
      public:
          C() {
              cout << "C Constructor" << endl;
          }
          ~C() {
              cout << "C Destructor" << endl;
          }
          void print() const {
              cout << "C print()" << endl;
          }
          int m_b
      };
      
      class D
      : public A
      , public B
      , public C
      {
      public:
          D() {
              cout << "D Constructor" << endl;
          }
          ~D() {
              cout << "D Destructor" << endl;
          }
          /* void print() const
          {
              cout << "D print()" << endl;
          } */
      };
      
      // 多继承的二义性    
      void test3() {
          D d{};
          /* d.print(); // error: 成员名访问冲突*/
          // member 'print' found in multiple base classes of different types
          // 通过类名::作用域方式解决冲突 , 指明调用是哪个基类的方法
          d.A::print();
          d.B::print();
          d.C::print();
      }
      ```
   
      解决成员名访问冲突的方法：**加类作用域（不推荐）**—— 应该尽量避免
   
      同时，<span style=color:red;background:yellow>**如果D类中声明了同名的成员，可以对基类的这些成员造成隐藏效果**</span>，那么就可以直接通过成员名进行访问
   
      ```cpp
          D d;
          d.A::print();
          d.B::print();
          d.C::print();
          d.print(); // ok
      ```
   
   - ==**存储二义性**==
   
      - 菱形(diamond)继承结构
   
        一个派生类同时继承两个直接基类，而这两个直接基类又共同继承自同一个间接基类
      
        ```cpp
        class A {
        public:
            void print() const{
                cout << "A::print()" << endl;
            }
            double m_a;
        };
        
        class B : public A {
        public:
            double m_b;
        };
        
        class C : public A {
        public:
            double m_c;
        };
        
        class D
        : public B
        , public C
        {
        public:
            double m_d;
        };
        ```
   
        ![image-20241209210610186](..\0.TyporaPicture\image-20241209210610186.png)
   
        菱形继承情况下，D类对象的创建会生成一个B类子对象，其中包含一个A类子对象；还会生成一个C类子对象，其中也包含一个A类子对象
   
        所以D类对象的内存布局中有多个A类子对象，访问继承自A的成员时会发生二义性**（无论是否涉及A类的数据成员，单纯访问A类的成员函数也会冲突）**
   
        因为编译器需要通过基类子对象去调用，但是不知道应该调用哪个基类子对象的成员函数，除非使用作用域限定符::
   
        **报错信息：**
   
        `non-static member 'print' found in multiple base-class subobjects of type 'A'`
   
        ![image-20241209211442119](..\0.TyporaPicture\image-20241209211442119.png)
   
        当然，D类如果再写一个同名成员函数，会发生隐藏
   
      - <span style=color:red;background:yellow>**解决存储二义性的方法：中间层的基类采用虚继承顶层基类的方式解决存储二义性**</span>
      
        ```cpp
        class A {
        public:
            void print() const{
                cout << "A::print()" << endl;
            }
            double m_a;
        };
        
        class B : virtual public A {
        public:
            double m_b;
        };
        
        class C : virtual public A {
        public:
            double m_c;
        };
        
        class D
        : public B
        , public C
        {
        public:
            double m_d;
        };
        ```
   
        ![image-20241209211645768](..\0.TyporaPicture\image-20241209211645768.png)
   
        采用虚拟继承的方式处理菱形继承问题，实际上改变了派生类的内存布局。**B类和C类对象的内存布局中多出一个虚基类指针，位于所占内存空间的起始位置，同时继承自A类的内容被放在了这片空间的最后位置**。D类对象中**只会有一份A类的基类子对象**
   
        ![image-20241209211855786](..\0.TyporaPicture\image-20241209211855786.png)
      
        > 通过VS验证，查看D类的内存布局：
        >
        > <img src="..\0.TyporaPicture\image-20240527165621041.png" alt="image-20240527165621041" style="zoom:67%;" />
        >
        > <img src="..\0.TyporaPicture\image-20240527165649690.png" alt="image-20240527165649690" style="zoom:67%;" />
        >
        > <img src="..\0.TyporaPicture\image-20240527165713475.png" alt="image-20240527165713475" style="zoom:67%;" />
        >
        > <img src="..\0.TyporaPicture\image-20240527165747487.png" alt="image-20240527165747487" style="zoom:67%;" />
        >
        > 
        >
        > 验证得到的结果：
        >
        > <img src="..\0.TyporaPicture\image-20240527165747487.png" alt="image-20250227182206756" style="zoom:50%;" />


## 四、基类与派生类之间的转换

**一般情况下，基类对象占据的空间小于派生类对象**

1. **问题引入**

   - 可否把一个基类对象赋值给一个派生类对象？可否把一个派生类对象赋值给一个基类对象？
   - 可否将一个基类指针指向一个派生类对象？可否将一个派生类指针指向一个基类对象？
   - 可否将一个基类引用绑定一个派生类对象？可否将一个派生类引用绑定一个基类对象？

   ```cpp
   Base base; // class Derived : public Base {};
   Derived d1;
   
   base = d1; // ok
   d1 = base; // error
   
   Base* pbase = &d1; // ok
   Derived * pderived = &base // error
       
   Base& rbase = d1; // ok
   Derived& rderived = base; // error
   ```

2. **向上转型**

   以上三个ok的操作，叫做向上转型（往基类方向就是向上），==**向上转型完全可行**==

   **体现派生类向基类的转型**

   - 用基类对象接受派生类对象的赋值（ok）
   - 用基类引用绑定派生类对象（ok）
   - 用基类指针指向派生类对象（ok）

   **反之，基类向派生类转型称为向下转型，==直接进行向下转型==都会==报错==**

3. **向下转型**

   - 向下转型有风险——以指针为例

     ![image-20241210105102397](..\0.TyporaPicture\image-20241210105102397.png)

     - 派生类指针指向基类对象，除了操纵基类对象的空间，还需要操纵一片空间，但是这片空间对于此指针来说是非法空间，所以会报错

     - 而基类指针指向派生类对象，派生类对象中存在一个Base类的基类子对象，这个基类指针所能操纵只有继承自基类的部分，所以不会出现问题

     ```cpp
     Base* pBase = &d1;
     // pBase指向派生类对象, 实际是指向派生类对象中的基类子对象部分 也只能访问该部分 而不能访问派生类扩展的部分
     pBase->print(); // 基类部分的结果
     ```

     <span style=color:red;background:yellow>**补充：**</span>

     - 基类对象和派生类对象之间的转换没有太大的意义
     - **基类指针指向派生类对象（基类引用绑定派生类对象）重点掌握，只能访问到基类的部分**

   - <font color=red>**有些场景下，向下转型是合理的，可以使用dynamic_cast来进行转换，如果属于合理情况，可以转换成功**</font>

     1. 基类向派生类的转型合理的例子

        ```cpp
        Base base;
        Derived d1;
        
        Base * pbase = &d1;
        // Derived * pderived = pbase; // 这种转型是合理的，但是也不能直接转型，直接想通过隐式转换仍然会报错
        Derived * pd = dynamic_cast<Derived*>(pbase); // right
        ```

        这种转型合理的原因如图：

        ![image-20241210113529514](..\0.TyporaPicture\image-20241210113529514.png)

        注意：在使用dynamic_cast时还<span style=color:red;background:yellow>**需要有多态的内容**</span>，我们需要加上一个虚函数

     2. 不合理的转换实例

        ```cpp
        // pbase本身是指向一个Base对象的，所以不能向下转换
        // 此时dynamic_cast会返回一个空指针
        void test1(){
            Base base(1);
            Bas* pbase = &base; 
        
            Derived* pd = dynamic_cast<Derived*>(pbase);
            if (pd) {
                cout << "转换成功" << endl;
                pd->display();
            } else {
                cout << "转换失败" << endl;
            }
        }
        ```

4. <span style=color:red;background:yellow>**结论：**</span>

   **可以用派生类对象赋值给基类对象（用基类对象接受派生类对象的赋值）**
   **可以用基类指针指向派生类对象，可以用基类引用绑定派生类对象**

   **反之均不可**

## 五、派生类对象间的复制控制

<font color=red>**复制控制函数就是：拷贝构造函数、赋值运算符函数**</font>

1. **原则**

   - ==基类部分与派生类部分要单独处理==

     - **当派生类中没有显式定义复制控制函数时，就会自动完成基类部分的复制控制操作**

       > 如果派生类中没有指针数据成员，不需要显式写出复制控制函数。<font color=red>**编译器会自动进行基类部分的复制控制**</font>

     - **当派生类中有显式定义复制控制函数时，不会再自动完成基类部分的复制控制操作，需要显式地调用**

     ![image-20241210114804352](..\0.TyporaPicture\image-20241210114804352.png)

     **对于拷贝构造**

     如果**显式定义**了派生类的拷贝构造，在其中**不去显式调用**基类的拷贝构造，那么无法通过复制初始化基类的部分，只能**尝试用基类无参构造**初始化基类的部分。**如果基类没有无参构造，编译器就会报错**

     **对于赋值运算符函数**

     如果显式定义了派生类的赋值运算符函数，在其中不去显式调用基类的赋值运算符函数，那么基类的部分没有完成赋值操作

   - **编译器自动完成基类部分复制工作的示例**

     如下，**派生类对象没有指针成员申请堆空间**，**不需要显式定义**拷贝构造函数和赋值运算符函数。**编译器会自动完成基类部分的复制工作**

     如果在**基类中显式写出了复制控制的函数**，**就需要显式地调用**基类的复制控制函数

     > 如果只是Base类的数据成员申请了堆空间，那么Base类的复制控制函数必须显式定义，Derived类自身的数据成员如果没有申请堆空间，不用显式定义复制控制函数

2. **派生类的拷贝构造函数**

   - 如果给Derived类中添加一个char* 成员，依然**不显式定义Derived的复制控制函数**

     那么进行派生类对象的复制时，基类的部分会完成正确的复制，**派生类的部分只能完成浅拷贝(因为编译器默认提供的拷贝构造函数是浅拷贝)**（最终对象销毁时导致double free问题）

   - 如果接下来**给Derived类、Base类显式定义了拷贝构造**，**但是没有在这个拷贝构造中显式调用==基类==的拷贝构造**（**或没有写任何的基类子对象的创建语句**），会**直接报错**

     > 详细解释：在派生类的构造函数的初始化列表中没有显式调用基类的任何的构造函数，编译器会自动调用基类的无参构造，此时基类没有无参构造，所以报错

     因为没有初始化d2的基类子对象（**只有编译器默认提供的派生类拷贝构造函数才会==自动调用==基类的拷贝构造函数**），所以编译器在这时会自动调用无参构造（但是这时不存在无参构造，即使存在基类子对象也无法完成成功拷贝），<font color=red>**所以需要在derived的拷贝构造函数中显式调用Base的拷贝构造**</font>

     ```cpp
     Derived(const Derived& rhs)
     : Base(rhs) // 显式调用Base的拷贝构造
     , m_derived(new char[strlen(rhs.m_derived) + 1]{})
     {
         cout << "Derived(const Derived& rhs)" << endl;
         // 深拷贝
         strcpy(m_derived, rhs.m_derived);
     }    
     ```

3. **派生类的赋值运算符函数**

   如果给Derived显式定义赋值运算符函数，但是没有在其中显式调用基类的赋值运算符函数

   那么基类的部分不会自动完成复制，<font color=red>**需要在Derived的赋值运算符函数中显式调用Base的赋值运算符函数**</font>，才能完成正确的复制

4. **总结**

   **给Derived类==手动定义==复制控制函数，注意在其中==显式调用==相应的基类的复制控制函数**

   **（注意：派生类对象进行复制时一定会==立刻调用==派生类的复制控制函数，在进行复制时会==首先复制==基类的部分，此时调用基类的复制控制函数）**

   ```cpp
   Derived(const Derived& rhs)
   : Base(rhs) // 显式调用基类的拷贝构造
   , m_derived(new char[strlen(rhs.m_derived) + 1]())
   {
       strcpy(m_pderived, rhs.m_derived);
       cout << "Derived(const Derived&)" << endl;
   }
   
   Derived& operator=(const Derived& rhs) {
       cout << "Derived & operator=(const Derived&)" << endl;
       if (this != &rhs) {
           // 显式调用基类的赋值运算符函数
           Base::operator=(rhs); // 关键，涉及到派生类向基类的类型转换
           delete [] m_derived;
           m_derived = new char[strlen(rhs.m_derived) + 1]();
           strcpy(m_derived,rhs.m_derived);
           m_derived = rhs.m_derived;
       }
       return *this;
   }
   ```

## 六、补充

1. <span style=color:red;background:yellow>**常考题总结**</span>

   - **派生类在类之外对于基类成员的访问，具有什么样的限制？**

     只有公有继承自基类，且对于public成员，才可以**通过派生类对象**直接访问，其他情况一律都不可以进行访问

   - **派生类在类内部对于基类成员的访问，具有什么样的限制？**

     对于基类的私有成员，不管以哪种方式继承，在**派生类内部**都不能访问

     对于基类的非私有成员，不管以哪种方式继承，在**派生类内部**都可以访问

   - **保护继承和私有继承的区别？**

     如果继承层次中都采用的是**保护继承**，**任意层次都可以访问顶层基类的非私有成员**

     但如果采用**私有继承**之后，这种**特性会被打断**

2. **继承关系的本质**

   继承关系本质上是一个**子类B IS 父类A**的关系，即**把子类当作父类使用**。苹果是水果，狗是动物；但是反过来说就不行，**不能把父类当作子类使用**

# Day16_多态

## 一、多态&虚函数

1. **什么是多态**

   **多态**（ polymorphism ）是**面向对象设计语言的基本特征**之一

   仅仅是将数据和函数捆绑在一起，进行类的**封装**，使用一些简单的**继承**，还不能算是真正应用了**面向对象的设计思想**。**多态是面向对象的精髓**。多态可以简单地概括为“**一个接口，多种方法**”，即同一操作作用于不同对象时，产生不同的行为。比如说：警车鸣笛，普通人反应一般，但逃犯听见会大惊失色，拔腿就跑

   通常是指对于同一个消息、同一种调用，在不同的场合，不同的情况下，执行不同的行为

2. **为什么需要多态性** 

   - **代码复用与简化**

     多态通过允许在父类接口下操作不同的子类对象，避免了重复编写针对不同类型对象的处理代码。在没有多态的情况下，我们可能需要为每个对象类型写不同的函数版本，而多态允许我们用统一的接口来处理所有类型的对象，从而减少了代码冗余。`复用`

   - **代码的可扩展性与灵活性**

     多态使得系统可以容易地进行扩展。你可以通过增加新的子类来扩展系统功能，而不必修改现有代码。当系统中增加新的类时，现有的代码能够自动适应新的子类，而无需修改调用它们的函数。`扩展`

   - **支持抽象化与接口统一**

     多态使得我们能够创建抽象的接口，通过这些接口，程序可以统一地处理不同的对象。在基类中声明虚函数或抽象方法后，派生类只需要实现这些方法，就能通过统一的接口进行调用。`统一标准`

   - **提高代码的可维护性**

     由于多态允许通过统一的接口处理不同类型的对象，因此系统的各个部分变得更加解耦。每个对象负责自己的行为，而不是依赖外部的控制代码来做出决定。这种分离关注点的方式使得代码更容易理解、修改和扩展。`解耦`

3. **多态性的两种形式**

   <span style=color:red;background:yellow>**C++支持两种多态性：编译时多态和运行时多态**</span>

   > ==**静态联编 = 编译期**就确定调用哪个函数的代码==
   >
   > ==**动态联编 = 运行时**才确定调用哪个函数的代码==

   1. **编译时多态**

      也称为静态多态，我们之前学习过的**函数重载**、**运算符重载**就是采用的静态多态，C++编译器根据传递给函数的参数和函数名决定具体要使用哪一个函数，不依赖于对象的实际类型，又称为==**静态联编**==

   2. **运行时多态**

      在一些场合下，编译器无法在编译过程中完成联编，必须在程序运行时完成选择，因此编译器必须提供这么一套称为“动态联编”（dynamic binding）的机制，也叫动态多态，在运行阶段，根据对象的实际类型决定调用哪个函数，实现动态绑定。<font color=red>**C++通过虚函数来实现动态联编**</font>。接下来，我们提到的多态，不做特殊说明，指的就是<font color=red>**动态多态**</font>

4. **虚函数**

   > **基类中显式声明的 `virtual` 函数 → 一定是虚函数**
   >
   > **派生类中对基类虚函数的「正确重写（Override）」→ 自动成为虚函数**（无论派生类是否重复写 `virtual` 关键字）

   ==**(非静态)成员函数**==在==**类内声明时**==，函数声明前面加上virtual关键字，该函数就成为**虚函数** 

   示例：基类和派生类中定义了同名的display函数

   ```cpp
   class Base {
   public:
   	Base() {
           cout << "Base()" << endl;
       }
   	Base(long num)
       : m_base(num)
       {
           cout << "Base arg constructor" << endl;
       }
       ~Base() {
           cout << "Base destructor" << endl;
       }
       void display() const {
       // virtual void display() const { // 虚函数版本
           cout << "Base::display()" << endl;
       }
   private:
   	long m_base;
   };
   
   
   class Derived : public Base {
   public:
   	Derived(long base, long derived)
       : Base(base) // 不显示调用的话，自动调用Base的默认无参构造
   	, m_derived(derived)
   	{ 
           cout << "Derived constructor" << endl; 
       }
       ~Derived() {
           cout <<"Derived destructor" << endl;
       }
       void display() const {
           cout << "Derived::display()" << endl;
       }
   private:
   	long m_derived;
   };
   
   // 参数为基类型的指针
   void print(Base* pBase) {
       // 基类指针可以指向基类对象
       // 基类指针也可以指向派生类对象
       pBase->display();
   }
   
   void test0() {
       Base base(10);
       Derived dd(1,2);
   
       print(&base);
       cout << endl;
       // 用一个基类指针指向派生类对象
       // 能够操纵的只有基类部分
       print(&dd);
       
       cout << "sizeof(Base):" << sizeof(Base) << endl;
       cout << "sizeof(Derived):" << sizeof(Derived) << endl;
   }
   ```

   - **结果**

       ```cpp
       Base::display()
       Base::display()
       sizeof(Base):8
       sizeof(Derived):16
       ```

   - **若是给Base中的display函数加上virtual关键字修饰，得到的结果**

       ```cpp
       Base::display()
       Derived::display()
       sizeof(Base):16
       sizeof(Derived):24
       ```

       从运行结果中我们发现，virtual关键字加入后，发生了一件“奇怪”的事情 —— 用基类指针指向派生类对象后，**通过这个基类对象竟然可以调用派生类的成员函数**。而且，**基类和派生类对象所占空间的大小都改变了，说明其内存结构发生了变化**

   - **内存结构变化**

       ![image-20241211102255253](..\0.TyporaPicture\image-20241211102255253.png)

## 二、虚函数的实现原理

1. **虚函数指针**

   - 当Base的display函数加上了virtual关键字，变成了一个虚函数，Base对象的存储布局就改变了。在存储的开始位置会多加一个虚函数指针，<span style=color:red;background:yellow>**该虚函数指针指向一张虚函数表**</span>（简称虚表），其中存放的是虚函数的入口地址

   - Derived继承了Base类，那么创建一个Derived对象，依然会创建出一个Base类的基类子对象

     - 若是没有在Derived中定义display函数

       ![image-20241211103810170](..\0.TyporaPicture\image-20241211103810170.png)

     - 若是在Derived类中又定义了display函数，则触发了==**覆盖机制**==（override），<font color=red>**覆盖的是虚函数表中虚函数的入口地址**</font>

       ![image-20241211103827119](..\0.TyporaPicture\image-20241211103827119.png)

       Base* p 去指向Derived对象，<font color=red>**依然只能访问到基类的部分**</font>。用**指针p去调用display函数，发现是一个虚函数**，那么会<font color=red>**通过vfptr找到虚表**</font>，此时虚表中存放的是Derived::display的入口地址，所以调用到Derived的display函数

2. **虚函数的覆盖——override**

   如果**一个基类的成员函数定义为虚函数**，那么它在所有派生类中也保持为虚函数，**即使在派生类中重定义的函数省略了virtual关键字，也仍然是虚函数**。虚函数一般用于灵活拓展，所以需要派生类中对此虚函数进行覆盖。

   - **覆盖的格式**有一定的要求：

     - 与基类的虚函数有相同的函数名

     - 与基类的虚函数有相同的参数个数

     - 与基类的虚函数有相同的参数类型

     - 与基类的虚函数有相同的返回类型

     即同名函数，需要长的一模一样

     我们在派生类中对虚函数进行覆盖时，很有可能写错函数的形式（函数名、返回类型、参数个数），等到要使用时才发现没有完成覆盖。这种错误很难发现，所以C++提供了**关键字override**来解决这一问题

   - **关键字override的作用**

     <font color=red>**在虚函数的函数参数列表之后，函数体的大括号之前，加上override关键字，告诉编译器此处定义的函数是要对基类的虚函数进行覆盖**</font>

     ```cpp
     class Base {
     public:
         virtual void display() const {
             cout << "Base::display()" << endl;
         }
     private:
         long m_base;
     };
     
     class Derived : public Base {
     public:
         // 想要在派生类中定义虚函数覆盖基类的虚函数
         // 很容易打错函数名字，同时又不会报错
         // 没有完成有效的覆盖
         /* void dispaly() const {   // 名字打错但不会报错 */
         /* void dispaly() const override   // 名字打错编译器会报错 */
         void display() const override {
             cout << "Derived::display()" << endl;
         }
     private:
         long m_derived;
     
     };
     ```

   - **覆盖的总结**

     1. **覆盖**是在**虚函数之间的概念**，需要派生类中定义的虚函数与基类中定义的虚函数的形式<span style=color:red;background:yellow>**完全相同**</span>
     2. **当基类中定义了虚函数时，派生类去进行覆盖，即使在派生类的同名的成员函数前不加virtual，依然是虚函数**
     3. **发生在基类与派生类之间**，基类与派生类中同时定义形式相同的虚函数。<span style=color:red;background:yellow>**覆盖的是虚函数表中的入口地址，并不是覆盖函数本身**</span>

3. ==**动态多态（虚函数机制）激活的条件**==

   虚函数机制是如何被激活，或者说动态多态是怎么表现出来的，是一个重要的问题。其实激活条件还是比较严格的，**需要满足以下全部要求**：

   1. 基类定义虚函数
   2. <font color=red>**派生类中要覆盖虚函数 **</font>（覆盖的是虚函数表中的地址信息）
   3. 创建派生类对象
   4. **基类的指针指向派生类对象（或基类引用绑定派生类对象）**
   5. <font color=red>**通过基类==指针（引用）==调用虚函数**</font>

   最终的效果：

   **基类指针调用到了派生类实现的虚函数（如果没有虚函数机制，基类指针只能调用到基类的成员函数）**

4. **虚函数表**

   - **在虚函数机制中virtual关键字的含义**

     1. **（存在）**虚函数是存在的
     2. **（间接）**通过间接的方式去访问
     3. **（共享）**通过基类的指针访问到派生类的函数，基类的指针共享了派生类的方法

   - 如果**没有虚函数**，当通过pBase指针去调用一个普通的成员函数，那么就不会通过虚函数指针和虚函数表，而是**直接**到程序代码区中找到该函数

     **有了虚函数**，去找这个虚函数的方式就是**间接**的方式

   - <span style=color:red;background:yellow>**关于虚函数表的重要问题（面试常考题）**</span>

     1. ==虚表存放在哪里？==

        编译完成时，虚表应该已经存在；在使用的过程中，虚函数表不应该被修改掉（如果能修改，将会找不到对应的虚函数）

        所以应该**存在只读段**

        > 具体位置即决定把虚表放到哪个段、符号怎么命名、哪些段是只读、哪些可读写，不同编译器与操作系统厂家有不同实现

     2. ==一个类中虚函数表有几张？==

        **虚函数表（虚表）可以理解为是一个数组，存放的是一个个虚函数的地址**

        - 一个类可以**没有虚函数表**（没有虚函数就没有虚函数表）
        - 可以**有一张虚函数表**（<font color=red>**即使这个类有多个虚函数，将这些虚函数的地址都存在虚函数表中**</font>）
        - 也可以**有多张虚函数表**（继承多个有虚函数的基类）

     3. ==虚函数机制的底层实现是怎样的？==

        虚函数机制的底层是**通过虚函数表实现**的

        当类中**定义了虚函数之后**，就**会在对象的存储开始位置，多一个虚函数指针**，该**虚函数指针指向一张虚函数表**，**虚函数表中存储的是虚函数入口地址**

     4. <span style=color:red;background:yellow>**重载、隐藏、覆盖——三个概念的区分**</span>

        - **重载(overload)**

          发生在同一作用域中， 当函数名称相同时 ，函数参数类型、顺序 、个数任一不同(形参列表不同)

        - **隐藏(oversee)**

          发生在基类与派生类之间 ，函数名称相同时，就构成隐藏（参数不同也能构成隐藏）

        - **覆盖(override)**

          发生在基类与派生类之间，基类与派生类中同时定义返回类型、参数信息、名字都相同的虚函数，覆盖的是虚函数表中存的相应虚函数的入口地址，并不是覆盖函数本身

## 三、虚函数的限制

虚函数机制给C++提供了灵活的用法，但仍然受到了一些约束，以下几种函数不能设为虚函数：

1. ==构造函数不能设为虚函数==

   构造函数的作用是创建对象，完成数据的初始化，而**虚函数机制被激活的条件之一就是要先创建对象，有了对象才能表现出动态多态**

   如果**将构造函数设为虚函数，那此时构造未执行完，对象还没创建出来，存在矛盾**

2. ==静态成员函数不能设为虚函数==

   虚函数的实际调用：<span style=color:red;background:yellow> this -> vfptr -> vtable -> virtual function</span>

   但是**静态成员函数没有this指针，所以无法访问到vfptr**

   > vfptr是属于一个特定对象的部分，虚函数机制起作用必然需要通过vfptr去间接调用虚函数，而静态成员函数找不到这样特定的对象
   >

3. ==Inline函数不能设为虚函数==

   因为inline函数在**编译期间**完成替换，而在**编译期间无法展现动态多态机制**，所以起作用的时机是冲突的，如果同时存在，inline则失效

   > C++ 语法上允许写 `inline virtual`，不是语法报错；但逻辑上几乎没用、编译器基本不会展开，所以工程上都说 “虚函数不能是 inline”
   >
   > 例如：基类与派生类中均写了虚函数，加上inline之后，在主函数中调用这个函数，因为是inline，所以编译期会执行展开操作，**但是编译期根本不知道要展开哪个版本**，这就是根本冲突

4. **普通函数不能设为虚函数**

   虚函数要解决的是对象多态的问题，与普通函数无关

## 四、虚函数的各种访问情况

==**引用/指针保留多态，值拷贝丢失多态**==

虚函数机制的触发条件中规定了要<font color=red>**使用基类指针（或引用）来调用虚函数**</font>

而其他调用方式的具体情况如下：

1. **通过派生类对象直接调用虚函数**

   并没有满足动态多态触发机制的条件，此时只是Derived中定义的display函数对Base中的display函数形成了**隐藏**

2. **在构造函数和析构函数中访问虚函数&”隔代“覆盖**

   ```cpp
   class Grandpa {
   public:
       Grandpa() { cout << "Grandpa()" << endl; }
       ~Grandpa() { cout << "~Grandpa()" << endl; }
       virtual void func1() {
           cout << "Grandpa::func1()" << endl;
       }
       virtual void func2() {
           cout << "Grandpa::func2()" << endl;
       }
   };
   
   class Parent
   : public Grandpa
   {
   public:
       Parent() {
           cout << "Parent()" << endl;
           // func1(); // 构造函数中可以调用虚函数
       }
       ~Parent() {
           cout << "~Parent()" << endl;
           // func2(); // 析构函数中可以调用虚函数
       }
   };
   
   class Son : public Parent {
   public:
       Son() { cout << "Son()" << endl; }
       ~Son() { cout << "~Son()" << endl; }
       virtual void func1() override {
           cout << "Son::func1()" << endl;
       }
       virtual void func2() override {
           cout << "Son::func2()" << endl;
       }
   };
   
   void test0() {
       Son ss;
       Grandpa* p = &ss;
       p->func1();
       p->func2();
   }
   ```

   - 用Grandpa类指针p指向Son类对象，用这个指针p调用func1/func2.结果是指针p调用到的是Son类的func1和func2函数即结果是

     ```cpp
     Son::func1()
     Son::func2()
     ```

     说明**即使Parent中没有对Grandpa中的func1和fucn2覆盖，在Son中也可以对func1和func2覆盖**

     ![image-20231103150156687](..\0.TyporaPicture\image-20231103150156687.png)

   - <font color=red>**如果在Parent类的构造和析构函数中调用虚函数**</font>

     ![undefined202403191632256](..\0.TyporaPicture\undefined202403191632256.png)

     - 构造函数中调用虚函数

       在Son对象构造时，先调用Parent的构造函数执行时，这里的Parent构造函数并不知道是在构造Son的对象，在此过程中，**只能看到本层及以上的部分**（因为此时Grandpa类的基类子对象已经创建完毕，虚表中当前仅记录了Grandpa::func1和func2的地址，还未被覆盖）

     - 析构函数中调用虚函数

       在Parent的析构函数执行时，此时Son的析构函数已经执行完了，可以理解为Son需要进行的回收工作都已经结束了。所以Parent的析构函数**也只能看到本层及以上的部分**

     由分析可以看出这里表现出来的事**静态联编**，且<font color=red>**如果Parent类中也覆盖了func1和func2，那么会调用Parent本层的虚函数（即隐藏）**</font>

     <span style=color:red;background:yellow>**总结：**</span>

     C++标准规定，**在构造函数和析构函数中**，通过`this`指针（隐式或显式）调用的虚函数会被解析为**当前类（即构造函数或析构函数所属的类）的版本**，**而不是通过虚函数表来动态解析**

3. **在普通成员函数中调用虚函数**

   ```cpp
   class Base {
   public:
       Base(long x)
       : m_base(x)
       {}
       virtual void display() const {
           cout << "Base::display()" << endl;
       }
       void func1() {
           display();
           cout << m_base << endl;
       }
       void func2() {
           Base::display();
       }
   private:
       long m_base = 10;
   };
   
   class Derived : public Base {
   public:
       Derived(long base,long derived)
       : Base(base)
       , m_derived(derived)
       {}
       void display() const override {
           cout << "Derived::display()" << endl;
       }
   private:
       long m_derived;
   };
   
   void test1() {
       Base base(10); 
       Derived derived(1,2);
   
       base.func1();
       base.func2(); 
       derived.func1();
       derived.func2(); 
   }
   ```

   ```cpp
   // 程序执行结果
   Base::display()
   10
   Base::display()
   Derived::display()
   1
   Base::display()
   ```

   <span style=color:red;background:yellow>**第3次调用即`derived.func1()`的情况比较特殊：**</span>

   derived对象调用func1函数，因为Derived类中没有重新定义自己的func1函数，所以会去调用基类子对象的func1函数（通过基类子对象调用func1函数），可以理解为**this指针此时发生了向上转型，成为了Base*类型**。且此时this指针还是**指向的derived对象**，就符合基类指针指向派生类对象的条件，在func1中调用虚函数display，**触发动态多态机制**

   调用虚函数时, C++ 会根据对象的实际类型（`Derived`）动态绑定到相应虚函数 `Derived::display()`（动态绑定，由对象实际类型决定）

   > **==注意==**：
   >
   > 这里并不会丢失多态，因为丢失多态是发生在值拷贝的向上转型中的，这里并没有值拷贝，而是直接使用派生类对象来调用func1()，若是值拷贝的话，即最终会使用一个独立的基类对象来调用func1()了即`Base bs = derived; bs.func1();`
   >
   > **补充：**
   >
   > - **静态类型**：声明时写的类型（如 `Base*`）
   > - **动态类型**：当前实际指向/引用的对象的类型（如 `Derived` 对象）

## 五、抽象类&纯虚函数

1. **抽象类**

   在 C++ 中，**抽象类**（Abstract Class）是指至少包含一个**纯虚函数**（Pure Virtual Function）的类

   - 含有纯虚函数的类是抽象类
   - 未经覆盖直接继承纯虚函数的类是抽象类

2. **什么是纯虚函数**

   **纯虚函数**是一种特殊的虚函数，在许多情况下，在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数，**它的实现留给该基类的派生类去做**。这就是纯虚函数的作用。纯虚函数的格式如下：

   ```cpp
   class 类名 {
   public:
   	virtual 返回类型 函数名(参数 ...) = 0;
   };
   ```

3. **纯虚函数的效果**

   - 在基类中声明纯虚函数就是在让派生类提供一个纯虚函数的实现，但不关心具体如何实现

   - 多个派生类可以对纯虚函数进行多种不同的实现，但是都需要遵循基类给出的接口（纯虚函数的声明）
   - <span style=color:red;background:yellow>**声明了纯虚函数的类成为抽象类，抽象类不能实例化对象。**</span>

4. **抽象类的两种情况**

   - 含有纯虚函数(1个或多个)的类是抽象类

     ```cpp
     // 抽象类
     class AbstractClass {
     public:
         virtual void virtualFunc1() = 0;
         virtual void virtualFunc2() = 0;
     	// ...
     };
     ```

   - 未经覆盖直接继承纯虚函数的派生类是抽象类

     ```cpp
     // A类属于第一种情况,是抽象类，有2个纯虚函数
     class A {
     public:
         virtual void print() = 0;
         virtual void display() = 0;
     };
     
     // B类继承A类，但是没有override完全A类中的纯虚函数，即还存在未被覆盖的纯虚函数 ---> 即第二种情况，B类也是抽象类
     class B : public A {
     public:
         virtual void print() override{
             cout << "B::print()" << endl;
         }
     };
     
     class C : public B {
     public:
         virtual void display() override {
             cout << "C::display()" << endl;
         }
     };
     
     void test0() {
         // A类定义了纯虚函数，A类是抽象类
         // 抽象类无法创建对象
         // A a; // error
         // B b; // error
         C c;
         A* pa2 = &c;
         pa2->print();
         pa2->display();
     }
     ```

     **解释说明：**

     - 在A类中声明纯虚函数，A类就是抽象类，无法创建对象

     - 在B类中去覆盖A类的纯虚函数，**如果把所有的纯虚函数都覆盖了（即都实现了）**，B类可以创建对象；只要还有一个纯虚函数没有实现，B类也会是抽象类，也无法创建对象

     - 再往下派生C类，完成所有的纯虚函数的实现，C类才能够创建对象

     - **最顶层的基类（声明纯虚函数的类）==虽然无法创建对象，但是可以定义此类型的指针，指向派生类对象==，去调用实现好的纯虚函数**

       > <font color=red>**这种使用方式也归类为动态多态**</font>，尽管不符合第一个条件（即基类中只声明纯虚函数，没有定义），最终的效果仍然是基类指针调用到了派生类实现的虚函数，属于**动态多态的特殊情况**

5. **纯虚函数的使用案例**

   实现一个图形库，获取图形名称，获取图形之后计算它的面积

   ```cpp
   #define PI 3.14
   class Figure {
   public:
       virtual string getName() const = 0;
       virtual double getArea() const = 0;
   };
   
   void display() {
       cout << getName() 
            << "的面积是:" 
            << getArea() << endl ;
   }
   
   class Rectangle : public Figure { // 矩形
   public:
       Rectangle(double len,double wid)
       : m_length(len)
       , m_width(wid)
       {}
       string getName() const override {
           return "矩形";
       }
       double getArea() const override {
           return m_length * m_width;
       }
   private:
       double m_length;
       double m_width;
   };
   
   class Circle : public Figure {
   public:
       Circle(double r)
       : m_radius(r)
       {}
       string getName() const override {
           return "圆形";
       }
       double getArea() const override {
           return PI * m_radius * m_radius;
       }
   private:
       double m_radius;
   };
   ```

   基类Figure中定义纯虚函数，交给多个派生类去实现，最后可以使用基类的指针（引用）指向（绑定）不同类型的派生类对象，再去调用已经被实现的纯虚函数

   <font color=red>**纯虚函数就是为了后续扩展而预留的接口**</font>

## 六、补充

1. **赋值运算符函数在赋值运算符函数里的使用方式**

   > ==**原理**==
   >
   > 在**非静态成员函数内部**，凡是**成员函数形式的二元运算 / 成员函数**，**左操作数默认就是隐式的 `this`**，可以直接省略不写

   只有在「成员函数内部」，才允许省略左操作数（靠隐式 `this`）；外部普通调用绝对不能省

   ```cpp
   Derived& operator=(const Derived& other) {
       Base::operator=(other); 
       // 等价于 this->Base::operator=(other);
       // this 是隐式的，所以左操作数省略了
   }
   // 不光派生类，基类自己的成员函数里也能这么写：
   Base& operator=(const Base& other) {
       Base::operator=(other); // 内部调用自己，同样省略左操作数
   }
   ```

   ```cpp
   a2 = a1;
   // 等价
   a2.operator=(a1); // 左操作数 a2 必须写，不能省
   ```

   # Day17_多态2

## ==一、析构函数设为虚函数==

虽然**构造函数不能被定义成虚函数**，但**析构函数可以定义为虚函数**，一般来说，如果类中定义了虚函数，析构函数也应被定义为虚析构函数，尤其是**类内有申请的动态内存**，需要清理和释放的时候

在C++中，**虚析构函数（virtual destructor）** 的==**作用**是确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数==，**从而避免资源泄漏和不完整销毁的问题**

```cpp
class Base {
public:
	Base()
    : m_base(new int{10})
    { 
        cout << "Base constructor" << endl; 
    virtual ~Base() {
        if (m_base) {
            delete m_base;
            m_base = nullptr;
        }
        cout << "Base destructor" << endl;
    }
    virtual void display() {
        cout << "m_base " << *m_base << endl;

    };
private:
	int * m_base;
};

class Derived : public Base {
public:
	Derived()
	: m_derived(new int{20})
	{ 
        cout << "Derived constructor" << endl; 
    }
    ~Derived() {
        if (m_derived) {
            delete m_derived;
            m_derived = nullptr;
        }
        cout <<"Derived destructor" << endl;
    }
    void display() override {
        cout << "*m_derived = " << *m_derived << endl;
    }
private:
   int * m_derived;
};

void test0() {
    Base * pbase = new Derived();
    pbase->display();
    delete pbase;
    // 编译器会进行类型检查，pbase指向的空间是一个Derived对象
  	// 所以会调用Derived的析构函数 —— 需要让析构函数设为虚函数，Derived析构函数会在虚表中覆盖Base析构函数的地址
    // 这样通过pbase才能调用到Derived析构函数
    // Derived析构函数执行完，会自动调用Base的析构函数（没有走虚表这个途径）—— 析构函数本身的机制
}
```

在执行**delete pbase**时：

- （没有将析构函数设置为虚函数）**首先会去调用Derived的析构函数(因为删除的是Derived对象所占的空间的基地址，所以删除后则会自动调用其析构函数**)，**但是此时是通过一个Base类指针去调用，无法访问到，只能跳过**，再去调用Base的析构函数，回收掉存放10这个数据的这片空间，最后调用operator delete回收掉什堆对象本身所占的整片空间（**编译器知道需要回收的是堆上的Derived对象，会自动计算应该回收多大的空间，与delete语句中指针的类别没有关系——delete pbase**）

![image-20241213092715064](..\0.TyporaPicture\image-20241213092715064.png)

由图中可知，由于根本没有调用派生类子对象的析构函数，所以派生类子对象内部的指针成员申请的空间即20所在的堆空间没有被释放，造成内存泄露

- 为了让基类指针能够调用派生类的析构函数，**所以需要将Base的析构函数也设为虚函数**，所以Derived类中发生虚函数的覆盖，将Derived的虚函数表中记录的虚函数地址改变了。==**析构函数尽管不重名，也认为发生了覆盖**==

  ![image-20241213092816012](..\0.TyporaPicture\image-20241213092816012.png)

  在派生类析构函数执行完毕后，会自动调用基类析构函数。这是由编译器在析构函数调用序列中隐式安排的，这个过程不依赖于虚函数表，属于C++的语言规则，由此，就完成了所有申请的堆空间的释放，没有内存泄漏

**总结：**

<span style=color:red;background:yellow>**在实际的使用中，如果有通过基类指针回收派生类对象的需求，都要将基类的析构函数设为虚函数**</span>

## ==二、验证虚表的存在==

通过程序来验证虚表的存在：

```cpp
#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
        virtual void print() {
                cout << "Base::print()" << endl;
                }
        virtual void display() {
                cout << "Base::display()" << endl;
        }
        virtual void show() {
                cout << "Base::show()" << endl;
        }
private:
        long m_base = 10;
};

class Derived : public Base {
public:
        virtual void print() {
                cout << "Derived::print()" << endl;
        }
        virtual void display() {
                cout << "Derived::display()" << endl;
        }
        virtual void show() {
                cout << "Derived::show()" << endl;
        }
private:
        long m_derived = 100;
};

void test1() {
    Derived derived{};

    long* pDerived = reinterpret_cast<long*>(&derived); // 将派生类对象地址转换为long指针
    cout << pDerived[0] << endl; // 拿到派生类对象的第一个8字节内容—— 虚表基地址
    cout << pDerived[1] << endl; // 拿到派生类对象的第二个8字节内容—— 基类子对象的数据成员m_base=10
    cout << pDerived[2] << endl; // 拿到派生类对象的第三个8字节内容—— 派生类子对象的数据成员m_derived=100

    cout << "----------------" << endl;

    // 将虚函数指针强制为long类型指针数组
    long* pVTable = reinterpret_cast<long*>(pDerived[0]); // 将虚表基地址转换为long指针
    cout << pVTable[0] << endl; // 虚表中第一个8字节内容—— 即第一个成员函数print()的地址的long型解释
    cout << pVTable[1] << endl; // 虚表中第二个8字节内容—— 即第二个成员函数display()的地址的long型解释
    cout << pVTable[2] << endl; // 虚表中第三个8字节内容—— 即第三个成语函数show()的地址的long型解释
                                //
    cout << "----------------" << endl;

    // 强转为void(*)()类型函数指针
    void (*func1)() = reinterpret_cast<void (*)()>(pVTable[0]); // Derived::print()的地址转换为函数指针
    void (*func2)() = reinterpret_cast<void (*)()>(pVTable[1]); // Derived::display()的地址转换为函数指针
    void (*func3)() = reinterpret_cast<void (*)()>(pVTable[2]); // Derived::show()的地址转换为函数指针
    /* cout << func1 << endl; // error: 函数指针通过cout输出为1 */
    printf("%p\n", func1);
    printf("%p\n", func2);
    printf("%p\n", func3);
    func1(); // 访问的函数中用不到数据成员时能正常运行
    func2();
    func3();
    cout << "----------------" << endl;
    // 规范调用方式
    void (*func)(Derived*) = reinterpret_cast<void (*)(Derived*)>(pVTable[0]);
    func(&derived);

    cout << "----------------" << endl;

    // 或者使用typedef
    typedef void (*Function)();
    Function f = (Function)pVTable[0];
    printf("%p\n", f);
    f();
    f = (Function)pVTable[1];
    printf("%p\n", f);
    f();
    f = (Function)pVTable[2];
    printf("%p\n", f);
    f();
}

int main() {
    test1();

    return 0;
}
```

```cpp
// 程序运行结果
99840355773752
10
100
----------------
99840355763674
99840355763736
99840355763798
----------------
0x5acde4f085da
0x5acde4f08618
0x5acde4f08656
Derived::print()
Derived::display()
Derived::show()
----------------
Derived::print()
----------------
0x5acde4f085da
Derived::print()
0x5acde4f08618
Derived::display()
0x5acde4f08656
Derived::show()
```

1. 创建一个Derived类对象derived，这个对象的内存结构是由三个内容构成的，开始位置是虚函数指针，第二个位置是long型数据m_base，第三个位置是long型数据m_derived

2. 第一次强转将这个Derived类对象视为了存放三个long型元素的数组，打印这个数组中的三个元素，后两个本身就是long型数据，输出其值，第一个本身是指针（地址），打印出来的结果是编译器以long型数据来看待这个地址的值
3. 这个虚函数指针指向虚表，虚表中存放三个虚函数的入口地址（3 * 8字节），那么再将虚表视为存放三个long型元素的数组，第二次强转，直接输出数组的三个元素，得到的结果是编译器以long型数据来看待这三个函数地址的值
4. 虚表中的三个元素本身是函数指针，那么再将这个三个元素强转成相应类型的函数指针，就可以通过函数指针进行调用了

验证了虚表中存放虚函数的顺序，是按照基类中虚函数的声明顺序去存放的

![image-20241213110810548](..\0.TyporaPicture\image-20241213110810548.png)

![image-20241213110945496](..\0.TyporaPicture\image-20241213110945496.png)

## 三、带虚函数的多继承

1. **场景前提**

    Base1、Base2、Base3都拥有虚函数f、g、h，Derived公有继承以上三个类，在Derived中覆盖了虚函数f，还有一个普通的成员函数g1，四个类各有一个double成员

    ```cpp
    class Base1 {
    public:
        Base1() 
        : m_base1(10) 
        {
            cout << "Base1()" << endl;
        }
        virtual void f() {
            cout << "Base1::f()" << endl;
        }
        virtual void g() {
            cout << "Base1::g()" << endl;
        }
        virtual void h() {
            cout << "Base1::h()" << endl;
        }
        virtual ~Base1() {}
    private:
        double m_base1;
    };
    
    class Base2 {
    public:
        // ...省略构造、f、g、h
    private:
        double m_base2;
    };
    
    class Base3 {
    public:
        // ...省略构造、f、g、h、析构
    private:
        double m_base3;
    };
    
    class Derived 
    : public Base1
    , public Base2
    , public Base3
    {
    public:
        Derived()
        : m_derived(10000) 
        {
            cout << "Derived()" << endl;
        }
        void f() {
            cout << "Derived::f()" << endl;
        }
        virtual void g1() {
            cout << "Derived::g1()" << endl;
        }
    private:
        double m_derived;
    };
    
    int main(void) {
        cout << sizeof(Derived) << endl;
    
        Derived d;
        Base1* pBase1 = &d;
        Base2* pBase2 = &d;
        Base3* pBase3 = &d;
    
        cout << "&Derived = " << &d << endl; 
        cout << "pBase1 = " << pBase1 << endl; 
        cout << "pBase2 = " << pBase2 << endl; 
        cout << "pBase3 = " << pBase3 << endl; 
    
        return 0;
    }
    ```

    ```cpp
    // 结果
    56
    Base1()
    Base2()
    Base3()
    Derived()
    &Derived = 0x7ffeb5e5d320
    pBase1 = 0x7ffeb5e5d320
    pBase2 = 0x7ffeb5e5d330
    pBase3 = 0x7ffeb5e5d340
    ```

    **结果分析：**

    <span style=color:red;background:yellow>**三种不同的基类类型指针指向派生类对象时，实际指向的位置是相应类型的基类子对象的位置**</span>

    ![image-20241213113556205](..\0.TyporaPicture\image-20241213113556205.png)

    VS上验证布局和虚函数表存放的内容

    ![image-20241213115205142](..\0.TyporaPicture\image-20241213115205142.png)

2. **布局规则**

    通过VS平台展示类对象内存布局的功能，我们可以总结出以下规则：

    1. 每个基类都有自己的虚函数表（前提是基类定义了虚函数）

    2. 派生类如果有自己的虚函数，会被加入到第一个虚函数表之中——希望尽快访问到虚函数，也就是说省去一个虚表指针

       > 设计目的：**最快访问速度 + 节省对象内存**

       ![image-20241213115247030](..\0.TyporaPicture\image-20241213115247030.png)

    3. 内存布局中，其基类的布局按照基类被声明时的顺序进行排列（<font color=red>**有虚函数的基类会往上放——希望尽快访问到虚函数**</font>）

       如果继承顺序为Base1/Base2/Base3，在Derived对象的内存布局中就会先是Base1类的基类子对象，然后是Base2、Base3基类子对象

       此时，如果Base1中没有定义虚函数，那么内存排布上会将Base1基类子对象排在Base2、Base3基类子对象之后

       ![image-20241213115316275](..\0.TyporaPicture\image-20241213115316275.png)

    4. 派生类**覆盖**基类的虚函数**时**，**只有第一个虚函数表中存放的是真实的被覆盖的函数的地址**；**其它的虚函数表中**对应位置存放的并不是真实的对应的虚函数的地址，而是一条**跳转指令** —— 指示到哪里去寻找被覆盖的虚函数的地址

       > **派生类没有覆盖虚函数时，其他虚函数表中不再是跳转指令，而是直接存放对应基类虚函数的真实地址**，完全没有跳板（Thunk）

       ![image-20241213115717692](..\0.TyporaPicture\image-20241213115717692.png)

3. **带虚函数的多重继承的二义性**

    - **示例：**

        ```cpp
        class A {
        public:
            virtual void a() { cout << "A::a()" << endl; } 
            virtual void b() { cout << "A::b()" << endl; } 
            virtual void c() { cout << "A::c()" << endl; } 
        };
        
        class B {
        public:
            virtual void a() { cout << "B::a()" << endl; } 
            virtual void b() { cout << "B::b()" << endl; } 
            void c() { cout << "B::c()" << endl; } 
            void d() { cout << "B::d()" << endl; } 
        };
        
        class C
        : public A
        , public B
        {
        public:
            virtual void a() { cout << "C::a()" << endl; } 
            void c() { cout << "C::c()" << endl; } 
            void d() { cout << "C::d()" << endl; } 
        };
        
        // 先不看D类
        class D : public C {
        public:
            void c() { cout << "D::c()" << endl; }
        };
        ```

    - **内存结构的示意图：**

        ![image-20241213120147255](..\0.TyporaPicture\image-20241213120147255.png)

    - <font color=red>**各种调用情况的结果**</font>

        ```cpp
        void test(){
            C c;
            c.a();
            /* c.b(); // error */
            c.c();
            c.d();
        
            cout << endl;
            A* pa = &c;
            pa->a();
            pa->b();
            pa->c();
            /* pa->d(); // error */
        
            cout << endl;
            B* pb = &c;
            pb->a();
            pb->b();
            pb->c();
            pb->d();
        
        
            cout << endl;
            C * pc = &c;
            pc->a();
            /* pc->b(); // error */
            pc->c();
            pc->d();
        }
        ```

        ```cpp
        // 结果
        C::a()
        C::c()
        C::d()
        
        C::a()
        A::b()
        C::c()
        
        C::a()
        B::b()
        B::c()
        B::d()
        
        C::a()
        C::c()
        C::d()
        ```

    - **结果分析**

        ![image-20241213165940757](..\0.TyporaPicture\image-20241213165940757.png)

        ![image-20241213170123524](..\0.TyporaPicture\image-20241213170123524.png)

        **问题补充：pc->c()这里的c函数是不是虚函数**

        - 从内存的角度分析：C::c()已经在第一张虚函数表中了，所以应该当成是虚函数处理**即通过第一张虚表直接访问,没有跳转**（不算动态是因为直接通过C对象的同类型指针访问的，没有向上转换）

          > ==**虚函数**只是提供了多态的**能力**，**向上转型**（基类指针 / 引用指向派生类）才是触发多态的**开关**==
          >
          > 只要没有向上转型，无论你用：
          >
          > - 派生类对象本身
          > - 派生类指针
          > - 派生类引用
          >
          > 去调用重写后的虚函数，**全都是静态绑定，编译期就确定调用哪个函数，不走虚表动态查找，不是多态**

        - 验证：D类继承C类，重新定义c()函数，用C类指针指向D类对象，并调用c()函数

          ![image-20241213170711443](..\0.TyporaPicture\image-20241213170711443.png)

          如果将A类中c函数的virtual关键字去掉，毫无疑问C中c函数是一个普通函数（发生的仅是**隐藏**）

    > **总结：**
    >
    > - ==**静态绑定——访问成员函数**==
    >
    >   如果**通过==对象==来调用函数**，(**不管是虚函数，还是非虚函数**)都不会通过虚表来找虚函数，取决于对象的静态类型，跟`virtual`关键字无关,因为编译器从一开始就确定调用函数的对象是什么类型，直接到程序代码区中找到对应函数的实现
    >
    > - ==**动态绑定——经典多态**==
    >
    >   如果**基类指针指向派生类对象**，**通过==基类指针==调用函数**
    >
    >   - 通过指针调用虚函数：
    >     - 若派生类中对这个虚函数进行了覆盖（重写-override），那么<font color=red>**符合动态多态的触发机制**</font>，最终的效果是基类指针调用到了派生类定义的虚函数
    >     - 如果派生类对这个虚函数没有进行覆盖，也会通过虚表访问，访问到的是基类自己定义的虚函数的入口地址
    >   - 通过指针调用非虚函数
    >     - 则调用的函数由指针或引用的静态类型决定
    >
    > - ==**静态绑定——虚函数机制，但没有多态**==
    >
    >   如果是**==派生类指针==指向本类对象**，调用虚函数时，也会通过虚表去访问虚函数。若本类中对基类的虚函数进行覆盖，那么调用到的就是本类的虚函数实现，如果没有覆盖，那么会调用到基类实现的虚函数

## 四、虚拟继承

1. **虚函数 vs 虚拟继承**

   - **在虚函数机制（动态多态机制）中**

     1. 虚函数是存在的；**（存在）**
     2. 通过间接的方式去访问；**（间接）**
     3. 通过基类的指针访问到派生类的函数，基类的指针共享了派生类的方法**（共享）**

     如果没有虚函数，当通过pBase指针去调用一个普通的成员函数，那么就不会通过虚函数指针和虚表，直接到程序代码区中找到该函数；有了虚函数，去找这个虚函数的方式就成了间接的方式

   - **虚拟继承同样使用virtual关键字（存在、间接、共享）**

     1. **存在**即表示虚继承体系和虚基类确实存在
     2. **间接性**表现在当访问虚基类的成员时同样也必须通过某种间接机制来完成（通过虚基表来完成）
     3. **共享性**表现在虚基类会在虚继承体系中被共享，而不会出现多份拷贝

2. **虚拟继承**

   1. 虚基类

      如果**B类虚拟继承了A类**，那么说**A类是B类虚基类**，因为A类还可以以非虚拟的方式派生其他类

      ```cpp
      class A {
          void func() {}
          void run() {
              cout << "A::run()" << endl;
          }
          void run1() {
              cout << "A::run1()" << endl;
          }
          void run2() {
              cout << "A::run2()" << endl;
          }
          double a = 10;
      };
      
      class B : virtual public A { //B虚拟继承A类
          void run() {
              cout << "B::run()" << endl;
          }
          void run1() {
              cout << "B::run1()" << endl;
          }
          double b = 1;
      };
      ```

   2. 虚拟继承的内存结构

      ![image-20241213171357631](..\0.TyporaPicture\image-20241213171357631.png)

   3. 如果虚基类中包含了虚函数，将A中的3个run()函数增加virtual关键字修饰

      ![image-20250302164442517](..\0.TyporaPicture\image-20250302164442517.png)

   4. 如果派生类中又定义了新的虚函数，会在内存中多出一个属于派生类的虚函数指针，指向一张新的虚表（VS的实现）

      ```cpp
      // C虚拟继承A
      // 派生类C中增加一个虚函数run3()
      class A {
          void func() {}
          virtual void run() {
              cout << "A::run()" << endl;
          }
          virtual void run1() {
              cout << "A::run1()" << endl;
          }
          virtual void run2() {
              cout << "A::run2()" << endl;
          }
          double a = 10;
      };
      
      class C : virtual public A { // B虚拟继承A类
          virtual void run() {
              cout << "c::run()" << endl;
          }
          virtual void run1() {
              cout << "c::run1()" << endl;
          }
          virtual void run3() {
              cout << "c::run3()" << endl;
          }
      };
      ```

      ![image-20241213171723557](..\0.TyporaPicture\image-20241213171723557.png)

   5. 带虚函数的菱形继承——虚拟继承方式

      ![image-20241213171748752](..\0.TyporaPicture\image-20241213171748752.png)

      ![image-20241213171807623](..\0.TyporaPicture\image-20241213171807623.png)

3. **虚拟继承时派生类对象的构造和析构**

   如下菱形继承的结构中，中间层基类虚拟继承了顶层基类，注意底层派生类的构造函数

   ```cpp
   class A {
   public:
       A(double a)
       : m_a(a)
       {
           cout << "A(double)" << endl;
       }
       ~A() {cout << "~A()" << endl;}
   private:
       double m_a = 10;
   };
   
   class B : virtual public A {
   public:
       B(double a, double b)
       : A(a)
       , m_b(b)
       {
           cout << "B(double,double)" << endl;
       }
   
       ~B() { cout << "~B()" << endl; }
   private:
       double m_b;
   };
   
   
   class C : virtual public A {
   public:
       C(double a, double c)
       : A(a)
       , m_c(c)
       {
           cout << "C(double,double)" << endl;
       }
       ~C() { cout << "~C()" << endl; }
   private:
       double m_c;
   };
   
   class D
   : public B
   , public C
   {
   public:
       D(double a,double b,double c,double d)
       : A(a)
       , B(a,b)
       , C(a,c)
       , m_d(d)
       {
           cout << "D(double * 4)" << endl;
       }
       ~D() { cout << "~D()" << endl; }
   private:
       double m_d;
   };
   ```

   ![undefined202403201441781](..\0.TyporaPicture\undefined202403201441781.png)

   <font color=red>**在虚拟继承的结构中，最底层的派生类不仅需要显式调用中间层基类的构造函数，还要在初始化列表最开始调用顶层基类的构造函数**</font>

   ![image-20250302174944194](..\0.TyporaPicture\image-20250302174944194.png)

   **注意：A类构造并不会调用3次**

   有了A类的构造之后，会压抑B、C构造时调用A类构造，A类构造只会调用一次。可以对照菱形继承的内存模型理解，D类对象中只有一份A类对象的内容

   对于析构函数，同样存在这样的压抑效果，D类析构执行完后，根据继承声明顺序的反序调用C类的析构函数，C的析构函数执行完后并没有自动调用A的析构函数，而是接下来调用B的析构函数，最后调用A的析构函数

   ![image-20241213172109831](..\0.TyporaPicture\image-20241213172109831.png)

## 五、补充

1. **多态(虚函数)与虚拟继承同时出现**

   ```cpp
   #include <iostream>
   
   using std::cout;
   using std::endl;
   
   class Phone {
   public:
       /* void print() { */
       virtual void print() {
           cout << "Phone" << endl;
       }
       virtual double getData() {
           return m_p;
       }
   private:
       /* int m_p; // 由于内存对齐的机制，所以这里会填充4字节，因为前面有个虚指针 */
       double m_p;
   };
   
   class Phone1 : public Phone {
   public:
       void print() {
           cout << "Phone1" << endl;
       }
       double getData() {
           return m_p1;
       }
   private:
       double m_p1;
   };
   
   class Phone2 : virtual public Phone {
   public:
       void print() {
           cout << "Phone2" << endl;
       }
   private:
       double m_p2;
   };
   
   class Phone3 : public Phone {
   public:
       void print() {
           cout << "Phone3" << endl;
       }
   };
   void test1() {
       Phone1 p1;
       Phone2 p2;
       Phone3 p3;
       /* p1.print(); */
       /* p2.print(); */
       /* p3.print(); */
       cout << "-------" << endl;
       Phone* P1 = &p1;
       Phone* P2 = &p2;
       Phone* P3 = &p3;
       P1->print();
       P2->print();
       P3->print();
       cout << "-------" << endl;
       Phone1 p;
       Phone& P4 = p;
       Phone P5 = p;
       P4.print();
       P5.print();
       cout << "-------" << endl;
   }
   
   void test2() {
       Phone p;
       Phone1 p1;
       Phone2 p2;
       cout << "1个虚函数表+1个double：" << sizeof(p) << endl;
       cout << "1个虚函数表+2个double：" << sizeof(p1) << endl;
       cout << "1个虚函数表+2个double+虚继承：" << sizeof(p2) << endl;
   }
   
   /*
   Phone2 对象内存（总32字节）
   ┌─────────────────────────────┐  0x0000 首地址（最上面）
   │   合并指针(vptr+vbptr)       │  8字节
   ├─────────────────────────────┤
   │   double m_p2               │  8字节
   ├─────────────────────────────┤
   │   ┌─────────────────────┐   │
   │   │  Phone基类           │   │
   │   │  虚指针 vptr(8)      │   │
   │   │  double m_p(8)      │   │  16字节
   │   └─────────────────────┘   │
   └─────────────────────────────┘
   */
   
   int main() {
       test1();
       /* test2(); */
   
       return 0;
   }
   
   /* 结果
   -------
   Phone1
   Phone2
   Phone3
   -------
   Phone1
   Phone
   -------
   *
   ```

   

# Day18

## 一、模板

1. **模板的引入**

   **模板**是一种**通用的描述机制**，使用模板允许**使用通用类型**来定义**函数**或**类**。在使用时，**通用类型可被具体的类型**，如 int、double 甚至是用户自定义的类型**来代替**。通过模板，开发者可以编写**不同数据类型的相同操作**，而无需为每种类型重复编写相似的代码。这不仅**减少了代码冗余**，提高了开发效率，还增强了类型安全性，因为模板在编译时进行类型检查，避免了运行时错误

   模板引入一种全新的编程思维方式，称为“**泛型编程**”或“**通用编程**”

   > 示例：想要实现能够处理各种类型参数的加法函数
   >
   > 之前实现需要进行函数重载（函数名相同，函数参数不同）
   >
   > ```cpp
   > int add(int x, int y) {
   > 	return x + y;
   > }
   > double add(double x, double y) {
   > 	return x + y;
   > }
   > long add(long x, long y) {
   > 	return x + y;
   > }
   > string add(string x, string y) {
   > 	return x + y;
   > }
   > ```
   >
   > 只需要调用add函数，传入不同类型的参数就可以进行相应的计算了，看似很方便
   >
   > 但是程序员为了这种方便，实际上要定义很多个函数来处理各种情况的参数

   - <span style=color:red;background:yellow>**模板（将数据类型作为参数）**</span>

       上述问题用函数模板的方式就可以轻松解决：

       ```cpp
       // 希望将类型参数化
       // 使用class关键字或typename关键字都可以，完全没有区别
       template <class T>
       T add(T x, T y) {
        return x + y;
       }
       
       int main(void) {
           // 处理int数据
           cout << add(1,2) << endl;
           // 处理double数据
           cout << add(1.2,3.4) << endl;
           return 0;
       }
       ```

   - **函数模板的优点：**

     不需要程序员定义出大量的函数，在调用时实例化出对应的模板函数，更“智能”

   - <span style=color:red;background:yellow>**模板发生的时机是在编译时**</span>

       **模板本质**上就是一个**代码生成器**，它的作用就是让编译器根据实际调用来生成代码

       编译器去处理时，实际上由函数模板生成了多个模板函数，或者由类模板生成了多个模板类

2. **模板的定义**

   模板作为实现代码重用机制的一种工具，**它可以实现类型参数化，也就是把类型定义为参数**，从而实现了真正的代码可重用性

   - 模板可以分为两类：

     1. 一个是**函数模版**
     2. 另外一个是**类模板**

     通过参数实例化定义出具体的函数或类，称为**模板函数**或**模板类**

   - 模板的形式如下：

     ![image-20241216162022545](..\0.TyporaPicture\image-20241216162022545.png)

     T1、T2可以是任何合法的C++类型，如`int`、`double`、自定义类等

## 二、函数模板-实例化&重载

1. **基本语法**

   ```cpp
   template <typename T>
   T functionName(T param1, T param2) {
       // 函数体
   }
   ```

   - `template`：关键字，表明这是一个模板
   - `<typename T>`：模板参数列表，`T` 是一个占位符，代表一个类型
   - `T` 可以是任何合法的C++类型，如 `int`、`double`、自定义类等

   示例：

   ```cpp
   // 函数模板定义
   template <typename T>
   T add(T a, T b) {
       return a + b;
   }
   ```

2. **函数模板的实例化**

   由函数模板到模板函数的过程称之为<span style=color:red;background:yellow>**实例化**</span>, 即根据模板参数生成具体类型或函数的过程：

   **函数模板 --> 生成相应的模板函数 --> 编译 --> 链接 --> 可执行文件** 

   实例化的两种方式

   - **隐式实例化**：当模板被使用时，编译器根据传入的模板参数自动生成相应的实例(自动推导)

     函数模板在生成模板函数时通过传入的参数类型确定出（推导出）模板类型

     下面代码中实际上可以理解为生成了四个模板函数：

     ```cpp
     template <class T>
     T add(T t1,T t2) {
         return t1 + t2;
     }
     
     void test0() {
         short s1 = 1, s2 = 2;
         int i1 = 3, i2 = 4;
         long l1 = 5, l2 = 6;
         double d1 = 1.1, d2 = 2.2;
         // 自动推导
         cout << "add(s1,s2): " << add(s1,s2) << endl;
         cout << "add(i1,i2): " << add(i1,i2) << endl;
         cout << "add(l1,l2): " << add(l1,l2) << endl;
         cout << "add(d1,d2): " << add(d1,d2) << endl;  
     }
     ```

   - **显示实例化**：开发者可以显式指示编译器生成特定类型的模板实例 (显式指定)

     我们在使用函数模板时还可以在函数名之后<>内直接写上模板的类型参数列表，指定类型

     ```cpp
     template <class T>
     T add(T t1,T t2) {
         return t1 + t2;
     }
     
     void test0() {
         int i1 = 3, i2 = 4;
         // 显式实例化，指定参数类型
         cout << "add(i1,i2): " << add<int>(i1,i2) << endl;  	
     }
     ```

3. **函数模板的重载**

   **函数模板的重载（Function Template Overloading）**指的是在同一个作用域内定义多个**具有相同名称**但**不同模板参数列表**或**函数参数列表**的函数模板。通过重载，开发者可以为不同的参数类型或数量提供不同的模板实现，以适应多种使用场景

   函数模板的重载分为：

   - 函数模板与函数模板重载**（谨慎使用）**


   - 函数模板与普通函数重载

   1. **函数模板与函数模板重载**

      如果源文件中只有某个函数模板且该函数模板要求两个参数是同类型的数据，则在使用函数模板时传入两个不同类型的参数，会出现错误

      - 函数模板重载时的问题

        <span style=color:red;background:yellow>**此时显然可以进行显式实例化**</span>，如下，指定了类型T为int型，虽然s1是short型数据，但会发生类型转换。这个转换没有问题，因为int肯定能存放short型数据的所有内容

        ```cpp
        template <class T>
        T add(T t1,T t2) {
        	return t1 + t2;
        }    
        
        void test0() {
            short s1 = 1;
            int i2 = 4;
            cout << "add(s1,s2): " << add(s1,i2) << endl; // error
            cout << "add(s1,s2): " << add<int>(s1,i2) << endl; // ok
        }
        ```

        但如果是以下这种转换，实际上就会损失数据精度。此时的d2会转换成int型

        ```cpp
        int i1 = 4；
        double d2 = 5.3;
        cout << "add(i1,d2): " << add<int>(i1,d2) << endl; // 可以通过，但损失了精度
        ```

        如果一个函数模板无法实例化出合适的模板函数（去进行显式实例化也有一些问题）的时候，可以再给出另一个函数模板进行重载

      - ==**函数模板重载的条件**==

        1. 首先，名称必须相同（显然）

        2. 模板参数列表中的模板参数在函数中所处位置不同——<span style=color:red;background:yellow>**但不建议进行这样的重载**</span>

           ```cpp
           template <class T1, class T2>  
           T1 add(T1 t1, T2 t2) {
           	cout << "模板一" << endl;
           	return t1 + t2;
           } 
           
           template <class T1, class T2>  
           T1 add(T2 t2, T1 t1) {
           	cout << "模板二" << endl;
           	return t1 + t2;
           }
           
           int a = 10;
           double b = 1.2;
           cout << add(a,b) << endl; // error ambiguous
           cout << add<int>(a,b) << endl; // 模板一
           cout << add<double>(a,b) << endl; // 模板二
           ```

        3. 模板参数的个数不一样时，可以构成重载（相对常见）

           ```cpp
           // 函数模板与函数模板重载
           // 模板参数个数不同，ok
           template <class T> // 模板一
           T add(T t1,T t2) { 
           	return t1 + t2;
           }
           
           template <class T1, class T2> // 模板二
           T1 add(T1 t1, T2 t2) {
           	return t1 + t2;
           }
           
           template <class T1, class T2, class T3> // 模板三
           T1 add(T1 t1, T2 t2, T3 t3) {
           	return t1 + t2 + t3;
           }
           ```

   2. **函数模板与普通函数重载**

      <span style=color:red;background:yellow>**普通函数优先于函数模板执行——因为普通函数更快**</span>

      **编译器扫描到函数模板的实现时并没有生成函数**，只有扫描到下面**调用**add函数的语句**时**，给add传参，知道了参数的类型，这**才生成一个相应类型的模板函数**——模板参数推导。所以**使用函数模板一定会增加编译的时间**

      所以，此处就直接调用了普通函数，而不去采用函数模板，因为更直接，效率更高

      ```cpp
      // 函数模板与普通函数重载
      template <class T1, class T2>
      T1 add(T1 t1, T2 t2) {
      	return t1 + t2;
      }
      
      short add(short s1, short s2) {
      	cout << "add(short,short)" << endl;
      	return s1 + s2;
      }
      
      void test1() {
      	short s1 = 1, s2 = 2;
      	cout << add(s1,s2) << endl; // 调用普通函数
      }
      ```

      如果没有普通函数，就会调用上面的函数模板，实例化出相应的模板函数。尽管s1、s2的类型相同，也是可以使用该模板的

      <font color=red>**——T1、T2并不一定非得是不同类型，能推导出即可**</font>

      当然，**如果采用显式实例化的方式调用，肯定是调用函数模板**

   3. **函数模板匹配优先级**

      - **非模板函数优先于模板函数**：如果存在一个非模板函数与调用匹配，编译器优先选择非模板函数
      - **更具体的模板优先**：在模板函数中，匹配程度更高（**==需要更少类型转换==/==参数约束更严格==**）的模板优先级更高

      ```cpp
      template <class T> //模板一
      T add(T t1,T t2)
      { 
      return t1 + t2;
      }
      
      template <class T1, class T2> // 模板二
      T1 add(T1 t1, T2 t2) {
      	return t1 + t2;
      }
      double x = 9.1;
      int y = 10;
      cout << add<int,int>(x,y) << endl; // 模板二  	（1）
      cout << add<int>(x,y) << endl; // 模板一   	（2）
      cout << add<int>(y,x) << endl; // 模板二   	（3）
      ```

      1. 第(1)次调用

         指定了2个模板参数类型，直接匹配模板二

      2. 第(2)次调用

         模板一与模板二都能匹配，且都需要转换一次(double --> int)，**但模板一要求2个参数必须不同(更严格)，模板二要求2个参数可以相同(更宽松)，所以匹配模板一**

      3. 第(3)次调用

         同样指定了返回类型和第一个参数类型为int，y本身就是int，x是double类型，匹配模板二，可以不需要进行任何类型转换，所以优先匹配模板二

      **所以，多个模板都匹配的情况，尽量避免，不要写**

## 三、函数模板-==头文件与实现文件形式==&特化&==使用规则==

1. ==**函数模板的头文件与实现文件形式**==

   如果像普通函数一样去写出了头文件、实现文件、测试文件，编译时会出现未定义报错

   ```cpp
   // add.h
   template <class T>
   T add(T t1, T t2);
   
   // add.cc
   #include "add.h"
   template <class T>
   T add(T t1, T t2) {
   	return t1 + t2;
   }
   
   // testAdd.cc
   #include "add.h"
   void test0() {
   	int i1 = 1, i2 = 2;
   	cout << add(i1,i2) << endl;
   }
   ```

   出现问题的原因其实与编译.cc源文件的顺序无关，根本原因而是 C++ 的**分离编译模型**和模板**实例化规则**共同决定的

   > - 单独编译“实现文件”，使之生成目标文件，查看目标文件，会发现没有生成与add名称相关的函数
   >
   >   ![image-20241217093316612](..\0.TyporaPicture\image-20241217093316612.png)
   >
   > - 单独编译测试文件，发现有与add名称相关的函数，但是没有地址，这就表示只有声明
   >
   >   ![image-20241217093316612](..\0.TyporaPicture\image-20241217093316612.png)

   看起来与普通函数的情况有些不一样，从原理上进行分析，这是因为函数模板定义好之后并不会直接产生一个具体的模板函数，只有在调用时才会实例化出具体的模板函数

   **本质还是因为函数模板的实例化是发生在编译期的，而编译期每个源文件都是独立的，在所需模板函数的源文件里由于看不到函数模板的具体实现而生成不了模板函数，这样就出现了问题**

   > **错误的解决方法：**
   >
   > 1. **在”实现文件“中要进行调用，因为有了调用才有推导，才能由函数模板生成需要的函数**
   >
   >     ```cpp
   >     // add.cc
   >     template <class T>
   >     T add(T t1, T t2) {
   >         return t1 + t2;
   >     }
   >     
   >     // 在这个文件中如果只是写出了函数模板的实现
   >     // 并没有调用的话，就不会实例化出模板函数
   >     void test1() { 
   >     cout << add(1,2) << endl;
   >     }
   >     ```
   >
   >     此时单独编译实现文件，发现生成了对应的函数
   >
   >     ![image-20241217093851514](..\0.TyporaPicture\image-20241217093851514.png)
   >
   >     但是在“实现文件”中对函数模板进行了调用，这种做法不仅不优雅，还**破坏封装，不可扩展，绝不能使用**
   >
   > 2. 另一种方法的设想：如果在测试文件调用时，在推导的过程中，<font color=red>**看到的是完整的模板的代码**</font>，那么应该可以解决这个问题
   >
   >     ```cpp
   >     // add.h
   >     template <class T>
   >     T add(T t1, T t2);
   >                 
   >     #include "add.cc"
   >     ```
   >
   >     可以在头文件中加上#include "add.cc"，即使实现文件中没有调用函数模板来生成模板函数，但在单独编译testAdd.cc，也可以发现问题已经解决即可以生成模板函数
   >
   >     因为本质上相当于把函数模板的定义写到了头文件中（其实就是合并了链各个源文件，但是会引发重定义的错误）
   >
   >     **极易引发循环包含和重定义，高危操作，违反规范，绝不能使用**
   >
   > **正确的解决方法：**
   >
   > **方法一（最常用）：把模板定义直接放在头文件里**
   >
   > ```cpp
   > // add.h
   > template <class T>
   > T add(T t1, T t2) {
   >     return t1 + t2;
   > }
   > ```
   >
   > 编译器在编译 `testAdd.cc` 时，就能同时看到声明和定义，当场实例化出代码
   >
   > **方法二：在定义所在的 `.cc` 文件中，进行显式实例化**
   >
   > ```cpp
   > // add.cc
   > #include "add.h"
   > template <class T>
   > T add(T t1, T t2) {
   >     return t1 + t2;
   > }
   > 
   > // 显式要求编译器生成 int 版本的代码
   > template int add<int>(int, int);
   > ```
   >
   > 这样 `add.o` 里就会包含 `add<int>` 的定义，链接时能找到。但缺点是你必须提前预知所有用到的类型并逐个声明
   >
   > **总结**：对普通函数，声明和定义分离没问题；但==对模板而言，**使用它的编译单元必须有定义可见**==，这是模板最常遇到的坑

   <span style=color:red;background:yellow>**总结：**</span>

   - **对模板的使用，必须要拿到模板的全部实现，如果只有一部分，那么推导也只能推导出一部分，无法满足需求。**

   - **换句话说，就是模板的使用过程中，其实没有了头文件和实现文件的区别，在头文件中也需要获取模板的完整代码，不能只有一部分。(声明和实现要放在一起)**

   C++的标准库都是由模板开发的，所以经过标准委员会的商讨，<font color=red>**将这些头文件取消了后缀名，与C的头文件形成了区分**</font>
   而在GUN中，这些实现文件的后缀名设为了.tcc，注意这并非 C++ 语言的通用规则

2. **模板的特化**

   **模板特化（Template Specialization）**允许**为特定的模板参数**提供不同于通用模板的实现。当通用模板(的定义实现)无法满足某些特定类型的需求，模板特化就显得尤为重要

   1. 模板特化主要分为两种类型

      - **全特化（Full Specialization）**：为特定的模板参数提供完全不同的实现
      - **偏特化（Partial Specialization）**：为部分模板参数提供特殊实现，**仅适用于类模板，函数模板不支持偏特化**

      **注意**：**C++**不支持函数模板的偏特化，**只能进行全特化**

   2. 函数模板全特化语法

      - template后直接跟 <> ，里面不写类型
      - 在函数名后跟 <> ，其中写出要特化的类型

      ```cpp
      // 通用函数模板
      template <typename T1, typename T2>
      ReturnType functionName(T1 t1, T2 t2) {
          // 通用实现
      }
      
      // 全特化函数模板
      template <>
      ReturnType functionName<SpecificType1, SpecificType2>(SpecificType1 t1, SpecificType2 t2) {
          // 特化实现
      }
      ```

   3. 示例

      add函数模板在处理C风格字符串相加时遇到问题，如果只是简单地让两个C风格字符串进行+操作，会出现报错，这里就可以利用特化模板解决：

      ```cpp
      // 通用模板
      template <typename T1, typename T2>
      T1 add(T1 t1, T2 t2) {
          return t1 + t2;
      }
      
      // 特化模板 这里就是告诉编译器这里是一个模板
      template <>
      const char* add<const char*>(const char* p1,const char* p2) {
          // 先开空间
          char* ptmp = new char[strlen(p1) + strlen(p2) + 1]();
          strcpy(ptmp,p1); // 先复制前半段
          strcat(ptmp,p2); // 再将后半段拼接到前半段之后
          return ptmp;
      }
      
      void test0() {
          // 通用模板无法应对如下的调用
          const char* p = add<const char*>("hello",",world");
          cout << p << endl;
          delete[] p;
      }
      ```

   4. 注意

      - <font color=red>**使用模板特化时，必须要先有基础的函数模板**</font>

        如果没有模板的通用形式，无法定义模板的特化形式。因为特化模板就是为了解决通用模板无法处理的特殊类型的操作

      - 特化版本的**函数名、参数列表**要和原基础的函数模板**相同**，避免不必要的错误

3. **==模板的使用规则==**

   - **在一个模块中定义多个通用模板的写法应该谨慎使用**
   - **调用函数模板时==尽量使用隐式调用==，让编译器推导出类型**
   - **无法使用隐式调用的场景==只指定必须要指定部分的类型==**
   - **需要==使用特化模板==的场景==时==就根据特化模板==将类型指定清楚==**

## 四、函数模板-参数类型&成员函数模板

1. **模板的参数类型**

   - 类型参数

     之前的T、T1、T2等等称为**模板参数，也称为类型参数**，类型参数T可以写成任何类型

   - 非类型参数

     **==需要是整型数据==， char/short/int/long/size_t等**
     不能是浮点型，float/double不可以

   1. 非类型参数的应用示例

      定义模板时，在模板参数列表中除了类型参数还可以加入非类型参数

      需要注意的是，在此时，<font color=red>**调用模板时需要传入非类型参数的值**</font>

      ```cpp
      template <class T,int kBase>
      T multiply(T x, T y) {
      	return x * y * kBase;
      }
      
      void test0() {
          int i1 = 3,i2 = 4;
          // !!!此时想要进行隐式实例化就不允许了，因为kBase无法推导
          cout << multiply(i1,i2) << endl; // error
          cout << multiply<int,10>(i1,i2) << endl; // ok
      }
      ```

   2. 非类型参数的默认值

      可以给非类型参数赋默认值，有了默认值后调用模板时就可以不用传入这个非类型参数的值

      ```cpp
      template <class T,int kBase = 10>
      T multiply(T x, T y) {
      	return x * y * kBase;
      }
      
      void test0() {
      	int i1 = 3,i2 = 4;
      	cout << multiply<int,10>(i1,i2) << endl;
      	cout << multiply<int>(i1,i2) << endl;
      	cout << multiply(i1,i2) << endl;
      }
      ```

   3. 类型参数的默认值

      函数模板的模板参数赋默认值与普通函数相似，从右到左，右边的非类型参数赋了默认值，左边的**类型参数也可以赋默认值**

      ```cpp
      template <class T = int,int kBase = 10>
      T multiply(T x, T y) {
      	return x * y * kBase;
      }
      
      void test0() {
      	double d1 = 1.2, d2 = 1.2;
      	cout << multiply<int>(d1,d2) << endl; // ok
      	cout << multiply(d1,d2) << endl; // ok
      }
      ```

      第一次调用时，T代表了int，因为使用模板时指定了类型参数
      但是第二次调用时，T不是代表int的，而是代表了double

      由此可以得出结论：

      **类型参数生成结果的优先级：指定的类型  >  推导出的类型  > 类型的默认参数**

      > 补充：**类型参数的默认值仅在无法推导出才会生效，与普通函数默认参数的逻辑==完全相反==**

   4. 使用类型默认参数的时机

      既没有指定，又推导不出来的类型

      ```cpp
      template <class T1,class T2 = double,int kBase = 10>
      T1 multiply(T2 t1, T2 t2){
      	return t1 * t2 * kBase;
      }
      ```

      在上面这个函数模板中，T1类型无法根据传入的参数推导而出，**如果不通过显式实例化进行指定，这个函数模板就无法使用**

      ```cpp
      cout << multiply(1.2,1.2) << endl; // 没匹配上
      cout << multiply<double>(1.2,1.2) << endl; // ok
      ```

      给**T1也赋予默认值**，**才可以进行隐式实例化**

      ```cpp
      template <class T1 = double,class T2 = double,class kBase = 10>
      T1 multiply(T2 t1, T2 t2) {
      	return t1 * t2 * kBase;
      }
      cout << multiply(1.2,1.2) << endl; // ok
      ```

   5. **关于类型/非类型参数默认值的总结**

      在没有指定类型时，模板参数的默认值（不管是类型参数还是非类型参数）只有在没有足够的信息用于推导时起作用。**当存在足够的信息时，编译器会按照实际参数的类型去调用，不会受到默认值的影响**

2. **成员函数模板**

   - 在普通类中也可以定义成员函数模板，如下：
   
       ```cpp
       class Point {
       public:
           Point(double x,double y)
       	: m_x(x)
       	, m_y(y)
       	{}
           // 定义一个成员函数模板
           // 将m_x转换成目标类型
           template <class T>
               T convert() {
               return (T)m_x;
           }
       private:
        	double m_x;
       	double m_y;
       };
       
       void test0() {
       	Point pt(1.1,2.2);
           cout << pt.convert<int>() << endl;
           cout << pt.convert() << endl; // error
       }
       ```

       此时调用这个成员函数模板，不能采用隐式实例化的方式，因为编译器不知道要将`pt.m_x`转换成什么类型
   
   - 可以给成员函数模板中类型参数赋默认值，有了默认值后才可以进行隐式实例化
   
       ```cpp
       // 定义一个成员函数模板
       // 将m_x转换成目标类型
       template <class T = int>
       T convert() {
       	return (T)m_x;
       }
       
       cout << pt.convert() << endl; // ok
       ```
   
   - 示例
   
       在Point类中定义一个add函数模板
   
       ```cpp
       class Point {
       public:
       	Point(double x,double y)
       	: m_x(x)
       	, m_y(y)
       	{}
       	template <class T>
       	T add(T t1) {
       		return m_x + m_y + t1;
       	}
       private:
       	double m_x;
       	double m_y;
       };
       
       void test0() {
           Point pt(1.5,3.8);
       	cout << pt.add(8.8) << endl;
       }
       ```
   
       - 在add函数模板中可以访问Point的数据成员，说明成员函数模板的使用原理同普通函数模板一样，在调用时会实例化出一个模板成员函数
       - 普通的成员函数会有隐含的this指针作为参数，这里生成的模板成员函数中也会有。如果定义一个static的成员函数模板，那么在其中就不能访问非静态数据成员（与普通的static成员函数一样没有this指针）
       - <span style=color:red;background:yellow>**成员函数模板不能加上virtual修饰**</span>，否则编译器报错，因为函数模板是在编译时生成函数，而虚函数机制起作用的时机是在运行时
   
   - 如果要将成员函数模板在类之外进行实现，需要<span style=color:red;background:yellow>**注意带上模板的声明**</span>
   
       ```cpp
       class Point {
       public:
               Point(double x,double y)
               : m_x(x)
               , m_y(y)
               {}
               // ...
           template <class T>
               T add(T t1);
       private:
           double m_x;
           double m_y;
       };
       
       template <class T>
       T Point::add(T t1) {
               return m_x + m_y + t1;
       }
       ```

## 五、可变参数模板

1. **什么是可变参数模板**

   可变参数模板(variadic templates)是 C++11 新增的最强大的特性之一，它对参数进行了高度泛化，它能表示0到任意个数、任意类型的参数。由于可变参数模板比较抽象，使用起来需要一定的技巧，所以它也是 C++11 中最难理解和掌握的特性之一

   **关键点**：

   - **参数数量不固定**：模板可以接受任意数量的参数
   - **参数类型多样**：参数可以是不同类型的，甚至是混合类型

   回想一下C语言中的`printf`函数，其实是比较特殊的。`printf`函数的参数个数可能有很多个，用...表示，参数的个数、类型、顺序可以随意，可以写0到任意多个参数

   ![image-20241218094433651](..\0.TyporaPicture\image-20241218094433651.png)

2. **基本语法**

   可变参数模板和普通模板的语义是一样的，只是写法上稍有区别，声明可变参数模板时需要在`typename`或`class`后面带上省略号 “**...**” 

   ```cpp
   template <class... Args>  
   void func(Args... args);
   
   // 与普通函数模板做对比
   template <class T1,class T2>
   void func(T1 t1, T2 t2);
   ```

   - `Args`叫做**模板参数包**，相当于将 T1/T2/T3/...等类型参数打了包

   - `args`叫做**函数参数包**，相当于将 t1/t2/t3/...等函数参数打了包

   <span style=color:red;background:yellow>**省略号写在参数包的左边，代表打包**</span>

3. **什么情况使用**

   例如在定义一个函数时，可能有很多个不同类型的参数，不适合一个一个写出，就可以使用可变参数模板的方法，利用可变参数模板输出参数包中参数的个数

   ```cpp
   template <class... Args> // Args，模板参数包
   void display(Args... args) { //args，函数参数包
       // 输出模板参数包中类型参数个数
       cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
       // 输出函数参数包中参数的个数
       cout << "sizeof...(args) = " << sizeof...(args) << endl;
   }
   
   void test0() {
       display();
       display(1,"hello",3.3,true,5);
   }
   ```

4. **示例**

   - 需求：希望打印出传入的不同类型参数的内容

   - 处理思路

     对于可变参数模板的处理，主要通过**递归模板**来解包(展开参数包)，这种递归方法需要定义一个递归基例和一个递归模板，以逐步处理每个参数，直到<span style=color:red;background:yellow>**递归出口**</span>

   - **具体实现方法**：

     1. **定义一个递归基例**：当没有参数时，什么也不做，作为递归出口
     2. **定义一个递归模板**：处理第一个参数，并递归处理剩余参数

     ```cpp
     // 递归的出口
     void print() {
     	cout << endl;
     }
     
     // 重新定义一个可变参数模板，至少得有一个参数
     template <class T,class ...Args>
     void print(T x, Args ...args) {
     	cout << x << " ";
     	print(args...);  // 省略号在参数包右边
     }
     ```

     <span style=color:red;background:yellow>**省略号写在参数包的右边，代表解包**</span>

   - 调用时的过程分析

     如下所示，各种调用的步骤：

     ```cpp
     void test1(){
     // 调用普通函数
     // 不会调用函数模板，因为函数模板至少有一个参数
     print();
         
     print(2.3);
     // cout << 2.3 << " ";
     // cout << endl;
     
     print(1,"hello",3.6,true);
     // cout << 1 << " "; 		print("hello",3.6,true);
     // cout << "hello" << " "; 	print(3.6,true);
     // ...
     }
     ```

     <font color=red>**如果没有准备递归的出口，那么在可变参数模板中解包解到print()时，不知道该调用什么，因为这个模板至少需要一个参数。**</font>

   - 设置不同的递归出口

     ```cpp
     // 出口1 —— 在这里有出口2的前提下出口1不会被使用，除非print函数模板中一次性打印两个参数，即：
     /*
     template <class T,class... Args>
     void print(T x1, T x2, Args... args) {
         cout << x1 << " " << x2 << " ";
         print(args...);
     }
     */
     // 这样的话，原始的函数参数包中参数个数为奇数的话最终调用出口2，参数个数为偶数的话最终调用出口1
     void print() {
         cout << endl;
     }
     
     // 出口2
     // 只剩下一个int型参数的时候，不会再使用函数模板，而是通过普通函数即出口2结束递归
     void print(int x) {
         cout << x << endl;
     }
     
     template <class T,class... Args>
     void print(T x, Args... args) {
         cout << x << " ";
         print(args...);
     }
     
     print(1,"hello",3.6,true,100);
     ```

## 六、类模板

1. **形式**

   ```cpp
   template <class/typename T, ...>
   class 类名 {
   // 类定义．．．
   };
   ```

   实际上，之前已经多次见到了类模板，打开c++参考文档，发现vector、set、map等等都是使用类模板定义的

2. **不使用与使用类模板的对比**

   - 需求：不使用/使用类模板, 定义一个Box类型的容器, 可以存放不同类型的数据,体会一下差别

   - 不使用模板

     ```cpp
     // 存放int类型数据
     class Box {
     private:
         int m_data;
     };
     // 存放double类型的数据
     class Box2 {
     private:
         double m_data;
     };
     // 存放string类型数据
     class Box3 {
     private:
         string m_data;
     };
     // ...
     ```

   - 使用类模板

     ```cpp
     // 使用模板
     template <typename T>
     class Box {
     public:
         Box(T data)
         : m_data(data)
         {
             cout << "store data" << endl;
         }
         // 成员函数定义在类内部
         void display() {
             cout << "data = " << m_data << endl;
         }
         // 成员函数声明和实现分开 实现在类外部
         void show();
     private:
         T m_data;
     };
     
     template <typename T>
     void Box<T>::show() {
         cout << "data is = " << m_data << endl;
     }
     
     void test1() {
         // 类模板使用跟普通类一样,只需要指定模板参数
         // 实例化类模板
         Box<int> box{100}; // 存放int数据
         box.display();
         
         Box<double> box2{3.14}; // 存放double数据
         box2.display();
         
         string s = "abc";
         Box<string> box3{s}; // 放string数据
         box3.display();
         box.show();
     }
     ```

3. **类模板的成员函数如果放在类模板定义之外进行实现**

   需要**注意**：

   - 需要带上**template模板形参列表**（**如果有默认参数，此处不要写，写在声明时就够了**）
   - 在添加作用域限定时需要写上**完整的类名和模板实参列表**

   ```cpp
   template <typename T>
   void Box<T>::show() {
       cout << "data is = " << m_data << endl;
   }
   ```

## 七、补充

1. **用类模板的方式实现一个Stack类，可以存放任意类型的数据，模拟栈的相关操作**

   ![image-20241218105957026](..\0.TyporaPicture\image-20241218105957026.png)

   ```cpp
   template <typename T, size_t capacity = 10>
   class Stack {
   public:
       Stack()
       : m_data(new T[capacity]{})
       , m_top(-1)
       {
           cout << "init stack" << endl;
       }
       ~Stack() {
               delete[] m_data; // 对空指针使用 delete 或 delete[] 是合法的，什么都不会发生
               /* m_data = nullptr; // 多余，析构函数结束之后，成员变量 m_data 所占用的内存也会随着对象一起被回收 */
       }
   
       void push(const T& value);
       void pop();
       bool empty() const;
       bool full() const;
       T top() const;
   private:
       T* m_data;
       int m_top; // 永远指向栈顶元素
   };
   
   // 类外实现成员函数
   template <typename T, size_t capacity>
   bool Stack<T,capacity>::empty() const {
       return m_top == -1;
   }
   
   template <typename T, size_t capacity>
   bool Stack<T,capacity>::full() const {
       return m_top == capacity - 1;
   }
   
   template <typename T, size_t capacity>
   void Stack<T,capacity>::push(const T & value) {
       if (full()) {
           cout << "stack is full" << endl;
           return;
       } else {
           m_data[++m_top] = value;
       }
   }
   
   template <typename T, size_t capacity>
   void Stack<T,capacity>::pop() {
       if (empty()) {
           cout << "stack is empty" << endl;
           return;
       } else {
           --m_top;
       }
   }
   
   template <typename T, size_t capacity>
   T Stack<T,capacity>::top() const {
       if (!empty()) {
           return m_data[m_top];
       } else {
           cout << "stack is empty" << endl;
           /* throw "stack is empty"; */
       }
   }
   ```

   

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

   <span style=color:red;background:yellow>**实际上，右值引用本身既可以是左值（比如：作为函数的参数、有名字的变量），也可以是右值（函数的返回类型），只不过其只能绑定右值**</span>

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
# Day20_移动语义与资源管理2

## 一、智能指针

智能指针本质是**封装裸指针的类模板**，核心依赖**RAII 机制**实现自动内存管理；不同类型（unique_ptr/shared_ptr/weak_ptr）叠加**独占所有权**、**引用计数**、**弱引用**等技术；RAII 的核心特征是**资源生命周期与对象绑定**、**异常安全**、**自动释放**

- **实现原理**：智能指针是封装裸指针的类模板，通过 RAII 机制将资源释放绑定到析构函数，实现自动内存管理

- **核心技术**：以**RAII**为基石，结合**操作符重载**、**引用计数**、**移动语义**等技术，实现不同类型智能指针的差异化功能

- **技术特征**：RAII 的核心是**资源与对象生命周期绑定**，具有**构造获取、析构释放、作用域绑定、异常安全、所有权清晰**五大特征，从根源上解决资源泄漏问题

1. **`auto_ptr(C++17已弃用)`**

   - 特点

     - auto_ptr是最简单的智能指针，使用上存在缺陷，自C++17起被弃用，**转移所有权，源对象置空**

     - auto_ptr是有复制函数的

     > `std::auto_ptr` **实现了拷贝构造函数** 和 **拷贝赋值运算符**，但正是这两个函数的**错误设计**，成为了它最致命的缺陷，最终导致被 C++ 标准废弃

   - 使用

     ```cpp
     void test0() {
         int* pInt = new int(10);
         // 创建auto_ptr对象接管资源
         auto_ptr<int> ap(pInt);
         cout << "*pInt:" << *pInt << endl;
         cout << "*ap:" << *ap << endl;
     }
     ```

     尽管会有warning提示，代码仍可通过。发现不用对pInt进行delete，也没有内存泄露

   - 风险隐患

     ```cpp
     auto_ptr<int> ap2(ap);
     cout << "*ap2:" << *ap2 << endl; // ok
     cout << "*ap:" << *ap << endl;  // error
     // auto_ptr底层的原理是移交管理权, 所以ap底层指针已经被置空了,所以对ap解引用导致段错误
     ```

     auto_ptr可以进行复制，但是存在隐患 ，当ap2复制了ap后，对ap2管理的资源进行访问没有问题，但是对ap解引用会导致段错误

   - 原理分析

     通过阅读auto_ptr源码的实现，可知ap的指针被置为了空指针

     ```cpp
     template <class _Tp> 
     class auto_ptr {
     public:
         // 拷贝构造
         auto_ptr(auto_ptr& __a) __STL_NOTHROW 
     	// ap2的_M_ptr 被赋值为 ap调用release函数的返回值
     	: _M_ptr(__a.release()) 
     	{}
         // ap调用release函数
         _Tp* release() __STL_NOTHROW {
             // 用局部的指针__tmp接管ap的指针所指向的资源
             _Tp* __tmp = _M_ptr;
             _M_ptr = nullptr; // 将ap底层的指针设为空指针
             return __tmp; // 返回的就是原本ap管理的资源的地址
         }  
     private:
         _Tp* _M_ptr;
     };
     ```

     也就是说，`auto_ptr<int> ap2(ap); `这一步表面上执行了**拷贝操作**，但是**底层已经将右操作数ap所托管的堆空间的控制权交给了新对象ap2**，并且将**ap底层的指针数据成员置空**，该拷贝操作存在隐患，所以auto_ptr被弃用了

2. <span style=color:red>**`unique_ptr`**</span>

   unique_ptr对auto_ptr进行了改进

   - **特点1：不允许复制或者赋值**

     具备对象语义

     > **对象语义（Object Semantics）** 又称**引用语义（Reference Semantics）**，是 C++ 中与**值语义（Value Semantics）** 相对的概念，描述对象拷贝 / 赋值时的行为规则与资源管理方式
     >
     > - **本质**：对象代表独立的**资源所有者**或**实体标识**，而非单纯的值容器
     >
     > - **核心特征**：拷贝行为要么**被禁止**，要么**共享底层资源**（浅拷贝），拷贝后两个对象并非完全独立
     >
     > - **哲学**：关注 “对象本身” 而非 “对象的值”，强调**身份标识**与**资源所有权**

   - **特点2：独享所有权的智能指针**

     ```cpp
     void test0() {
         unique_ptr<int> up(new int(10));
         cout << "*up:" << *up << endl;
         // get()-->返回指向被管理对象的指针
         cout << "up.get(): " << up.get() << endl;
     
         cout << endl;
         // 独享所有权的智能指针，对托管的空间独立拥有
         // 拷贝构造已经被删除
         unique_ptr<int> up2 = up; // 复制操作 error
         
         // 赋值运算符函数也被删除
         unique_ptr<int> up3(new int(20));
         up3 = up; // 赋值操作 error
     }
     ```

     将auto_ptr的缺陷摒弃了，**具有对象语义，语法层面不允许复制、赋值**

   - **特点3：作为容器元素**

     要利用**移动语义**的特点，可以直接传递右值属性的unique_ptr作为容器的元素。如果传入左值形态的unique_ptr，会进行复制操作，而unique_ptr是不能复制的

     - 而构建右值的方式有：

         1. 可以直接**使用unique_ptr的构造函数，创建匿名对象**（临时对象）来构建右值
         2. `std::move()`函数

         ```cpp
         vector<unique_ptr<Point>> vec;
         
         unique_ptr<Point> up4(new Point(10, 20));
         // up4是一个左值
         // 将up4这个对象作为参数传给了push_back函数，会调用拷贝构造
         // 但是unique_ptr的拷贝构造已经删除了
         // 所以这样写会报错
         vec.push_back(up4);  // error
         
         vec.push_back(unique_ptr<Point>(new Point(10, 20))); // ok
         vec.push_back(std::move(up4));  // ok
         ```

         > 补充
         >
         > - 方法 3：`std::make_unique<数据类型>(构造参数)`函数（C++14起）
         > - 方法 4：函数返回值（纯右值，编译器优化，编译器开启 RVO 返回值优化，无拷贝 / 移动，直接插入容器）
         >
         > - 方法 5：`emplace` 系列**原地构造右值**（✅ 最优推荐）
         >
         > - 方法 6：方法1的特殊情况，字符串字面量、字面值**隐式构造临时右值**（前提：构造函数没有关键字`explicit`修饰）
         >
         >   > 如果加了 `explicit`，这个隐式转换会直接报错，只能用显式构造
         >   >
         >   > 字面值隐式构造的**唯一条件**（字符串字面量同理，因为字符串字面量是C++ 标准定义的「字面值（字面量）」的一种）：
         >   >
         >   > **构造函数是单参数 + 无 `explicit` + 传入的值能匹配构造函数的参数类型**
         >
         > ```cpp
         > vec.push_back(std::make_unique<Point>(10, 20));
         > vec.push_back(makePoint(30, 40));
         > vec.emplace_back(new Point(50, 60));
         > vec_name.push_back("原点坐标"); // 对象的数据成员为字符串时
         > // 注意：unique_ptr是指针，所以接收的是地址
         > 
         > // vec_name.push_back(&{70, 80}); // 想当然传入一个指针
         > // error1(语法上)：C++根本不允许对{}初始化列表直接取地址
         > // error2(逻辑上): 列表初始化方式，在这里是不合理的，因为unique_ptr管理的是堆上的资源，而这里的Point对象是栈上的资源，栈上资源是系统自动管理的
         > ```

         > 注意：
         >
         > vector的元素一定在堆上，而up4是在栈上的智能指针对象，但`vec.push_back(std::move(up4));`这里并没有发生复制，因为unique_ptr的拷贝构造是被删除的，所以说明了这里实际上是移交管理权，up4不再拥有(10,20)这个Point对象的管理权
         >
         > ```cpp
         > up4->print(); // error
         > vec[0]->print(); // ok
         > ```

   - unique_ptr作为容器元素的注意事项

     ```cpp
     // 将unique_ptr作为容器元素时,只能传入右值
     std::vector<unique_ptr<int>> vec;
     unique_ptr<int> up{new int{10}};
     // vector的元素会存在堆上, 但up本身是一个栈上的对象
     // 这里本应该发生unique_ptr的复制, 调用已经被删除的拷贝构造函数，但显示不会成功
     /* vec.push_back(up); // error: 不能添加左值 */
     
     vec.push_back(unique_ptr<int>{new int{100}});
     vec.push_back(std::move(up))
     
     cout << &up << endl; // 栈上地址，up变量本身地址
     cout << &vec[1] << endl; // 堆上地址，vector内部存储该的unique_ptr对象的地址
     ```

3. <span style=color:red>**`shared_ptr`**</span>

   智能指针独享资源的控制权固然是一种需求，但**有些场景下也需要允许共享控制权**

   shared_ptr就是**共享所有权的智能指针**，**可以进行复制或赋值**，但**复制或赋值时，并不是真正拷贝了被管理的对象**，而只是将**引用计数加1**了。即shared_ptr引入了引用计数，其思想与COW技术类似，又称为是==**强引用的智能指针**（**唯一的**弱引用的智能指针——std::weak_ptr）==

   - 特征

     1. **共享所有权的智能指针**

        可以使用**引用计数**记录对象的个数

     2. **可以进行复制或者赋值**

        具备值语义

     3. **也可以作为容器的元素**

        作为容器元素的时候，既可以传递左值，也可以传递右值（区别于unique_ptr只能传右值）

     4. **也具备移动语义**

        也有移动构造函数与移动赋值函数

        ```cpp
        shared_ptr<int> sp(new int(10));
        cout << "sp.use_count(): " << sp.use_count() << endl; // 1
        
        cout << endl;
        cout << "执行复制操作" << endl;
        shared_ptr<int> sp2 = sp; // 拷贝构造
        cout << "sp.use_count(): " << sp.use_count() << endl; // 2
        cout << "sp2.use_count(): " << sp2.use_count() << endl; // 2
        
        cout << endl;
        cout << "再创建一个对象sp3" << endl;
        shared_ptr<int> sp3(new int(30));
        cout << "sp.use_count(): " << sp.use_count() << endl; // 2
        cout << "sp2.use_count(): " << sp2.use_count() << endl; // 2
        cout << "sp3.use_count(): " << sp3.use_count() << endl; // 1
        
        cout << endl;
        cout << "执行赋值操作" << endl;
        sp3 = sp; // 赋值
        cout << "sp.use_count(): " << sp.use_count() << endl; // 3
        cout << "sp2.use_count(): " << sp2.use_count() << endl; // 3
        cout << "sp3.use_count(): " << sp3.use_count() << endl; // 3
        
        cout << endl;
        cout << "作为容器元素" << endl;
        vector<shared_ptr<int>> vec;
        vec.push_back(sp); // 可以以左值形式"拷贝"进容器
        vec.push_back(std::move(sp2)); // 也可以以右值形式"移动"进容器
        ```

   - shared_ptr的循环引用问题

     建立一个Parent和Child类的一个结构，数据成员均为对方的类对象的shared_ptr智能指针

     ```cpp
     class Child;
     
     class Parent {
     public:
     	Parent() {
     		cout << "Parent()" << endl;
         }
     	~Parent() {
     		cout << "~Parent()" << endl;
         }
     	// 只需要Child类型的指针，不需要类的完整定义
     	shared_ptr<Child> m_spChild;
     };
     
     class Child {
     public:
     	Child() {
             cout << "child()" << endl;
         }
     	~Child() {
             cout << "~child()" << endl;
         }
     	shared_ptr<Parent> m_spParent;
     };
     ```

     首先进行如下的创建：

     ```cpp
     shared_ptr<Parent> parentPtr(new Parent());
     shared_ptr<Child> childPtr(new Child());
     // 获取到的引用计数都是1
     cout << "parentPtr.use_count():" << parentPtr.use_count() << endl;
     cout << "childPtr.use_count():" << childPtr.use_count() << endl;
     ```

     ![image-20250204214053867](..\0.TyporaPicture\image-20250204214053867.png)

     再进行如下的智能指针绑定操作：

     ```cpp
     parentPtr->spChild = childPtr;
     childPtr->spParent = parentPtr;
     // 获取到的引用计数都是2
     cout << "parentPtr.use_count():" << parentPtr.use_count() << endl;
     cout << "childPtr.use_count():" << childPtr.use_count() << endl;
     ```

     至此形成了这样的结构：

     ![image-20250304165311716](..\0.TyporaPicture\image-20250304165311716.png)

     但是在程序结束时，发现**堆上的Parent对象和child对象的析构函数都没有被调用**

     这是因为栈上的childPtr和parentPtr会先后销毁，但是堆上的Parent对象和Child对象的引用计数只会变为1，而不会减到0，所以没有自动回收

     > 即childPtr和parentPtr销毁时调用析构函数：先减少引用计数，但是引用计数减一之后仍未为0，所以不会触发销毁资源的操作
     >
     > 注意：这里两个类对象资源本身不在栈上，而是在堆上由两个智能指针所托管，但是其内部还存在智能指针且相互引用，所以栈上的两个智能指针丧失了绝对管理权，这样也体现了共享的含义，但这是一种不合理的共享

     ![image-20250205094319879](..\0.TyporaPicture\image-20250205094319879.png)

   - 循环引用问题的解决思路——`weak_ptr`的引入

     将Parent类或Child类中的任意一个shared_ptr换成weak_ptr类型的智能指针

     例如：将Parent类中的shared_ptr类型指针换成weak_ptr

     ![image-20250205100631944](..\0.TyporaPicture\image-20250205100631944.png)

     栈上的childPtr对象销毁，会使堆上的Child对象的引用计数减1，因为这个Child对象的引用计数原本是1，所以现在减为0，从而回收了这个Child对象，造成了堆上的Parent对象的引用计数也减1（因为此Child内部的智能指针也销毁，所以触发其析构函数从而检查引用计数）

     ![image-20250205100836157](..\0.TyporaPicture\image-20250205100836157.png)

     然后，当parentPtr销毁时，会再让堆上的Parent对象的引用计数从1减为0，所以Parent对象也能够回收，从而就解决了循环引用的问题

     ![image-20250205102757308](..\0.TyporaPicture\image-20250205102757308.png)

4. **`weak_ptr`**

   weak_ptr是**弱引用的智能指针**，它是shared_ptr的一个补充，**使用它进行复制或者赋值时，并不会导致引用计数加1**，是为了解决shared_ptr的循环引用问题而诞生的
   
   weak_ptr知道所托管的对象是否还存活，且如果存活，**必须要提升为shared_ptr才能对资源进行访问**，不能直接访问
   
   - 初始化
   
     ```cpp
     weak_ptr<int> wp; // 无参的方式创建weak_ptr，!!!所有智能指针的默认值均为nullptr
     
     // 也可以利用shared_ptr创建weak_ptr 
     weak_ptr<int> wp2(sp);
     ```
   
   - 判断关联的空间是否还在
   
     1. **可以直接使用use_count函数**
   
        如果use_count的返回值大于0，表明关联的空间还在
   
     2. **将weak_ptr提升为shared_ptr**
   
        ```cpp
        shared_ptr<int> sp(new int(10));
        weak_ptr<int> wp; // 无参的方式创建weak_ptr
        wp = sp; // 赋值
        ```
   
        虽然通过shared_ptr赋值可以让wp也能够托管这片空间，但是它作为一个`weak_ptr`时仍不能够去管理，甚至连访问都不允许（weak_ptr不支持直接解引用）
   
        **想要真正地去进行管理需要使用`lock()`成员函数将`weak_ptr`提升为`shared_ptr`**
   
        ```cpp
        shared_ptr<int> sp2 = wp.lock(); // 若是没有shared_ptr对象来接收lock()返回值的话，在表达式结束之后，引用计数不变(+1-1=0)
        if (sp2) {
        	cout << "提升成功" << endl;
        	cout << *sp2 << endl;
        } else {
        	cout << "提升失败，托管的空间已经被销毁" << endl;
        }
        ```
   
        如果托管的资源没有被销毁，就可以成功提升为shared_ptr，否则就会返回一个空的shared_ptr（空指针）
   
        > **lock函数的说明**
        >
        > ```cpp
        > std::shared_ptr<T> lock() const noexcept;
        > // 将weak_ptr提升成一个shared_ptr，然后再来判断shared_ptr，进而知道weak_ptr指向的空间还在不在
        > ```
   
     3. **可以使用expired函数**
   
        ```cpp
        bool expired() const noexcept;
        // weak_ptr去判断托管的资源有没有被回收
        ```
   
        该函数返回true等价于use_count() == 0
   
        示例：
   
        ```cpp
        bool flag = wp.expired();
        if (flag) {
        	cout << "托管的空间已经被销毁" << endl;
        } else {
        	cout << "托管的空间还在" << endl;
        }
        ```

## 二、删除器

很多时候我们都用new来申请空间，用delete来释放。库中实现的各种智能指针，默认也都是用delete来释放空间。

但如果我们是用**fopen打开文件**，这时智能指针的默认处理方式就不能解决了，<font color=red>**必须为智能指针定制删除器**</font>，也就是**定制化释放资源的方式**

1. **unique_ptr对应的删除器**

   `std::unique_ptr`的类模板：

   ![image-20250205150959959](..\0.TyporaPicture\image-20250205150959959.png)

   定义unique_ptr时，如果没有指定删除器参数，就会使用默认的删除器。点开默认删除器的std::default_delete的说明可以发现其重载了()运算符：

   ![image-20250205151039467](..\0.TyporaPicture\image-20250205151039467.png)

   **默认删除器类型重载了函数调用运算符**，**底层还是利用函数对象的delete实现资源回收**

   根据参考文档的说明可知：对于默认的删除器来说，无论接管的是什么类型的资源，回收时都是会执行delete语句或delete[]，所以可能会导致出现问题

   - 问题示例

     - 文件指针原本的用法，回收时不会出现问题

       ```cpp
       void test0() {
           string msg = "hello,world\n";
           FILE* fp = fopen("res1.txt", "a+");
           fwrite(msg.c_str(), 1, msg.size(), fp);
           fclose(fp);
       }
       ```

     - 使用`unique_ptr`托管文件资源且使用默认删除器，回收时存在问题

       ```cpp
       // 用unique_ptr托管文件资源，回收时有问题
       void test1() {
           string msg = "hello,world\n";
           unique_ptr<FILE> up(fopen("res2.txt", "a+"));
           // get函数可以从智能指针中获取到裸指针
           fwrite(msg.c_str(), 1, msg.size(), up.get());
           // fclose(up.get()); // double free
       }
       ```

       一般地，智能指针的特点就是可以自动回收托管的资源，所以在接管资源后应该可以不用手动fclose（但只是单纯的delete）

       这样做会有<font color=red>**一个问题**</font>：内容msg并没有写到文件中去，因为没有fclose的调用，msg的内容存在缓冲区中，并不会刷新到文件流中

       ![image-20250205151438948](..\0.TyporaPicture\image-20250205151438948.png)

       但是显式进行fclose，又会出现double free的问题，即已回收的文件资源，由默认的删除器又会尝试进行一次回收

   - 问题的根本原因以及解决方法

     接管文件资源时，智能指针在析构时也是使用delete语句来回收资源，导致错误，所以需要自定义删除器

     仿照参考文档上默认删除器的示例，创建一个代表删除器的struct，定义operator()函数

     ```cpp
     struct FILECloser {
         void operator()(FILE * fp) {
             if (fp) {
                 fclose(fp);
                 cout << "fclose(fp)" << endl;
             }
         }
     };
     ```

   综上所述，在创建unique_ptr接管文件资源时，删除器参数需要使用我们自定义的删除器，示例：

   ```cpp
   void test1(){
   	string msg = "hello,world\n";
   	unique_ptr<FILE,FILECloser> up(fopen("res2.txt", "a+"));
   	// get函数可以从智能指针中获取到裸指针
   	fwrite(msg.c_str(), 1, msg.size(), up.get());
   }
   ```

   <span style=color:red;background:yellow>**总结：**</span>

   **如果管理的是普通的资源，不需要写出删除器**，就使用默认的删除器即可，只有**针对FILE或者socket这一类创建的资源，才需要自定义删除器**，使用fclose之类的函数

2. **shared_ptr对应的删除器**

   <span style=color:red;background:yellow>**unique_ptr 和 shared_ptr区别：**</span>

   - 对于unique_ptr，**删除器**是**模板参数**

     ![image-20250205151628132](..\0.TyporaPicture\image-20250205151628132.png)

   - 对于shared_ptr，**删除器**是**构造函数参数**

     ![image-20250205151643129](..\0.TyporaPicture\image-20250205151643129.png)

   所以传入删除器参数的位置不同：

   ```cpp
   void test1() {
       string msg = "hello,world\n";
       // 在unique_ptr的模板参数中加入删除器类
       unique_ptr<FILE，FILECloser> up(fopen("res2.txt", "a+"));
       fwrite(msg.c_str(), 1, msg.size(), up.get());
   }
   
   
   void test2() {
       string msg = "hello,world\n";
       FILECloser fc;
       //在shared_ptr的构造函数参数中加入删除器对象
       shared_ptr<FILE> sp(fopen("res3.txt", "a+"), fc);
       // 另一种写法
       // shared_ptr<FILE> sp2(fopen("res3.txt", "a+"), FILECloser()); // 这里的FILECloser()既不是函数也不是operator()成员函数，而是一个临时对象(使用无参构造函数)
       fwrite(msg.c_str(), 1, msg.size(), sp.get());
   }
   ```

## 三、智能指针的误用

智能指针被误用的情况，<span style=color:red;background:yellow>**原因都是将一个原生裸指针交给了不同的智能指针进行托管，而造成尝试对一个对象销毁两次**</span>

- **误用的具体情形**

  1. unique_ptr需要注意的误用

     ```cpp
     void test0() {
         // 需要人为注意避免
         Point * pt = new Point(1,2);
         unique_ptr<Point> up(pt);
         unique_ptr<Point> up2(pt);
     }
     
     void test1() {
         unique_ptr<Point> up(new Point(1,2));
         unique_ptr<Point> up2(new Point(1,2));
         // 让两个unique_ptr对象托管了同一片空间
         up.reset(up2.get());
     }
     ```

  2. shared_ptr需要注意的误用

     虽然shared_ptr是共享类型的智能指针，但是使用不同的shared_ptr智能指针对象托管同一片堆空间，**只能通过shared_ptr开放的接口**

     如果是用裸指针的形式将一片资源交给不同的智能指针对象管理，即使是shared_ptr也是不行的

     <span style=color:red;background:yellow>**之前进行的shared_ptr的复制、赋值的参数都是shared_ptr的对象，不能直接多次把同一个裸指针传给它的构造**</span>

     ```cpp
     void test2() {
         Point* pt = new Point(10,20);
         shared_ptr<Point> sp(pt);
         shared_ptr<Point> sp2(pt);
     }
     
     void test3() {
         // 使用不同的智能指针托管同一片堆空间
         shared_ptr<Point> sp(new Point(1,2));
         shared_ptr<Point> sp2(new Point(1,2));
         sp.reset(sp2.get());
     }
     ```

  3. 给被托管资源类加入了返回值为其本身指针的成员函数，并且还将返回值用于构造智能指针

     ```cpp
     Point* addPoint(Point* pt) {
     	m_x += pt->m_x;
     	m_y += pt->m_y;
     	return this;
     }
     ```

     ```cpp
     shared_ptr<Point> sp(new Point(1,2));    
     shared_ptr<Point> sp2(new Point(3,4));
     
     // 创建sp3的参数实际上是sp所对应的裸指针
     // 效果还是多个智能指针托管了同一块空间
     shared_ptr<Point> sp3(sp->addPoint(sp2.get()));
     cout << "sp3 = ";
     sp3->print();
     ```

     这样还是使得sp3和sp同时托管了同一个堆对象

     **需要给sp3的构造函数传入`shared_ptr<Point>` 对象，而不是裸指针**

     <span style=color:red;background:yellow>**解决思路：**</span>

     **修改成员函数的返回值为通过this指针获取的托管本对象的shared_ptr智能指针**

      - 错误改法

        ```cpp
        shared_ptr<Point> addPoint(Point* pt) {
            m_ix += pt->m_ix;
            m_iy += pt->m_iy;
            return shared_ptr<Point>(this); 
        }
        ```

        但是这样写，在addPoint函数中创建的匿名智能指针对象接收的还是sp对应的裸指针，那么这个匿名对象和sp所托管的空间还是同一片空间。匿名对象销毁时会delete一次，sp销毁时又会delete一次

        ```cpp
        // 验证如下
        sp->addPoint(sp2.get());
        delete sp.get(); // 此时指针所指向的堆空间已经被回收，程序崩溃
        cout << "over" << endl; // 不会被执行
        ```

      - 正确改法

        使用智能指针辅助类`class enable_shared_from_this`的成员函数`shared_from_this()`

        ![image-20250205152452832](..\0.TyporaPicture\image-20250205152452832.png)

        ![image-20250205152641659](..\0.TyporaPicture\image-20250205152641659.png)

        在Point的addPoint函数中需要使用shared_from_this函数返回的shared_ptr作为返回值，要想在Point类中调用enable_shared_from_this的成员函数，最佳方案可以**让Point类继承enable_shared_from_this类**

        ```cpp
        class Point : public std::enable_shared_from_this<Point> {
        public:
            // ...
            shared_ptr<Point> addPoint(Point& pt) {
                m_ix += pt.m_ix;
                m_iy += pt.m_iy;
                // 使用继承过来的shared_form_this()函数，以返回共享*this所有权的shared_ptr智能指针
                return shared_from_this();
            }
        };
        
        shared_ptr<Point> sp3(sp->addPoint(sp2.get())); // 至此，这类操作不会再引发问题
        ```

**总结：智能指针的误用全都是使用了不同的智能指针托管了同一块堆空间（同一个裸指针）**

## 四、补充

1. **智能指针本身不具备“延长右值生命周期”的能力**

   - **延长生命周期**：C++ 中只有**将临时对象绑定到 const 左值引用或右值引用**时，临时对象的生命周期才会延长到该引用的生命周期结束。
   - **移动语义**：智能指针的移动构造函数只是**转移资源所有权**，临时对象本身仍然在完整表达式结束时被销毁。

   根本原因：**只有将临时对象绑定到函数外部的引用变量才能延长其生命周期**，而函数参数（即使是引用）在函数返回后即销毁，无法充当那个外部载体。与生命周期长短比较无关

   > **智能指针的构造函数形参是指针，这决定了它根本接收不了指针指向的对象**
# Day21_STL标准模板库-序列式容器

## 一、标准模板库与STL六大组件

1. **STL标准模板库**

   - **标准模板库(Standard Template Library)**，简称STL，是一个具有工业强度的，高效的C++程序库。它被容纳于C++标准库中，是ANSI/ISO C++标准中最新的也是极具革命性的一部分。该库包含了诸多在计算机科学领域里所常用的基本数据结构和基本算法。为广大C++程序员们提供了一个可扩展的应用框架，高度体现了软件的可复用性
   - 与之前学到的编程思想面向对象编程不一样，STL采用的是一种新的编程模式：**泛型编程**。它允许程序员编写通用的代码，即可适用于不同的数据类型，而不必为每种类型编写不同的代码。这种编程方法的基本思想是将数据类型抽象化，使用泛型来表示数据类型，并在编写代码时使用泛型来代替具体的数据类型。本章重点在于介绍泛型编程的思想和本质，介绍一些常用的方法

2. **STL六大组件**

   1. **容器：用来存储数据，即数据结构**

      - **序列式容器**
        1. array(C++11) -- 静态的连续数组
        2. **vector - 动态的连续数组**
        3. **deque -- 双端队列**
        4. forward_list(C++11) -- 单链表
        5. **list -- 双链表**
      - **关联式容器：底层采取红黑树**
        1. set
        2. multiset
        3. map
        4. multimap
      - **无序关联式容器：底层采用哈希表**
        1. unordered_set
        2. unordered_map
        3. unordered_multiset
        4. unordered_multimap

   2. **迭代器：为了访问容器中的元素，可以将其看成是一种指针，称为泛型指针**

      ```cpp
      vector<int> nums = {1,2,3};
      vector<int>::iterator it = nums.begin();
      ```

   3. **算法：一些普通函数，可以操作容器中的元素**

      ```cpp
      std::sort(vec.begin(),vec.end());
      ```

   4. **适配器：起到适配的作用**

      - 容器适配器  stack、queue、priority_queue
      - 迭代器的适配器
      - 函数适配器   bind、bind1st、bind2nd、function等

   5. **函数对象：做定制化的操作**

   6. **空间配置器：管理内存**

3. **数据结构 + 算法 = 程序**

   ![image-20260302155445054](..\0.TyporaPicture\image-20260302155445054.png)

4. **STL六大组件之间的关系**

   - 容器作为STL的主体，是许多不同的数据结构 
   - 分配器为容器的实现分配应有的空间 

   - 泛型算法用来处理容器中的数据 

   - 迭代器是泛型算法和容器之间的桥梁

   - 仿函数使得算法可以有更加灵活的自定义模式 

   - 适配器保证了自定义的功能可以和STL中现有的功能相融合

## 二、序列式容器

### **1.基本操作**

#### 1.1 初始化

```cpp
// 1.无参构造
vector<int> box1; // vector<int> box1(); 是声明函数不是初始化
// 2.初始化列表
vector<int> box2 {1,2,3,4,5}; // 或 ({})
// 3.拷贝构造
vector<int> box3{box2}; // 或 vector<int> box3 = box2;
// 4.迭代器范围
vector<int> box4{box2.begin(), box2.end()}; // 左闭右开[,)
// 5.cout个value
vector<int> box5(3, 100); // 3个100
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list** 都具备五种初始化方式：
  1. 无参
  2. 初始化列表
  3. 拷贝或移动
  4. 迭代器范围
  5. count个value

#### 1.2 遍历

```cpp
vector<int> box1 {1,2,3,4,5};
// [下标]for i
for (int i = 0; i < box1.size(); ++i) {
    cout << box1[i] << " ";
}    
cout << endl;
// 增强for循环foreach
for (auto& e : box1) {
    cout << e << " ";
}
cout << endl;
// 迭代器
for (auto it = box1.begin(); it != box1.end(); ++it) {
    cout << *it << " ";
}
cout << endl;
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list 都支持使用增强for循环与迭代器**方式进行遍历
- 因为list不支持下标，所以**==仅list不能使用下标进行遍历==，vector与deque均可以通过[下标]进行遍历**

#### 1.3 在尾部进行插入与删除

```cpp
list<int> box{1,2,3};
box.push_back(4); // 1 2 3 4
box.push_back(5); // 1 2 3 4 5
box.pop_back(); // 1 2 3 4
box.pop_back(); // 1 2 3 4 5
// push_back 与 pop_back 的返回值类型均为 void
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list 均支持在尾部进行插入与删除**

#### 1.4 在头部进行插入与删除

```cpp
list<int> box{1,2,3};
box.push_front(4); // 4 1 2 3
box.push_front(5); // 5 4 1 2 3
box.pop_front(); // 4 1 2 3
box.pop_front(); // 1 2 3
// push_front 与 pop_front 的返回值类型均为 void
```

<span style=color:red;background:yellow>**总结：**</span>

**vector 不支持在头部进行插入与删除，deque、list 均支持**

#### 1.5 模型理解

- **vector**

  ![image-20250314113757563](..\0.TyporaPicture\image-20250314113757563.png)

  vector头部是固定的，不能通过`push_front`与`pop_front`进行插入与删除，因为其没有这两个成员函数，只提供了在尾部进行插入与删除的操作，如果真的要在头部插入或者删除，必须用通用的 **`insert()`** 和 **`erase()`**，但是这样的话，其他的元素会发生移动，这样操作就比较复杂（时间复杂度O(n)）

  **实现效果**是**动态数组**

  **底层实现**是**一块连续堆内存、三个指针（start, finish, end_of_storage）**

- **deque**

  ![image-20250314113918079](..\0.TyporaPicture\image-20250314113918079.png)

  **实现效果**是**双端队列**

  **底层实现**是**分段连续的动态数组（中控器 + 多个缓冲区）**

- **list**

  ![image-20250314114024724](..\0.TyporaPicture\image-20250314114024724.png)

  list的**实现效果**是**双向链表**

  **底层实现**是**带哨兵头结点的双向循环链表**

#### 1.6 源码阅读

- **vector**

  1. 继承图

     ![image-20241114211419722](..\0.TyporaPicture\image-20241114211419722.png)

  2. 源码

     ```cpp
     // 模板参数：_Tp 元素类型，_Alloc 空间分配器，默认为标准分配器
     template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
     class vector {
     public:
         // 1.基础类型别名（为容器和算法提供类型萃取的能力）
         typedef _Tp         value_type;          // 值类型，即容器中存放的元素类型
         typedef value_type* pointer;             // 指针类型，指向元素的指针
         typedef const value_type* const_pointer; // 指向 const 元素的指针
         // ★重点：vector的迭代器就是原生指针！
         // 因为 vector 的元素是连续存储的，指针完全满足随机访问迭代器的要求
         typedef value_type* iterator;            	// 可变迭代器，本质就是 _Tp*
         typedef const value_type* const_iterator;	// 只读迭代器，本质就是 const _Tp*
         typedef value_type& reference;           	// 元素引用类型
         typedef const value_type& const_reference;	// const 元素引用类型
         typedef size_t     size_type;            	// 大小类型（通常为 unsigned 整型）
         typedef ptrdiff_t  difference_type;      	// 差值类型（两个迭代器相减的结果类型，有符号整型）
     	// vector<int>::iterator it; // iterator相当于vector的内部
         // 后面还会有容量、修改操作等成员函数……
     };
     ```

     在源码中，除了vector的数据成员，还可以看到一些成员函数的实现，比如push_back有可能发生的动态扩容，2倍扩容的机制就写在源码中（主流实现分**1.5倍(MSVC)**和**2倍(GCC、Clang)**）

  3. 获取vector的第一个元素的首地址，应该怎么做？

     ![image-20240806111634713](..\0.TyporaPicture\image-20240806111634713.png)

     验证如下：

     ![image-20250314144207535](..\0.TyporaPicture\image-20250314144207535.png)

     vector中`at()`与`operator[]`都具备随机访问的含义，但是**operator[]完全不做范围检查**，存在越界的风险，也就是不安全，但是**at具备范围限制，更加安全**，测试如下：

     ![image-20250314144256583](..\0.TyporaPicture\image-20250314144256583.png)

     > - **迭代器 ≠ 原生地址**，它是**对指针 / 节点的封装（抽象化的指针）**
     >
     > - **只有 vector 的迭代器**（GCC/Clang 实现）**本质是原生指针**，可以直接输出地址
     >
     >   **list /deque/map 等所有其他容器**的迭代器是**类对象**，**不能直接用 cout 输出**（编译报错）
     >
     > - 想**通用、标准地获取元素的首地址**，永远用 `&*it`，而不是直接输出迭代器

- **deque**

  > **底层实现**
  >
  > **数组中控器（map）+ 多个缓冲区片段**的**分段连续内存结构**，**块内连续、块间不连续，整体物理上不连续，逻辑上连续**
  >
  > 1. 数据缓冲区
  >
  >    - 每个缓冲区是**固定大小的连续数组**（SGI 实现默认 512 字节）
  >    - 元素真实存在这些小块里，**块内地址连续**
  >    - 块与块之间**地址不连续**
  >
  > 2. 数组中控器（map，即指针数组）
  >
  >    - `T** map;`：每个元素是一个 `T*`，指向一块缓冲区
  >    - 相当于一个**动态的二维数组**：`map[i]` 指向第 i 个数据块
  >
  > 3. 头尾插入
  >
  >    - `push_back`：尾块有空间直接写；满了就**新开一块**，放到 `map` 尾部
  >    - `push_front`：头块有空间直接写；满了就**在 map 头部插入新块**
  >    - 只新增 / 删除指针和小块，**不移动大量元素**，效率远高于 vector 的头插
  >
  > 4. 中控 map 扩容
  >
  >    当 map数组满了（指针不够用）：
  >
  >    - 重新分配一个**更大的指针数组**
  >    - 把旧指针复制过去
  >    - 旧 `map` 释放，**数据块本身不需要拷贝**
  >
  > 5. 迭代器
  >
  >    - `cur`：当前元素指针
  >    - `first`/`last`：当前块首尾
  >    - `node`：指向 `map` 中当前块的指针
  >
  > deque 底层采用 “中控指针数组 + 固定大小数据块” 的分段连续存储，块内连续、块间不连续；通过中控数组实现 O (1) 随机访问，头尾增删 O (1)，兼顾 vector 的随机访问和 list 的头尾高效操作

  1. 继承图

     ![image-20250324164403999](..\0.TyporaPicture\image-20250324164403999.png)

  2. 原理

     deque是由多个片段组成的，**片段内部连续**，**片段之间不连续**，多个片段被一个称为中控器的结构控制（也称为map，但是跟容器std::map不是一回事）

     所以说deque是<font color=red>**在物理上是不连续的，但是逻辑上是连续的**</font>

     - 初始化

       初始化deque时，根据元素的个数分配一个/多个缓冲区片段，在缓冲区片段中存放实际的元素，这里以int型元素为例。**通常情况下，在初始化时第一个元素会被放置在第一个缓冲区中相对靠前的位置（而非第一个缓冲区的首地址，这样方便在头部添加元素）**，前后相邻的两个元素在逻辑上是连续的，但是物理层面上可能并不是连续的

       同时还会生成一个**数组中控器（map），存放每个缓冲区片段的首地址**（注意map中的元素是`int* p`，而不是严格意义的数组指针即`int (*p)[]`，这一点从源码中可以进行理解），**通常情况下，第一个缓冲区片段的首地址被放在中控器map的居中位置**

     - 插入元素

       deque初始化完成后，进行添加元素的操作：

       1. **如果在尾部添加元素value**

          找到最后一个存放着元素的缓冲区片段，在其中最后一个元素的后面添加元素value

          **如果此时最后的缓冲区片段是满的**，那么就再**申请一个新的缓冲区片段（作为最后一个片段）**，**将要添加的元素value存放在新片段的首个位置**。同时中控器也加上一个元素（新片段的首地址），让中控器与新片段联系起来

       2. **如果是在deque的头部添加元素value**

          找到已经存储的第一个元素的位置，在它的前面存放新元素value

          经过若干次头部添加元素之后，**如果第一个缓冲区片段满了**，还要继续在头部添加元素，则**新开辟一个缓冲区片段（作为第一个片段）**，**将value存在新片段中的最后一个位置**。同时在中控器的相应位置存放新的缓冲片段的首地址

       3. **那么这里会有一个小小的问题（数组中控器map扩容）**

          如果一直往deque头部添加元素，中控器的前半部分已经满了，后半部分还没满，会怎么样呢？

          这种情况会通过一个reallocate_map函数来管理中控器的设置，**先做一个判断，我们可以简单理解为如果中控器后半部分的空位较多，那么就将中控器中记录的地址全都后移若干位**，这样中控器的前半部分就有空位了。**如果中控器后半部分的空位较少，就再开辟新的更大的空间作为中控器，将原本中控器中记录的地址复制到新的中控器中**

          同理，如果一直往deque尾部添加元素，中控器的后半部分已经满了，前半部分还没满，也是一样的处理流程

       4. **注意：**

          在deque头部添加元素或者尾部添加元素的过程中，原本已经存在deque中的元素始终没有改变位置，这一点与vector形成很大的区别

          ![image-20250315160520768](..\0.TyporaPicture\image-20250315160520768.png)

     - 每个缓冲区片段的元素个数

       每个缓冲区是**固定大小的连续数组**（SGI 实现默认 512 字节）

       ![image-20250314162540413](..\0.TyporaPicture\image-20250314162540413.png)

       如果deque存放的元素类型的大小小于 512 字节。每个缓冲区片段的大小为 512 字节，512 除以元素类型的大小，就可以得到每个缓冲区片段能够存放的元素数量

       例如元素类型是 int，在 64 位系统中，sizeof(int)= 4 字节。**那么 deque_buf_size(4) 的结果就是 512 / 4 = 128，即每个缓冲区片段可以存放 128 个 int 类型的元素**

       这种设计的好处是，对于较小的元素类型，每个缓冲区可以存放较多的元素，减少了缓冲区的数量，从而降低了中控器（用于管理缓冲区的数组）的管理开销

       如果元素类型大小大于等于 512 字节，函数返回 1。这表示每个缓冲区片段只存放一个元素，比如自定义类型A的对象作为deque的元素，单个元素的大小超过了 512 字节，那么 __deque_buf_size(sizeof(A)) 的结果就是 1，每个缓冲区片段只会存放一个 A类型的元素

     - deque的迭代器底层

       deque的迭代器比vector的迭代器复杂得多，`vector<T>`的迭代器实际是对T*的包装，但deque的迭代器实际应该视为对象，数据成员包含四个指针，并且进行了一系列的运算符重载，使得迭代器能够像指针一样被使用

       ![image-20250315161915597](..\0.TyporaPicture\image-20250315161915597.png)
  
       ![image-20250315161952642](..\0.TyporaPicture\image-20250315161952642.png)

#### ==1.7 insert操作==

之前的push_back和push_front尽管可以插入元素，但是插入的位置都比较固定

实际上三种序列式容器都允许在任意位置插入元素，使用insert成员函数即可

- 它们都具备以下四种插入的功能

  ![image-20240806144651816](..\0.TyporaPicture\image-20240806144651816.png)

  ```cpp
  vector<int> box{1,2,3,4,5};
  cout <<"size=" << box.size() << endl; // 5
  cout << "capacity=" << box.capacity() << endl; // 5
  print(box); // 1 2 3 4 5
  // 1.给定位置，插入单个元素
  auto it =box.begin();
  ++it;
  // box.insert(it, 100); 由于扩容机制，所以可能会有迭代器失效的问题
  it = box.insert(it, 100); // 所以必须更新迭代器
  cout <<"size=" << box.size() << endl; // 6
  cout << "capacity=" << box.capacity() << endl; // 10
  print(box); // 1 100 2 3 4 5
  cout << "*it=" << *it << endl; // 100
  // 2.给定位置，插入多个元素 
  it = box.insert(it, 2, 200); // 更新迭代器
  print(box); // 1 200 200 100 2 3 4 5
  cout << "*it=" << *it << endl; // 200
  ++it;
  cout << "*it=" << *it << endl; // 200
  ++it;
  cout << "*it=" << *it << endl; // 100
  // 3.给定位置，插入迭代器范围
  auto it2 = box.begin();
  ++it2;
  vector<int> box2{10,20,30};
  it2 = box.insert(it2, box2.begin(), box2.end());
  print(box); // 1 10 20 30 200 200 100 2 3 4 5
  // 4.给定位置, 用初始化列表插入
  it2 = box.insert(it2, {1000,2000});
  print(box); // 1 1000 2000 10 20 30 200 200 100 2 3 4 5
  cout << "*it2=" << *it2 << endl; // 1000
  ```
  
- 以list为例

  1. 双向链表由于其底层结构的原因，插入是非常方便的

     ![image-20241203105613687](..\0.TyporaPicture\image-20241203105613687.png)

  2. 从参考文档出发可知三种序列式容器都有这样的插入方式，但insert过程中的细节却值得注意

     ![image-20241203112930981](..\0.TyporaPicture\image-20241203112930981.png)

  3. 如果把list换成deque，情况会有所不同

     ![image-20241203151641204](..\0.TyporaPicture\image-20241203151641204.png)

  4. 在利用迭代器遍历容器元素并做出处理时，往往需要更新迭代器

     <span style=color:red;background:yellow>**虽然insert函数有多种形式，但它们的返回值都是指向第一个被插入元素的迭代器**</span>

     ![image-20241203152546132](..\0.TyporaPicture\image-20241203152546132.png)
  
  5. 对于vector，insert操作执行过程中还存在着更大的隐患，可能导致<span style=color:red;background:yellow>**迭代器失效**</span>
  
     ![image-20241203162022141](..\0.TyporaPicture\image-20241203162022141.png)
  
     这是因为当vector使用insert进行插入时，可能会发生动态扩容。比如上述的nums是一个“存满”状态的vector，此时size和capacity的结果是一样的。增加新的元素会进行扩容
  
     扩容的过程中会申请一块新的空间，然后将老的空间上的元素拷贝到新的空间来，然后会清理老的空间、这时如果还继续使用原本的迭代器，对应的也就是老的空间的地址，会出现问题，因为此时迭代器已经失效了
  
     <span style=color:red;background:yellow>**所以，每次在使用迭代器进行insert操作时，更新迭代器（重新置位）**</span>
  
     ![image-20241203175553874](..\0.TyporaPicture\image-20241203175553874.png)
  
     > <span style=color:red;background:yellow>**补充**</span>
     >
     > 之前在学习vector的push_back操作时，我们了解了2倍扩容机制。而insert导致的扩容，规则更复杂一些。
     >
     > **vector的insert扩容（仅作了解）**
     >
     > ``` cpp
     > nums.size() = m
     > nums.capacity() = n;
     > // 要插入的元素的个数为t
     > // (1) t < n - m       	不会扩容
     > // (2) n - m < t < m   	按照2*size()进行扩容
     > // (3) n - m < t, m < t	按照t + m进行扩容，即新插入的元素的数量大于当前元素个数，仅将容量单纯扩大为当前元素个数的2倍仍装不下
     > ```
     >

#### ==1.8 erase操作==

三种序列式容器都可以进行erase操作，用来删除容器中的单个元素或多个元素

![image-20240806160154610](..\0.TyporaPicture\image-20240806160154610.png)

- **list的erase操作**

  由于list的原理，list中的元素无论是插入还是删除都非常的方便，erase后迭代器it仍然指向原本的地址（<font color=red>**实际已经不属于list元素的空间，也可以归为一种迭代器失效问题**</font>），想要继续正常使用it，需要进行迭代器更新

  <span style=color:red;background:yellow>**erase函数的返回值为被删除元素后一位元素对应的迭代器**</span>

  ![image-20241202175257615](..\0.TyporaPicture\image-20241202175257615.png)

- **deque的erase操作**

  deque的erase操作后，迭代器it仍然指向原本的位置。但是原本的位置上存放的是什么，**取决于删除的元素属于前半段还是后半段**

  > `deque` 是分段连续空间——由多个固定大小的数组（缓冲区）通过一个中控器（指针数组）串联而成
  > 这导致它**不能像 `vector` 那样直接通过一个指针偏移来整体搬移元素**，因为元素可能跨缓冲区
  >
  > 因此，当在中间删除一个元素时，必须移动后续所有元素来填补空位，但往哪边移动就成了一个选择：
  >
  > - 可以把**被删位置前面的元素整体往后移一位**（覆盖被删元素）
  > - 或者把**被删位置后面的元素整体往前移一位**（覆盖被删元素）

  ![image-20241203093724218](..\0.TyporaPicture\image-20241203093724218.png)

  如果想要在erase之后继续正常使用it这个迭代器，那么同样建议进行迭代器更新

  ![image-20241203093928234](..\0.TyporaPicture\image-20241203093928234.png)

- **vector的erase操作**

  如果将上述例子中的容器换成vector，似乎不会出现问题：

  删除掉一个元素后，如果不更新迭代器，后面的元素往前移，迭代器仍指向原本的位置，对应的就是被删除的元素后一位的元素，如果更新迭代器，迭代器指向也能够确保是后一位的元素

  也就是说，**对于vector而言，使用erase删除单个元素时，是否更新迭代器效果是一样的**

  > **注意：在删除连续重复元素时，可能出现的逻辑上的错误**
  >
  > - 例如：使用vector时很可能写出这样的代码
  >
  >   ![image-20241204110148074](..\0.TyporaPicture\image-20241204110148074.png)
  >
  >   此时通过`it = nums.erase(it)`这样简单更新迭代器并不能解决问题（效果一样）。问题的**根本在于无论是对于该删除的元素还是不该删除的元素，迭代器的偏移采取的是统一的方式**
  >
  >   因为在vector在物理存储上是连续的，如果删掉某个元素，后面的元素前移，如果此时迭代器依然往后移动一次，那么就会跳过一个元素
  >
  >   **解决方式：在==删除元素时，不移动迭代器==，从逻辑的角度上来说，对应的元素已经变成了被删元素的下一位**
  >
  > - list进行erase时，**还需要更新迭代器**
  >
  >   因为list在物理存储上是不连续的，所以erase后仍旧指向已经失效的被删除元素，所以需要更新erase即向后移动一次
  >
  >   ![image-20241204115650449](..\0.TyporaPicture\image-20241204115650449.png)

#### 1.9 元素的清空

![image-20240806162826639](..\0.TyporaPicture\image-20240806162826639.png)

![image-20240806162838101](..\0.TyporaPicture\image-20240806162838101.png)

![image-20240806162848551](..\0.TyporaPicture\image-20240806162848551.png)

<span style=color:red;background:yellow>**总结**</span>：

- 三种序列式容器 **vector、deque、list 都有`clear()`**清空元素、以及获取元素个数的函数**`size()`**
- 对于 **vector与deque，还有**回收多余空间的函数**`shrink_to_fit()`**
- 对于 **vector** 还有记录容量大小的函数**`capacity`**

#### 1.10 其它成员函数

```cpp
// 三种序列式容器均具备的：
// 交换
void swap( list& other ); // 此处的list可以改为vector或者deque，注意：交换的两个容器类型要完全相同
// 改变元素个数
void resize( size_type count, T value = T() );
void resize( size_type count );
void resize( size_type count, const value_type& value )
// 获取容器的第一个元素与最后一个元素
reference front(); 
const_reference front() const;
reference back();
const_reference back() const;    
```

#### 1.11 emplace(_back)函数

这三种序列式容器还有两个值得关注的函数：`emplace` 和 `emplace_back`

- `emplace` 与 `insert`对比，前者是直接在指定位置构造对象，后者是将一个已存在的对象复制并插入到容器中指定位置
- `emplace_back` 与 `push_back`对比， 前者是直接在容器尾部构造对象，后者是将一个已存在的对象复制并插入到容器末尾

![image-20250317095728675](..\0.TyporaPicture\image-20250317095728675.png)

- `emplace_back`的效果

  ![image-20240806164845608](..\0.TyporaPicture\image-20240806164845608.png)

- `emplace`的效果

  ![image-20250317104810864](..\0.TyporaPicture\image-20250317104810864.png)

> 补充：**STL中的emplace_back和push_back有什么区别？**
>
> 1. 构造方式不同
>
>    - **push_back**：
>
>      先在容器**外部**构造一个完整对象（或传入已存在的对象），然后将该对象**拷贝或移动**到容器尾部
>
>    - **emplace_back**：
>      直接在容器**内部内存空间**中，用传入的参数**原地构造对象**，不产生临时对象
>
> 2. 参数形式不同
>
>    - **push_back**：接收**一个已构造好的对象**（值、左值引用或右值引用）
>    - **emplace_back**：接收**元素构造函数的参数列表**（支持多参数、可变参数）
>
> 3. 性能差异
>
>    - **push_back**：
>      至少一次**拷贝构造**或**移动构造**，还可能产生临时对象并析构，开销较大
>    - **emplace_back**：
>      **仅一次构造函数调用**，无临时对象、无额外拷贝 / 移动，效率更高；对象越复杂，性能优势越明显

### ==2.list的特殊操作==

list还具有一些vector与deque没有的**独占成员函数**

#### 2.1 sort——排序

> 注意：vector和deque没有此**成员函数**，通过**全局算法函数**`std::sort(vec.begin(),vec.end());`来对容器内的元素进行排序

- **函数原型**

  将list中的元素排序

  ![image-20241205154048844](..\0.TyporaPicture\image-20241205154048844.png)

- **无参版本的示例**

  如果使用**无参版本的sort函数**，则list中的元素**默认以升序排列**

  ![image-20241205154657832](..\0.TyporaPicture\image-20241205154657832.png)

- **有参版本**

  第二个版本的sort函数有一个参数，参数为Compare类型的对象。关于Compare，第一次见到应该是在set类模板声明中

  ![image-20241206162659730](..\0.TyporaPicture\image-20241206162659730.png)

  之前在简单使用set时我们知道元素会默认按照升序排序，这里就**是使用了`std::less<key>`的效果**：

  ![image-20241206162926925](..\0.TyporaPicture\image-20241206162926925.png)

  效果和无参的sort版本是一样的，同样采用升序排序

  **这里对std::less的使用与之前unique_ptr的默认删除器的使用是很相似的**

  ![image-20241206163620509](..\0.TyporaPicture\image-20241206163620509.png)

  - `std::less`类的内部

    通过cpp参考文档能够了解到std::less进行了函数调用运算符的重载，在`operator()`函数中接受两个参数，代表两个元素，在函数定义中对两个元素进行了比较

    ![image-20241206164121319](..\0.TyporaPicture\image-20241206164121319.png)

  - 降序排列

    如果想要按照降序排列，对应位置可以换成std::greater

    ![image-20241209102349777](..\0.TyporaPicture\image-20241209102349777.png)

  - 定制化Compare

    当然，针对需要排序的各种元素类型，可能需要更灵活的Compare，那么我们可以像定制化删除器一样定制化Compare

    ![image-20241209105703516](..\0.TyporaPicture\image-20241209105703516.png)

    会发现自定义的Compare对象被当成函数调用了很多次，可以简单阅读list的**sort**函数源码，发现**其底层实现实际是一种基于归并排序的做法**

    ```cpp
    // 两个template关键字，是因为这里定义的是类模板的成员函数模板，而且在类外定义。此为C++语法规定的写法
    
    template <class _Tp, class _Alloc>
    template <class _StrictWeakOrdering>
    void list<_Tp, _Alloc>::sort(_StrictWeakOrdering __comp) 
    {
        // 如果链表长度 <= 1，则已经有序，直接返回
        // _M_node 是链表的尾后哨兵节点，_M_node->_M_next 是真正的头节点
        // 条件: 头节点不是哨兵 (链表非空) 且 头节点的下一个不是哨兵 (长度 >= 2)
        if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node) 
        {
            list<_Tp, _Alloc> __carry;          // 临时存放当前待归并的小段
            list<_Tp, _Alloc> __counter[64];    // 归并桶数组，counter[i] 最多存 2^i 个元素
            int __fill = 0;                     // 当前使用到的最大桶索引 + 1
    
            // 不断从原链表中剥离第一个元素，放入 __carry 作为长度为 1 的有序段
            while (!empty()) 
            {
                // 将 *this 的第一个元素剪切到 __carry 的头部
                __carry.splice(__carry.begin(), *this, begin());
    
                int __i = 0;
                // 像二进制加法一样，若当前桶 i 非空，则与 __carry 合并，并进位到下一桶
                while (__i < __fill && !__counter[__i].empty()) 
                {
                    // 将 __carry 合并到 __counter[__i] 中，结果留在 __counter[__i]
                    __counter[__i].merge(__carry, __comp);
                    // 交换 __carry 与 __counter[__i]，现在 __carry 持有合并后更大的有序段
                    __carry.swap(__counter[__i++]);
                }
                // 将进位得到的 __carry 放入空桶 __counter[__i]
                __carry.swap(__counter[__i]);
                // 如果进位到了更高的空桶，更新 __fill
                if (__i == __fill) 
                    ++__fill;
            }
    
            // 此时，所有元素已分布在不同大小的桶中（counter[0] ~ counter[fill-1]）
            // 需要将所有桶从低到高依次合并，最终结果汇聚在 counter[fill-1]
            for (int __i = 1; __i < __fill; ++__i)
                __counter[__i].merge(__counter[__i - 1], __comp);
    
            // 将最终结果交换回 *this
            swap(__counter[__fill - 1]);
        }
    }
    
    template <class _Tp, class _Alloc>
    template <class _StrictWeakOrdering>
    void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x,
                                  _StrictWeakOrdering __comp) 
    {
        iterator __first1 = begin();    // 当前链表起始位置
        iterator __last1  = end();      // 当前链表尾后哨兵
        iterator __first2 = __x.begin();// __x 起始位置
        iterator __last2  = __x.end(); // __x 尾后哨兵
    
        // 两个链表都还有元素时，比较头部元素
        while (__first1 != __last1 && __first2 != __last2)
        {
            // 若 __x 的头元素更小（按严格弱序），将其转移到当前链表的 __first1 之前
            if (__comp(*__first2, *__first1)) 
            {
                iterator __next = __first2;      // 暂存当前节点
                // transfer: 将 [__first2, ++__next) 即单个元素移动到 __first1 之前
                transfer(__first1, __first2, ++__next);
                // 更新 __first2 为下一个节点（transfer 后原 __first2 已移走）
                __first2 = __next;
            }
            else 
            {
                // 否则当前链表元素更小（或相等），直接后移 __first1
                ++__first1;
            }
        }
    
        // 如果 __x 还有剩余元素，全部粘接到当前链表尾部
        if (__first2 != __last2)
            transfer(__last1, __first2, __last2);
    }
    ```

#### 2.2 reverse——将list中所有元素顺序反转

![image-20241209114609938](..\0.TyporaPicture\image-20241209114609938.png)

> 注意和vector的reserve函数(预留空间)区分，拼写上非常相似

![image-20250317155350549](..\0.TyporaPicture\image-20250317155350549.png)

#### 2.3 unique——去重list中重复的元素

**必须先排序**（无论是从小到大还是从大到小），才能够实现效果

![image-20250317154753075](..\0.TyporaPicture\image-20250317154753075.png)

#### 2.4 merge——将一个list合并到当前list中

**合并结果**：lst2中的元素合并到lst1中，**lst2的元素被清空**

> 注意：如果合并前的list是无序的，合并后的list整体也是无序的
>
> 想要合并后的list结果是有序的，需要<span style=color:red;background:yellow>**合并前两个list中的元素先排好序**</span>

![image-20250818212441074](..\0.TyporaPicture\image-20250818212441074.png)

![image-20250818212500682](..\0.TyporaPicture\image-20250818212500682.png)

#### 2.5 remove & remove_if——移除元素

- remove函数能够**移除所有等于 value 的元素**

- remove_if函数能够**移除所有符合条件的元素**，==需要传入一个一元谓词（返回值为bool的一元函数）——如果某元素作为函数参数能够返回true，则判定为应该删除的元素==

  ![image-20250808154243844](..\0.TyporaPicture\image-20250808154243844.png)

#### 2.6 splice——移动元素

> `splice` 是**直接修改原数组**的方法，它会从数组中**物理移除**元素，返回的是被移除元素组成的新数组

![image-20240807100112283-1733123638304-4](..\0.TyporaPicture\image-20240807100112283-1733123638304-4.png)

==第一个参数相当于是移动的目的地==

![image-20240807100952020-1733123638304-5](..\0.TyporaPicture\image-20240807100952020-1733123638304-5.png)

![image-20240807101035059-1733123638304-6](..\0.TyporaPicture\image-20240807101035059-1733123638304-6.png)

<span style=color:red;background:yellow>**注意：**</span>如果在同一个链表中进行splice操作

![image-20240807101633898-1733123638304-7](..\0.TyporaPicture\image-20240807101633898-1733123638304-7.png)

**可能会出现问题（取决于范围有没有交叉）**

类似于strcpy，目的字符串与源字符串不要有交叉，同理还有memcpy也是要注意这个问题

> 补充：
>
> - splice函数可以帮助我们很方便地实现LRU(Least Recently used)
>
>
> - <span style=color:red;background:yellow>**LRU:最近最少使用算法**</span>
>
>   一种常用的页面置换算法，用于在有限的内存空间中管理数据缓存，以提高系统性能
>
>   LRU 算法基于一个假设：如果一个数据在最近一段时间内没有被访问，那么在未来它被访问的概率也相对较低。因此，当内存空间不足时，LRU 算法会选择淘汰最近最少使用的数据，为新的数据腾出空间
>
>   ```cpp
>   思想：新元素放在前面，老的元素放在后面
>   比如现在有 1 2 3 4 四个元素逐一存到容器中，限制容量为4
>   刚存放完       插入元素3      插入元素5      插入元素4
>   4 3 2 1 ----> 3 4 2 1 ----> 5 3 4 2  ---> 4 5 3 2
>       
>   // 假设现在插入元素2   
>   int number = tmp.back();
>   tmp.pop_back();
>   tmp.push_front(number);
>       
>   // 如果明确了是用list存储，可以使用splice函数，
>   tmp.splice(tmp.begin(), tmp, --tmp.end());
>   ```
# Day22_STL标准模板库2-关联式容器与无序关联式容器

## 一、关联式容器

**关联式容器包括：set、multiset、map、multimap四种**。它们的底层使用的数据结构都是**红黑树**。要学习它们的使用，可以从：**初始化、遍历、查找、插入、删除、针对自定义类型的处理**等方面进行学习。

> - set特征
>   存放的是**key类型**，key值是**唯一**的，**不能重复**
> - multiset特征
>   存放的是**key类型**，key值**不一定唯一**，**可以重复**
> - map的特征
>   存放的是**key-value类型**，key值是**唯一**的，**不能重复**，**value没有要求是否唯一**
> - multimap的特征
>   存放的是**key-value类型**，key值**不一定唯一**，**可以重复**，**value没有要求是否唯一**
>
> 且以上均为**默认按照关键字key进行升序排列**

## 1.set的使用

### 1.1 构造

![image-20250317175534262](..\0.TyporaPicture\image-20250317175534262.png)

- **无参构造**

- **迭代器方式进行构造，传入一个first迭代器，传入一个last迭代器**

- **拷贝构造**

- **标准初始化列表（大括号的形式）**

### 1.2 基本特征

![image-20240807115258806](..\0.TyporaPicture\image-20240807115258806-1733124502629-22.png)

### 1.3 查找

![image-20240807112809259](..\0.TyporaPicture\image-20240807112809259-1733124502628-19.png)

### 1.4 insert操作

![image-20240807113245685](..\0.TyporaPicture\image-20240807113245685-1733124502629-20.png)

![image-20240807114212763](..\0.TyporaPicture\image-20240807114212763-1733124502629-21.png)

==**注意：关联式容器都没有头部插入/删除或者尾部插入/删除的函数（因为插入之后是自动排序的，根本不需要关心一开始插入的位置）**==

### 1.5 erase操作

![image-20240807114416260](..\0.TyporaPicture\image-20240807114416260-1733124502629-23.png)

> <span style=color:red;background:yellow>**注意**</span>
>
> - **set不支持下标操作，因为没有operator[]函数**
>
>   ![image-20240807114916461](..\0.TyporaPicture\image-20240807114916461-1733124502629-25.png)
>
>   所以**访问set的元素只能通过迭代器方式**，但通过迭代器访问到的元素**只能进行读操作**
>
> - **set的元素不支持修改**
>
>   ![image-20240807115114358](..\0.TyporaPicture\image-20240807115114358-1733124502629-24.png)

### ==1.6 针对于自定义类型的写法==

![image-20240808102542239](..\0.TyporaPicture\image-20240808102542239-1733124502629-26.png)

对于set而言，因为第二个模板参数Compare默认会采用std::less，但是std::less针对的Key如果不能比较大小即当Key类型是类类型的时候，就需要进行改写

因为直接定义一个存放Point的set，编译一定会报错，根本原因在于默认的std::less针对Point对象并不知道该如何比较大小

<img src="..\0.TyporaPicture\image-20250317183935132.png" alt="image-20250317183935132" style="zoom:67%;" />

改写的方式有三种：<span style=color:red;background:yellow>**模板的特化、运算符的重载、函数对象**</span>

1. **模板的特化**

  std::less是一个通用模板类，针对解决不了的特殊类型，可以想到<span style=color:red;background:yellow>**特化模板**</span>

  **为std::less准备一个特化版本，这个特化模板类中定义函数调用运算符重载函数，定义一套Point对象的比较规则**

  ![image-20250318150258925](..\0.TyporaPicture\image-20250318150258925.png)

    > 自定义对象的**比较规则当然也是自定义的**，例如：
    >
    > 先比较到原点的距离（定义getDistance获取点到原点的距离），如果相同再比较横坐标，如果再相同再比较纵坐标。
    >
    > ![image-20250318150348968](..\0.TyporaPicture\image-20250318150348968.png)
    >
    > <span style=color:red;background:yellow>**注意：**</span>
    >
    > - 在operator()函数中需要访问Point的私有成员，可以有两个思路：
    >
    >   1. 在自定义类中中作相应的友元声明；
    >
    >      <img src="..\0.TyporaPicture\image-20241226224935206.png" alt="image-20241226224935206" style="zoom:67%;" />
    >
    >   2. 给Point提供公有的get系列函数，间接访问Point的私有数据成员
    >
    > - 函数调用运算符重载函数(即operator())最好设为**const函数**
    >
    >   因为在 C++17 中，std::set 要求比较对象必须是 **常量可调用** 的。模板参数列表中的class Compare在set的底层实现中会创建出对象，并作为函数对象使用，也就是调什用operator()函数，这个函数需要是const成员函数
    >
    >   - 参考std::less的operator()函数
    >
    >
    >   ![image-20250317193513788](..\0.TyporaPicture\image-20250317193513788.png)
    >
    >   - 这涉及了set的内部实现的版本演变，不做探究
    >
    >
    >   <img src="..\0.TyporaPicture\image-20250317192201592.png" alt="image-20250317192201592" style="zoom:67%;" />

2. **(对象)运算符重载**

   当然，如果让std::less通用模板知道Point对象该怎么比较大小可以做到吗？当然可以，使用<span style=color:red;background:yellow>**运算符重载**</span>就行

   operator< 以友元方式重载：（也可以重载为类的成员函数）

   ![image-20240808102807663](..\0.TyporaPicture\image-20240808102807663-1733124502629-28.png)

   **这个场景下，如果特化模板与运算符重载同时存在，==模板特化优先级高于运算符重载==**

3. **(比较)函数对象(即自定义比较器)**

   上面两种方法都是围绕着std::less想办法，我们也可以自已准备Compare类（类似于智能指针的删除器，也可以理解为自定义比较器）

   Compare类重载函数调用运算符，set的底层实现中使用Compare类对象作为<span style=color:red;background:yellow>**函数对象**</span>，以此来规定元素的排序

   ![image-20240808102837821](..\0.TyporaPicture\image-20240808102837821-1733124502629-29.png)

## 2.multiset的使用

### 2.1 基本特征

包含于`<set>`头文件

![image-20240808110150953](..\0.TyporaPicture\image-20240808110150953-1733124502629-30.png)

### 2.2 其他功能

multiset的**查找功能（count、find）、插入功能（insert）、删除功能（erase）与set是一样的**

multiset**也没有[]下标操作，也同样不支持使用迭代器修改元素**

### 2.3 bound系列函数

注意：**equal_range返回的范围仍然是前闭后开的范围（返回的是一对数据即一个pair对象，其中包含两个迭代器）**

<img src="..\0.TyporaPicture\image-20241210101903143.png" alt="image-20241210101903143" style="zoom:67%;" />

<img src="..\0.TyporaPicture\image-20250318143726479.png" alt="image-20250318143726479"  />

<img src="..\0.TyporaPicture\image-20250318143624627.png" alt="image-20250318143624627"  />

<img src="..\0.TyporaPicture\image-20250318143647024.png" alt="image-20250318143647024"  />

> 如下，可以用**两种方式找出multiset中所有等于key的元素**
>
> 1. **[it11, it22)**
> 2. **(std::pair)ret**
>
> ![image-20240808111636211](..\0.TyporaPicture\image-20240808111636211-1733124502630-31.png)

### 2.4 针对于自定义类型

multiset**针对于自定义类型的用法**与set完全一样，**也有三种形式：模板的特化、函数对象的形式、运算符重载**

## **3.map的使用**

### 3.1 基本特征

![image-20240808113609526](..\0.TyporaPicture\image-20240808113609526-1733124502630-32.png)

### 3.2 查找

<img src="..\0.TyporaPicture\image-20250318145851453.png" alt="image-20250318145851453"  />

![image-20240808113855833](..\0.TyporaPicture\image-20240808113855833-1733124502630-33.png)

### 3.3 insert操作

![image-20250318145655104](..\0.TyporaPicture\image-20250318145655104.png)

map**也有三种插入的方式：插入一个元素、插入迭代器范围的元素、插入大括号范围的元素**

> **注意**
>
> 插入时是**要插入一个或多个pair(包含一个key+一个value)**，**而不是插入key或者插入value**
>
> ==插入单个元素可能不成功（即这个元素已经存在于map中）==
>
> ![image-20240808114453984](..\0.TyporaPicture\image-20240808114453984-1733124502630-34.png)

### 3.4 erase操作

![image-20240808114701760](..\0.TyporaPicture\image-20240808114701760-1733124502630-35.png)

**map可以删除==迭代器指向的元素==、以及==迭代器范围的元素==**

### 3.5 下标操作（重要）

![image-20240808121115356](..\0.TyporaPicture\image-20240808121115356-1733124502630-36.png)

<span style=color:red;background:yellow>**注意：**</span>

使用下标操作时，如果下标传入的是不存在的key，那么会将这个新的key和value的默认值组合成一个pair，插入到map之中

==这就有一个要求：**value对应的类型能够产生一个默认值**==

### 3.6 针对于自定义类型

![image-20240808144703570](..\0.TyporaPicture\image-20240808144703570-1733124502630-37.png)

- 如果**key本身是可比较类型(即key是内置类型)**或**仅value是自定义类型**，其实不需要额外的操作，map可以正常进行遍历

  ![image-20240808144700093](..\0.TyporaPicture\image-20240808144700093-1733124502630-38.png)

- 如果Key对应的是自定义类型

  1. 之前写的函数模板可以遍历前面五种容器的元素，但是map不行，因为map的元素都是pair，而**pair不能直接用输出流运算符进行输出**

     ![image-20241210115238336](..\0.TyporaPicture\image-20241210115238336.png)

     此时有两个display构成**函数模板的重载**，第一个适用于任意的容器类型，**第二个专门用于map类型**

     在**调用display时会首先尝试调用第二个**，如果能匹配则使用，如上图的`mps`是一个map对象，正好可以使用，**如果不能匹配则尝试调用其他的display模板**，如上图的`pts`显然是无法匹配map<T1,T2>的，所以无法使用第二个模板，当然如果想要使用第一个函数模板，还需要为Point重载输出流运算符

  2. 上述讨论仅仅是解决map元素的遍历问题，**想要完成创建**，仍然要让编译器能够根据key值给map的元素排序。

     - **给Point重载<运算符**，或者**针对Point特化std::less**，代码都可以直接通过

     - 但如果用的是**函数对象**的方法，**在遍历时还需要一点改动（==即增添一个模板参数==）**

       <img src="..\0.TyporaPicture\image-20241210171242405.png" alt="image-20241210171242405" style="zoom:67%;" />

## 4.multimap的使用

### 4.1 基本特征

![image-20240808145243572](..\0.TyporaPicture\image-20240808145243572-1733124502630-39.png)

### 4.2 其他操作

multimap的**查找功能（count、find）、插入功能（insert）、删除功能（erase）与map是一样的**

### 4.3 不支持下标

![image-20240808145436542](..\0.TyporaPicture\image-20240808145436542-1733124502630-40.png)

### 4.4 针对于自定义类型

**使用方式与map完全一样**

## 5.总结

- 关联式容器中的元素会按照key进行排序


- 底层使用的都是红黑树数据结构


- <font color=red>**map是具备下标的，其他三种关联式容器没有下标**</font>

## 二、无序关联式容器



<img src="D:\Typora Picture\image-20241210143437004.png" alt="image-20241210143437004" style="zoom: 80%;"/>

无序关联式容器底层是哈希表实现的。

首先来回顾一下哈希表

## 1.哈希

### 1.1 哈希相关的概念

- **哈希(过程)**

  哈希是一种可以接受各种类型、大小的输入，输出一个固定长度整数的过程

  可以将哈希理解成一种特殊的映射，将一个理论无限的集合A映射到有限整数集合B上

- **哈希函数**

  哈希函数是哈希过程的核心，它决定了**哈希映射过程的规则**

  可以通过key找到在表中的位置：`index = H(key)`

- **哈希冲突**

  哈希是一种化无限为有限的映射。理想中的映射应该做到一一对应，即“不同的输入一定得到不同的输出，同样的输入一定得到同样的输出”。但这种理想情况其实是做不到的。退而求其次，在实际使用中我们允许出现多对一（不同输入得到相同输出），但绝不允许出现一对多（相同输入得到不同输出）

  若**映射中出现多对一，就是哈希冲突，哈希冲突可以减少，但绝不可能没有**

  ```cpp
  // 不同的key值所对应的位置一样，这就是哈希冲突
  key1 != key2
  H(key1) = H(key2)  
  ```

- <span style=color:red;background:yellow>**如何构建哈希函数**</span>

  1. 定址法： H(key) = a * key + b
  2. <font color=red>**平方取中法**</font>： key^2 = 1234^2 = 1522756 ------>227
  3. 数字分析法：H(key) = key % 10000；
  4. 除留取余法：H(key) = key mod p (p <= m, m为表长)  

  **哈希函数之所以要设计得这么复杂，就是为了尽量减少哈希冲突**

- <font color=red>**装载因子(装填因子)**</font>

  那么表长应该如何设计比较合理？比如说针对上面这点元素，我准备一个容量为1000的表，选择一种哈希函数，能够让出现冲突的概率很低，但是又显得没有必要（为10个元素准备长度为1000的表，太浪费了）

  装载因子a = 元素的个数/表长，一般是一个小于1的小数。（因为如果大于1，代表着元素个数大于表长，那肯定会有哈希冲突，太小的表长显然不够）

  如果装载因子的值比较大，冲突的概率比较大，空间利用率比较高；如果装载因子的值比较小，冲突的概率比较低，空间利用率比较低；需要做一个权衡，一般设置在0.5~0.75左右

### 1.2 如何解决哈希冲突

1. 开放定址法
2. <font color=red>**链地址法 **</font>(推荐使用这种，这也是STL中使用的方法)
3. 再散列法
4. 建立公共溢出区  

> **链地址法：**
>
> 如下，假设有19 1 23 37 68 55 11  14 86这些元素，表长为11
>
> 1. 19 mod 11 = 8，挂载在下标8位置
> 2. 1 mod 11 = 1，挂载在下标1位置
> 3. 23 mod 11 = 1，用链表的形式挂在元素1的后面
>
> ![image-20240808151302071](..\0.TyporaPicture\image-20240808151302071-1733125193831-63.png)
>

## 2.unordered_set的使用

unordered_set在使用时除了元素的类型，还需要关注几个模板参数

1. Hash决定了具体使用怎样的哈希函数，通过Hash类的operator()函数确定，而哈希冲突的解决方式则是由容器内部的实现机制确定的；

2. KeyEqual决定了元素的判重方式，同样也是通过operator()函数确定。

对于内置类型和指针类型，可以直接使用这一容器，如果是自定义类型对象作为元素，则需要为其准备这些模板参数。

<img src="..\0.TyporaPicture\image-20241212113324137.png" alt="image-20241212113324137" style="zoom:67%;" />

### 2.1 基本特征

创建unordered_set的方式和之前的容器没有多大区别

![image-20240808153120111](..\0.TyporaPicture\image-20240808153120111-1733125234824-65.png)

<img src="..\0.TyporaPicture\image-20241212115621977.png" alt="image-20241212115621977" style="zoom:80%;" />

**效果：无序 + 去重**

### 2.2 其他操作

unordered_set的**查找（count、find）、插入（insert）、删除（erase）等常用操作与set完全一样**，**也不支持下标[]**

### ==2.3 针对于自定义类型==

![image-20240808155505140](..\0.TyporaPicture\image-20240808155505140-1733125234824-68.png)

针对于自定义类型而言，可能需要改写第二个模板参数Hash与第三个模板参数KeyEqual

- Hash

    Hash的默认采用的是std::hash，所以可以**改写的方案有两种**：**模板的特化**、**函数对象的形式**，==与运算符重载没有什么关系==

    1. **模板特化**

       ![image-20240808163638815](..\0.TyporaPicture\image-20240808163638815-1733125234824-66.png)

       **如图，对横纵坐标分别进行左移再异或，其==本质实际就是任意设计出一套哈希函数==**

    2. **函数对象**

       ![image-20240808163705044](..\0.TyporaPicture\image-20240808163705044-1733125234824-67.png)

- KeyEqual

    第三个模板参数KeyEqual的传参有**三种方式**：**模板的特化**、**函数对象的形式**、**运算符重载**

    <font color=red>**注意：在operator()函数中加上打印语句后，可以观察打印的次数，进而能更直观地分析什么时候才会用上equal_to函数对象**</font>

    1. **模板特化**

       ![image-20240808163825379](..\0.TyporaPicture\image-20240808163825379-1733125234824-70.png)

    2. **函数对象**
    
       ![image-20240808163848707](..\0.TyporaPicture\image-20240808163848707-1733125234824-69.png)
    
    3. **运算符重载**
    
       ![image-20240808163930278](..\0.TyporaPicture\image-20240808163930278-1733125234824-71.png)

## 3.unordered_multiset的使用

### 3.1 基本特征

![image-20240808170654309](..\0.TyporaPicture\image-20240808170654309-1733125234824-72.png)

### 3.2 其他操作

unordered_multiset的**查找（count、find）、插入（insert）、删除（erase）与multiset完全一样**，**也不支持下标[]**

### 3.3 针对于自定义类型

unordered_multiset**针对于自定义类型的写法与unordered_set的用法一样**，需要改写第二个参数Hash与第三个参数KeyEqual

## 4.unordered_map的使用

### 4.1 基本特征

![image-20240808171339880](..\0.TyporaPicture\image-20240808171339880-1733125234824-73.png)

### 4.2 其他操作

unordered_map的**查找（count、find）、插入（insert）、删除（erase）与map完全一样**

### ==4.3 支持下标==

![image-20240808171527718](..\0.TyporaPicture\image-20240808171527718-1733125234824-74.png)

## 5.unordered_multimap的使用

### 5.1 基本特征

![image-20240808172135639](..\0.TyporaPicture\image-20240808172135639-1733125234825-75.png)

### 5.2 其他操作

unordered_multimap的**查找（count、find）、插入（insert）、删除（erase）与multimap完全一样**

### ==5.3 不支持下标==

![image-20240808172248938](..\0.TyporaPicture\image-20240808172248938-1733125234825-76.png)

## 6.总结

- 无序关联式容器中的元素是**没有顺序的**

- 底层使用的都是**哈希表**数据结构

- **仅unordered_map具备下标操作**，其他三种无序关联式容器都没有下标[]操作

## ==三、容器的选择==

1. **元素是不是有顺序的**

   - 如果**元素是有顺序**的，**首选的是关联式容器（因为可以自动维护元素有序）**，不应该选择的是无序关联式容器，**其次可以选择序列式容器**

   > 序列式容器中的元素可以排序
   >
   > 例如**list中是有sort函数**的，对于**vector与deque可以借鉴使用算法库中的sort函数**进行排序
   >
   > <img src="..\0.TyporaPicture\image-20241213115102389.png" alt="image-20241213115102389"  />

2. **迭代器的类型**

   - 随机访问迭代器：vector、deque

   - 双向迭代器：list、关联式容器
   - 前向迭代器：无序关联式容器

3. **查找的时间复杂度**

   - 序列式容器：时间复杂度O(N)

   - 关联式容器：时间复杂度O(logN)——树形查找，与树高相关联
   - 无序关联式容器：时间复杂度O(1)——哈希查找

4. **是否支持下标**

   - 序列式容器：vector、deque
   - 关联式容器：map
   - 无序关联式容器：unordered_map

## 四、容器适配器

**容器适配器**的作用其实可以理解为**是对==序列式容器==进行封装**，*使其表现出特定的行为和接口，以满足不同的应用需求*

<img src="..\0.TyporaPicture\image-20241213152152135.png" alt="image-20241213152152135" style="zoom:67%;" />

### 1.栈(stack)

<img src="..\0.TyporaPicture\image-20241213155815990.png" alt="image-20241213155815990" style="zoom:67%;" />

### 2.队列(queue)

<img src="..\0.TyporaPicture\image-20241213160014049.png" alt="image-20241213160014049" style="zoom: 67%;" />

### 3.优先级队列(priority_queue)

![image-20240809102130717](..\0.TyporaPicture\image-20240809102130717-1733126644616-89.png)

![image-20241213161252492](..\0.TyporaPicture\image-20241213161252492.png)

<img src="..\0.TyporaPicture\image-20241213161347228.png" alt="image-20241213161347228" style="zoom:67%;" />

对于vector或者deque，value_type就是T，即**priority_queue的Compare要提供的是对容器中元素的比较方式**

### 3.1 基本使用方法

- 对优先级队列的元素进行遍历，**以前常用的几种方式都不支持（下标、迭代器、增强for循环）**，应该参考C语言中对栈或者队列中元素遍历的方式

  以下的遍历实际上是清空式的遍历，遍历完后优先级队列实际上没有元素了，如果不想进行清空式的遍历，可以在遍历之前先复制一次priority_queue

  ![image-20240809105418557](..\0.TyporaPicture\image-20240809105418557-1733126644617-91.png)

  <img src="..\0.TyporaPicture\image-20241213172224047.png" alt="image-20241213172224047" style="zoom:67%;" />



- 默认的compare是std::less，最终呈现的效果为什么是从大到小，而不是从小到大呢？

  稍微修改一下代码，往空的优先级队列添加元素，观察填充过程

  <img src="..\0.TyporaPicture\image-20250323172224604.png" alt="image-20250323172224604" style="zoom:67%;" />

  > `priority_queue`（优先级队列）和 `set` 虽然都能用 `compare` 自定义排序，**共用同样的比较函数（less/greater/ 自定义），但语义、效果、底层逻辑完全相反**
  >
  > - 两者**默认比较器都是 `std::less<T>`**，但**排序效果完全相反**
  >
  > - `set` 的比较器：决定**全局有序排列规则**
  >
  >   `priority_queue` 的比较器：决定**堆的优先级（谁在堆顶）**
  >
  > - 这是底层数据结构决定的（红黑树 vs 堆）
  >
  > | 容器                | 默认比较器 | 效果                         |
  > | ------------------- | ---------- | ---------------------------- |
  > | `set<T>`            | `less<T>`  | **升序排列**（从小到大）     |
  > | `priority_queue<T>` | `less<T>`  | **大顶堆**（堆顶是最大元素） |

- 优先级队列使用了大根堆，其过程：

  当**有元素插入的时**候，会**将该元素与堆顶进行比较**（细节上实际是一级一级比较）

  1. 如果堆顶比新插入的元素要小，就会满足std::less，会将新插入的元素作为新的堆顶；
  2. 如果新插入的元素与堆顶进行比较，堆顶比新插入的元素要大，那么就不满足std::less，就不会进行置换，上一次的堆顶仍然是堆顶

### 3.2 使用函数总结

- **判空：**empty
- **元素的个数：**size
- **插入：**push
- **删除：**pop
- **获取top元素：**top
- **交换函数：**swap

> **注意**
>
> **C++ 标准的三大容器适配器（stack /queue/priority_queue），官方设计上就是「没有迭代器」的**，这不是缺陷，而是刻意为之的核心特性
>
> 因为**迭代器 = 自由遍历**，而**容器适配器 = 严格限制访问**

### 3.3 针对于自定义类型

因为**优先级队列的第三个模板参数使用的是Compare，默认值是std::less**，所以**如果自定义类型不能进行比较，就需要进行改写**，**改写的方案与set针对于Compare的改写方式完全一样**，有三种：模板的特化、函数对象的形式、运算符重载
# Day23_STL标准模板库3-迭代器

## 一、迭代器

### 1.概念

可以将迭代器看成是一种指针，但是不完全是指针，因为**有些时候迭代器是一个类类型，然后重载了指针的功能，所以迭代器可以像指针一样使用**

- C++为什么要设计迭代器

  迭代器算是C++一个非常重要的抽象概念，它的意义在于：

  1. **为访问容器中的元素提供了统一的方式**

     比如，vector/deque/list三种容器存储元素的方式完全不同，存储元素的类型也可能不同，但是都可以用迭代器来遍历和操作容器中的元素，而不需要关心容器的具体实现细节

  2. **使算法能够独立于容器进行设计和实现**

     例如，std::sort算法可以对任何支持随机访问迭代器的容器进行排序，而不需要为每种容器单独实现排序算法。这样可以提高代码的可复用性和灵活性。

  也就是说**C++通过迭代器把不同的容器的元素的访问逻辑抽象了出来**

### 2.迭代器的类型

1. 输入迭代器(InputIterator)
2. 输出迭代器(OutputIterator)
3. 前向迭代器(ForwardIterator)
4. 双向迭代器(BidirectionIterator)
5. 随机访问迭代器(RandomAccessIterator)

<img src="..\0.TyporaPicture\image-20250102105616784.png" alt="image-20250102105616784" style="zoom:80%;" />

- **五种迭代器之间的关系（逻辑层面上近似于继承关系）**

  <img src="..\0.TyporaPicture\image-20240809114205549-1733126659853-98.png" alt="image-20240809114205549" style="zoom:67%;" />

  > 举个简单的例子，根据我们对继承关系的了解，我们可以推测出：
  >
  > ![image-20250102114216223](..\0.TyporaPicture\image-20250102114216223.png)

- **为什么要定义这么多种迭代器**

  为了物尽其用，使得具体的操作使用具体类型的迭代器，避免迭代器的功能太大或者太小，导致使用起来不方便。每个容器及其对应的迭代器的类型图表如下：

  <img src="..\0.TyporaPicture\image-20250102114702572.png" alt="image-20250102114702572" style="zoom: 67%;" />

- **总结**

  迭代器就是访问容器中元素的手段，大多数时候并不需要研究迭代器的具体实现，能够根据容器的迭代器类型进行正确的使用即可

  > 1. **输入迭代器**（Input Iterator）
  >
  >    - **特点**：==用于读取容器中的元素，只能向前移动，支持自增操作（`++`）来指向下一个元素，**可进行解引用，但不能修改元素的值**==（`*`）操作来访问当前元素的值，还能进行相等（`==`）和不等（`!=`）比较以判断两个迭代器是否指向同一位置。
  >    - **应用场景**：常用于只读算法，如 `std::find`、`std::count` 等，这些算法只需要从容器中读取元素，不需要修改元素的值。
  >
  > 2. **输出迭代器**（Output Iterator）
  >
  >    - **特点**：==用于向容器中写入元素，只能向前移动，支持自增操作（`++`），**可通过解引用**（`*`）操作来**修改元素的值，但不能读取元素的值**==。输出迭代器不支持比较操作。
  >
  >    - **应用场景**：常用于输出算法，如 `std::copy` 算法可以将一个范围的元素复制到另一个由输出迭代器指定的位置。
  >
  > 3. **前向迭代器**（Forward Iterator）
  >
  >    - **特点**：结合了输入迭代器和输出迭代器的功能，既能读取又能写入元素，并且可以多次读取同一个元素。它==仅可以向前移动，仅支持自增操作（`++`）==，**也支持解引用（`*`）操作，还能进行相等（`==`）和不等（`!=`）比较**。
  >
  >    - **应用场景**：适用于需要对容器元素进行读写操作，且只需要单向遍历容器的场景，例如对单链表的遍历和操作。
  >
  > 4. **双向迭代器**（Bidirectional Iterator）
  >
  >    - **特点**：在向前迭代器的基础上，==增加了向后移动的功能，支持自减操作（`--`）==，可以方便地在容器中前后移动，进行元素的访问和修改。
  >
  >    - **应用场景**：常用于需要双向遍历容器的算法，如 `std::reverse` 算法用于反转容器中元素的顺序，就需要双向迭代器来从两端向中间进行元素交换。
  >
  > 5. **随机访问迭代器**（Random Access Iterator）
  >
  >    - **特点**：具有最强的功能，除了支持双向迭代器的所有操作外，==还支持随机访问元素，就像数组下标访问一样，可以通过偏移量直接访问容器中的任意元素==。支持加法（`+`）、减法（`-`）操作来计算迭代器之间的距离，也支持比较操作（`<`、`>`、`<=`、`>=`）来判断两个迭代器的相对位置。
  >
  >    - **应用场景**：适用于需要快速随机访问元素的算法，如 `std::sort` 算法对容器中的元素进行排序，通常要求迭代器具有随机访问能力，以便高效地进行元素的比较和交换。

### 3.流迭代器

#### 3.1 输出流迭代器

- **流迭代器是特殊的迭代器，其作用有：**

  1. 可以将输入/输出流作为**容器**看待(因为输入输出流都有**缓冲区**的概念，也可以视为存一些数据)，流迭代器可以用来访问输入输出流这种“容器”中的数据。

  2. STL 中有许多算法都是基于迭代器设计的，输入流迭代器和输出流迭代器使得这些算法能够直接应用于输入输出流。因此任何接受迭代器参数的算法都可以和流一起工作。

- **通过cpp参考文档查看输出流迭代器构造函数的说明：**

  <img src="..\0.TyporaPicture\image-20250102152744535.png" alt="image-20250102152744535" style="zoom:67%;" />

  > `std::ostream_iterator` 是模板类，定义在 `<iterator>` 头文件中，**有两个公开构造函数**：
  >
  > ```cpp
  > // 1. 无分隔符构造函数
  > ostream_iterator(ostream_type& __s);
  > 
  > // 2. 带分隔符构造函数
  > ostream_iterator(ostream_type& __s, const char* __delim);
  > ```
  >
  > 
  >
  > 尝试使用一下输出流迭代器，如下（使用了algorithm提供的==**copy函数**==）
  >
  > 最常用的一种使用方式：使用 `std::copy` 算法通过输入流迭代器从文件中读取数据，然后通过输出流迭代器将数据输出到控制台，就像操作普通容器一样
  >
  > ![image-20250318195617489](..\0.TyporaPicture\image-20250318195617489.png)
  >
  > <img src="..\0.TyporaPicture\image-20250102153042767.png" alt="image-20250102153042767" style="zoom:67%;" />
  >
  > 
  >
  > <img src="..\0.TyporaPicture\image-20250102152333957.png" alt="image-20250102152333957" style="zoom:67%;" />
  >
  > 其实结果很容易推测出来。**至此，我们发现又多了一种遍历容器元素的方式**，那么这个输出的效果是怎么实现的呢？

- **通过copy源码来认识如何将数据输出到控制台**

     1. 输出流迭代器的类模板形式：

         > **补充**
         >
         > `_Traits` 必须是一个类似 `std::char_traits` 的类，里面定义了一系列静态方法，告诉标准库如何处理字符，例如：
         >
         > - 怎么**比较**两个字符/字符串
         > - 怎么**复制/移动**字符序列
         > - 文件结束符 **EOF** 是哪个值
         > - 怎么**查找**字符长度
         >
         > 默认情况下，`_Traits` 取 `char_traits<_CharT>`，也就是**用 _CharT 对应的标准特性**。比如：
         >
         > - 当 `_CharT` 是 `char` 时，`_Traits` 默认为 `std::char_traits<char>`（窄字符规则）
         > - 当 `_CharT` 是 `wchar_t` 时，`_Traits` 默认为 `std::char_traits<wchar_t>`（宽字符规则）
     
         ```C++
         // 类模板定义
         // _Tp     : 要输出的数据类型（例如 int, string）
         // _CharT  : 字符类型（默认 char）
         // _Traits : 字符特性类（默认 char_traits<_CharT>）
         template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT> >
         class ostream_iterator {
         public:
             // 为方便使用，定义流类型的别名
             // （源码中一般会有这行，这里补充并注释）
             typedef basic_ostream<_CharT, _Traits> ostream_type;
         
             // ---------- 构造函数 ----------
             // 参数：
             //   __s : 输出流对象（如 std::cout）
             //   __c : 分隔字符串指针（如 " "），可为空指针（表示无分隔）
             // 初始化列表：
             //   _M_stream 指向输出流的指针
             //   _M_string 指向分隔字符串（浅拷贝，需保证生命周期）
             ostream_iterator(ostream_type& __s, const _CharT* __c) 
                 : _M_stream(&__s)   // 保存流地址
                 , _M_string(__c)    // 保存分隔符地址
             {}
         
             // ---------- 迭代器必需操作 ----------
             // 解引用操作符：标准要求返回自身引用
             // 这里不进行实际输出，仅返回迭代器本身
             ostream_iterator<_Tp>& operator*() { return *this; }
         
             // 前置递增：标准要求返回自身引用，不做额外操作
             ostream_iterator<_Tp>& operator++() { return *this; }
         
             // 后置递增：标准要求返回自身引用，不做额外操作
             ostream_iterator<_Tp>& operator++(int) { return *this; }
         
             // ---------- 核心赋值操作 ----------
             // 当执行 *it = value 时，实际调用此赋值运算符
             // 1. 将 value 输出到绑定的流中
             // 2. 如果分隔字符串非空，则再输出分隔字符串
             ostream_iterator<_Tp>& operator=(const _Tp& __value) { 
                 *_M_stream << __value;               // 输出数据，如: cout << 1
                 if (_M_string)                       // 判断分隔符是否存在
                     *_M_stream << _M_string;         // 输出分隔符，如: cout << "  "
                 return *this;                        // 返回自身引用，支持链式赋值
             }
         
         private:
             ostream_type* _M_stream;   // 指向关联的输出流
             const _CharT* _M_string;   // 指向分隔字符串（空指针表示无分隔）
         };
         ```
     
     1. copy函数的实现（cpp参考文档相关页直接给出）
     
        ```C++
        template<class InputIt, class OutputIt>
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                *d_first++ = *first++;
            }
            return d_first;
        }
        ```
     
     1. 以上述例子为参考进行分析

        ``` c++
        // copy(vec.begin(), vec.end(), osi);
        // first = vec.begin();
        // last = vec.end()
        // d_first = osi 
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                //需要查看ostream_iterator的后置++与解引用（相应的运算符重载函数） 
                *d_first++ = *first++;//++优先级高于解引用
            }
            return d_first;
        }
        
        //	*******分析过程*******
        osi = 1 // ostream_iterator调用operator=函数
                last
        1 5 9 7
        f ------> f
        ```

#### 3.2 输入流迭代器

- **构造函数**

  <img src="..\0.TyporaPicture\image-20250103091012302.png" alt="image-20250103091012302" style="zoom:67%;" />

- **使用示例**

  可以利用一个通用输入流对象初始化istream_iterator

  <img src="..\0.TyporaPicture\image-20250103090859551.png" alt="image-20250103090859551" style="zoom:67%;" />

  可能出现的段错误

  <img src="..\0.TyporaPicture\image-20250103114516852.png" alt="image-20250103114516852" style="zoom:67%;" />

  > **解析**
  >
  > `std::copy` 是一个**模板函数**，只有**唯一的通用原型**
  > 两个调用的区别：只是**模板参数类型不同**（编译器自动推导）
  >
  > 通用——第1个参数：起点迭代器；第2个参数：终点迭代器（尾后迭代器）
  >
  > 1. `std::copy(isi, istream_iterator<int>(), vec.begin());`
  >
  >    - 第一个参数 `isi`
  >
  >      绑定了标准输入 `cin` 的**有效输入迭代器**，代表**要读取的第一个数据的起始位置**，每次解引用 `*isi` 就会从键盘读一个 int
  >
  >    - 第二个参数 `istream_iterator<int>()`
  >
  >      这是**默认构造的流迭代器**，代表 **流结束标记（EOF）**，是遍历的**终止条件**。
  >
  >      当控制台没有数据可读时（Windows 按 `Ctrl+Z`，Linux/Mac 按 `Ctrl+D`），`isi` 就会等于这个终止迭代器，`copy` 停止循环
  >
  >    - 第三个参数错误
  >
  >      `std::copy` 的工作逻辑是：
  >
  >      ```cpp
  >      template<class InputIt, class OutputIt>
  >      OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
  >      {
  >          while (first != last) {
  >              *d_first++ = *first++; // 核心：直接对目标迭代器做赋值操作
  >              ++first;
  >              ++d_first;
  >          }
  >          return d_first;
  >      }
  >      ```
  >
  >      它会**直接对目标迭代器 `d_first` 执行赋值操作**，**不会自动帮你扩展容器的大小**
  >
  >      而代码里：
  >
  >      - `vec` 是空的（`size=0`），`vec.begin()` 指向的是一个**不存在的元素位置**
  >      - `std::copy` 试图向这个位置写入数据，就会越界访问内存 → 触发 **Segmentation fault**
  >
  >      ==为什么会段错误？==
  >
  >       把`vector<int>` 想象成一个数组：
  >
  >      - 空 `vector` 相当于一个长度为 0 的数组，没有分配任何可写入的元素空间
  >      - `vec.begin()` 就像指向数组第 0 个元素的指针，但这个元素根本不存在
  >      - `std::copy` 执行 `*d_first++ = *first++;` 时，相当于对一个空指针 / 无效地址做写入，直接触发段错误
  >
  >      ==修正方案==
  >
  >      要解决这个问题，需要让 `std::copy` 在写入时自动向 `vector` 添加元素。C++ 提供了`std::back_inserter`（属于插入迭代器），它会在每次赋值时调用 `push_back`，自动扩展容器
  >
  > 2. `copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));`
  >
  >    - 第一个参数：`vec.begin()`
  >
  >      - **类型**：`vector<int>` 的迭代器（**输入迭代器**，负责读数据）
  >
  >      - **作用**：**数据源的起始位置**
  >
  >      - **通俗理解**：从 vector 的**第一个元素**开始复制数据
  >
  >    - 第二个参数：`vec.end()`
  >
  >      - **类型**：`vector<int>` 的迭代器
  >      - **作用**：**数据源的尾后位置**（STL 固定规则：**前闭后开区间 `[begin, end)`**）
  >      - **通俗理解**：复制到 vector 末尾**就停止**，**不包含**这个位置
  >      - **关键**：这是 STL 所有算法的统一规则，不是这个函数独有！
  >
  >    - 第三个参数：`ostream_iterator<int>(cout, " ")`
  >
  >      - **类型**：**输出流迭代器**（**输出迭代器**，负责写数据）
  >
  >      - **作用**：**数据要写入的目标起始位置**
  >
  >      - **拆解细节**：
  >
  >        1. `ostream_iterator<int>`：专门往**输出流**写 `int` 数据的迭代器
  >
  >        2. `cout`：绑定控制台输出（写到屏幕）
  >
  >        3. `" "`：每写一个数字，**自动追加一个空格**
  >
  >           **对应之前知识点**：输出迭代器**只能写、不能读**
  >
  >    整行代码的执行流程
  >
  >    1. 从 `vec` 的第一个元素开始拿数据
  >    2. 一直拿到 `vec` 的最后一个元素（遇到 `vec.end()` 停止）
  >    3. 把每一个元素，**通过输出迭代器写到控制台**，并且数字之间用空格隔开

  正确使用（用到了一个函数==**back_inserter——生成(插入)迭代器适配器的快捷函数**==）

  > | 名称                       | 类型         | 作用                                               |
  > | -------------------------- | ------------ | -------------------------------------------------- |
  > | **`back_insert_iterator`** | **类模板**   | **迭代器适配器本体**，包装容器，实现尾插逻辑       |
  > | **`back_inserter`**        | **函数模板** | 辅助工具，**快速创建** `back_insert_iterator` 对象 |

  <img src="..\0.TyporaPicture\image-20250103114847667.png" alt="image-20250103114847667" style="zoom:67%;" />

- **源码**

  ```cpp
  // 模板参数：
  // _Tp    ：要从流中读取的数据类型
  // _CharT ：流使用的字符类型，默认 char
  // _Traits：字符特性类，默认 char_traits<_CharT>
  // _Dist  ：迭代器距离类型，通常 ptrdiff_t（这里未使用）
  template <class _Tp,
            class _CharT = char, class _Traits = char_traits<_CharT>,
            class _Dist = ptrdiff_t>
  class istream_iterator
  {
  public:
      // 为了方便使用，通常会有以下类型别名（原代码略）
      // typedef _Tp value_type;
      // typedef _Tp& reference;
      // typedef basic_istream<_CharT, _Traits> istream_type;
  
      //----------------------------------------------
      // 1. 默认构造函数 —— 创建“结束标记”迭代器
      //----------------------------------------------
      istream_iterator()
          : _M_stream(nullptr),   // 不关联任何输入流
            _M_ok(false)          // 标记读取失败，这是一个“尾后”迭代器
      {}
  
      //----------------------------------------------
      // 2. 带流引用的构造函数 —— 创建“开始”迭代器
      //    __s 通常是 cin 或文件流
      //----------------------------------------------
      istream_iterator(istream_type& __s)
          : _M_stream(&__s)       // 记录流的地址
      {
          _M_read();              // 立即尝试读取第一个元素，惰性求值
      }
  
      //----------------------------------------------
      // 核心读取函数：从流中提取一个数据项到 _M_value，
      // 并更新状态标记 _M_ok
      //----------------------------------------------
      void _M_read()
      {
          // 如果流指针有效且流本身处于可用状态，才尝试读取
          _M_ok = (_M_stream && *_M_stream) ? true : false;
  
          if (_M_ok)
          {
              // 执行输入操作：将流中的数据读入 _M_value
              *_M_stream >> _M_value;
  
              // 读取后再次检查流状态：
              // 如果读取成功（状态为 goodbit），_M_ok 保持 true；
              // 若遇到 EOF、类型不匹配等错误，流会变为非 goodbit，_M_ok 变为 false。
              _M_ok = *_M_stream ? true : false;
          }
      }
  
      //----------------------------------------------
      // 判断两个流迭代器是否“相等”
      // 用于结束条件判断
      //----------------------------------------------
      bool _M_equal(const istream_iterator& __y) const
      {
          // 两个迭代器相等当且仅当：
          // 1. 它们的有效标志位 _M_ok 相同（都为 true 或都为 false）
          // 2. 并且：
          //    - 如果 _M_ok 为 false（即双方都是结束迭代器），则认为相等（! _M_ok 为 true）；
          //    - 如果 _M_ok 为 true，则要求它们关联的是同一个流对象。
          // 这种设计使得：所有默认构造的迭代器彼此相等，且与任何已“读完”的流迭代器相等。
          return (_M_ok == __y._M_ok) && (!_M_ok || _M_stream == __y._M_stream);
      }
  
      //----------------------------------------------
      // 后置递增运算符：返回旧值，然后前进（读取下一个元素）
      //----------------------------------------------
      istream_iterator operator++(int)
      {
          istream_iterator __tmp = *this;  // 保存当前状态（含当前值 _M_value）
          _M_read();                       // 从流中读取下一个元素
          return __tmp;                    // 返回未递增前的副本
      }
  
      // 前置递增（通常也需实现，这里略）
      // istream_iterator& operator++() { _M_read(); return *this; }
  
      // 解引用操作符：返回当前缓存的元素
      reference operator*() const { return _M_value; }
  
  private:
      istream_type* _M_stream;  // 指向关联的输入流
      _Tp           _M_value;   // 缓存最近一次成功读取的值
      bool          _M_ok;      // 当前读取状态是否有效
  };
  
  //----------------------------------------------
  // 全局 operator!=：依赖 _M_equal 成员函数
  //----------------------------------------------
  inline bool operator!=(const istream_iterator& __x, const istream_iterator& __y)
  {
      return !__x._M_equal(__y);
  }
  
  //==============================================
  // 使用示例：std::copy(isi, istream_iterator<int>(), std::back_inserter(vec));
  //==============================================
  /*
   * 假如我们有：
   *   istream_iterator<int> isi(cin);     // 开始迭代器，构造时立刻读取第一个整数
   *   istream_iterator<int> end;          // 结束标记迭代器
   *
   * 调用 std::copy(isi, end, back_inserter(vec)) 实际执行的算法如下：
   */
  
  // first = isi （开始迭代器）
  // last  = istream_iterator<int>() （结束标记）
  // d_first = back_inserter(vec)  （输出迭代器，负责向 vec 末尾添加元素）
  OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
  {
      // 循环条件：first != last
      // 利用上述 operator!= 进行比较，本质是调用 first._M_equal(last)
      // 只要流还在有效状态且未遇到结束迭代器，循环就继续
      while (first != last)
      {
          // *d_first++ = *first++;
          // 分解步骤：
          // 1. *first   ：取出当前缓存的元素（上一次 _M_read 读到的值）
          // 2. *d_first++  = 值 ：将该值通过 back_insert_iterator 追加到容器，然后移动输出迭代器
          // 3. first++  ：后置递增，触发 _M_read()，尝试从流中读取下一个元素。
          //    若读取失败（EOF/错误），first 的 _M_ok 变为 false，
          //    导致下一次 while 条件判断时 first != last 变为 false，循环终止。
          *d_first++ = *first++;
      }
      return d_first;
  }
  
  // back_inserter 辅助函数：创建 back_insert_iterator 对象
  template <class _Container>
  inline back_insert_iterator<_Container> back_inserter(_Container& __x)
  {
      // back_insert_iterator 的 operator= 内部会调用 __x.push_back(value)
      return back_insert_iterator<_Container>(__x);
  }
  ```
  
  **back_insert_iterator(==迭代器适配器-类模板==)的实现**
  
  ```cpp
  template <class _Container>
  class back_insert_iterator {
  protected:
      _Container* container;  // 指向目标容器的指针
  
  public:
      // 在实际的 C++ 标准库中，还需要提供一些迭代器所需的类型别名，例如：
      // using iterator_category = output_iterator_tag;
      // using value_type      = void;
      // using difference_type = void;
      // using pointer         = void;
      // using reference       = void;
      // 因为它是输出迭代器，这些类型通常不重要，这里略去。
  
      //----------------------------------------------
      // 构造函数：接收容器引用，保存其地址
      // 例如：back_insert_iterator(vec) 会使 container = &vec
      // 注意：该构造函数通常声明为 explicit，防止意外的隐式转换
      //----------------------------------------------
      explicit back_insert_iterator(_Container& __x)
          : container(&__x)
      {}
  
      //----------------------------------------------
      // 赋值运算符：核心操作
      // 当执行 *it = value 时，实际调用本函数，
      // 将 value 追加到容器尾部。
      //----------------------------------------------
      back_insert_iterator<_Container>&
      operator=(const typename _Container::value_type& __value)
      {
          container->push_back(__value);   // 向关联容器尾部添加元素
          return *this;
      }
  
      // 移动赋值版本（C++11起），此处省略，原理类似，调用 push_back 的右值版本。
  
      //----------------------------------------------
      // operator* ：解引用操作
      // 对于纯输出迭代器，此操作通常返回迭代器自身，
      // 因为真正的工作发生在随后的赋值操作中。
      //----------------------------------------------
      back_insert_iterator<_Container>& operator*()
      {
          return *this;
      }
  
      //----------------------------------------------
      // operator++（前置）与 operator++(int)（后置）
      // 对于输出迭代器，递增操作一般也是空操作，
      // 返回自身即可，因为迭代器并不真正“移动”到下一个位置。
      //----------------------------------------------
      back_insert_iterator<_Container>& operator++()
      {
          return *this;
      }
  
      back_insert_iterator<_Container>& operator++(int)
      {
          return *this;
      }
  };
  
  // 辅助函数 back_inserter —— 创建 back_insert_iterator 的便捷接口
  // template <class _Container>
  // inline back_insert_iterator<_Container> back_inserter(_Container& __x)
  // {
  //     return back_insert_iterator<_Container>(__x);
  // }
  ```

### 4.迭代器适配器

#### 4.1 三组插入迭代器适配器

- **三组插入迭代器适配器**

  <img src="..\0.TyporaPicture\image-20250103181150482.png" alt="image-20250103181150482" style="zoom:67%;" />

  1. back_inserter是**便捷函数**，该函数返回类型是back_insert_iterator，它们的底层会调用容器的push_back

  2. front_inserter是函数，该函数的返回类型是front_insert_iterator，它们的底层会调用容器的push_front
  3. inserter是函数，该函数的返回类型是insert_iterator，它们的底层会调用容器的insert

- **简单示例：**

  将list的元素插入到vector尾部

  **除了以往的常规方式（遍历list的元素，再使用vector的push_back函数添加这些元素），还可以使用迭代器**

  <img src="..\0.TyporaPicture\image-20250106111219439.png" alt="image-20250106111219439" style="zoom:67%;" />

    > **上面两行copy语句是等价的，它们实现的功能一模一样，只是写法上的 “便捷版” 和 “完整版” 区别**
    >
    > 1. **`back_inserter(vec)` 是便捷函数**
    >
    >    `std::back_inserter` 是 C++ 标准库提供的一个**模板辅助函数**
    >
    >    它的作用就是帮你自动推导容器类型，生成对应的 `std::back_insert_iterator` 对象
    >
    >    底层实现：
    >
    >    ```cpp
    >    template <class Container>
    >    std::back_insert_iterator<Container> back_inserter(Container& c) {
    >        return std::back_insert_iterator<Container>(c);
    >    }
    >    ```
    >
    > 2. **`back_insert_iterator<vector<int>>(vec)` 是显式构造**
    >
    >    这是直接手动构造了一个 `back_insert_iterator` 模板类的对象，明确指定了容器类型为 `vector<int>`，效果和 `back_inserter(vec)` 完全一致
    >
    > 作为 `std::copy` 的第三个参数，它们的功能都是：
    >
    > - 生成一个**输出迭代器**
    > - 每次拷贝元素时，自动调用 `vec.push_back(元素)`，将元素追加到 `vec` 的末尾

    再将vector的元素插入到list头部

    <img src="..\0.TyporaPicture\image-20250106111304333.png" alt="image-20250106111304333" style="zoom:67%;" />

    <img src="..\0.TyporaPicture\image-20250106144924432.png" alt="image-20250106144924432" style="zoom:67%;" />

    从得到的结果可以想到，执行的过程是从头到尾遍历vector的元素，然后一次次执行了push_front函数

    > **补充**
    >
    > 1. 可不可以将list元素插入到vector头部呢？
    >
    >    - 可以把 list 的元素插到 vector 头部，但不能用 front_inserter，而且效率很低
    >
    >      1. 但是不能使用 front_inserter 往 vector 头插
    >
    >        `std::front_inserter` 内部调用的是 `push_front()`。
    >
    >        **vector 没有 push_front**，只有 list、deque 才有。
    >
    >        所以下面这种写法**编译不通过**：
    >
    >        ```cpp
    >        std::list<int> lst = {1,2,3};
    >        std::vector<int> vec;
    >        // 错误：vector 不能用 front_inserter
    >        std::copy(lst.begin(), lst.end(), std::front_inserter(vec));
    >        ```
    >
    >      2. 应该使用 insert + 反向迭代器
    >
    >        想把整个 list 一次性插到 vector 头部，可以用 `vec.insert`，并注意**顺序**：
    >
    >        ```cpp
    >        #include <vector>
    >        #include <list>
    >        #include <algorithm>
    >                  
    >        int main() {
    >            std::list<int> lst = {1,2,3};
    >            std::vector<int> vec = {10,20,30};
    >                  
    >            // 把 list 元素整体插到 vector 头部
    >            vec.insert(vec.begin(), lst.begin(), lst.end());
    >            // vec 现在：1,2,3,10,20,30
    >        }
    >        ```
    >
    >        如果希望**逆序插入**（类似 front_inserter 的效果）：
    >
    >        ```cpp
    >        vec.insert(vec.begin(), lst.rbegin(), lst.rend());
    >        // vec 变成：3,2,1,10,20,30
    >        ```
    >
    >
    >    - 效率问题与更好的方案
    >
    >      > vector 是**连续数组**，头部插入会让**所有元素后移**
    >      >
    >      > 每次 `insert(vec.begin(), ...)` 的复杂度是 **O(n)**
    >      >
    >      > 如果循环逐个头插：
    >      >
    >      > ```cpp
    >      > for (auto x : lst) vec.insert(vec.begin(), x);
    >      > ```
    >      >
    >      > 会变成 **O(n²)**，数据量大时很慢
    >
    >      1. **对于少量数据**：
    >
    >         直接用 `vec.insert(vec.begin(), lst.begin(), lst.end())` 无所谓
    >
    >      2. **而对于大量数据**：
    >
    >         - 先把 list 拷贝到临时 vector；
    >
    >         - 再 `reserve` 扩容；
    >
    >         - 最后 `insert` 一次性合并。
    >
    >      3. **频繁头插**：**别用 vector**，改用 `std::deque`（支持 O (1) push_front）
    >
    > 2. 将list的元素插入到set中
    >
    >    ![image-20240809164112172](..\0.TyporaPicture\image-20240809164112172-1733126659852-96.png)
    >
    > <font color=red>**所以：使用上述三种插入迭代器的时候，如果容器本身不具备对应插入函数的话，那么就不能乱用**</font>

- **copy、front_inserter、front_insert_iterator的源码：**

    ```cpp
    // ==============================================
    // 1. std::copy 算法的实现
    // 将 [first, last) 范围内的元素依次复制到 d_first 开始的位置
    // ==============================================
    template<class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        while (first != last) {
            // 核心循环：
            // *d_first++ = *first++;
            // 1. *first  : 获取当前输入位置的元素
            // 2. first++ : 输入迭代器前进（后置递增，返回原值后移动）
            // 3. *d_first++ = 值 : 将值赋给输出迭代器的当前位置，然后输出迭代器前进
            // 
            // 对于 front_insert_iterator，*d_first 返回迭代器自身，
            // ++ 也是空操作，真正的插入发生在赋值运算符中（调用 push_front）
            *d_first++ = *first++;
        }
        return d_first;
    }
    
    // ==============================================
    // 2. front_inserter 辅助函数
    // 用于方便地创建 front_insert_iterator 对象
    // ==============================================
    template <class _Container>
    inline front_insert_iterator<_Container> front_inserter(_Container& __x)
    {
        // 将容器的引用传递给 front_insert_iterator 的构造函数，
        // 使其持有指向该容器的指针。
        return front_insert_iterator<_Container>(__x);
    }
    
    // ==============================================
    // 3. front_insert_iterator 类模板
    // 输出迭代器，专用于在容器前端插入元素
    // ==============================================
    template <class _Container>
    class front_insert_iterator {
    protected:
        _Container* container;  // 指向目标容器的指针
    
    public:
        // ---- 迭代器特征类型定义 ----
        typedef _Container          container_type;
        typedef output_iterator_tag iterator_category; // 标记为输出迭代器
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;
    
        // 构造函数：接收容器引用，保存其地址
        // 使用 explicit 避免隐式转换
        explicit front_insert_iterator(_Container& __x) : container(&__x) {}
    
        // ---- 赋值运算符：核心操作 ----
        // 当执行 *it = value 时调用此函数
        front_insert_iterator<_Container>&
        operator=(const typename _Container::value_type& __value)
        {
            // 在容器头部插入元素
            // 要求容器支持 push_front 操作（如 list, deque, forward_list 等）
            container->push_front(__value);
            return *this;
        }
    
        // ---- 以下三个运算符是输出迭代器的接口要求，实现为空操作 ----
        // operator*：解引用，返回迭代器自身，以便后续赋值
        front_insert_iterator<_Container>& operator*() { return *this; }
    
        // operator++（前置）：前进到下一位置，在此无实际位置概念
        front_insert_iterator<_Container>& operator++() { return *this; }
    
        // operator++(int)（后置）：同样返回自身，维持链式语法兼容性
        front_insert_iterator<_Container>& operator++(int) { return *this; }
    };
    ```

#### 4.2 反向迭代器适配器

![image-20240809170644459](..\0.TyporaPicture\image-20240809170644459-1733126659852-95.png)

**注意遍历时偏移的方式，仍然是自增（只不过这里的自增对应的是向左移动）**

![image-20240809171255460](..\0.TyporaPicture\image-20240809171255460-1733126659853-99.png)

# Day24_STL标准模板库4-算法

## 一、算法

### 1.特点

STL的算法库中的函数，都是属于普通函数（并不是哪一个类的成员函数）

### 2.分类

- 非修改式的序列算法：**for_each**、count、find
- 修改式的序列算法：**`copy`**、`remove`、**`remove_if`**、`replace`、`fill`
- 排序函数：**`sort`**
- 二分搜索的算法：`lower_bound`、`upper_bound`、`equal_range`
- 集合操作：**`set_intersection`**（取交集）
- 堆相关的函数：`make_heap`、`push_heap`
- 取最值：`max`、`min`
- 数值操作：`iota`
- 未初始化的内存操作：**`uninitialized_copy`**

### 3.`for_each`——非修改式的序列算法

首先查看cpp参考文档的描述

<img src="..\0.TyporaPicture\image-20250110103033784.png" alt="image-20250110103033784" style="zoom:67%;" />

- 第三个参数需要传一个一元函数（或者仿函数），其函数形参只有一个（不一定要有const或者&）

  > 一元函数：函数的参数只有一个
  >
  > 二元函数：函数的参数只有两个

- 示例

  <img src="..\0.TyporaPicture\image-20250110104510905.png" alt="image-20250110104510905" style="zoom:67%;" />

  想要通过for_each改变vector中元素的内容，就得在func函数上做文章，可以给func函数形参改成引用

  <font color=red>**实际使用时，func函数是否改变容器元素，for_each是没有限制的**</font>

- 参考for_each的源码

  ```cpp
  template<class InputIt, class UnaryFunction>
  constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
      for (; first != last; ++first) {
          f(*first);
      }
      return f; 
  }
  ```

### 4.lambda表达式(重要)

以for_each的使用为例，有时**为了使用一些简单的函数**，会经常使用到lambda表达式

<img src="..\0.TyporaPicture\image-20250110141631261.png" alt="image-20250110141631261" style="zoom:67%;" />

#### 4.1 语法结构

**lambda表达式**也称为**匿名函数**，其基本语法结构如下：

``` c++
[capture](params) opt -> retureType {
	body;
}
```

- 其中capture是捕获列表，params是参数列表，opt是函数选项，retureType是返回值类型，body是函数体


> 如下的lambda表达式中：
>
> []——**捕获列表**：捕获**lambda表达式函数体外**的**==局部==变量**
>
> ()——函数的**参数列表**
>
> {}——函数的**函数体**
>
> <img src="..\0.TyporaPicture\image-20250110151601816.png" alt="image-20250110151601816" style="zoom:67%;" />
>
> 如果没有在[]中捕获a、b，那么在匿名函数的函数体中无法访问它们
>
> 进一步的，还可以给匿名函数增加函数参数，以及指定函数返回类型
>
> <img src="..\0.TyporaPicture\image-20250110154439061.png" alt="image-20250110154439061" style="zoom:67%;" />
>
> <span style=color:red;background:yellow>**注意：**</span>捕获列表捕获的是局部变量，全局变量不需要捕获
>
> <img src="..\0.TyporaPicture\image-20250110154541870.png" alt="image-20250110154541870" style="zoom:67%;" />

#### 4.2 引用捕获与值捕获的区别

如果**想要通过捕获列表(形参)改变局部变量(实参)的值**

<img src="..\0.TyporaPicture\image-20250110163859032.png" alt="image-20250110163859032" style="zoom:67%;" />



函数选项的位置**加上mutable关键字才能对==局部变量==a/b(lambda表达式中的形参)进行修改操作，但这样做也并不能修改a和b实际的值(传给lambda表达式的实参)（==即加上mutable仅为前提==）**

<img src="..\0.TyporaPicture\image-20250110164140708.png" alt="image-20250110164140708" style="zoom:67%;" />

看到上述的结果，应该能联想到常规函数的值传递场景，**==想要真正通过形参改变实参==，形参需要写成==引用形式==（==此为核心==）**

那么对于匿名函数而言，如果想要在匿名函数中修改捕获的变量其本身的值，那么应该采用的是<font color=red>**引用捕获**</font>

<img src="..\0.TyporaPicture\image-20250110164446682.png" alt="image-20250110164446682" style="zoom:67%;" />

**另外，对于==全局变量和函数参数(形参)==，匿名函数中可以直接完成修改**

> **==如果需要捕获的内容太多==**，有一些比较方便的写法：
>
> - 如果想将外部局部变量全部捕获，可以在捕获列表中使用 **[=]**，表示全部是值捕获；或者使用 **[&]**，表示全部是引用捕获
>
> - 如果某一个变量是值捕获，其他的全部是引用捕获，可以 **[&, num]**
>
> - 如果某一个变量是引用捕获，其他的全部是值捕获，可以 **[=, &num]**
>
> - 最简单的方式是，将每个变量的捕获形式单独写出来，理解起来更简单

#### 4.3 lambda表达式可以被接收

现在考虑到一个问题，在前面的例子中，匿名函数每次都是当场定义**当场调用**(**表达式函数体结尾的`}`之后加上(实参)**)的，那么匿名函数是否可以像普通的函数一样去复用呢？

![image-20240810112342157](..\0.TyporaPicture\image-20240810112342157-1733126757209-108.png)

> **经典写法与错误：**
>
> ```cpp
> class Example {
> public:
> 	void print(int x, int y) {
> 		auto x1 = [] { return _number; }; // error: 通过this才能访问_number
> 		auto x2 = [this] { return _number; };
> 		auto x3 = [this] { return _number + x + y; }; // error: 未捕获x与y
> 		auto x4 = [this, x, y] { return _number + x + y; }; 
> 		auto x5 = [this] { return _number++; }; // 并没有修改this，只是通过this修改其指向的对象的内容
> 		auto x6 = [=] { return _number + x + y; }; // 全部局部变量包括this
> 		auto x7 = [&] { return _number + x + y; }; 
> 	}
> 	int _number = 100;
> };
> ```
>
> ```cpp
> void test() {
>  int a = 10, b = 20;
>  auto f1 = [] { return a; }; // error: 未捕获a
>  auto f2 = [&] { return a++; };
>  auto f3 = [=] { return a; }; 
>  auto f4 = [=] { return a++; }; // error: 值捕获不能进行写操作，a++是写操作
>  auto f5 = [a] { return a + b; }; // error: 未捕获b
>  auto f6 = [a, &b] { return a + (b++); }; 
>  auto f7 = [=, &b] { return a + (b++); }; 
> }
> ```
>
> <span style=color:red;background:yellow>**总结：**</span>
>
> 对于lambda表达式，大家可能会在实际代码中见到非常多种形式，需要读懂它的意思
>
> 1. lambda表达式的参数列表与普通函数的参数列表一样，如果没有参数，则参数列表可以省略不写，而这个具体的省略形式为：
>
>    - **普通函数**：无参数 ➜ **必须写 `( )`**
>
>    - **Lambda**：无参数 ➜ **可以不写 `( )`**
>
> 2. 即使没有需要捕获的内容，也需要写上 **[ ]**
>
> 3. 选项如非必需，可以省略
>
>    - mutable：可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）
>
>
>    - noexcept：`noexcept` 是一种契约，向编译器和调用者保证函数不会抛出异常。如果违反了这个契约，程序的行为将是未定义的，通常会导致程序终止
>
> 4. 返回类型可以省略。通过返回值后置语法来定义的。一般情况下，不指定lambda表达式的返回值，编译器会根据return语句自动推导返回值的类型，但需要注意的是labmda表达式不能通过列表初始化自动推导出返回值类型
>
>    ```cpp
>    // ok，可以自动推导出返回值类型
>    auto f = [](int i) {
>    	return i;
>    };
>    
>    // error,不能推导出返回值类型
>    auto f1 = []() {
>    	return {1, 2}; // 基于列表初始化推导返回值，错误
>    };
>    ```
>
> 5. 函数体不能省略，但可以为空
>
>    ```cpp
>    auto f = []{}; 
>    []{}(); // 极致省略的匿名函数立即调用
>    ```
>
> 6. lambda 表达式赋值给变量时，`}` 后面必须写 `;`
>    因为**lambda 是一个「表达式」**，不是函数定义，也不是代码块

#### 4.4 lambda表达式的类型

至此仍然存在一个问题：auto推导出来的类型究竟是什么呢？

- lambda表达式的类型与匿名函数的returnType并非是同一件事

  ==**auto 推导出的不是函数指针，也不是 std::function，而是一个编译器自动生成的、独一无二的「闭包类型（closure type）」**，你写不出它的名字，只能用 auto 或模板参数接住它==

- lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。mutable选项的作用就在于取消operator()的const属性


- 因为lambda表达式在C++中会被看做是一个仿函数，因此可以使用std::function和std::bind来存储和操作lambda表达式（算法适配器的使用）

**进一步解释见std::function部分**

> 这里附上一个网站：https://cppinsights.io/，可以通过它查看编译器是如何处理代码的

### 5.`remove_if`——修改式的序列算法

#### 5.1 基本使用

依旧从cpp参考文档出发

![image-20250110170422501](..\0.TyporaPicture\image-20250110170422501.png)

- 第三个参数p是一个一元谓词


> **一元函数**：函数的参数只有一个
> **二元函数**：函数的参数只有两个
>
> **一元断言/谓词**：函数的参数只有一个，并且返回类型是bool
> **二元断言/谓词**：函数的参数只有两个，并且返回类型是bool

- 示例：想要移除vector中大于5的元素


<font color=red>**但是发现没有得到想要的结果**</font>，那么此时可以从源码出发来进行探索

<img src="..\0.TyporaPicture\image-20250110170124860.png" alt="image-20250110170124860" style="zoom:67%;" />

#### 5.2 源码

- `remove_if`

  ```C++
  // first = vec.begin()
  // last = vec.end()
  // p = func
  template<class ForwardIt, class UnaryPredicate>
  ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
      first = std::find_if(first, last, p); // 找到第一个应该删除的开始向后遍历
      if (first != last)
          for(ForwardIt i = first; ++i != last; )
              if (!p(*i))
                  *first++ = std::move(*i); // 把不满足条件即不应该删除保留下来，且first就作为局部新容器的尾后迭代器
      return first;
  }
  // std::remove_if 最后返回的 first，是容器中「保留下来的有效元素」的尾后迭代器
  ```

- 跳转到`find_if`函数查看

  ``` c++
  // first = vec.begin()
  // last = vec.end()
  // p = func
  template<class InputIt, class UnaryPredicate>
  constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
  {
      for (; first != last; ++first) {
          if (p(*first)) {
              return first;
          }
      }
      return last;
  }
  
  //分析一下过程，其实就是找到第一个大于5的元素，返回相应迭代器
                         last
  1, 3, 5, 9, 6, 4, 6, 5
           f
  ```

- 接着往下看

  ``` c++
  // 使用的代码
  remove_if(vec.begin(), vec.end(), func);
  // first = vec.begin()
  // last =  vec.end()
  // p = func
  ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
      first = std::find_if(first, last, p);
      if (first != last){
          for(ForwardIt i = first; ++i != last; )
          {
              if (!p(*i))
              {
                  *first++ = std::move(*i);
              }
          }
      }
      return first;
  }
  
           f             last
  1, 3, 5, 9, 6, 4, 6, 5
                 i
  
              f          last
  1, 3, 5, 4, 6, 4, 6, 5
                    i
  
              f          last
  1, 3, 5, 4, 6, 4, 6, 5
                       i
  
                 f       last
  1, 3, 5, 4, 5, 4, 6, 5
                       i 
  //最终返回4这个元素对应的迭代器       
  ```

再次观察结果，可以发现期待的最终结果是{1,3,5,4,5}，而这个理想结果实际上已经是vector的前五个元素了

而且<font color=red>**remove_if函数的返回值就是待删除的元素的首迭代器**</font>

也就是说，remove只负责移动，最终的删除还需要调用erase

<img src="..\0.TyporaPicture\image-20250113112112414.png" alt="image-20250113112112414" style="zoom:67%;" />

> 思维拓展：
>
> remove_if实际上最终的效果是同时做了两件事，更改了容器中特定位置的元素，并且返回了待删除元素的首迭代器
>
> 而在我们以往的认知中，同时干两件事总是比较容易出问题。比如多线程环境下，一个线程对某个数据进行写操作，一个线程对它进行读操作，如果不加锁的话，没法确定执行的先后，可能会出现预期之外的值。可以通过下面的例子来理解一下：
>
> <img src="..\0.TyporaPicture\image-20250113175527651.png" alt="image-20250113175527651" style="zoom:67%;" />
>
> 大家认为这样一串代码会有什么样的结果呢？运行一下，可能会大跌眼镜
>
> 回顾vector迭代器失效的原理，试试该怎样解决

> 很容易想到：更新迭代器的方法
>
> <img src="..\0.TyporaPicture\image-20250506170452148.png" alt="image-20250506170452148" style="zoom:67%;" />
>
> 小心迭代器失效，如果有扩容机制，一定得记得更新迭代器

#### 5.3 使用lambda代替一元谓词作为第三个参数

回到remove_if的使用，第三个参数是一元谓词

``` c++
bool func(int value) {
    return value > 5;
}

void test0() {
    vector<int> vec = {1,3,5,9,6,4,6,5};
    for_each(vec.begin(),vec.end(),[](int& value) {
        		cout << value << " ";
             });
    cout << endl;

    auto it = remove_if(vec.begin(),vec.end(),func);
    vec.erase(it,vec.end()); // 搭配remove_if使用
	
    for_each(vec.begin(),vec.end(),[](int& value){
                cout << value << " ";
             });
    cout << endl;
}
```

当然也**可以用lambda表达式替代**

``` c++
    vector<int> vec = {1,3,5,9,6,4,6,5};
    for_each(vec.begin(),vec.end(),[](int& value) {
                cout << value << " ";
             });
    cout << endl;
   
    auto it = remove_if(vec.begin(),vec.end(),[](int& value) {
							return value > 5; 
						});
    vec.erase(it,vec.end());

    for_each(vec.begin(),vec.end(),[](int& value) {
                cout << value << " ";
             });
    cout << endl;
```

> 既然是比较两个数的大小，我们很容易联想到之前已经多次使用的std::less和std::greater，尝试使用会发现一个问题
>
> <img src="..\0.TyporaPicture\image-20250330173517241.png" alt="image-20250330173517241" style="zoom:67%;" />
>
> ``` c++
> // std::less对象作为函数对象，其底层的operator()函数需要两个参数
> // 一个参数由vector提供（remove_if会遍历迭代器范围的元素）
> // 另一个参数呢，按照需求应该提供一个5，但是如何传参呢？
> auto it = remove_if(vec.begin(),vec.end(),std::less<int>()); // error
> vec.erase(it,vec.end());
> ```
>
> 实际上，可以利用算法适配器实现这一效果

### 6.`copy`——修改式的序列算法

- **函数原型**

  ![image-20260525201412483](..\0.TyporaPicture\image-20260525201412483.png)

- **源码**

  ```cpp
  // copy
  template<class InputIt, class OutputIt>
  OutputIt copy(InputIt first, InputIt last, 
                OutputIt d_first)
  {
      while (first != last) {
          *d_first++ = *first++;
      }
      return d_first;
  }
  // copy_if
  template<class InputIt, class OutputIt, class UnaryPredicate>
  OutputIt copy_if(InputIt first, InputIt last, 
                   OutputIt d_first, UnaryPredicate pred)
  {
      while (first != last) {
          if (pred(*first))
              *d_first++ = *first;
          ++first;
      }
      return d_first;
  }
  ```

### 7.`sort`——排序算法

- **函数原型**

  ![image-20260525201554174](..\0.TyporaPicture\image-20260525201554174.png)

- **示例**

  ```cpp
  #include <algorithm>
  #include <functional>
  #include <array>
  #include <iostream>
   
  int main() {
      std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
   
      // 用默认的 operator< 排序
      std::sort(s.begin(), s.end());
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用标准库比较函数对象排序
      std::sort(s.begin(), s.end(), std::greater<int>());
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用自定义函数对象排序
      struct {
          bool operator()(int a, int b) const
          {   
              return a < b;
          }   
      } customLess;
      std::sort(s.begin(), s.end(), customLess);
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用 lambda 表达式排序
      std::sort(s.begin(), s.end(), [](int a, int b) {
          return b < a;   
      });
      for (auto a : s) {
          std::cout << a << " ";
      } 
      std::cout << '\n';
  }
  ```

  ```cpp
  // 输出结果
  0 1 2 3 4 5 6 7 8 9 
  9 8 7 6 5 4 3 2 1 0 
  0 1 2 3 4 5 6 7 8 9 
  9 8 7 6 5 4 3 2 1 0
  ```

### 8.其余算法

- **非修改式的序列算法：`count`、`find`**

  ![image-20260526195414859](..\0.TyporaPicture\image-20260526195414859.png)

  ![image-20260526195434166](..\0.TyporaPicture\image-20260526195434166.png)

  ```cpp
  vector<int> vec = {1, 2, 3, 2, 2, 4};    
  // 统计数字 2 出现的次数
  int res = count(vec.begin(), vec.end(), 2); 
  cout << "2出现的次数：" << res; // 输出：3
  
  vector<int> vec = {10, 20, 30, 40};  
  // 查找数字 30
  auto it = find(vec.begin(), vec.end(), 30); 
  if (it != vec.end()) {
      cout << "找到元素：" << *it; // 输出：30
  } else {
      cout << "未找到";
  }
  ```

- **修改式的序列算法：`replace`、`fill`**

  ![image-20260526195814371](..\0.TyporaPicture\image-20260526195814371.png)

  ![image-20260526195826853](..\0.TyporaPicture\image-20260526195826853.png)

  ```cpp
  // 将区间 [first, last) 内所有等于 old_value 的元素替换为 new_value
  std::vector<int> v = {1, 2, 3, 2, 4, 2};
  std::replace(v.begin(), v.end(), 2, 99); // v 变成 {1, 99, 3, 99, 4, 99}
  
  // 将区间 [first, last) 内的所有元素一律赋值为 value，原来的内容会被完全覆盖
  std::vector<int> v(5);           	// {0,0,0,0,0}
  std::fill(v.begin(), v.end(), 7); 	// {7,7,7,7,7}
  ```

- **二分搜索的算法：`lower_bound`、`upper_bound`、`equal_range`**

  ![image-20260526200035316](..\0.TyporaPicture\image-20260526200035316.png)

  ![image-20260526200041641](..\0.TyporaPicture\image-20260526200041641.png)

  ![image-20260526200050275](..\0.TyporaPicture\image-20260526200050275.png)

  ```cpp
  // 返回第一个不小于(即大于或等于) value 的元素位置，即第一个 *it >= value 的位置
  std::vector<int> v = {1, 2, 4, 4, 5, 7}; // 有序
  auto it = std::lower_bound(v.begin(), v.end(), 4); // it 指向第一个 4 的位置（索引 2）
  it = std::lower_bound(v.begin(), v.end(), 3); // 没有3，指向第一个不小于3的元素，即4的位置（索引2）
  
  // 返回第一个大于 value 的元素位置，即第一个 *it > value 的位置
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto it = std::upper_bound(v.begin(), v.end(), 4); // it 指向第一个大于4的元素，即值为5的位置（索引 4）
  
  // 一次性返回等于 value 的元素的左闭右开区间，结果是一个 std::pair，包含 lower_bound 和 upper_bound 的结果
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto range = std::equal_range(v.begin(), v.end(), 4);
  // range.first 指向第一个4（索引2）
  // range.second 指向5（索引4）
  auto range2 = std::equal_range(v.begin(), v.end(), 3);
  // range2.first == range2.second，都指向可以插入3的位置（索引2，即当前第一个4的位置）
  ```

  ```cpp
  // lower_bound 与 upper_bound 的结合使用
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto low = std::lower_bound(v.begin(), v.end(), 4);
  auto up  = std::upper_bound(v.begin(), v.end(), 4);
  // 此时的 [low, up) 就是所有等于4的元素的范围
  for (auto i = low; i != up; ++i) std::cout << *i << ' '; // 4 4
  ```

  > **补充**
  >
  > 若是使用另一个版本的函数原型：
  >
  > ```cpp
  > // 以lower_bound为例
  > template< class ForwardIt, class T, class Compare >
  > ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
  > // 要做的事情的本质是：
  > // 找第一个 `comp(element, value)` 为 false 的位置，即第一个不满足比较器的元素
  > ```
  >
  > ==**二分搜索算法与 `Compare` 的关系：**==
  >
  > **前提**：区间 `[first, last)` 已按 `comp` 排序（默认 `<`）
  >
  > | 算法          | 内部判断             | 返回值与含义                                                 |
  > | :------------ | :------------------- | :----------------------------------------------------------- |
  > | `lower_bound` | `comp(*it, value)`   | **第一个使 `comp(*it, value) == false` 的位置** 即 `*it >= value`（不小于 `value`） |
  > | `upper_bound` | `comp(value, *it)`   | **第一个使 `comp(value, *it) == true` 的位置** 即 `*it > value`（严格大于 `value`） |
  > | `equal_range` | 同时使用上述两种判断 | **`std::pair<It, It>`** `first` = `lower_bound` 的结果 `second` = `upper_bound` 的结果 表示等于 `value` 的元素范围 `[first, second)` |

- **取最值：`max`、`min`、`minmax(C++11)`**

  1. **两个值的比较（基础版本）**

     ![image-20260526202139764](D:\Typora Picture\image-20260526202139764-177979822600998.png)

     ![image-20260526202148451](..\0.TyporaPicture\image-20260526202148451.png)

  2. **带自定义比较器的版本**

     ```cpp
     template< class T, class Compare >
     const T& max( const T& a, const T& b, Compare comp );
     
     template< class T, class Compare >
     const T& min( const T& a, const T& b, Compare comp );
     
     // min返回 comp(a, b) == true
     // max返回 comp(a, b) == false
     ```

     ```cpp
     auto cmp = [](int a, int b) { return std::abs(a) < std::abs(b); };
     int a = -10, b = 5;
     int min_abs = std::min(a, b, cmp); //  5
     int max_abs = std::max(a, b, cmp); // -10，因为 |-10| > |5|
     ```

  3. **初始化列表版本（C++11 起）**

     ```cpp
     template< class T >
     T max( std::initializer_list<T> ilist );
     
     template< class T >
     T min( std::initializer_list<T> ilist );
     ```

     ```cpp
     int worst = std::min({3, 1, 4, 1, 5, 9}); // 1
     int best = std::max({3, 1, 4, 1, 5, 9});  // 9
     ```

  4. **一次性获取最小和最大：`std::minmax`**

     ```cpp
     template< class T >
     std::pair<const T&, const T&> minmax( const T& a, const T& b );
     
     template< class T >
     std::pair<T, T> minmax( std::initializer_list<T> ilist );
     ```

     ```cpp
     int a = 10; int b = 20;
     auto result = std::minmax(a, b);
     std::cout << "min: " << result.first << '\n';	// 10
     std::cout << "max: " << result.second << '\n';	// 20
     // 结构化绑定用法（C++17起支持）
     int x = 5, y = 12;
     auto [lo, hi] = std::minmax(x, y);
     // 引用绑定版本：auto& [lo_ref, hi_ref] = std::minmax(x, y); lo_ref 是 const int&，绑定到原来的较小者（x），但 x 之后修改，lo_ref 也会变
     
     auto [lo, hi] = std::minmax({3, 1, 4, 2}); // lo = 1, hi = 4
     //传统写法
     std::pair<int, int> result = std::minmax({3, 1, 4, 2});
     int lo = result.first;
     int hi = result.second;
     ```

- **集合操作：`set_intersection`(取交集)、`set_union `(取并集)**

  ![image-20260526203506775](D:\Typora Picture\image-20260526203506775.png)

  ![image-20260526203546363](D:\Typora Picture\image-20260526203546363.png)

  ```cpp
  std::vector<int> v1 = {1, 2, 3, 3, 4, 5, 5, 7};
  std::vector<int> v2 = {3, 3, 5, 6, 7, 7, 8};
  // 取交集
  std::vector<int> intersection;
  std::set_intersection(v1.begin(), v1.end(),
                            v2.begin(), v2.end(),
                            std::back_inserter(intersection));
  for (int x : intersection) std::cout << x << ' '; // 结果：{3, 3, 5, 7}
  // 取并集
  std::vector<int> union_result;
  std::set_union(v1.begin(), v1.end(),
                     v2.begin(), v2.end(),
                     std::back_inserter(union_result));
  for (int x : union_result) std::cout << x << ' '; // 输出：1 2 3 3 4 5 5 6 7 7 8
  ```

  > **补充：使用自定义比较器**
  >
  > ```cpp
  > template< class InputIt1, class InputIt2, class OutputIt, class Compare >
  > OutputIt set_intersection( InputIt1 first1, InputIt1 last1,
  >                            InputIt2 first2, InputIt2 last2,
  >                            OutputIt d_first, Compare comp );
  > ```
  >
  > ```cpp
  > // 默认为降序排列
  > std::vector<int> a = {9, 7, 5, 3, 1};
  > std::vector<int> b = {8, 7, 7, 4, 3, 2};
  > std::vector<int> result;
  > std::set_intersection(a.begin(), a.end(),
  >                       b.begin(), b.end(),
  >                       std::back_inserter(result),
  >                       std::greater<int>()); // 同样的比较器
  > // result: {7, 3}
  > ```
  >
  > **与默认比较器相比**
  >
  > - 如果自定义比较器和默认 `<` 定义了**相同的等价关系**（比如只是把升序改成降序），那么结果的多重集（元素及出现次数）不变，但**顺序会变**
  > - 如果自定义比较器改变了等价关系（比如不区分大小写、按某个成员比较等），那么**哪些元素被视为相同就会不同**，最终结果的内容就会不同

# 二、补充

1. **容器、迭代器、算法之间的关系是怎样的？他们是如何结合在一起的？**

   - 三者关系

     1. **容器（Containers）**：负责数据的存储和管理
     2. **迭代器（Iterators）**：提供统一的接口来访问容器中的元素
     3. **算法（Algorithms）**：定义数据的处理逻辑

     这三者之间的关系可以概括为：**算法通过迭代器与容器进行交互，迭代器作为容器和算法之间的桥梁**

   - 结合方式

     1. 容器调用`begin()`、`end()`产生迭代器，标记出待操作的数据区间
     2. STL 算法接收迭代器作为参数，以此确定操作范围
     3. 算法通过迭代器实现元素遍历、读写访问，完成查找、排序、移除等逻辑处理
     4. 依托这套机制，同一套算法可以适配多种不同容器，实现代码通用复用# Day25_STL标准模板库5-算法(函数)适配器

# 一、算法适配器

**算法**适配器也称为**函数**适配器

## 1.bind1st、bind2nd

- 本质是**函数绑定器**

  如下模板形式中，两个函数绑定器的第一个参数就是一个函数，第二个参数就是一个数字，如果F是一个二元函数(普通二元函数或者二元谓词)，我们可以绑定F的第一个参数(bind1st)或者第二个参数(bind2nd)，达到我们想要的效果(使用二元谓词的效果)

  ![image-20240812102558858](..\0.TyporaPicture\image-20240812102558858-1733126757209-110.png)

  <img src="..\0.TyporaPicture\image-20250114172229681.png" alt="image-20250114172229681" style="zoom:80%;" />

- **代码示例**

  ```cpp
  void test0()
  {
      vector<int> vec = {1,3,5,9,6,4,6,5};
      for_each(vec.begin(),vec.end(),[](int & value){
                  cout << value << " ";
               });
      cout << endl;
  
      auto it = remove_if(vec.begin(),vec.end(),
                          bind1st(std::less<int>(),5)); // 这样相当于将std::less的operator()函数的第一个参数固定为5
      vec.erase(it,vec.end());
  
      for_each(vec.begin(),vec.end(),[](int & value){
                  cout << value << " ";
               });
      cout << endl;
  }
  ```

  > 1. 这样做的结果是删除所有大于5的元素还是所有小于5的元素？
  >
  >    - bind1st` → 固定**第一个参数**为 `5
  >    - 调用：`less<int>()(5, 元素x)` → `5 < x`
  >    - 等价：**元素 x > 5** 时，谓词返回 `true`
  >    - 结论：**删除所有大于 5 的元素** ✅
  >
  > 2. 还可以利用上bind2nd（固定第二个参数）与 std::greater（其底层的operator()函数逻辑不同）
  >
  >    - 组合 1：`bind1st + less<int>`
  >
  >      ```cpp
  >      bind1st(less<int>(), 5) → less(5, x) → 5 < x → x > 5
  >      ```
  >
  >    - 组合 2：`bind2nd + less<int>`
  >
  >      ```cpp
  >      bind2nd(less<int>(), 5) → less(x, 5) → x < 5
  >      ```
  >
  >    - 组合 3：`bind1st + greater<int>`
  >
  >      ```cpp
  >      bind1st(greater<int>(), 5) → greater(5, x) → 5 > x → x < 5
  >      ```
  >
  >    - 组合 4：`bind2nd + greater<int>`
  >
  >      ```cpp
  >      bind2nd(greater<int>(), 5) → greater(x, 5) → x > 5
  >      ```

## ==2.bind==

**[bind原理图释链接](https://www.cnblogs.com/xusd-null/p/3698969.html)**

> **引入**
>
> bind1st、bind2nd实际属于比较过时的方法，因为它们对其绑定的函数对象要求过于严格
>
> - 硬性要求 1：必须是「二元函数对象」
>
>   只接受 **有且仅有两个参数** 的函数 / 仿函数
>
>   ✅ 可以：`less<T>`, `greater<T>`, 自定义二元仿函数
>
>   ❌ 不行：普通函数、一元函数、三元函数、lambda、成员函数
>
> - 硬性要求 2：必须自带固定的类型别名
>
>   `bind1st`/`bind2nd` **不会自动推导类型**，强制要求函数对象内部定义 3 个类型：
>
>   ```cpp
>   // 必须定义这三个！少一个都报错
>   first_argument_type   // 第一个参数类型
>   second_argument_type  // 第二个参数类型
>   result_type           // 返回值类型
>   ```
>
> <img src="..\0.TyporaPicture\image-20250425102949642.png" alt="image-20250425102949642" style="zoom:67%;" />

<span style=color:red;background:yellow>**现在有一个更通用的手段——bind**</span>

<img src="..\0.TyporaPicture\image-20240812110817465-1733126757209-116.png" alt="image-20240812110817465" style="zoom:80%;" />

<img src="..\0.TyporaPicture\image-20250114180053729.png" alt="image-20250114180053729" style="zoom:67%;" />

> **注意**
>
> - **std::bind 的本质：是一个**==函数适配器== **，底层是 **编译器生成的匿名仿函数对象**（标准可调用实体）**
>
>   它和 lambda 是**同类底层原理**（都是仿函数对象），但分工完全不同：
>
>   - **lambda**：自己写全新的执行逻辑
>   - **bind**：==**包装、改造已有的可调用对象**==，不写新逻辑
>
> - **`std::bind` 只能绑定一个动作（一个可调用对象），不能同时绑定两个函数**
>
>   想执行多个函数，用 **lambda**，不要用 bind

### 2.1 基本使用

1. **绑定普通N元函数**

    如下，bind可以绑定N元函数，并用统一的方式进行使用

    <img src="..\0.TyporaPicture\image-20250114181459086.png" alt="image-20250114181459086" style="zoom:67%;" />

    根据cpp参考文档的解释，**第一个参数可以是函数对象、函数指针、函数引用(比较少见)、指向成员函数指针或指向数据成员指针**。如上将函数名直接作为参数，相当于是传入函数指针。其他的几种情况也可以试试：

2. **绑定函数对象**

    <img src="..\0.TyporaPicture\image-20250115144417723.png" alt="image-20250115144417723" style="zoom:67%;" />

3. **绑定==函数引用==**

  ==函数引用的语法与函数指针类似==

  <img src="..\0.TyporaPicture\image-20250115144332359.png" alt="image-20250115144332359" style="zoom:67%;" />

4. **绑定*成员函数指针***

    > 只能绑定成员函数指针，而不能绑定成员函数本身
    >
    > 因为成员函数**只能通过 `&类名::函数` 获取指针**
    >
    > ```cpp
    > // 错误写法
    > auto f = std::bind(Test::show, &obj, std::placeholders::_1);
    > auto f = std::bind(obj.show, std::placeholders::_1);
    > // 唯一正确写法
    > // std::bind(&类名::成员函数, 对象指针/对象, 参数...);
    > // 传：成员函数指针&Test::show + 对象地址&obj/对象本身obj
    > auto f = std::bind(&Test::show, &obj, std::placeholders::_1); // 传入一个地址
    > auto f = std::bind(&Test::show, obj, std::placeholders::_1); // 传入一个对象，对象拷贝
    > ```

    <img src="..\0.TyporaPicture\image-20250115144930383.png" alt="image-20250115144930383" style="zoom:67%;" />

    > **补充：bind绑定成员函数时参数列表中的第一个参数（参数列表即除去真正的第一个参数-调用实体之外的所有参数）**
    >
    > 当bind函数绑定类的成员函数(指针)时，需要传入对象的地址以对应this指针这个参数，除此之外还有另一种写法
    >
    > ![image-20240812155206272](..\0.TyporaPicture\image-20240812155206272-1733126757209-121.png)
    >
    > 即bind绑定成员函数的时候，有两种传递的方式
    >
    > - **第一种：直接传递对象的地址**
    >
    >   传递的是地址值，那么就只会有一个指针大小的开销
    >
    > - **第二种：将对象拷贝进来**
    >
    >   传递对象，会拷贝对象，如果对象占据的空间比较大，那么开销也会比较大
    >
    > 如果使用的是第一种，传递的是地址值，**如果对象本身已经销毁了，那么有可能会有野指针的情况**，比如对象ex的创建是A线程，bind的绑定是B线程，在bind绑定时传对象的地址值，但A线程已经销毁了，就会出现这样的问题
    >
    > 但是如果使用第二种形式，**传递的是对象，那么就不会出现野指针的问题**
    >
    > <span style=color:red;background:yellow>**所以在多线程环境下，更建议传对象，而不是传地址**</span>

5. **绑定指向==数据成员==的指针**（这种写法比较奇特，仅作了解）

    ==返回值则为数据成员的类型==

    <img src="..\0.TyporaPicture\image-20250115145044752.png" alt="image-20250115145044752" style="zoom:67%;" />

    用**这种方式访问Example类的成员还有一个前提——这些成员都是public权限的**


### 2.2 引用折叠

bind的声明形式，第一个参数看起来是一个右值引用，为什么在真正使用过程中，传入一些左值也可以呢？这涉及到模板中的**引用折叠**

1. 如下代码修改成模板后是可以正常运行的：

   <img src="..\0.TyporaPicture\image-20250115152358590.png" alt="image-20250115152358590" style="zoom:67%;" />

2. 在调用func时，如果传入的实参是左值，那么T会被推导成左值引用；如果实参是右值，那么T会被推导成右值引用

   ```cpp
   template <typename T>
   int func(T&& a) {
       return a;
   }
   
   int a = 10;
   func(10); // T = int &&
   func(a); // T = int &
   ```

3. 模板中a为T&&类型，那么会造成多个引用符号写到一起。我们自己在写代码时不能将两个以上的引用符号写到一起，因为**模板推导时会遵循一套==引用折叠==的机制**

   ```cpp
   // T&&有两种情况
   & &&---->&
   && &&---->&&
   // 如果模板的函数参数为T&形式，也有两种情况
   & & ---->&
   && &----->&
   ```

   根据上面的引用折叠规则可知：

   - **模板中为T&&**，==实参既可以传**左值**，也可以传**右值**==
   - **模板中为T&**，==实参就只能传**左值**==

### 2.3 占位符

1. 回到bind的基本使用，似乎每次都需要将被绑定的函数的所有参数都一起传入，但除此之外，还有一种**占位符的写法：**

   ![image-20250116152316060](..\0.TyporaPicture\image-20250116152316060.png)

2. 除了bind中指定的1，还使用占位符占据了一个函数参数位置，那么这个std::placeholders::_1占据的是add函数的参数x的位置，还是参数y的位置呢？

   <img src="..\0.TyporaPicture\image-20250330213225163.png" alt="image-20250330213225163" style="zoom:67%;" />

   <img src="..\0.TyporaPicture\image-20250330213443331.png" alt="image-20250330213443331" style="zoom:67%;" />

   根据上面的结果可以发现，占位符占据的是bind所绑定的函数的参数列表中的哪个参数位置，**取决于==单个占位符在bind参数列表中出现的位置（而其取值则取决于调用时的实参列表）==**

3. 进一步地：

   <img src="..\0.TyporaPicture\image-20250116165041225.png" alt="image-20250116165041225" style="zoom:67%;" />

4. 更多参数的情况：

   <img src="..\0.TyporaPicture\image-20250116173910192.png" alt="image-20250116173910192" style="zoom:67%;" />

   <img src="..\0.TyporaPicture\image-20250116170139188.png" alt="image-20250116170139188" style="zoom:67%;" />

> <span style=color:red;background:yellow>**注意**</span>
>
> <font color=red>**如果将占位符改换一下，就会出错**</font>
>
> <img src="..\0.TyporaPicture\image-20250116170903860.png" alt="image-20250116170903860" style="zoom:67%;" />
>
> - **首先，使用了_4这个占位符，那么在传入实参时==至少要传入4个参数==（f调用时可以传很多个参数，多余的参数被舍弃）**
>
> - 对于func函数，第一个参数是传入的10，第二个参数是占位符匹配到的20，第三个参数是占位符匹配到的400，第四个和第五个则是传入的number
>
><span style=color:red;background:yellow>**可以理解为：占位符整体代表的是形参的位置，占位符中的数字代表的是实参的位置**</span>

### 2.4 引用包装器

> **引入**
>
> <img src="..\0.TyporaPicture\image-20250116172739413.png" alt="image-20250116172739413" style="zoom:67%;" />
>
> 上图**说明了bind的默认传递方式是值传递**，如果在bind中想要使用引用传递，需要用到<font color=red>**引用包装器**</font>
>
> ==**引用包装器也属于函数(算法)适配器**==

- bind传参时使用<font color=red>**引用包装器std::ref**</font> (reference)

  <img src="..\0.TyporaPicture\image-20250116175032813.png" alt="image-20250116175032813" style="zoom:67%;" />

- 如果func函数中原本形参形式为const引用，相应地可以使用<font color=red>**常引用包装器std::cref**</font> (const reference)

  <img src="..\0.TyporaPicture\image-20250116175501510.png" alt="image-20250116175501510" style="zoom: 67%;" />

### 2.5 函数指针不能接收bind返回值

上面的例子中我们每次都使用了auto f的形式接收了bind函数的返回值，那么auto究竟推导出什么类型？

看到某一个变量后加上括号，起到调用函数的作用，应该会联想到以前学习过的函数指针，先类比着进行理解。

假设有相同类型的函数

``` c++
int func()
{
    return 10;
}

int func2()
{
    return 20;
}
```



func和func2的返回类型与参数情况一致，可以使用同种函数指针进行调用。为了方便使用，可以给这种函数指针类型起别名。	

函数指针被初始化为函数的地址(函数指针指向函数)相当于是函数的注册；

使用函数指针调用函数时才会执行函数。

这就对应了一种延迟调用的思想（先注册，后执行），可以用来作回调函数。与之理念相似的还有C++的多态思想：基类指针调用虚函数时，只有到运行时（根据基类指针究竟指向的是哪个派生类对象）才能确定具体执行哪个虚函数。

![image-20240812113718833](D:\Typora Picture\image-20240812113718833-1733126757209-115.png)

``` c++
int func(){}

//逻辑层面
int()//函数类型
int(*)()//函数指针类型
typedef int(*Function)()  
    
using Function = int(*)()
    
int (*p)() = &func;
Function f = &func;

function<int()> f;

```

**不过，如果直接根据bind所绑定的函数的类型定义函数指针，是不能直接接收bind返回值的，==而使用function则可以接收==**

## 3.function

<img src="..\0.TyporaPicture\image-20240812145418894-1733126757209-119.png" alt="image-20240812145418894" style="zoom:67%;" />

![image-20250117103618406](D:\Typora Picture\image-20250117103618406-177978327708439.png)

- **`std::function` 不是函数，它是 C++ STL 提供的：一个**通用、多态、类型安全的**可调用对象==包装器==** **（基于**==类型擦除==**实现的类模板）**

  简单说：它是一个**容器**，专门用来**装各种可调用的东西**（普通函数、lambda、仿函数、成员函数等），只要它们的**调用签名（返回值 + 参数）一致**，就能装进同一个 `std::function` 里

- **体现了万物皆对象的思想**

- <span style=color:red;background:yellow>**function称为函数包装器，其存储的是函数类型，所以也可以称为函数容器**</span>

### 3.1 function存普通函数

**模板参数由函数签名决定**——签名 = **返回值类型 + 参数类型 (个数)**

```cpp
#include <iostream>
#include <functional>  // 必须包含
using namespace std;

// ====================== 1. 定义普通函数 ======================
// 函数1：加法函数
// 【函数签名】：int (int, int)
// （返回值int，参数是两个int）
int add(int a, int b) {
    return a + b;
}
// 函数2：打印函数
// 【函数签名】：void (int)
// （返回值void，参数是一个int）
void printNum(int num) {
    cout << "数字：" << num << endl;
}
// ====================== 2. 使用 function 存储 ======================
int main() {
    // --------------------------
    // 存储 签名为 int(int, int) 的函数
    // function 模板参数 = 函数签名
    // --------------------------
    function<int(int, int)> func1;  // 模板参数严格匹配签名
    func1 = add;                    // 存入普通函数
    cout << func1(10, 20) << endl;  // 调用：输出30
    
    // --------------------------
    // 存储 签名为 void(int) 的函数
    // function 模板参数 = 函数签名
    // --------------------------
    function<void(int)> func2;      // 模板参数严格匹配签名
    func2 = printNum;              	// 存入普通函数
    func2(666);                    	// 调用：输出 数字：666

    return 0;
}
```

### 3.2 function接收bind的返回值

对于函数而言，函数的类型包含了两个信息：**函数返回类型 + 函数参数列表(包含了函数参数的类型、个数、顺序)**

<img src="..\0.TyporaPicture\image-20250117100409588.png" alt="image-20250117100409588" style="zoom:67%;" />

很多时候，逻辑层面上很好理解，但是原生的语法却并不支持这种表达，STL则提供了一种方式可以支持这种表达——即`std::function`

- **bind绑定普通函数**

  ==**function的模板参数具体由打包之后的函数的调用签名决定**==

  > 1. **函数的调用签名（Signature）**：**返回值类型 + 参数的类型 / 个数**（比如 `int(int, int)`）
  > 2. **函数的逻辑（Logic）**：函数内部具体做什么（加法、乘法、打印、哈希计算、业务判断……）

  <img src="..\0.TyporaPicture\image-20250117104001027.png" alt="image-20250117104001027" style="zoom:67%;" />

  同理，**==打包之后==的逻辑类型应该为int(int)时**，可以写成：

  <img src="..\0.TyporaPicture\image-20250117104615584.png" alt="image-20250117104615584" style="zoom:67%;" />

- **bind绑定成员函数指针**

  对于bind绑定成员函数的结果，也是一样的形式，非常简单

  <img src="..\0.TyporaPicture\image-20250117105554463.png" alt="image-20250117105554463" style="zoom:67%;" />

  **使用function接收bind绑定成员函数的返回值，function对象在初始化与使用时不需要顾及类的信息**

- **bind中使用结合占位符**

  <img src="D:\Typora Picture\image-20250117114418119.png" alt="image-20250117114418119" style="zoom:67%;" />

  **写代码的时候不建议写成这种带"炮灰"的形式，没有必要，还很容易混淆**

> **补充：bind的返回值究竟是什么类型，为什么能够用不同类型的function对象来接这个返回值**
>
> 1. **`std::bind` 的返回值类型**：
>
>    是**编译器自动生成的、没有名字的匿名仿函数类型（闭包类型）**，这个类型我们**无法手动书写**，所以只能用 `auto` 接收
>
> 2. **为什么能用 `std::function` 接收？**
>
>    因为 **`std::function` 根本不关心绑定对象的原始类型！它只认「调用签名」**
>
>    只要 `bind` 返回的匿名对象，**调用签名**和 `function` 的模板参数匹配，就能被包装

### 3.3 function表示lambda表达式返回值

lambda表达式的返回值，也可以利用std::function进行相应的表示

![image-20240812151459260](..\0.TyporaPicture\image-20240812151459260-1733126757209-112.png)

### 3.4 function使用的误区

<span style=color:red;background:yellow>**在使用std::function表示lambda表达式时，不要捕获局部变量的引用**</span>

![image-20240812152701250](..\0.TyporaPicture\image-20240812152701250-1733126757209-109.png)

### ==3.5 bind与function结合使用体现多态性==

我们了解了std::bind和std::function各自的基本使用，再来看看它们的结合使用，这是一种**非常**强大的用法，因为**bind具备改变函数形态的功能，只要函数的返回类型相同，任何参数类型的函数都可以被bind绑定之后，变成函数类型完全一致的函数对象，然后都可以被function进行接收**

- std::function与std::bind结合使用体现出多态性的例子——也就是注册回调函数与执行回调函数

  ```cpp
  #include <iostream>
  #include <functional>  // 必须包含，用于 std::function 和 std::bind
  
  using std::cout;
  using std::endl;
  using std::function;
  using std::bind;
  
  // 核心类：通过回调函数实现多态行为（替代传统继承+虚函数）
  class Figure {
  public:
      // 定义回调函数类型（与图中一致）
      using DisplayCallback = function<void()>;       // 显示回调：无参数、无返回值
      using AreaCallback = function<double()>;        // 面积回调：无参数、返回double
  
      // 注册回调函数（图中的“回调注册”）
      void setDisplayCallback(DisplayCallback&& cb) {
          _displayCallback = std::move(cb);  // 移动语义避免拷贝
      }
      void setAreaCallback(AreaCallback&& cb) {
          _areaCallback = std::move(cb);
      }
  
      // 执行回调函数（图中的“回调执行”）
      void handleDisplay() const {
          if (_displayCallback) {  // 确保回调已注册才执行
              _displayCallback();
          }
      }
      double handleArea() const {
          if (_areaCallback) {
              return _areaCallback();
          }
          return 0.0;  // 未注册时返回默认值
      }
  
  private:
      DisplayCallback _displayCallback;  // 存储显示回调
      AreaCallback _areaCallback;         // 存储面积回调
  };
  
  // 矩形类（无需继承Figure）
  class Rectangle {
  public:
      Rectangle(double len, double wid)
          : _length(len), _width(wid) {}
  
      // 成员函数：作为回调的“具体实现”
      void display() const {
          cout << "矩形";
      }
      double area() const {
          return _length * _width;
      }
  
  private:
      double _length;
      double _width;
  };
  
  // 圆形类（新增一个类，体现多态的“不同行为”）
  class Circle {
  public:
      Circle(double r) : _radius(r) {}
  
      // 成员函数：与Rectangle同名，但实现不同
      void display() const {
          cout << "圆形";
      }
      double area() const {
          return 3.14159 * _radius * _radius;
      }
  
  private:
      double _radius;
  };
  
  // 统一接口函数（相当于传统多态中接收基类引用的display函数）
  void printFigure(const Figure& fig) {
      fig.handleDisplay();
      cout << "的面积：" << fig.handleArea() << endl;
  }
  
  void test() {
      // 1. 矩形对象：注册Rectangle的成员函数作为回调
      Rectangle rect(2, 5);  // 长2，宽5
      Figure fig1;
      // std::bind 将成员函数+对象绑定为可调用对象，适配std::function
      fig1.setDisplayCallback(bind(&Rectangle::display, &rect));
      fig1.setAreaCallback(bind(&Rectangle::area, &rect));
      printFigure(fig1);  // 输出：矩形的面积：10
  
      // 2. 圆形对象：注册Circle的成员函数作为回调
      Circle circle(3);  // 半径3
      Figure fig2;
      fig2.setDisplayCallback(bind(&Circle::display, &circle));
      fig2.setAreaCallback(bind(&Circle::area, &circle));
      printFigure(fig2);  // 输出：圆形的面积：28.27431
  }
  
  int main() {
      test();
      return 0;
  }
  
  // 结果
  // 矩形的面积：10
  // 圆形的面积：28.2743
  ```

  > 1. **为什么要使用移动语义**
  >
  >    在之前的回调多态代码中，使用`std::move`的核心目的是**避免不必要的深拷贝、提升性能**，尤其对`std::function`这类管理资源的对象效果显著。下面从原理到实战，完整解释移动语义的价值与应用逻辑
  >
  > 2. **拷贝语义 vs 移动语义的本质区别**
  >
  >    | 特性             | 拷贝语义                             | 移动语义                               |
  >    | ---------------- | ------------------------------------ | -------------------------------------- |
  >    | **资源操作**     | 深拷贝（复制全部数据，重新分配内存） | 所有权转移（仅修改指针，不复制数据）   |
  >    | **性能开销**     | 高（O (n) 时间复杂度，涉及内存分配） | 极低（O (1) 时间复杂度，仅指针操作）   |
  >    | **原对象状态**   | 保持不变，可继续正常使用             | 进入 “有效但未定义” 状态（通常被置空） |
  >    | **典型触发方式** | 左值赋值（如`a = b`）                | 右值引用（如`a = std::move(b)`）       |

- **多态的两种写法**

  面向对象的写法：继承 + 纯虚函数(或者普通的虚函数)，具有一定的局限性：必须建立继承关系，派生类对基类的虚函数进行覆盖时必须要函数名和函数形式完全一致等
  
  <font color=red>**基于对象(即面向函数)**</font>的写法：std::function + std::bind，这一套写法摒弃了上述的局限性，同样体现出多态性且更灵活

> **补充：两种多态的区别**
>
> 1. **总结**
>
>    - **虚函数 + 继承（传统多态）**
>
>      - **不用手动切换逻辑**
>
>      - 基类指针 / 引用**指向不同子类对象**，**直接调用**就自动执行对应逻辑，**全程自动、隐式切换**。
>
>    - **std::function + std::bind（函数多态）**
>
>      - **想切换逻辑，必须手动重新赋值 / 注册**
>
>      - 它不会自动变，你不手动给 `function` 绑定新的闭包，它永远执行老逻辑
>
> 2. **对比**
>
>    - 虚函数多态：自动切换（指向谁，就用谁）
>
>      ```cpp
>      // 基类
>      class Base {
>      public:
>          virtual void do() = 0; // 虚函数
>      };
>      // 子类1
>      class A : public Base { void do() { cout << "A逻辑"; } };
>      // 子类2
>      class B : public Base { void do() { cout << "B逻辑"; } };
>      
>      // 使用
>      Base* ptr;
>      ptr = new A(); 
>      ptr->do(); // 自动执行A ✅ 不用手动改
>      
>      ptr = new B(); // 只改指向的对象
>      ptr->do(); // 自动执行B ✅ 自动切换
>      ```
>
>      **核心**：改的是**对象**，调用方式完全不变，**多态自动生效**
>
>    - function+bind 多态：手动切换（不赋值，永远不变）
>
>      ```cpp
>      // 两个独立逻辑（无继承）
>      void logicA() { cout << "A逻辑"; }
>      void logicB() { cout << "B逻辑"; }
>            
>      // 使用
>      function<void()> func;
>            
>      // 第一次注册
>      func = bind(logicA);
>      func(); // 执行A
>            
>      // 想切换成B？必须手动重新赋值！
>      func = bind(logicB); // 手动切换
>      func(); // 执行B
>      ```
>
>      **核心**：不改赋值，永远执行老逻辑；**切换逻辑 = 手动重新给 function 赋值**。
>
> 3. **差异**
>
>    - **虚函数多态**：**对象决定行为**，切换对象 → 行为自动变
>
>    - **function+bind 多态**：**赋值决定行为**，不手动重新赋值 → 行为永远不变
>
> 4. **补充**
>
>    这不是缺陷，是设计定位不同
>
>    - 虚函数：**面向对象多态**，用于一类有继承关系的对象行为
>
>    - `function+bind`：**函数式多态**，用于任意独立函数 / 回调的灵活替换

## 4.成员函数指针(包装)适配器mem_fn

因为成员函数与算法库中的算法不能直接很好的适配，所以二者结合使用的时候，需要使用成员函数适配器进行适配

![image-20250121150627602](D:\Typora Picture\image-20250121150627602-177978568827644.png)

1. **示例**

  <img src="..\0.TyporaPicture\image-20250121151937130.png" alt="image-20250121151937130" style="zoom:67%;" />

  <img src="..\0.TyporaPicture\image-20250331210156190.png" alt="image-20250331210156190" style="zoom:67%;" />

  1. **使用成员函数适配器mem_fn对成员函数指针进行简单的包装**即可：

  <img src="..\0.TyporaPicture\image-20250121152520023.png" alt="image-20250121152520023" style="zoom:67%;" />

  <img src="..\0.TyporaPicture\image-20250121152629153.png" alt="image-20250121152629153" style="zoom:67%;" />

2. 上述例子中使用for_each遍历vector时，使用了mem_fn为成员函数print做适配。根据以前学过的知识，还有没有什么方法实现同样效果呢？

  **for_each的第三个参数要求是一个一元函数**，成员函数print看起来无参，实际上有隐含的this指针作为参数，它的确是一个一元函数

  <img src="..\0.TyporaPicture\image-20250121162733638.png" alt="image-20250121162733638" style="zoom:67%;" />

3. 或者我们也可以用**function接收bind绑定成员函数的结果**

   ![image-20250121164540811](..\0.TyporaPicture\image-20250121164540811.png)

# 二、适配器

适配器就是Interface(接口)，对容器、迭代器和算法进行包装，但其实质还是容器、迭代器和算法，只是不依赖于具体的标准容器、迭代器和算法类型，容器适配器可以理解为容器的模板，迭代器适配器可理解为迭代器的模板，算法适配器可理解为算法的模板

# 三、函数对象

<span style=color:red;background:yellow>**函数对象也称为仿函数**</span>，严格意义上说函数对象仅仅指重载了函数调用运算符的类的对象。

<img src="..\0.TyporaPicture\image-20250331201115252.png" alt="image-20250331201115252" style="zoom: 67%;" />

<img src="D:\Typora Picture\image-20250331201151276.png" alt="image-20250331201151276" style="zoom:67%;" />

还有一个概念—— 只要可以与小括号进行结合展示出函数含义都可以称为<span style=color:red;background:yellow>**可调用对象**</span>。很多资料中模糊了函数对象和可调用对象的概念说明。上图出自C++之父的书——《C++程序设计语言-第4卷》

> 可调用对象包含了：
>
> - 函数对象
> - 函数指针、函数引用
> - 函数名
> - lambda表达式（可视为一个匿名的函数对象，可以直接在定义后调用，也可以给function函数对象赋值）

还有一个更大范围的概念 —— **可调用实体**，它在可调用对象的基础上还增加了成员函数、成员函数指针（这两者的共同特点是也可以调用，但不能仅凭自己完成调用）

# 四、补充

1. **什么是回调函数，注册回调函数，执行回调函数？**

   - **回调函数：就是一个 “被别人调用” 的普通函数**

     1. 写一个函数 A
     2. 把 A 的地址 / 引用交给另一个函数 B
     3. B **在合适时机（事件发生、任务完成）反过来调用 A**
     4. A 就叫**回调函数**

     特点：

     1. 不直接 `A()`，而是**其余函数间接调用**
     2. 核心是**函数指针 / 可调用对象传递**
     3. 常用于：事件处理、异步通知、排序比较、回调接口

   - **注册回调函数（Register Callback）**

     **注册：就是把回调函数 “交给” 系统 / 库，让其记住此函数**

     一共做两件事：

     1. 定义好符合规范的回调函数（参数、返回值要对）
     2. 调用系统提供的 “注册函数”，把回调函数地址传进去

   - **执行回调函数（Execute Callback）**

     **执行回调：就是系统 / 库在事件发生时，真的去调用注册的那个回调函数**

     流程：

     1. 程序员：注册回调 → 继续干别的事
     2. 系统：监测事件（定时器到点、按钮点击、数据到达）
     3. 事件发生 → 系统自动调用你的回调函数 → **回调被执行**

2. **对于一元函数与二元函数的mem_fn具体使用形式**

   - ==一元函数==

     - **定义示例**

       `void print() const;`

     - **`mem_fn` 返回的可调用对象**

       一元函数，形式为 `void(const T&)` 或 `void(T*)`，只接受一个对象实参。

     - **直接使用**：

       `std::mem_fn(&T::print)` 可直接作为 `for_each` 的第三参数

       ```cpp
       for_each(v.begin(), v.end(), mem_fn(&T::print));
       ```

       > ==**补充：显示写出占位符**==
       >
       > ```cpp
       > for_each(v.begin(), v.end(), bind(mem_fn(&T::print), std::placeholders::_1));
       > ```
       >
       > 正确，但多余
       >
       > - `mem_fn(&T::print)` 本身就是一个一元函数对象，只需传对象即可
       > - `bind` 加 `_1` 只是做了一层“转发”，没有改变参数个数，还是接收一个对象，调用 `obj.print()`
       > - 所以功能完全正常，只是代码更啰嗦

     对象由算法自动传递，无需额外绑定

   - ==二元函数==

     - **定义示例**

       `void print(const std::string& s) const;`

     - **`mem_fn` 返回的可调用对象**

       二元函数，形式为 `void(const T&, const std::string&)`，需要对象和参数两个实参

     - **无法直接用于 `for_each`**，必须将第二个参数绑定，转化为一元函数：

       1. 使用 `std::bind`：

          ```cpp
          for_each(v.begin(), v.end(), bind(mem_fn(&T::print), std::placeholders::_1, "Hello"));
          ```

       2. 使用 lambda：

          ```cpp
          auto f = std::mem_fn(&T::print);
          std::for_each(v.begin(), v.end(), [&f](const T& obj) { f(obj, "Hello"); });
          ```

     需要手写函数对象包装

   - **核心区别**：

     - 一元成员函数 → `mem_fn` 返回一元可调用对象 → 可直接配 `for_each`
     - 二元成员函数 → `mem_fn` 返回二元可调用对象 → 需绑定多余参数变为一元，才能用于 `for_each`

3. **bind的引用包装器的问题**

   ```cpp
   #include <iostream>
   #include <functional>
   
   using namespace std;
   using namespace placeholders;
   
   void modify(int &a, int &b) {
   /* void modify(int a, int b) { */
       a *= 2;
       b += 10;
   }
   
   void test1() {
       int x = 5, y = 5;
       auto f = bind(modify, x, y);
       f(x, y);
       cout << x << "," << y << endl; // ?
   }
   
   void test2() {
       int x = 5, y = 5;
       auto f = bind(modify, _1, _2);
       f(x, y);
       cout << x << "," << y << endl; // ?
   }
   
   void test3() {
       int x = 5, y = 5;
       auto g = bind(modify, ref(x), ref(y));
       g();
       cout << x << "," << y << endl; // ?
   }
   
   int main() {
       cout << "---------test1()---------" << endl;
       test1();
       cout << "---------test2()---------" << endl;
       test2();
       cout << "---------test3()---------" << endl;
       test3();
   
       return 0;
   }
   
   /*
   ---------test1()---------
   5,5
   ---------test2()---------
   10,15
   ---------test3()---------
   10,15
   */
   ```

   - test1()：**直接绑定变量名**

     这时 `bind` 会在创建时把 `x` 和 `y` 的值（5,5）拷贝到内部，之后的修改只影响副本，外部 `x` 和 `y` 就不会变。所以输出 `5,5`

   - test2()：使用的是占位符 `_1` 和 `_2`，**并没有绑定具体的值**

     `f(x, y)` 调用时，参数 `x`、`y` 会被**完美转发**给 `modify`。因为 `x`、`y` 是左值，所以 `modify(int&, int&)` 接收到的就是 `x` 和 `y` 本身的引用。因此 `modify` 会直接修改 `x` 和 `y`

   - test3()：绑定了具体对象，**使用 `ref()`，强制绑定了引用**，也没有拷贝

     调用 `g()` 时，`modify` 操作的还是 `x` 和 `y` 本身
# Day26_STL标准模板库6-空间适配器

# 一、空间配置器

**在C++中所有STL容器的空间分配其实都是使用的std::allocator**

std::allocator是**可以感知类型的空间分配器**，将**空间的申请**与**对象的构建**、以及**空间的回收**与**对象的销毁**==严格分离==

以前我们知道使用**new创建单个对象**的时候，**空间的申请与对象的构造实际也是分开的**（可以回顾new表达式的工作步骤）

> 那么为什么要将空间的申请与对象的构建分开呢？
>
> 1. **减少不必要的对象构造和析构**：在**容器的使用过程中，有时只是需要预留一些空间，而并不需要立即在这些空间上构造对象**。例如，std::vector 的 reserve 函数，它的作用是为容器预留足够的内存空间，但不会构造任何对象。如果不将空间申请和对象构建分开，每次预留空间时都会构造对象，之后又可能因为不需要这些对象而进行析构，这会带来不必要的性能开销
> 2. **方便实现复杂的容器操作**：**在实现容器的一些操作，如插入、删除元素时，将空间申请和对象构建分开可以更方便地处理各种情况**。例如，在插入元素时，如果当前空间不足，容器可以先申请新的空间，然后将原有元素移动到新空间，最后在合适的位置构造新的对象，这样的操作更加灵活和高效。（比如vector的动态扩容机制背后就使用了空间配置器）

## 1.函数使用

- **std::allocator最重要的成员函数：**

  <img src="..\0.TyporaPicture\image-20250124102502538.png" alt="image-20250124102502538" style="zoom:67%;" />

  ```cpp
  // 申请空间
  T* allocate( std::size_t n );
  
  // 构建对象
  void construct( pointer p, const_reference val );
  
  // 执行析构
  void destroy( pointer p ); // p->~T()，即destroy会使指针指向的对象执行析构函数
  
  // 释放空间
  void deallocate( T* p, std::size_t n );
  ```

- 来尝试完成一个任务，实现自定义的vector，首先给出如下的代码接口

  ```cpp
  template <class T>
  class MyVector {
  public:
      MyVector();
      ~MyVector();
  
      void push_back(const T &);
      void pop_back();
      int size() const;
      int capacity() const;
  private:
      // 重新分配内存，动态扩容要用的
      void reallocate(); 
  
      // 空间的申请与对象的构建分开
      static std::allocator<T> _alloc;
  
      T* _start;
      T* _finish;
      T* _end_of_storage;
  };
  ```

  1. 先完成比较简单的

     <img src="..\0.TyporaPicture\image-20250124103233188.png" alt="image-20250124103233188" style="zoom:67%;" />

  2. 尾部插入元素、删除元素，模拟vector的核心问题就是动态扩容

     <img src="..\0.TyporaPicture\image-20250124103731526.png" alt="image-20250124103731526" style="zoom:67%;" />

  3. 完成动态扩容的功能

     ```cpp
     template <class T>
     void MyVector<T>::reallocate() {
         // 1.申请两倍的新的空间
         int oldCapacity = size(); // 此时的size就是等于capacity的
         int newCapacity = oldCapacity > 0 ? 2 * oldCapacity : 1; // 若是为空容器则先扩容为1
     
         T* ptmp = _alloc.allocate(newCapacity);
     
         if (_start) {
             // 2.使用算法库的函数将老的空间上的元素拷贝到新的空间
             std::uninitialized_copy(_start, _finish, ptmp); // 在裸内存上创建新对象，目标内存为原始未初始化内存（只有空间，无对象）
             // 而std::copy：拷贝已存在的对象，目标内存必须已初始化（已有合法对象）
     
             // 3.老的空间上的元素需要销毁，同时老的空间也要回收
             while (_start != _finish) {
                 /* _alloc.destroy(_start++); */
                 // 注意一下边界问题，这样写是完善的
                 _alloc.destroy(--_finish); // 从后往前销毁元素比较方便，_start指针不动
             }
     
             // 参数为指针(T*)和偏移量(size_t)
             // 如果从_finish开始，偏移量为负数，而size_t不好表达
             // 如果从_start开始,偏移量为正数，更方便
             // 所以选择_start固定，移动_finish;
             _alloc.deallocate(_start, oldCapacity);
         }
     
         // 4.三个指针与新的空间之间产生联系
         _start = ptmp;
         _finish = ptmp + oldCapacity; // 尾后指针
         _end_of_storage = ptmp + newCapacity;
     }
     
     ```

  4. 析构函数的逻辑类似，也是销毁元素、回收空间

     <img src="..\0.TyporaPicture\image-20250124104636381.png" alt="image-20250124104636381" style="zoom:67%;" />

  5. 测试效果并发现不足

     <img src="..\0.TyporaPicture\image-20250124105021706.png" alt="image-20250124105021706" style="zoom:67%;" />

     如果想遍历容器中的元素，首先想到的肯定是增强for循环方式（没有实现取下标，也没有实现迭代器相关的函数），但会出现错误，说明增强for循环的底层实际上也是通过迭代器实现的

     ![image-20250124105645274](..\0.TyporaPicture\image-20250124105645274.png)

  6. 完成迭代器相关函数

     <img src="..\0.TyporaPicture\image-20250124110222143.png" alt="image-20250124110222143" style="zoom:67%;" />

  7. 最终测试

     <img src="..\0.TyporaPicture\image-20250124110309969.png" alt="image-20250124110309969" style="zoom:67%;" />

  完成了简单的模拟后，其实还有很多可以完善的地方，比如取下标、比如insert，可以自行完善，本章主要借此展示了alloctor空间配置器的基本使用

## 2.原理

- 空间配置器分为两级：

  1. **一级空间配置器使用类模板malloc_alloc_template**，其**底层使用的是malloc/free进行空间的申请与释放**

  2. **二级空间配置器使用类模板default_alloc_template（默认空间配置器）**，其底层根据申请空间大小又分为两个分支

     - 当**申请的空间大于128字节**的时候，**还是走malloc_alloc_template** 

     - 当**申请的空间小于或等于128字节**的时候，使用**内存池 + 自由链表**的方法申请空间

       <span style=color:red;background:yellow>**注意：这里提到的自由链表实际是一个容量为16的指针数组，在源码中使用了_S_free_list这个名字，直译为自由链表**</span>

- **二级空间配置器的内存池+自由链表方法**

  有一个容量为16的指针数组，每个元素（指针）指向一个链表 ，用于管理不同大小的内存块。这 16 个指针所指向的链表，分别对应 8、16、24、32、40、48、56、64、72、80、88、96、104、112、120、128 字节的内存块

  每当程序申请小于 128 字节的内存时，二级空间配置器会先将申请的内存大小上调为 8 的倍数，再根据上调后的大小（8的整数倍）找到对应的链表。

  > **示例**
  >
  > 1. 数组中下标为3的指针，代表着会按照8 * (3 + 1) = 32字节为基本单位申请空间，第一次申请32个字节空间的时候，一次性申请很大一片空间（比如32 * 20 = 640个字节），然后按照32字节为一个等分，分成多个等分，然后挂接在下标为3的指针下面，形成链表形式
  >
  >    以后需要32字节的时候，直接在下标为3的下面取出一个节点即可，就是32个字节的内存空间
  >
  > 2. 如果申请64字节空间，第一次申请时也申请很大一片空间，同样按照64字节为一个等分，分成多个等分，挂载在数组中下标为7的指针之下
  >
  >    以后如果需要申请64字节时，就在下标为7的下面取出一个节点即可
  >
  > 3. 其他下标的处理方式完全一致

- **自由链表的工作示意图**

  第一次申请空间时比较麻烦，后续再此申请同等大小的空间可以以O(1)的时间复杂度完成申请。

  ![image-20240813115402461](..\0.TyporaPicture\image-20240813115402461-1733127460324-147.png)

- **内存池+自由链表的意义**

  为什么不每次直接申请相应大小的空间？

  如果频繁申请小片空间，可能会出现内存碎片的问题，这样导致空间的利用率低，会在内核态与用户态之间进行频繁的切换，时间消耗也比较大

