# Day25_STL标准模板库5-算法(函数)适配器

# 一、算法适配器

**算法**适配器也称为**函数**适配器

## 1.bind1st、bind2nd

- 本质是**函数绑定器**

  如下模板形式中，两个函数绑定器的第一个参数就是一个函数，第二个参数就是一个数字，如果F是一个二元函数(普通二元函数或者二元谓词)，我们可以绑定F的第一个参数(bind1st)或者第二个参数(bind2nd)，达到我们想要的效果(使用二元谓词的效果)

  ![image-20240812102558858](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812102558858-1733126757209-110.png)

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250114172229681.png" alt="image-20250114172229681" style="zoom:80%;" />

- **代码示例**

  ```cpp
  void test0()
  {
      vector<int> vec = {1,3,5,9,6,4,6,5};
      for_each(vec.begin(),vec.end(),[](int & value){
                  cout << value << " ";
               });
      cout << endl;
  
      auto it = remove_if(vec.begin(),vec.end(),
                          bind1st(std::less<int>(),5)); // 这样相当于将std::less的operator()函数的第一个参数固定为5
      vec.erase(it,vec.end());
  
      for_each(vec.begin(),vec.end(),[](int & value){
                  cout << value << " ";
               });
      cout << endl;
  }
  ```

  > 1. 这样做的结果是删除所有大于5的元素还是所有小于5的元素？
  >
  >    - bind1st` → 固定**第一个参数**为 `5
  >    - 调用：`less<int>()(5, 元素x)` → `5 < x`
  >    - 等价：**元素 x > 5** 时，谓词返回 `true`
  >    - 结论：**删除所有大于 5 的元素** ✅
  >
  > 2. 还可以利用上bind2nd（固定第二个参数）与 std::greater（其底层的operator()函数逻辑不同）
  >
  >    - 组合 1：`bind1st + less<int>`
  >
  >      ```cpp
  >      bind1st(less<int>(), 5) → less(5, x) → 5 < x → x > 5
  >      ```
  >
  >    - 组合 2：`bind2nd + less<int>`
  >
  >      ```cpp
  >      bind2nd(less<int>(), 5) → less(x, 5) → x < 5
  >      ```
  >
  >    - 组合 3：`bind1st + greater<int>`
  >
  >      ```cpp
  >      bind1st(greater<int>(), 5) → greater(5, x) → 5 > x → x < 5
  >      ```
  >
  >    - 组合 4：`bind2nd + greater<int>`
  >
  >      ```cpp
  >      bind2nd(greater<int>(), 5) → greater(x, 5) → x > 5
  >      ```

## ==2.bind==

> **引入**
>
> bind1st、bind2nd实际属于比较过时的方法，因为它们对其绑定的函数对象要求过于严格
>
> - 硬性要求 1：必须是「二元函数对象」
>
>   只接受 **有且仅有两个参数** 的函数 / 仿函数
>
>   ✅ 可以：`less<T>`, `greater<T>`, 自定义二元仿函数
>
>   ❌ 不行：普通函数、一元函数、三元函数、lambda、成员函数
>
> - 硬性要求 2：必须自带固定的类型别名
>
>   `bind1st`/`bind2nd` **不会自动推导类型**，强制要求函数对象内部定义 3 个类型：
>
>   ```cpp
>   // 必须定义这三个！少一个都报错
>   first_argument_type   // 第一个参数类型
>   second_argument_type  // 第二个参数类型
>   result_type           // 返回值类型
>   ```
>
> <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250425102949642.png" alt="image-20250425102949642" style="zoom:67%;" />

<span style=color:red;background:yellow>**现在有一个更通用的手段——bind**</span>

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812110817465-1733126757209-116.png" alt="image-20240812110817465" style="zoom:80%;" />

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250114180053729.png" alt="image-20250114180053729" style="zoom:67%;" />

