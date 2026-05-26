# Day25_STL标准模板库5-算法(函数)适配器

# 一、算法适配器

算法适配器也称为函数适配器

## 1.bind1st、bind2nd

函数绑定器

如下模板形式中，两个函数绑定器的第一个参数就是一个函数，第二个参数就是一个数字，如果F是一个二元函数(普通二元函数或者二元谓词)，我们可以绑定F的第一个参数(bind1st)或者第二个参数(bind2nd)，达到我们想要的效果(使用二元谓词的效果)

![image-20240812102558858](D:\Typora Picture\image-20240812102558858-1733126757209-110.png)

<img src="D:\Typora Picture\image-20250114172229681.png" alt="image-20250114172229681" style="zoom:80%;" />





那么我们可以写出这样的代码

``` c++
void test0()
{
    vector<int> vec = {1,3,5,9,6,4,6,5};
    for_each(vec.begin(),vec.end(),[](int & value){
                cout << value << " ";
             });
    cout << endl;

    auto it = remove_if(vec.begin(),vec.end(),
                        bind1st(std::less<int>(),5));  //这样相当于将std::less的operator()函数的第一个参数固定为5
    vec.erase(it,vec.end());

    for_each(vec.begin(),vec.end(),[](int & value){
                cout << value << " ";
             });
    cout << endl;
}
```

—— 那么这样做的结果是删除所有大于5的元素还是所有小于5的元素呢？



—— 还可以利用上bind2nd（固定第二个参数），以及std::greater（其底层的operator()函数逻辑不同），分别试试搭配使用的效果并分析





## ==2.bind==

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
>   - **bind**：**包装、改造已有的可调用对象**，不写新逻辑
>
> - **`std::bind` 只能绑定一个动作（一个可调用对象），不能同时绑定两个函数**
>
>   想执行多个函数，用 **lambda**，不要用 bind

### 2.1 基本使用

- 绑定函数

    如下，bind可以绑定N元函数，并用统一的方式进行使用

    <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250114181459086.png" alt="image-20250114181459086" style="zoom:67%;" />

    根据cpp参考文档的解释，**第一个参数可以是函数对象、函数指针、函数引用(比较少见)、指向成员函数指针或指向数据成员指针**。如上将函数名直接作为参数，相当于是传入函数指针。其他的几种情况也可以试试：

- 绑定函数对象

    <img src="D:\Typora Picture\image-20250115144417723.png" alt="image-20250115144417723" style="zoom:67%;" />



函数引用

<img src="D:\Typora Picture\image-20250115144332359.png" alt="image-20250115144332359" style="zoom:67%;" />



成员函数指针稍稍复杂

<img src="D:\Typora Picture\image-20250115144930383.png" alt="image-20250115144930383" style="zoom:67%;" />



指向数据成员的指针（当然这种写法比较奇特，仅作了解）

<img src="D:\Typora Picture\image-20250115145044752.png" alt="image-20250115145044752" style="zoom:67%;" />

用这种方式访问Example类的成员还有一个前提 —— 这些成员都是public权限的。





### 引用折叠

补充思考：

看回bind的声明形式，第一个参数看起来是一个右值引用，为什么在真正使用过程中，传入一些左值也可以呢？

这涉及到模板中的引用折叠

如下代码修改成模板后是可以正常运行的：

<img src="D:\Typora Picture\image-20250115152358590.png" alt="image-20250115152358590" style="zoom:67%;" />



在调用func时，如果传入的实参是左值，那么T会被推导成左值引用；如果实参是右值，那么T会被推导成右值引用

```C++
template <typename T>
int func(T &&a)
{
    return a;
}

int a = 10;
func(10);//T = int &&
func(a);// T = int &
```



模板中a为T&&类型，那么会造成多个引用符号写到一起。我们自己在写代码时不能将两个以上的引用符号写到一起，但是模板推导时会遵循一套引用折叠的机制

``` c++
//T &&有两种情况
& &&---->&
&& &&---->&&

//如果模板的函数参数为T&形式
//也有两种情况
& & ---->&
&& &----->&
```

