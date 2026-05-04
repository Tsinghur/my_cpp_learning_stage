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

   ![image-20241128143050644](..\0.TyporaPicture\image-20241128143050644.png)