> **注意**
>
> - **std::bind 的本质：是一个**函数适配器 **，底层是 **编译器生成的匿名仿函数对象**（标准可调用实体）**
>
>   它和 lambda 是**同类底层原理**（都是仿函数对象），但分工完全不同：
>
>   - **lambda**：自己写全新的执行逻辑
>   - **bind**：==**包装、改造已有的可调用对象**==，不写新逻辑
>
> - **`std::bind` 只能绑定一个动作（一个可调用对象），不能同时绑定两个函数**
>
>   想执行多个函数，用 **lambda**，不要用 bind

### 2.1 基本使用

- **绑定函数**

    如下，bind可以绑定N元函数，并用统一的方式进行使用

    <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250114181459086.png" alt="image-20250114181459086" style="zoom:67%;" />

    根据cpp参考文档的解释，**第一个参数可以是函数对象、函数指针、函数引用(比较少见)、指向成员函数指针或指向数据成员指针**。如上将函数名直接作为参数，相当于是传入函数指针。其他的几种情况也可以试试：

- **绑定函数对象**

    <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250115144417723.png" alt="image-20250115144417723" style="zoom:67%;" />

- **绑定==函数引用==**

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250115144332359.png" alt="image-20250115144332359" style="zoom:67%;" />

- **绑定*成员函数指针***

    > 只能绑定成员函数指针，而不能绑定成员函数本身
    >
    > 因为成员函数**只能通过 `&类名::函数` 获取指针**
    >
    > ```cpp
    > // 错误写法
    > auto f = std::bind(Test::show, &obj, std::placeholders::_1);
    > auto f = std::bind(obj.show, std::placeholders::_1);
    > // 唯一正确写法
    > // std::bind(&类名::成员函数, 对象指针/对象, 参数...);
    > // 传：成员函数指针 &Test::show + 对象 &obj
    > auto f = std::bind(&Test::show, &obj, std::placeholders::_1); // 传入一个地址
    > auto f = std::bind(&Test::show, obj, std::placeholders::_1); // 传入一个对象，对象拷贝
    > ```
    
    <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250115144930383.png" alt="image-20250115144930383" style="zoom:67%;" />
    
    **指向数据成员的指针**（这种写法比较奇特，仅作了解）
    
    <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250115145044752.png" alt="image-20250115145044752" style="zoom:67%;" />
    
    用**这种方式访问Example类的成员还有一个前提——这些成员都是public权限的**
    
    > **补充：bind绑定成员函数时参数列表中的第一个参数（参数列表即除去真正的第一个参数-调用实体之外的所有参数）**
    >
    > 当bind函数绑定类的成员函数(指针)时，需要传入对象的地址以对应this指针这个参数，除此之外还有另一种写法
    >
    > ![image-20240812155206272](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812155206272-1733126757209-121.png)
    >
    > 即bind绑定成员函数的时候，有两种传递的方式
    >
    > - **第一种：直接传递对象的地址**
    >
    >   传递的是地址值，那么就只会有一个指针大小的开销
    >
    > - **第二种：将对象拷贝进来**
    >
    >   传递对象，会拷贝对象，如果对象占据的空间比较大，那么开销也会比较大
    >
    > 如果使用的是第一种，传递的是地址值，**如果对象本身已经销毁了，那么有可能会有野指针的情况**，比如对象ex的创建是A线程，bind的绑定是B线程，在bind绑定时传对象的地址值，但A线程已经销毁了，就会出现这样的问题
    >
    > 但是如果使用第二种形式，**传递的是对象，那么就不会出现野指针的问题**
    >
    > <span style=color:red;background:yellow>**所以在多线程环境下，更建议传对象，而不是传地址**</span>

### 2.2 引用折叠

bind的声明形式，第一个参数看起来是一个右值引用，为什么在真正使用过程中，传入一些左值也可以呢？这涉及到模板中的**引用折叠**

1. 如下代码修改成模板后是可以正常运行的：

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250115152358590.png" alt="image-20250115152358590" style="zoom:67%;" />

