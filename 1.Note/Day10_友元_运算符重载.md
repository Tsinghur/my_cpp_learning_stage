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

   