根据上面的引用折叠规则可知，模板中写成T&&，实参既可以传左值，也可以传右值；如果模板中写成了T&，那么实参就只能传左值。



### 占位符

> 回到bind的基本使用，似乎每次都需要将被绑定的函数的所有参数都一起传入。
>
> 除此之外，还有一种占位符的写法。
>
> ![image-20250116152316060](D:\Typora Picture\image-20250116152316060.png)
>
> 
>
> 除了bind中指定的1，还使用占位符占据了一个函数参数位置，那么这个std::placeholders::_1占据的是add函数的参数x的位置，还是参数y的位置呢？
>
> <img src="D:\Typora Picture\image-20250330213225163.png" alt="image-20250330213225163" style="zoom:67%;" />
>
> <img src="D:\Typora Picture\image-20250330213443331.png" alt="image-20250330213443331" style="zoom:67%;" />
>
> 根据上面的结果可以发现，占位符占据的是bind所绑定的函数的参数列表中的哪个参数位置，取决于占位符在bind参数列表中出现的位置。





还可以进一步地：

<img src="D:\Typora Picture\image-20250116165041225.png" alt="image-20250116165041225" style="zoom:67%;" />



> 这里的使用实际上非常容易出错，看看更多参数的情况：
>
> <img src="D:\Typora Picture\image-20250116173910192.png" alt="image-20250116173910192" style="zoom:67%;" />
>
> 
>
> 这样写自然没有问题
>
> <img src="D:\Typora Picture\image-20250116170139188.png" alt="image-20250116170139188" style="zoom:67%;" />



<span style=color:red;background:yellow>**注意：**</span>

> <font color=red>**如果将占位符改换一下，却会出错**</font>
>
> <img src="D:\Typora Picture\image-20250116170903860.png" alt="image-20250116170903860" style="zoom:67%;" />
>
> **也就是说使用了_4这个占位符，那么在传入实参时至少要传入4个参数。（f调用时可以传很多个参数，多余的参数被舍弃）**
>
> 对于func函数，第一个参数是传入的10，第二个参数是占位符匹配到的20，第三个参数是占位符匹配到的400，第四个和第五个则是传入的number
>
> <span style=color:red;background:yellow>**可以理解为占位符整体代表的是形参的位置，占位符中的数字代表的是实参的位置。**</span>
>
> 



### 引用包装器

—— 再看一个有意思的事情

<img src="D:\Typora Picture\image-20250116172739413.png" alt="image-20250116172739413" style="zoom:67%;" />

**说明了bind的默认传递方式是值传递**，如果在bind中想要使用引用传递，需要用到<font color=red>**引用包装器**</font>。

>  <img src="D:\Typora Picture\image-20250116175032813.png" alt="image-20250116175032813" style="zoom:67%;" />



如上在bind传参时使用<font color=red>**引用包装器std::ref**</font> (reference)

如果func函数中原本形参形式为const引用，相应地可以使用<font color=red>**常引用包装器std::cref**</font> (const reference)

>  <img src="D:\Typora Picture\image-20250116175501510.png" alt="image-20250116175501510" style="zoom: 67%;" />

**引用包装器也属于函数适配器。**





### 函数指针

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

**不过，如果直接根据bind所绑定的函数的类型定义函数指针，是不能直接接收bind返回值的。**





## function

### function接收bind的返回值

对于函数而言，函数的类型包含了两个信息：函数返回类型 + 函数参数列表（包含了函数参数的类型、个数、顺序）

<img src="D:\Typora Picture\image-20250117100409588.png" alt="image-20250117100409588" style="zoom:67%;" />



很多时候，逻辑层面上很好理解，但是原生的语法却并不支持这种表达，STL则提供了一种方式可以支持这种表达。

<img src="D:\Typora Picture\image-20240812145418894-1733126757209-119.png" alt="image-20240812145418894" style="zoom:67%;" />

![image-20250117103618406](D:\Typora Picture\image-20250117103618406.png)