2. 在调用func时，如果传入的实参是左值，那么T会被推导成左值引用；如果实参是右值，那么T会被推导成右值引用

   ```cpp
   template <typename T>
   int func(T&& a) {
       return a;
   }
   
   int a = 10;
   func(10); // T = int &&
   func(a); // T = int &
   ```

3. 模板中a为T&&类型，那么会造成多个引用符号写到一起。我们自己在写代码时不能将两个以上的引用符号写到一起，因为**模板推导时会遵循一套==引用折叠==的机制**

   ```cpp
   // T&&有两种情况
   & &&---->&
   && &&---->&&
   // 如果模板的函数参数为T&形式，也有两种情况
   & & ---->&
   && &----->&
   ```

   根据上面的引用折叠规则可知：

   - **模板中为T&&**，==实参既可以传**左值**，也可以传**右值**==
   - **模板中为T&**，==实参就只能传**左值**==

### 2.3 占位符

1. 回到bind的基本使用，似乎每次都需要将被绑定的函数的所有参数都一起传入，但除此之外，还有一种**占位符的写法：**

   ![image-20250116152316060](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116152316060.png)

2. 除了bind中指定的1，还使用占位符占据了一个函数参数位置，那么这个std::placeholders::_1占据的是add函数的参数x的位置，还是参数y的位置呢？

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250330213225163.png" alt="image-20250330213225163" style="zoom:67%;" />

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250330213443331.png" alt="image-20250330213443331" style="zoom:67%;" />

   根据上面的结果可以发现，占位符占据的是bind所绑定的函数的参数列表中的哪个参数位置，**取决于==单个占位符在bind参数列表中出现的位置（而其取值则取决于调用时的实参列表）==**

3. 进一步地：

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116165041225.png" alt="image-20250116165041225" style="zoom:67%;" />

4. 更多参数的情况：

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116173910192.png" alt="image-20250116173910192" style="zoom:67%;" />

   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116170139188.png" alt="image-20250116170139188" style="zoom:67%;" />

> <span style=color:red;background:yellow>**注意**</span>
>
> <font color=red>**如果将占位符改换一下，就会出错**</font>
>
> <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116170903860.png" alt="image-20250116170903860" style="zoom:67%;" />
>
> - **首先，使用了_4这个占位符，那么在传入实参时==至少要传入4个参数==（f调用时可以传很多个参数，多余的参数被舍弃）**
>
> - 对于func函数，第一个参数是传入的10，第二个参数是占位符匹配到的20，第三个参数是占位符匹配到的400，第四个和第五个则是传入的number
>
>
> <span style=color:red;background:yellow>**可以理解为：占位符整体代表的是形参的位置，占位符中的数字代表的是实参的位置**</span>

### 2.4 引用包装器

> **引入**
>
> <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116172739413.png" alt="image-20250116172739413" style="zoom:67%;" />
>
> 上图**说明了bind的默认传递方式是值传递**，如果在bind中想要使用引用传递，需要用到<font color=red>**引用包装器**</font>
>
> ==**引用包装器也属于函数(算法)适配器**==

- bind传参时使用<font color=red>**引用包装器std::ref**</font> (reference)

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116175032813.png" alt="image-20250116175032813" style="zoom:67%;" />

- 如果func函数中原本形参形式为const引用，相应地可以使用<font color=red>**常引用包装器std::cref**</font> (const reference)

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250116175501510.png" alt="image-20250116175501510" style="zoom: 67%;" />

### 2.5 函数指针不能接收bind返回值

上面的例子中我们每次都使用了auto f的形式接收了bind函数的返回值，那么auto究竟推导出什么类型？

看到某一个变量后加上括号，起到调用函数的作用，应该会联想到以前学习过的函数指针，先类比着进行理解。

假设有相同类型的函数

``` c++
int func()
{
    return 10;
}

int func2()
{
    return 20;
}
```



func和func2的返回类型与参数情况一致，可以使用同种函数指针进行调用。为了方便使用，可以给这种函数指针类型起别名。	

函数指针被初始化为函数的地址(函数指针指向函数)相当于是函数的注册；

