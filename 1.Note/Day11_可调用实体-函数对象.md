# Day11_函数对象

## 一、可调用实体

- 讲到调用这个词，我们首先能够想到**普通函数**和**函数指针**，在学习了类与对象的基础知识后，还增加了**成员函数**，那么它们都被称为<font color=red>**可调用实体**</font>。事实上，根据其他的一些不同的场景需求，**C++还提供了一些可调用实体，它们都是通过运算符重载来实现的**
- 普通函数执行时，有一个特点就是无记忆性。**一个普通函数执行完毕，它所在的函数栈空间就会被销毁，所以普通函数执行时的状态信息，是无法保存下来的**，这就让它**无法应用在那些需要对每次的执行状态信息进行维护的场景**。大家知道，我们学习了类与对象以后，**有了对象的存在，对象执行某些操作之后，只要对象没有销毁，其状态就是可以保留下来的**

## **二、函数对象**

1. **什么是函数对象**

   将重载了函数调用运算符（即以operator()**作为成员函数名**的）类创建的对象称为函数对象

   一个行为类似于函数的对象, 它的作用是在代码中能够像函数一样调用，但是它其实是一个类的实例

   ```cpp
   class FunctionObject {
       // ...
       // 重载函数调用运算符
       ReturnType operator()(ParameterList) {
           // do something....
       }
   };
   
   void test0() {
       FunctionObject fo{ };
       fo(); // 让对象像一个函数一样被调用
   }
   ```

2. **如何实现函数对象**
   上面的代码看起来很奇怪，如果我们从运算符的视角出发，就是函数调用运算符()要处理FunctionObject对象，只需要实现一个<font color=red>**函数调用运算符重载**</font>函数即可

   **函数调用运算符重载**，是一种允许对象像函数一样被调用的技术。它通过重载 `operator()` 运算符来实现，使得类的实例能够表现得像函数

   - 基本语法

     - **`ReturnType`**：函数调用返回的类型
     - **`ParameterList`**：可以是零个或多个参数，类似于普通函数
     - **函数调用运算符==必须以成员函数的形式进行重载==**

     ```cpp
     ReturnType operator()(ParameterList);
     ```

     ```cpp
     class FunctionObject {
         void operator()() {
             cout << "void operator()()" << endl;
         }
     };
     
     void test0() {
         FunctionObject fo;
         fo(); // ok
         // 本质如下
         fo.operator()();
     }
     ```

   - 形式

     <span style=color:red;background:yellow>**重载了函数调用运算符的类的对象称为函数对象**</span>，由于参数列表可以随意扩展 ，**所以可以有很多重载形式**（对应了普通函数的多种重载形式）

     ```cpp
     class FunctionObject {
     public:
         void operator()() {
             cout << "operator()" << endl;
         }
         int operator()(int x, int y) {
             cout << "operator(int, int)" << endl;
             return  x + y;
         }
         double operator()(double x, double y, double z) {
             cout << "operator(double, double, double)" << endl;
             return  x + y + z;
         }
     };
     
     void test1() {
         FunctionObject fo = FunctionObject{};
         // 函数调用运算符来处理fo对象的使用
         fo();
         cout << fo(1,2) << endl;
         cout << fo(1.1, 2, 3.3) << endl;
     }
     ```

3. **函数对象相比普通函数的优点**

   - **可以携带状态**（函数对象可以封装自己的数据成员、成员函数，具有更好的面向对象的特性）
   - **可以记录函数对象被调用的次数**，*而普通函数只能通过全局变量做到（全局变量不够安全）*
   - 除此之外，函数对象作为STL的六大组件之一而存在，可以做很多定制化的行为

   ```cpp
   class FunctionObject {
   public:
       void operator()() {
           cout << "FunctionObject operator()()" << endl;
           ++ m_count;
       }
       int operator()(int x, int y) {
           cout <<"operator()(int,int)" << endl;
           ++ m_count;
           return x + y;
       }
       int m_count = 0; // 携带状态
   };
   
   void test0(){
       FunctionObject fo;
     
       cout << fo() << endl;
       cout << fo.operator()() << endl; // 本质
   
       cout << fo(5,6) << endl;
       cout << fo.operator()(5,6) << endl; // 本质
   
       cout << "fo.m_count:" << fo.m_count << endl; // 记录这个函数对象被调用的次数
   }
   ```

   

