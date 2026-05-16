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

     ![image-20231103150156687](D:\Typora Picture\image-20231103150156687.png)

   - <font color=red>**如果在Parent类的构造和析构函数中调用虚函数**</font>

     ![undefined202403191632256](D:\Typora Picture\undefined202403191632256.png)

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

   