使用函数指针调用函数时才会执行函数。

这就对应了一种延迟调用的思想（先注册，后执行），可以用来作回调函数。与之理念相似的还有C++的多态思想：基类指针调用虚函数时，只有到运行时（根据基类指针究竟指向的是哪个派生类对象）才能确定具体执行哪个虚函数。

![image-20240812113718833](D:\Typora Picture\image-20240812113718833-1733126757209-115.png)

``` c++
int func(){}

//逻辑层面
int()//函数类型
int(*)()//函数指针类型
typedef int(*Function)()  
    
using Function = int(*)()
    
int (*p)() = &func;
Function f = &func;

function<int()> f;

```

**不过，如果直接根据bind所绑定的函数的类型定义函数指针，是不能直接接收bind返回值的，==而使用function则可以接收==**

## 3.function

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812145418894-1733126757209-119.png" alt="image-20240812145418894" style="zoom:67%;" />

![image-20250117103618406](D:\Typora Picture\image-20250117103618406-177978327708439.png)

- **`std::function` 不是函数，它是 C++ STL 提供的：一个**通用、多态、类型安全的**可调用对象==包装器==** **（基于**==类型擦除==**实现的类模板）**

  简单说：它是一个**容器**，专门用来**装各种可调用的东西**（普通函数、lambda、仿函数、成员函数等），只要它们的**调用签名（返回值 + 参数）一致**，就能装进同一个 `std::function` 里

- **体现了万物皆对象的思想**

- <span style=color:red;background:yellow>**function称为函数包装器，其存储的是函数类型，所以也可以称为函数容器**</span>

### 3.1 function存普通函数

**模板参数由函数签名决定**——签名 = **返回值类型 + 参数类型 (个数)**

```cpp
#include <iostream>
#include <functional>  // 必须包含
using namespace std;

// ====================== 1. 定义普通函数 ======================
// 函数1：加法函数
// 【函数签名】：int (int, int)
// （返回值int，参数是两个int）
int add(int a, int b) {
    return a + b;
}
// 函数2：打印函数
// 【函数签名】：void (int)
// （返回值void，参数是一个int）
void printNum(int num) {
    cout << "数字：" << num << endl;
}
// ====================== 2. 使用 function 存储 ======================
int main() {
    // --------------------------
    // 存储 签名为 int(int, int) 的函数
    // function 模板参数 = 函数签名
    // --------------------------
    function<int(int, int)> func1;  // 模板参数严格匹配签名
    func1 = add;                    // 存入普通函数
    cout << func1(10, 20) << endl;  // 调用：输出30
    
    // --------------------------
    // 存储 签名为 void(int) 的函数
    // function 模板参数 = 函数签名
    // --------------------------
    function<void(int)> func2;      // 模板参数严格匹配签名
    func2 = printNum;              	// 存入普通函数
    func2(666);                    	// 调用：输出 数字：666

    return 0;
}
```

### 3.2 function接收bind的返回值

对于函数而言，函数的类型包含了两个信息：**函数返回类型 + 函数参数列表(包含了函数参数的类型、个数、顺序)**

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250117100409588.png" alt="image-20250117100409588" style="zoom:67%;" />

很多时候，逻辑层面上很好理解，但是原生的语法却并不支持这种表达，STL则提供了一种方式可以支持这种表达——即`std::function`

- **bind绑定普通函数**

  ==**function的模板参数具体由打包之后的函数的调用签名决定**==

  > 1. **函数的调用签名（Signature）**：**返回值类型 + 参数的类型 / 个数**（比如 `int(int, int)`）
  > 2. **函数的逻辑（Logic）**：函数内部具体做什么（加法、乘法、打印、哈希计算、业务判断……）

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250117104001027.png" alt="image-20250117104001027" style="zoom:67%;" />

  同理，**==打包之后==的逻辑类型应该为int(int)时**，可以写成：

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250117104615584.png" alt="image-20250117104615584" style="zoom:67%;" />

