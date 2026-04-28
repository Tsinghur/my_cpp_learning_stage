# Day03_类与对象

## 一、异常处理

1. **异常**是程序在执行期间产生的问题，比如尝试除以零的操作

   **异常处理**是用于处理运行时错误的机制，允许开发者在程序中检测错误并采取相应的补救措施，从而使程序能够**优雅地处理**错误并继续运行C++

2. C++ 异常处理涉及到三个关键字：try、catch、throw

   ```cpp
   throw 表达式;
   
   try {
   //语句块
   } catch(异常类型) {
   //具体的异常处理...
   } ...
   catch(异常类型) {
   //具体的异常处理...
   }
   ```

   1. 先定义抛出异常的规则（throw）,异常是一个表达式，它的值可以是基本类型，也可以是类类型

   2. try-catch语句块的catch可以有多个，至少要有一个，否则会报错

      - 执行 try 块中的语句，如果执行的过程中没有异常拋出，那么执行完后就执行最后一个 catch块后面的语句，所有 catch 块中的语句都不会被执行
      - 如果 try 块执行的过程中拋出了异常，那么拋出异常后立即跳转到第一个“异常类型”和拋出的异常类型匹配的 catch 块中执行（称作异常被该 catch 块“捕获”），执行完后再跳转到最后一个catch 块后面继续执行

      注意：<font color=red>**catch的是类型，不是具体信息**</font>

      ```cpp
      double division(double x,double y){
          if(y == 0){
              throw "Deivision by zero";
          }
          return x/y;
      }
      
      void test0(){
          double x = 100, y = 0;
          try{
              cout << "before" << endl;
              cout << division(x,y) << endl;//异常行后的代码不会执行
              cout << "after" << endl;
          }catch(const char * msg){ //catch的小括号里是类型
          	cout << "hello" << endl;
              cout << "hello," << msg << endl;
          }catch(double x){
              cout << "double" << endl;
          }catch(int x){
              cout << "int" << endl;
          }
          cout << "end test" << endl;
      }
      
      ```

## ==二、内存布局==

1. 栈区：操作系统控制，由高地址向低地址生长，编译器做了优化，显示地址时栈区和其他区域保持一致的方向

2. 堆区：程序员分配，由低地址向高地址生长，堆区与栈区没有明确的界限

3. 全局/静态区：读写段（数据段），存放全局变量、静态变量

4. 文字常量区：只读段，存放程序中直接使用的常量，如const char * p = "hello";  hello这个内容就存在文字常量区

5. 程序代码区：只读段，存放函数体的二进制代码

   ![image-20241015175642417](..\0.TyporaPicture\image-20241015175642417.png)

6. **注意：**

   - 因为编译器的优化, 局部变量的地址分配通常是：
     ==虽然 **栈是从高地址向低地址生长的**（即每次函数调用时，栈指针减小），但在一个函数的**同一个栈帧内部**，多个局部变量的分配顺序是完全由编译器决定的。==
     - 后创建的变量分配高地址
     - 先创建的变量分配低地址

   - C++ 的 cout 没有专门处理 “函数指针” 的 operator<< 重载，于是把它隐式转成 bool，非空就是 true，输出为 1，如果**想打印出函数指针**的内容即指向的地址，则**需要使用C中的printf(“%p”, f);**

## 三、面向对象思想

1. **过程论**

   数据和逻辑是分离的、独立的，程序世界本质是过程，数据作为过程处理对象，逻辑作为过程的形式定义，世界就是各个过程不断进行的总体

2. **对象论**

   数据和逻辑不是分离的，而是相互依存的。相关的数据和逻辑形成个体，这些个体叫做对象，世界就是由一个个对象组成的

   **对象论更有助于分析规模较大的事物**

## 四、类

1. C++用**类**来描述对象，类是对现实世界中相似事物的抽象，比如同是“双轮车”的摩托车和自行车，有共同点，也有许多不同点。“车”类是对摩托车、自行车、汽车等相同点的提取与抽象。

   类的定义分为两个部分：

   - 数据，相当于现实世界中的属性，称为<font color=red>**成员变量**</font>

   - 对数据的操作，相当于现实世界中的行为，称为<font color=red>**成员函数**</font>

   从程序设计的观点来说，**类就是数据类型**，是用户定义的数据类型，对象可以看成某个类的实例（某类的变量），所以说**类是对象的抽象，对象是类的实例**

   <span style=color:red;background:yellow>**由对象抽象出类，由类实例化出对象**</span>

   C++中用关键字class来定义一个类，其基本形式如下：类的定义和声明

   ```cpp
   // 类名采用大驼峰命名
   class MyClass{//类的定义
       //……
       void myFunc(){}  //成员函数 采用小驼峰命名
       int m_a;          //数据成员
   };//一定要有分号
   
   
   //类也可以先声明，后完成定义
   class MyClass2;//类的声明
   
   class MyClass2{//类的定义
       //……
   };//分号不能省略
   ```

