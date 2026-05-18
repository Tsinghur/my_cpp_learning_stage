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

   

## 五、可变参数模板



## 六、类模板