- **bind绑定成员函数指针**

  对于bind绑定成员函数的结果，也是一样的形式，非常简单

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250117105554463.png" alt="image-20250117105554463" style="zoom:67%;" />

  **使用function接收bind绑定成员函数的返回值，function对象在初始化与使用时不需要顾及类的信息**

- **bind中使用结合占位符**

  <img src="D:\Typora Picture\image-20250117114418119.png" alt="image-20250117114418119" style="zoom:67%;" />

  **写代码的时候不建议写成这种带"炮灰"的形式，没有必要，还很容易混淆**

> **补充：bind的返回值究竟是什么类型，为什么能够用不同类型的function对象来接这个返回值**
>
> 1. **`std::bind` 的返回值类型**：
>
>    是**编译器自动生成的、没有名字的匿名仿函数类型（闭包类型）**，这个类型我们**无法手动书写**，所以只能用 `auto` 接收
>
> 2. **为什么能用 `std::function` 接收？**
>
>    因为 **`std::function` 根本不关心绑定对象的原始类型！它只认「调用签名」**
>
>    只要 `bind` 返回的匿名对象，**调用签名**和 `function` 的模板参数匹配，就能被包装

### 3.3 function表示lambda表达式返回值

lambda表达式的返回值，也可以利用std::function进行相应的表示

![image-20240812151459260](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812151459260-1733126757209-112.png)

### 3.4 function使用的误区

<span style=color:red;background:yellow>**在使用std::function表示lambda表达式时，不要捕获局部变量的引用**</span>

![image-20240812152701250](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240812152701250-1733126757209-109.png)

### ==3.5 bind与function的结合使用==

我们了解了std::bind和std::function各自的基本使用，再来看看它们的结合使用，这是一种**非常**强大的用法，因为**bind具备改变函数形态的功能，只要函数的返回类型相同，任何参数类型的函数都可以被bind绑定之后，变成函数类型完全一致的函数对象，然后都可以被function进行接收**