2. **访问修饰符**

   1. <span style=color:red;background:yellow>**public：**</span> 公有的访问权限，在类外可以通过对象直接访问公有成员

   2. <span style=color:red;background:yellow>**protected：**</span>保护的访问权限，在本类中和派生类中可以访问，在类外不能通过对象直接访问（后面学）

   3. <span style=color:red;background:yellow>**private：**</span>私有的访问权限，在本类之外不能访问，比较敏感的数据设为private，类定义中可以访问

      ![image-20241212155514035](..\0.TyporaPicture\image-20241212155514035.png)

      **注意：**

      - 类定义中访问修饰符的管理范围从当前行到下一个访问修饰符或类定义结束

      - class定义中如果在成员定义（或声明）之前没有任何访问修饰符，其<font color=red>**默认的访问权限为私有private**</font>

      - **public的成员函数**也可以称为**接口**，就是该类提供给外界使用的路径，在类外可以直接通过对象进行访问

        ```cpp
        class Computer {
        public:
        	void setBrand(const char * brand)
        	{
        		strcpy(m_brand, brand);
        	}
        	void setPrice(float price)
        	{
        		m_price = price;
        	}
        private:
        	char m_brand[20];
        	float m_price;
        }；
        
        int main(void){
            Computer pc;
            pc.setPrice(10000); //ok
            pc.m_price; //error,因为_price是私有的
        }
        
        ```

3. **struct 与 class的对比**

   - C中的struct只能是一些变量的集合体，可以封装数据但不能隐藏数据，而且成员不能是函数

   - C++中的struct对C中的struct做了拓展，可以定义函数，基本等同于class，默认访问权限是public

   - class默认访问权限是private

4. **成员函数的定义**

   1. **成员函数定义的三种形式**

      - 成员函数**定义在类内部**

        默认情况下是**内联函数**

        ```cpp
        class Computer {
        public:
        	void setBrand(const char * brand)
        	{
        		strcpy(m_brand, brand);
        	}
        	void setPrice(float price)
        	{
        		m_price = price;
        	}
        private:
        	char m_brand[20];
        	float m_price;
        }；
        ```

      - 成员函数在**类内部只进行声明**，在**类外部完成定义**

        类外定义的成员函数默认不是内联函数，除非使用 inline 来显式声明它为内联函数

        ```cpp
        class Computer {
        public:
        	//成员函数
        	void setBrand(const char * brand)；//设置品牌
        
        	void setPrice(float price)；//设置价格
                
            void print();//打印信息
        private:
        	//数据成员
        	char m_brand[20];
        	float m_price;
        };
        
        // 定义成员函数的时候结合作用域限定符一起使用 
        void Computer::setBrand(const char * brand)
        { 
            strcpy(m_brand, brand); 
        }
        void Computer::setPrice(float price)
        { 
            m_price = price;
        }
        ```

      - 成员函数在类中**声明使用头文件(.hpp)**，成员函数的**定义使用实现文件(.cc)**

        在头文件中定义一个函数时，如果多个源文件都包含了该头文件，那么在联合编译时会出现重定义错误

        ```cpp
        // 头文件 computer.h
        #ifndef __COMPUTER_H__
        #define __COMPUTER_H__
        class Computer{
        private:
            char m_brand[20];
            int m_price;
        public:
            // 在类中声明成员函数
            void setBrand(const char * brand);
            void setPrice(int price);
            void printInfo();
        };
        // -----------------
        
        // 实现文件computer.cc
        #include "computer.h"
        #include <iostream>
        #include <cstring>
        using std::cout;
        using std::endl;
        void Computer::setBrand(const char* brand){
            strcpy(m_brand, brand);
        }
        
        void Computer::setPrice(int price){
            m_price = price;
        }
        
        void Computer::printInfo(){
            cout << "computer info: brand: " << m_brand
                << ", price: " << m_price << endl;
        }
        // ---------------------------------
        
        // 测试文件 testComputer.cc
        #include "computer.h"
        #include <iostream>fs
        #include <cstring>
        
        int main(int argc, char *argv[])
        {
            Computer com;
            com.setBrand("Lenovo");
            com.setPrice(3999);
            com.printInfo();
            return 0;
        }
        ```

## 五、对象
