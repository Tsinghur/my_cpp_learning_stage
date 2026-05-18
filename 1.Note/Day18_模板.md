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

     ![image-20241216162022545](D:\Typora Picture\image-20241216162022545.png)

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

1. **函数模板的头文件与实现文件形式**

   

## 四、函数模板-参数类型&成员函数模板



## 五、可变参数模板



## 六、类模板