- std::function与std::bind结合使用体现出多态性的例子——也就是注册回调函数与执行回调函数

  ```cpp
  #include <iostream>
  #include <functional>  // 必须包含，用于 std::function 和 std::bind
  
  using std::cout;
  using std::endl;
  using std::function;
  using std::bind;
  
  // 核心类：通过回调函数实现多态行为（替代传统继承+虚函数）
  class Figure {
  public:
      // 定义回调函数类型（与图中一致）
      using DisplayCallback = function<void()>;       // 显示回调：无参数、无返回值
      using AreaCallback = function<double()>;        // 面积回调：无参数、返回double
  
      // 注册回调函数（图中的“回调注册”）
      void setDisplayCallback(DisplayCallback&& cb) {
          _displayCallback = std::move(cb);  // 移动语义避免拷贝
      }
      void setAreaCallback(AreaCallback&& cb) {
          _areaCallback = std::move(cb);
      }
  
      // 执行回调函数（图中的“回调执行”）
      void handleDisplay() const {
          if (_displayCallback) {  // 确保回调已注册才执行
              _displayCallback();
          }
      }
      double handleArea() const {
          if (_areaCallback) {
              return _areaCallback();
          }
          return 0.0;  // 未注册时返回默认值
      }
  
  private:
      DisplayCallback _displayCallback;  // 存储显示回调
      AreaCallback _areaCallback;         // 存储面积回调
  };
  
  // 矩形类（无需继承Figure）
  class Rectangle {
  public:
      Rectangle(double len, double wid)
          : _length(len), _width(wid) {}
  
      // 成员函数：作为回调的“具体实现”
      void display() const {
          cout << "矩形";
      }
      double area() const {
          return _length * _width;
      }
  
  private:
      double _length;
      double _width;
  };
  
  // 圆形类（新增一个类，体现多态的“不同行为”）
  class Circle {
  public:
      Circle(double r) : _radius(r) {}
  
      // 成员函数：与Rectangle同名，但实现不同
      void display() const {
          cout << "圆形";
      }
      double area() const {
          return 3.14159 * _radius * _radius;
      }
  
  private:
      double _radius;
  };
  
  // 统一接口函数（相当于传统多态中接收基类引用的display函数）
  void printFigure(const Figure& fig) {
      fig.handleDisplay();
      cout << "的面积：" << fig.handleArea() << endl;
  }
  
  void test() {
      // 1. 矩形对象：注册Rectangle的成员函数作为回调
      Rectangle rect(2, 5);  // 长2，宽5
      Figure fig1;
      // std::bind 将成员函数+对象绑定为可调用对象，适配std::function
      fig1.setDisplayCallback(bind(&Rectangle::display, &rect));
      fig1.setAreaCallback(bind(&Rectangle::area, &rect));
      printFigure(fig1);  // 输出：矩形的面积：10
  
      // 2. 圆形对象：注册Circle的成员函数作为回调
      Circle circle(3);  // 半径3
      Figure fig2;
      fig2.setDisplayCallback(bind(&Circle::display, &circle));
      fig2.setAreaCallback(bind(&Circle::area, &circle));
      printFigure(fig2);  // 输出：圆形的面积：28.27431
  }
  
  int main() {
      test();
      return 0;
  }
  
  // 结果
  // 矩形的面积：10
  // 圆形的面积：28.2743
  ```

  > 1. **为什么要使用移动语义**
  >
  >    在之前的回调多态代码中，使用`std::move`的核心目的是**避免不必要的深拷贝、提升性能**，尤其对`std::function`这类管理资源的对象效果显著。下面从原理到实战，完整解释移动语义的价值与应用逻辑
  >
  > 2. **拷贝语义 vs 移动语义的本质区别**
  >
  >    | 特性             | 拷贝语义                             | 移动语义                               |
  >    | ---------------- | ------------------------------------ | -------------------------------------- |
  >    | **资源操作**     | 深拷贝（复制全部数据，重新分配内存） | 所有权转移（仅修改指针，不复制数据）   |
  >    | **性能开销**     | 高（O (n) 时间复杂度，涉及内存分配） | 极低（O (1) 时间复杂度，仅指针操作）   |
  >    | **原对象状态**   | 保持不变，可继续正常使用             | 进入 “有效但未定义” 状态（通常被置空） |
  >    | **典型触发方式** | 左值赋值（如`a = b`）                | 右值引用（如`a = std::move(b)`）       |

- 面向对象的写法：继承 + 纯虚函数(或者普通的虚函数)，具有一定的局限性：必须建立继承关系，派生类对基类的虚函数进行覆盖时必须要函数名和函数形式完全一致等

  <font color=red>**基于对象(即面向函数)**</font>的写法：std::function + std::bind，这一套写法摒弃了上述的局限性，同样体现出多态性且更灵活