**体现了万物皆对象的思想**

<img src="D:\Typora Picture\image-20250117104001027.png" alt="image-20250117104001027" style="zoom:67%;" />



同理，逻辑类型应该为int(int)时，可以写成：

<img src="D:\Typora Picture\image-20250117104615584.png" alt="image-20250117104615584" style="zoom:67%;" />







### 绑定成员函数的传参

- **给成员函数绑定参数**

> 对于bind绑定成员函数的结果，也是一样的形式，非常简单
>
> <img src="D:\Typora Picture\image-20250117105554463.png" alt="image-20250117105554463" style="zoom:67%;" />
>
> **使用function接收bind绑定成员函数的返回值，function对象在初始化与使用时不需要顾及类的信息。**

> 如果结合占位符，其形式就更加多种多样了
>
> <img src="D:\Typora Picture\image-20250117114418119.png" alt="image-20250117114418119" style="zoom:67%;" />
>
> **当然，自己写代码的时候不建议写成这种带"炮灰"的形式，没有必要，还很容易混淆。**
>
> 
>
> 这里可以引申出一个思考——bind的返回值究竟是什么类型，为什么能够用不同类型的function对象来接这个返回值









- **绑定成员函数的第一个参数**

> 回到funcion接收bind返回值的例子，当bind函数绑定类的成员函数时，需要传入对象的地址以对应this指针这个参数，实际上还有一种写法
>
> ![image-20240812155206272](D:\Typora Picture\image-20240812155206272-1733126757209-121.png)
>
> bind绑定成员函数的时候，有两种传递的方式，**第一种：直接传递对象的地址，第二种，将对象拷贝进来。**
>
> —— 如果使用的是第一种，那么会传递的是地址值，那么就只会有一个指针大小的开销；但是如果是传递对象，就会拷贝对象，如果对象占据的空间比较大，那么开销也会比较大。
>
> 
>
> 那传递对象的写法有什么意义呢？
>
> —— 如果使用的是第一种，传递的是地址值，如果对象本身已经销毁了，那么有可能会有野指针的情况。
>
> 比如对象ex的创建是A线程，bind的绑定是B线程，在bind绑定时传对象的地址值，但A线程已经销毁了，就会出现这样的问题。
>
> 但是如果使用第二种形式，传递的是对象，那么就不会出现野指针的问题。
>
> <span style=color:red;background:yellow>**所以在多线程环境下，更建议传对象，而不是传地址。**</span>





### function表示lambda表达式返回值

在1.4.4这一节有一个遗留的问题，lambda表达式的返回值是什么？

我们也可以利用std::function进行相应的表示

![image-20240812151459260](D:\Typora Picture\image-20240812151459260-1733126757209-112.png)

总结：

<span style=color:red;background:yellow>**function称为函数包装器，其存储的是函数类型，所以也可以称为函数容器。**</span>



### function使用的误区

在使用std::function管理lambda表达式时还有一种使用的误区<font color=red>**（大坑）**</font>

![image-20240812152701250](D:\Typora Picture\image-20240812152701250-1733126757209-109.png)

<span style=color:red;background:yellow>**不要捕获局部变量的引用**</span>





### bind与function的结合使用（重要）

我们了解了std::bind和std::function各自的基本使用，再来看看它们的结合使用，这是一种**非常非常非常**强大的用法，因为bind具备改变函数形态的功能，只要函数的返回类型相同，任何参数类型的函数都可以被bind绑定之后，变成函数类型完全一致的函数对象，然后都可以被function进行接收。

来看一个std::function与std::bind结合使用体现出多态性的例子，也就是注册回调函数与执行回调函数。

在学习多态时，我们学过一段计算图形面积的例子

