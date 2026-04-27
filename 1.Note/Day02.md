# Day02_C++与C

## 一、命名空间namespace

### (1)什么是命名空间

1. **命名空间又名字空间，是程序员命名的内存区域**，程序员根据需要指定一些有名字的空间域，把一些全局实体分别存放到各个命名空间中，从而与其他全局实体分隔开

2. 每个名字空间都是一个名字空间域，存放在名字空间域中的全局实体只在本空间域内有效。名字空间对全局实体加以域的限制，从而合理的解决命名冲突

3. 名字冲突就是在同一个作用域中有两个或多个同名的实体，C语言中避免名字冲突，只能进行起名约定

   ```C
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

### (2)命名空间的使用方式

1. **作用域限定符**

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

2. **using编译指令**

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

3. **using声明机制**

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

### (3)using编译指令与using声明机制的注意事项

1. **using编译指令尽量写在局部作用域——建议：将using编译指令写在局部作用域**

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

2. **⭐采用using==编译指令==使用命名空间中的实体时，==要注意避免命名空间中实体与全局位置实体同名==**

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

3. **在不清楚命名空间中实体的具体情况时，尽量不使用using编译指令**

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

4. **在同一作用域内用using声明机制, 不同的命名空间的实体，不能是同名的，否则会发生冲突——using声明机制的特点是：需要哪个实体的时候就引入到程序中，不需要的实体就不引入，尽可能减小犯错误的概率**

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

### (4)命名空间的嵌套使用

```cpp
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

### (5)匿名命名空间（了解）

**不定义名字的命名空间称为匿名命名空间（简称匿名空间）**，如果我们希望一部分实体只在本文件中起作用，那么可以将它们定义在匿名空间中

```cpp
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

```cpp
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
2. 匿名空间中的实体不能跨模块调用

### (6)跨模块调用

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

```cpp
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

```cpp
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

### (1)引用的本质

**C++中的引用本质上是一种被限制的指针**。类似于线性表和栈的关系，栈是被限制的线性表，底层实现相同，只不过逻辑上的用法不同而已

由于<font color=red>**引用是被限制的指针**</font>，所以**引用是占据内存的**，占据的大小就是一个指针的大小。有很多的说法，都说引用不会占据存储空间，其只是一个变量的别名，但这种说法并不准确。引用变量会占据存储空间，存放的是一个地址，但是编译器阻止对它本身的任何访问，从一而终总是指向初始的目标单元。在**汇编里，引用的本质就是“间接寻址”**

可以尝试**对引用取址**，发现获取到的地址**就是引用所绑定变量的地址**

### (2)引用和指针的联系与区别

这是一道非常经典的面试题，请尝试着回答一下：

**联系：**

1. 引用和指针都有地址的概念，都是用来间接访问变量；

2. 引用的底层还是指针来完成，可以把引用视为一个受限制的指针。（const pointer）

**区别：**

1. 引用必须初始化，指针可以不初始化；
2. 引用不能修改绑定，但是指针可以修改指向；
3. 在代码层面对引用本身取址取到的是变量本体的地址，但是对指针取址取到的是指针变量的地址

### (3)常引用:使用const修饰的引用

如果不希望函数体中通过引用改变传入的变量，那么可以使用<span style=color:red;background:yellow>**常引用作为函数参数**</span>

1. 不会修改值
2. ==不会复制（不会造成不必要的开销）==

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

### (4)引用在函数返回值场景的应用

1. **要求：**当以引用作为函数的返回值时，<span style=color:red;background:yellow>**返回的变量其生命周期一定是要大于函数的生命周期**</span>的，即当函数执行完毕时，返回的变量还存在

2. **目的：** ==避免复制==，节省开销

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

3. **为什么 `int& ref = a;` 可以？为什么 `int& ref = test();`（返回 int 时）不可以？**
   因为 `a` 是一个**有名字的变量，可以取地址**；返回类型是 `int`，编译器会生成一个**临时的 `int` 值**（拷贝了 `a` 的内容）。这个临时值没有名字、不可取地址，是一个右值

   > | 类型              | 简单理解                                 | 关键特征                                           |
   > | :---------------- | :--------------------------------------- | :------------------------------------------------- |
   > | **左值 (lvalue)** | 有名字、能取地址、持续存在的**对象**     | 可以出现在等号左边（但不是绝对）                   |
   > | **右值 (rvalue)** | 没有名字、不能取地址、用完即弃的**数据** | 通常出现在等号右边，是临时值、字面量或计算中间结果 |

   函数按值返回时，**它给出的不是原来的那个变量，而是一个立刻生成的、临时的、没有名字的副本**

4. **注意事项**

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

### (1)什么是函数重载

<font color=red>**在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。**</font>重载函数通常**用来命名一组功能相似的函数**，**使得同一函数名可以作用于不同的数据类型或者参数组合,**适用于处理相似功能,但是输入类型不同的情况,这样做**减少了函数名的数量**，对于程序的可读性有很大的好处

### (2)实现函数重载的条件

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

### (3)函数重载的实现原理

名字改编(name mangling)——当函数名称相同时 ，编译器会根据参数的类型、顺序、个数进行改编

- g++ -c Overload.cc

- nm Overload.o


![image-20241014164716694](../0.TyporaPicture\image-20241014164716694.png)

### (4)extern "C"

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
   ```

8. 