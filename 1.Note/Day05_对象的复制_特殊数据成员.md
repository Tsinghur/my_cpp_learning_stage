# Day05

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