``` c++
#include <math.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Figure{
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

void display(Figure & fig){
    cout << fig.getName();
    cout << "的面积：";
    cout << fig.getArea() << endl;
}

class Rectangle
: public Figure
{
public:
    Rectangle(double len,double wid)
    : _length(len)
    , _width(wid)
    {}

    string getName() const override{
        return "矩形";
    }

    double getArea() const override{
        return _length * _width;
    }
private:
    double _length;
    double _width;
};
//...

void test0(){
    Rectangle rt(2,5);
    display(rt);
	//...
}

int main(void){
    test0();
    return 0;
}

```



![image-20240812180635362](D:\Typora Picture\image-20240812180635362-1733126757209-122.png)

![image-20240812180713368](D:\Typora Picture\image-20240812180713368-1733126757209-124.png)

![image-20240812180817369](D:\Typora Picture\image-20240812180817369-1733126757209-123.png)

—— 如上，思考一下为什么要使用移动语义呢？请回顾复制与移动的区别。





面向对象的写法：继承 + 纯虚函数(或者普通的虚函数)，具有一定的局限性：必须建立继承关系，派生类对基类的虚函数进行覆盖时必须要函数名和函数形式完全一致等；

<font color=red>**基于对象**</font>的写法：std::function + std::bind，这一套写法摒弃了上述的局限性，同样体现出多态性且更灵活。







## mem_fn成员函数适配器

因为成员函数与算法库中的算法不能直接很好的适配，所以二者结合使用的时候，需要使用成员函数适配器进行适配。

<img src="D:\Typora Picture\image-20250121151937130.png" alt="image-20250121151937130" style="zoom:67%;" />



使用成员函数适配器mem_fn进行简单的包装即可

![image-20250121150627602](D:\Typora Picture\image-20250121150627602.png)

> 完成遍历后可以顺带回顾一下remove_if的使用，多练习一下

<img src="D:\Typora Picture\image-20250331210156190.png" alt="image-20250331210156190" style="zoom:67%;" />



> <img src="D:\Typora Picture\image-20250121152520023.png" alt="image-20250121152520023" style="zoom:67%;" />
>
> <img src="D:\Typora Picture\image-20250121152629153.png" alt="image-20250121152629153" style="zoom:67%;" />







——思考：上述例子中使用for_each遍历vector时，使用了mem_fn为成员函数print做适配。根据以前学过的知识，还有没有什么方法实现同样效果呢？

for_each的第三个参数要求是一个一元函数，成员函数print看起来无参，实际上有隐含的this指针作为参数，它的确是一个一元函数。

<img src="D:\Typora Picture\image-20250121162733638.png" alt="image-20250121162733638" style="zoom:67%;" />







或者我们也可以用function接一下bind绑定成员函数的结果

![image-20250121164540811](D:\Typora Picture\image-20250121164540811.png)





# 二、适配器

适配器就是Interface(接口)，对容器、迭代器和算法进行包装，但其实质还是容器、迭代器和算法，只是不依赖于具体的标准容器、迭代器和算法类型，容器适配器可以理解为容器的模板，迭代器适配器可理解为迭代器的模板，算法适配器可理解为算法的模板。

# 三、函数对象

<span style=color:red;background:yellow>**函数对象也称为仿函数**</span>，严格意义上说函数对象仅仅指重载了函数调用运算符的类的对象。

<img src="D:\Typora Picture\image-20250331201115252.png" alt="image-20250331201115252" style="zoom: 67%;" />

<img src="D:\Typora Picture\image-20250331201151276.png" alt="image-20250331201151276" style="zoom:67%;" />



还有一个概念—— 只要可以与小括号进行结合展示出函数含义都可以称为<span style=color:red;background:yellow>**可调用对象**</span>。很多资料中模糊了函数对象和可调用对象的概念说明。上图出自C++之父的书——《C++程序设计语言-第4卷》



> 可调用对象包含了：
>
> - 函数对象
> - 函数指针、函数引用
> - 函数名
> - lambda表达式（可视为一个匿名的函数对象，可以直接在定义后调用，也可以给function函数对象赋值）



还有一个更大范围的概念 —— **可调用实体**，它在可调用对象的基础上还增加了成员函数、成员函数指针（这两者的共同特点是也可以调用，但不能仅凭自己完成调用）

