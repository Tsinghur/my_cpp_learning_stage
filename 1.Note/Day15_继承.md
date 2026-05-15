# Day15_继承

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



## 五、派生类对象间的复制控制

<font color=red>**复制控制函数就是：拷贝构造函数、赋值运算符函数**</font>

1. **原则**

   基类部分与派生类部分要单独处理

   - **当派生类中没有显式定义复制控制函数时，就会自动完成基类部分的复制控制操作**
   - **当派生类中有显式定义复制控制函数时，不会再自动完成基类部分的复制控制操作，需要显式地调用**

   ![image-20241210114804352](..\0.TyporaPicture\image-20241210114804352.png)

   > **对于拷贝构造**
   >
   > 如果**显式定义**了派生类的拷贝构造，在其中**不去显式调用**基类的拷贝构造，那么无法通过复制初始化基类的部分，只能**尝试用基类无参构造**初始化基类的部分。**如果基类没有无参构造，编译器就会报错**
   >
   > **对于赋值运算符函数**
   >
   > 如果显式定义了派生类的赋值运算符函数，在其中不去显式调用基类的赋值运算符函数，那么基类的部分没有完成赋值操作

   

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