> **补充：两种多态的区别**
>
> 1. **总结**
>
>    - **虚函数 + 继承（传统多态）**
>
>      - **不用手动切换逻辑**
>
>      - 基类指针 / 引用**指向不同子类对象**，**直接调用**就自动执行对应逻辑，**全程自动、隐式切换**。
>
>    - **std::function + std::bind（函数多态）**
>
>      - **想切换逻辑，必须手动重新赋值 / 注册**
>
>      - 它不会自动变，你不手动给 `function` 绑定新的闭包，它永远执行老逻辑
>
> 2. **对比**
>
>    - 虚函数多态：自动切换（指向谁，就用谁）
>
>      ```cpp
>      // 基类
>      class Base {
>      public:
>          virtual void do() = 0; // 虚函数
>      };
>      // 子类1
>      class A : public Base { void do() { cout << "A逻辑"; } };
>      // 子类2
>      class B : public Base { void do() { cout << "B逻辑"; } };
>      
>      // 使用
>      Base* ptr;
>      ptr = new A(); 
>      ptr->do(); // 自动执行A ✅ 不用手动改
>      
>      ptr = new B(); // 只改指向的对象
>      ptr->do(); // 自动执行B ✅ 自动切换
>      ```
>
>      **核心**：改的是**对象**，调用方式完全不变，**多态自动生效**
>
>    - function+bind 多态：手动切换（不赋值，永远不变）
>
>      ```cpp
>      // 两个独立逻辑（无继承）
>      void logicA() { cout << "A逻辑"; }
>      void logicB() { cout << "B逻辑"; }
>      
>      // 使用
>      function<void()> func;
>      
>      // 第一次注册
>      func = bind(logicA);
>      func(); // 执行A
>      
>      // 想切换成B？必须手动重新赋值！
>      func = bind(logicB); // 手动切换
>      func(); // 执行B
>      ```
>
>      **核心**：不改赋值，永远执行老逻辑；**切换逻辑 = 手动重新给 function 赋值**。
>
> 3. **差异**
>
>    - **虚函数多态**：**对象决定行为**，切换对象 → 行为自动变
>
>    - **function+bind 多态**：**赋值决定行为**，不手动重新赋值 → 行为永远不变
>
> 4. **补充**
>
>    这不是缺陷，是设计定位不同
>
>    - 虚函数：**面向对象多态**，用于一类有继承关系的对象行为
>
>    - `function+bind`：**函数式多态**，用于任意独立函数 / 回调的灵活替换

## 4.成员函数指针(包装)适配器mem_fn

因为成员函数与算法库中的算法不能直接很好的适配，所以二者结合使用的时候，需要使用成员函数适配器进行适配

![image-20250121150627602](D:\Typora Picture\image-20250121150627602-177978568827644.png)

- **示例**

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250121151937130.png" alt="image-20250121151937130" style="zoom:67%;" />

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250331210156190.png" alt="image-20250331210156190" style="zoom:67%;" />

  **使用成员函数适配器mem_fn对成员函数指针进行简单的包装**即可：

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250121152520023.png" alt="image-20250121152520023" style="zoom:67%;" />

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250121152629153.png" alt="image-20250121152629153" style="zoom:67%;" />

- 上述例子中使用for_each遍历vector时，使用了mem_fn为成员函数print做适配。根据以前学过的知识，还有没有什么方法实现同样效果呢？

  **for_each的第三个参数要求是一个一元函数**，成员函数print看起来无参，实际上有隐含的this指针作为参数，它的确是一个一元函数

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250121162733638.png" alt="image-20250121162733638" style="zoom:67%;" />

  或者我们也可以用**function接收bind绑定成员函数的结果**

  ![image-20250121164540811](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250121164540811.png)

# 二、适配器

适配器就是Interface(接口)，对容器、迭代器和算法进行包装，但其实质还是容器、迭代器和算法，只是不依赖于具体的标准容器、迭代器和算法类型，容器适配器可以理解为容器的模板，迭代器适配器可理解为迭代器的模板，算法适配器可理解为算法的模板

# 三、函数对象

<span style=color:red;background:yellow>**函数对象也称为仿函数**</span>，严格意义上说函数对象仅仅指重载了函数调用运算符的类的对象。

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250331201115252.png" alt="image-20250331201115252" style="zoom: 67%;" />

<img src="D:\Typora Picture\image-20250331201151276.png" alt="image-20250331201151276" style="zoom:67%;" />

还有一个概念—— 只要可以与小括号进行结合展示出函数含义都可以称为<span style=color:red;background:yellow>**可调用对象**</span>。很多资料中模糊了函数对象和可调用对象的概念说明。上图出自C++之父的书——《C++程序设计语言-第4卷》

> 可调用对象包含了：
>
> - 函数对象
> - 函数指针、函数引用
> - 函数名
> - lambda表达式（可视为一个匿名的函数对象，可以直接在定义后调用，也可以给function函数对象赋值）

还有一个更大范围的概念 —— **可调用实体**，它在可调用对象的基础上还增加了成员函数、成员函数指针（这两者的共同特点是也可以调用，但不能仅凭自己完成调用）

