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

## ==三、输入输出流运算符 << >> 的重载==

1. **输出流运算符 <<**

   

2. **输入流运算符 >>**

   

## 四、[] 运算符



## 五、+ += ++ 运算符的重载

1. **+运算符**

   

2. **+=运算符**

   

3. **++运算符**

   

## 六、成员访问运算符 -> 的重载



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

   