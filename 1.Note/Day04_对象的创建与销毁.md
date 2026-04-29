# Day04

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