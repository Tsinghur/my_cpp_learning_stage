# Day24_STL标准模板库4-算法

## 一、算法

### 1.特点

STL的算法库中的函数，都是属于普通函数（并不是哪一个类的成员函数）

### 2.分类

- 非修改式的序列算法：**for_each**、count、find
- 修改式的序列算法：**`copy`**、`remove`、**`remove_if`**、`replace`、`fill`
- 排序函数：**`sort`**
- 二分搜索的算法：`lower_bound`、`upper_bound`、`equal_range`
- 集合操作：**`set_intersection`**（取交集）
- 堆相关的函数：`make_heap`、`push_heap`
- 取最值：`max`、`min`
- 数值操作：`iota`
- 未初始化的内存操作：**`uninitialized_copy`**

### 3.`for_each`——非修改式的序列算法

首先查看cpp参考文档的描述

<img src="..\0.TyporaPicture\image-20250110103033784.png" alt="image-20250110103033784" style="zoom:67%;" />

- 第三个参数需要传一个一元函数（或者仿函数），其函数形参只有一个（不一定要有const或者&）

  > 一元函数：函数的参数只有一个
  >
  > 二元函数：函数的参数只有两个

- 示例

  <img src="..\0.TyporaPicture\image-20250110104510905.png" alt="image-20250110104510905" style="zoom:67%;" />

  想要通过for_each改变vector中元素的内容，就得在func函数上做文章，可以给func函数形参改成引用

  <font color=red>**实际使用时，func函数是否改变容器元素，for_each是没有限制的**</font>

- 参考for_each的源码

  ```cpp
  template<class InputIt, class UnaryFunction>
  constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
      for (; first != last; ++first) {
          f(*first);
      }
      return f; 
  }
  ```

### 4.lambda表达式(重要)

以for_each的使用为例，有时**为了使用一些简单的函数**，会经常使用到lambda表达式

<img src="..\0.TyporaPicture\image-20250110141631261.png" alt="image-20250110141631261" style="zoom:67%;" />

#### 4.1 语法结构

**lambda表达式**也称为**匿名函数**，其基本语法结构如下：

``` c++
[capture](params) opt -> retureType {
	body;
}
```

- 其中capture是捕获列表，params是参数列表，opt是函数选项，retureType是返回值类型，body是函数体


> 如下的lambda表达式中：
>
> []——**捕获列表**：捕获**lambda表达式函数体外**的**==局部==变量**
>
> ()——函数的**参数列表**
>
> {}——函数的**函数体**
>
> <img src="..\0.TyporaPicture\image-20250110151601816.png" alt="image-20250110151601816" style="zoom:67%;" />
>
> 如果没有在[]中捕获a、b，那么在匿名函数的函数体中无法访问它们
>
> 进一步的，还可以给匿名函数增加函数参数，以及指定函数返回类型
>
> <img src="..\0.TyporaPicture\image-20250110154439061.png" alt="image-20250110154439061" style="zoom:67%;" />
>
> <span style=color:red;background:yellow>**注意：**</span>捕获列表捕获的是局部变量，全局变量不需要捕获
>
> <img src="..\0.TyporaPicture\image-20250110154541870.png" alt="image-20250110154541870" style="zoom:67%;" />

#### 4.2 引用捕获与值捕获的区别

如果**想要通过捕获列表(形参)改变局部变量(实参)的值**

<img src="..\0.TyporaPicture\image-20250110163859032.png" alt="image-20250110163859032" style="zoom:67%;" />



函数选项的位置**加上mutable关键字才能对==局部变量==a/b(lambda表达式中的形参)进行修改操作，但这样做也并不能修改a和b实际的值(传给lambda表达式的实参)（==即加上mutable仅为前提==）**

<img src="..\0.TyporaPicture\image-20250110164140708.png" alt="image-20250110164140708" style="zoom:67%;" />

看到上述的结果，应该能联想到常规函数的值传递场景，**==想要真正通过形参改变实参==，形参需要写成==引用形式==（==此为核心==）**

那么对于匿名函数而言，如果想要在匿名函数中修改捕获的变量其本身的值，那么应该采用的是<font color=red>**引用捕获**</font>

<img src="..\0.TyporaPicture\image-20250110164446682.png" alt="image-20250110164446682" style="zoom:67%;" />

**另外，对于==全局变量和函数参数(形参)==，匿名函数中可以直接完成修改**

> **==如果需要捕获的内容太多==**，有一些比较方便的写法：
>
> - 如果想将外部局部变量全部捕获，可以在捕获列表中使用 **[=]**，表示全部是值捕获；或者使用 **[&]**，表示全部是引用捕获
>
> - 如果某一个变量是值捕获，其他的全部是引用捕获，可以 **[&, num]**
>
> - 如果某一个变量是引用捕获，其他的全部是值捕获，可以 **[=, &num]**
>
> - 最简单的方式是，将每个变量的捕获形式单独写出来，理解起来更简单

#### 4.3 lambda表达式可以被接收

现在考虑到一个问题，在前面的例子中，匿名函数每次都是当场定义**当场调用**(**表达式函数体结尾的`}`之后加上(实参)**)的，那么匿名函数是否可以像普通的函数一样去复用呢？

![image-20240810112342157](..\0.TyporaPicture\image-20240810112342157-1733126757209-108.png)

> **经典写法与错误：**
>
> ```cpp
> class Example {
> public:
> 	void print(int x, int y) {
> 		auto x1 = [] { return _number; }; // error: 通过this才能访问_number
> 		auto x2 = [this] { return _number; };
> 		auto x3 = [this] { return _number + x + y; }; // error: 未捕获x与y
> 		auto x4 = [this, x, y] { return _number + x + y; }; 
> 		auto x5 = [this] { return _number++; }; // 并没有修改this，只是通过this修改其指向的对象的内容
> 		auto x6 = [=] { return _number + x + y; }; // 全部局部变量包括this
> 		auto x7 = [&] { return _number + x + y; }; 
> 	}
> 	int _number = 100;
> };
> ```
>
> ```cpp
> void test() {
>  int a = 10, b = 20;
>  auto f1 = [] { return a; }; // error: 未捕获a
>  auto f2 = [&] { return a++; };
>  auto f3 = [=] { return a; }; 
>  auto f4 = [=] { return a++; }; // error: 值捕获不能进行写操作，a++是写操作
>  auto f5 = [a] { return a + b; }; // error: 未捕获b
>  auto f6 = [a, &b] { return a + (b++); }; 
>  auto f7 = [=, &b] { return a + (b++); }; 
> }
> ```
>
> <span style=color:red;background:yellow>**总结：**</span>
>
> 对于lambda表达式，大家可能会在实际代码中见到非常多种形式，需要读懂它的意思
>
> 1. lambda表达式的参数列表与普通函数的参数列表一样，如果没有参数，则参数列表可以省略不写，而这个具体的省略形式为：
>
>    - **普通函数**：无参数 ➜ **必须写 `( )`**
>
>    - **Lambda**：无参数 ➜ **可以不写 `( )`**
>
> 2. 即使没有需要捕获的内容，也需要写上 **[ ]**
>
> 3. 选项如非必需，可以省略
>
>    - mutable：可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）
>
>
>    - noexcept：`noexcept` 是一种契约，向编译器和调用者保证函数不会抛出异常。如果违反了这个契约，程序的行为将是未定义的，通常会导致程序终止
>
> 4. 返回类型可以省略。通过返回值后置语法来定义的。一般情况下，不指定lambda表达式的返回值，编译器会根据return语句自动推导返回值的类型，但需要注意的是labmda表达式不能通过列表初始化自动推导出返回值类型
>
>    ```cpp
>    // ok，可以自动推导出返回值类型
>    auto f = [](int i) {
>    	return i;
>    };
>    
>    // error,不能推导出返回值类型
>    auto f1 = []() {
>    	return {1, 2}; // 基于列表初始化推导返回值，错误
>    };
>    ```
>
> 5. 函数体不能省略，但可以为空
>
>    ```cpp
>    auto f = []{}; 
>    []{}(); // 极致省略的匿名函数立即调用
>    ```
>
> 6. lambda 表达式赋值给变量时，`}` 后面必须写 `;`
>    因为**lambda 是一个「表达式」**，不是函数定义，也不是代码块

#### 4.4 lambda表达式的类型

至此仍然存在一个问题：auto推导出来的类型究竟是什么呢？

- lambda表达式的类型与匿名函数的returnType并非是同一件事

  ==**auto 推导出的不是函数指针，也不是 std::function，而是一个编译器自动生成的、独一无二的「闭包类型（closure type）」**，你写不出它的名字，只能用 auto 或模板参数接住它==

- lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。mutable选项的作用就在于取消operator()的const属性


- 因为lambda表达式在C++中会被看做是一个仿函数，因此可以使用std::function和std::bind来存储和操作lambda表达式（算法适配器的使用）

**进一步解释见std::function部分**

> 这里附上一个网站：https://cppinsights.io/，可以通过它查看编译器是如何处理代码的

### 5.`remove_if`——修改式的序列算法

#### 5.1 基本使用

依旧从cpp参考文档出发

![image-20250110170422501](..\0.TyporaPicture\image-20250110170422501.png)

- 第三个参数p是一个一元谓词


> **一元函数**：函数的参数只有一个
> **二元函数**：函数的参数只有两个
>
> **一元断言/谓词**：函数的参数只有一个，并且返回类型是bool
> **二元断言/谓词**：函数的参数只有两个，并且返回类型是bool

- 示例：想要移除vector中大于5的元素


<font color=red>**但是发现没有得到想要的结果**</font>，那么此时可以从源码出发来进行探索

<img src="..\0.TyporaPicture\image-20250110170124860.png" alt="image-20250110170124860" style="zoom:67%;" />

#### 5.2 源码

- `remove_if`

  ```C++
  // first = vec.begin()
  // last = vec.end()
  // p = func
  template<class ForwardIt, class UnaryPredicate>
  ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
      first = std::find_if(first, last, p); // 找到第一个应该删除的开始向后遍历
      if (first != last)
          for(ForwardIt i = first; ++i != last; )
              if (!p(*i))
                  *first++ = std::move(*i); // 把不满足条件即不应该删除保留下来，且first就作为局部新容器的尾后迭代器
      return first;
  }
  // std::remove_if 最后返回的 first，是容器中「保留下来的有效元素」的尾后迭代器
  ```

- 跳转到`find_if`函数查看

  ``` c++
  // first = vec.begin()
  // last = vec.end()
  // p = func
  template<class InputIt, class UnaryPredicate>
  constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
  {
      for (; first != last; ++first) {
          if (p(*first)) {
              return first;
          }
      }
      return last;
  }
  
  //分析一下过程，其实就是找到第一个大于5的元素，返回相应迭代器
                         last
  1, 3, 5, 9, 6, 4, 6, 5
           f
  ```

- 接着往下看

  ``` c++
  // 使用的代码
  remove_if(vec.begin(), vec.end(), func);
  // first = vec.begin()
  // last =  vec.end()
  // p = func
  ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
  {
      first = std::find_if(first, last, p);
      if (first != last){
          for(ForwardIt i = first; ++i != last; )
          {
              if (!p(*i))
              {
                  *first++ = std::move(*i);
              }
          }
      }
      return first;
  }
  
           f             last
  1, 3, 5, 9, 6, 4, 6, 5
                 i
  
              f          last
  1, 3, 5, 4, 6, 4, 6, 5
                    i
  
              f          last
  1, 3, 5, 4, 6, 4, 6, 5
                       i
  
                 f       last
  1, 3, 5, 4, 5, 4, 6, 5
                       i 
  //最终返回4这个元素对应的迭代器       
  ```

再次观察结果，可以发现期待的最终结果是{1,3,5,4,5}，而这个理想结果实际上已经是vector的前五个元素了

而且<font color=red>**remove_if函数的返回值就是待删除的元素的首迭代器**</font>

也就是说，remove只负责移动，最终的删除还需要调用erase

<img src="..\0.TyporaPicture\image-20250113112112414.png" alt="image-20250113112112414" style="zoom:67%;" />

> 思维拓展：
>
> remove_if实际上最终的效果是同时做了两件事，更改了容器中特定位置的元素，并且返回了待删除元素的首迭代器
>
> 而在我们以往的认知中，同时干两件事总是比较容易出问题。比如多线程环境下，一个线程对某个数据进行写操作，一个线程对它进行读操作，如果不加锁的话，没法确定执行的先后，可能会出现预期之外的值。可以通过下面的例子来理解一下：
>
> <img src="..\0.TyporaPicture\image-20250113175527651.png" alt="image-20250113175527651" style="zoom:67%;" />
>
> 大家认为这样一串代码会有什么样的结果呢？运行一下，可能会大跌眼镜
>
> 回顾vector迭代器失效的原理，试试该怎样解决

> 很容易想到：更新迭代器的方法
>
> <img src="..\0.TyporaPicture\image-20250506170452148.png" alt="image-20250506170452148" style="zoom:67%;" />
>
> 小心迭代器失效，如果有扩容机制，一定得记得更新迭代器

#### 5.3 使用lambda代替一元谓词作为第三个参数

回到remove_if的使用，第三个参数是一元谓词

``` c++
bool func(int value) {
    return value > 5;
}

void test0() {
    vector<int> vec = {1,3,5,9,6,4,6,5};
    for_each(vec.begin(),vec.end(),[](int& value) {
        		cout << value << " ";
             });
    cout << endl;

    auto it = remove_if(vec.begin(),vec.end(),func);
    vec.erase(it,vec.end()); // 搭配remove_if使用
	
    for_each(vec.begin(),vec.end(),[](int& value){
                cout << value << " ";
             });
    cout << endl;
}
```

当然也**可以用lambda表达式替代**

``` c++
    vector<int> vec = {1,3,5,9,6,4,6,5};
    for_each(vec.begin(),vec.end(),[](int& value) {
                cout << value << " ";
             });
    cout << endl;
   
    auto it = remove_if(vec.begin(),vec.end(),[](int& value) {
							return value > 5; 
						});
    vec.erase(it,vec.end());

    for_each(vec.begin(),vec.end(),[](int& value) {
                cout << value << " ";
             });
    cout << endl;
```

> 既然是比较两个数的大小，我们很容易联想到之前已经多次使用的std::less和std::greater，尝试使用会发现一个问题
>
> <img src="..\0.TyporaPicture\image-20250330173517241.png" alt="image-20250330173517241" style="zoom:67%;" />
>
> ``` c++
> // std::less对象作为函数对象，其底层的operator()函数需要两个参数
> // 一个参数由vector提供（remove_if会遍历迭代器范围的元素）
> // 另一个参数呢，按照需求应该提供一个5，但是如何传参呢？
> auto it = remove_if(vec.begin(),vec.end(),std::less<int>()); // error
> vec.erase(it,vec.end());
> ```
>
> 实际上，可以利用算法适配器实现这一效果

### 6.`copy`——修改式的序列算法

- **函数原型**

  ![image-20260525201412483](..\0.TyporaPicture\image-20260525201412483.png)

- **源码**

  ```cpp
  // copy
  template<class InputIt, class OutputIt>
  OutputIt copy(InputIt first, InputIt last, 
                OutputIt d_first)
  {
      while (first != last) {
          *d_first++ = *first++;
      }
      return d_first;
  }
  // copy_if
  template<class InputIt, class OutputIt, class UnaryPredicate>
  OutputIt copy_if(InputIt first, InputIt last, 
                   OutputIt d_first, UnaryPredicate pred)
  {
      while (first != last) {
          if (pred(*first))
              *d_first++ = *first;
          ++first;
      }
      return d_first;
  }
  ```

### 7.`sort`——排序算法

- **函数原型**

  ![image-20260525201554174](..\0.TyporaPicture\image-20260525201554174.png)

- **示例**

  ```cpp
  #include <algorithm>
  #include <functional>
  #include <array>
  #include <iostream>
   
  int main() {
      std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
   
      // 用默认的 operator< 排序
      std::sort(s.begin(), s.end());
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用标准库比较函数对象排序
      std::sort(s.begin(), s.end(), std::greater<int>());
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用自定义函数对象排序
      struct {
          bool operator()(int a, int b) const
          {   
              return a < b;
          }   
      } customLess;
      std::sort(s.begin(), s.end(), customLess);
      for (auto a : s) {
          std::cout << a << " ";
      }   
      std::cout << '\n';
   
      // 用 lambda 表达式排序
      std::sort(s.begin(), s.end(), [](int a, int b) {
          return b < a;   
      });
      for (auto a : s) {
          std::cout << a << " ";
      } 
      std::cout << '\n';
  }
  ```

  ```cpp
  // 输出结果
  0 1 2 3 4 5 6 7 8 9 
  9 8 7 6 5 4 3 2 1 0 
  0 1 2 3 4 5 6 7 8 9 
  9 8 7 6 5 4 3 2 1 0
  ```

### 8.其余算法

- **非修改式的序列算法：`count`、`find`**

  ![image-20260526195414859](..\0.TyporaPicture\image-20260526195414859.png)

  ![image-20260526195434166](..\0.TyporaPicture\image-20260526195434166.png)

  ```cpp
  vector<int> vec = {1, 2, 3, 2, 2, 4};    
  // 统计数字 2 出现的次数
  int res = count(vec.begin(), vec.end(), 2); 
  cout << "2出现的次数：" << res; // 输出：3
  
  vector<int> vec = {10, 20, 30, 40};  
  // 查找数字 30
  auto it = find(vec.begin(), vec.end(), 30); 
  if (it != vec.end()) {
      cout << "找到元素：" << *it; // 输出：30
  } else {
      cout << "未找到";
  }
  ```

- **修改式的序列算法：`replace`、`fill`**

  ![image-20260526195814371](..\0.TyporaPicture\image-20260526195814371.png)

  ![image-20260526195826853](..\0.TyporaPicture\image-20260526195826853.png)

  ```cpp
  // 将区间 [first, last) 内所有等于 old_value 的元素替换为 new_value
  std::vector<int> v = {1, 2, 3, 2, 4, 2};
  std::replace(v.begin(), v.end(), 2, 99); // v 变成 {1, 99, 3, 99, 4, 99}
  
  // 将区间 [first, last) 内的所有元素一律赋值为 value，原来的内容会被完全覆盖
  std::vector<int> v(5);           	// {0,0,0,0,0}
  std::fill(v.begin(), v.end(), 7); 	// {7,7,7,7,7}
  ```

- **二分搜索的算法：`lower_bound`、`upper_bound`、`equal_range`**

  ![image-20260526200035316](..\0.TyporaPicture\image-20260526200035316.png)

  ![image-20260526200041641](..\0.TyporaPicture\image-20260526200041641.png)

  ![image-20260526200050275](..\0.TyporaPicture\image-20260526200050275.png)

  ```cpp
  // 返回第一个不小于(即大于或等于) value 的元素位置，即第一个 *it >= value 的位置
  std::vector<int> v = {1, 2, 4, 4, 5, 7}; // 有序
  auto it = std::lower_bound(v.begin(), v.end(), 4); // it 指向第一个 4 的位置（索引 2）
  it = std::lower_bound(v.begin(), v.end(), 3); // 没有3，指向第一个不小于3的元素，即4的位置（索引2）
  
  // 返回第一个大于 value 的元素位置，即第一个 *it > value 的位置
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto it = std::upper_bound(v.begin(), v.end(), 4); // it 指向第一个大于4的元素，即值为5的位置（索引 4）
  
  // 一次性返回等于 value 的元素的左闭右开区间，结果是一个 std::pair，包含 lower_bound 和 upper_bound 的结果
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto range = std::equal_range(v.begin(), v.end(), 4);
  // range.first 指向第一个4（索引2）
  // range.second 指向5（索引4）
  auto range2 = std::equal_range(v.begin(), v.end(), 3);
  // range2.first == range2.second，都指向可以插入3的位置（索引2，即当前第一个4的位置）
  ```

  ```cpp
  // lower_bound 与 upper_bound 的结合使用
  std::vector<int> v = {1, 2, 4, 4, 5, 7};
  auto low = std::lower_bound(v.begin(), v.end(), 4);
  auto up  = std::upper_bound(v.begin(), v.end(), 4);
  // 此时的 [low, up) 就是所有等于4的元素的范围
  for (auto i = low; i != up; ++i) std::cout << *i << ' '; // 4 4
  ```

  > **补充**
  >
  > 若是使用另一个版本的函数原型：
  >
  > ```cpp
  > // 以lower_bound为例
  > template< class ForwardIt, class T, class Compare >
  > ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
  > // 要做的事情的本质是：
  > // 找第一个 `comp(element, value)` 为 false 的位置，即第一个不满足比较器的元素
  > ```
  >
  > ==**二分搜索算法与 `Compare` 的关系：**==
  >
  > **前提**：区间 `[first, last)` 已按 `comp` 排序（默认 `<`）
  >
  > | 算法          | 内部判断             | 返回值与含义                                                 |
  > | :------------ | :------------------- | :----------------------------------------------------------- |
  > | `lower_bound` | `comp(*it, value)`   | **第一个使 `comp(*it, value) == false` 的位置** 即 `*it >= value`（不小于 `value`） |
  > | `upper_bound` | `comp(value, *it)`   | **第一个使 `comp(value, *it) == true` 的位置** 即 `*it > value`（严格大于 `value`） |
  > | `equal_range` | 同时使用上述两种判断 | **`std::pair<It, It>`** `first` = `lower_bound` 的结果 `second` = `upper_bound` 的结果 表示等于 `value` 的元素范围 `[first, second)` |

- **取最值：`max`、`min`、`minmax(C++11)`**

  1. **两个值的比较（基础版本）**

     ![image-20260526202139764](D:\Typora Picture\image-20260526202139764-177979822600998.png)

     ![image-20260526202148451](..\0.TyporaPicture\image-20260526202148451.png)

  2. **带自定义比较器的版本**

     ```cpp
     template< class T, class Compare >
     const T& max( const T& a, const T& b, Compare comp );
     
     template< class T, class Compare >
     const T& min( const T& a, const T& b, Compare comp );
     
     // min返回 comp(a, b) == true
     // max返回 comp(a, b) == false
     ```

     ```cpp
     auto cmp = [](int a, int b) { return std::abs(a) < std::abs(b); };
     int a = -10, b = 5;
     int min_abs = std::min(a, b, cmp); //  5
     int max_abs = std::max(a, b, cmp); // -10，因为 |-10| > |5|
     ```

  3. **初始化列表版本（C++11 起）**

     ```cpp
     template< class T >
     T max( std::initializer_list<T> ilist );
     
     template< class T >
     T min( std::initializer_list<T> ilist );
     ```

     ```cpp
     int worst = std::min({3, 1, 4, 1, 5, 9}); // 1
     int best = std::max({3, 1, 4, 1, 5, 9});  // 9
     ```

  4. **一次性获取最小和最大：`std::minmax`**

     ```cpp
     template< class T >
     std::pair<const T&, const T&> minmax( const T& a, const T& b );
     
     template< class T >
     std::pair<T, T> minmax( std::initializer_list<T> ilist );
     ```

     ```cpp
     int a = 10; int b = 20;
     auto result = std::minmax(a, b);
     std::cout << "min: " << result.first << '\n';	// 10
     std::cout << "max: " << result.second << '\n';	// 20
     // 结构化绑定用法（C++17起支持）
     int x = 5, y = 12;
     auto [lo, hi] = std::minmax(x, y);
     // 引用绑定版本：auto& [lo_ref, hi_ref] = std::minmax(x, y); lo_ref 是 const int&，绑定到原来的较小者（x），但 x 之后修改，lo_ref 也会变
     
     auto [lo, hi] = std::minmax({3, 1, 4, 2}); // lo = 1, hi = 4
     //传统写法
     std::pair<int, int> result = std::minmax({3, 1, 4, 2});
     int lo = result.first;
     int hi = result.second;
     ```

- **集合操作：`set_intersection`(取交集)、`set_union `(取并集)**

  ![image-20260526203506775](D:\Typora Picture\image-20260526203506775.png)

  ![image-20260526203546363](D:\Typora Picture\image-20260526203546363.png)

  ```cpp
  std::vector<int> v1 = {1, 2, 3, 3, 4, 5, 5, 7};
  std::vector<int> v2 = {3, 3, 5, 6, 7, 7, 8};
  // 取交集
  std::vector<int> intersection;
  std::set_intersection(v1.begin(), v1.end(),
                            v2.begin(), v2.end(),
                            std::back_inserter(intersection));
  for (int x : intersection) std::cout << x << ' '; // 结果：{3, 3, 5, 7}
  // 取并集
  std::vector<int> union_result;
  std::set_union(v1.begin(), v1.end(),
                     v2.begin(), v2.end(),
                     std::back_inserter(union_result));
  for (int x : union_result) std::cout << x << ' '; // 输出：1 2 3 3 4 5 5 6 7 7 8
  ```

  > **补充：使用自定义比较器**
  >
  > ```cpp
  > template< class InputIt1, class InputIt2, class OutputIt, class Compare >
  > OutputIt set_intersection( InputIt1 first1, InputIt1 last1,
  >                            InputIt2 first2, InputIt2 last2,
  >                            OutputIt d_first, Compare comp );
  > ```
  >
  > ```cpp
  > // 默认为降序排列
  > std::vector<int> a = {9, 7, 5, 3, 1};
  > std::vector<int> b = {8, 7, 7, 4, 3, 2};
  > std::vector<int> result;
  > std::set_intersection(a.begin(), a.end(),
  >                       b.begin(), b.end(),
  >                       std::back_inserter(result),
  >                       std::greater<int>()); // 同样的比较器
  > // result: {7, 3}
  > ```
  >
  > **与默认比较器相比**
  >
  > - 如果自定义比较器和默认 `<` 定义了**相同的等价关系**（比如只是把升序改成降序），那么结果的多重集（元素及出现次数）不变，但**顺序会变**
  > - 如果自定义比较器改变了等价关系（比如不区分大小写、按某个成员比较等），那么**哪些元素被视为相同就会不同**，最终结果的内容就会不同

# 二、补充

1. **容器、迭代器、算法之间的关系是怎样的？他们是如何结合在一起的？**

   - 三者关系

     1. **容器（Containers）**：负责数据的存储和管理
     2. **迭代器（Iterators）**：提供统一的接口来访问容器中的元素
     3. **算法（Algorithms）**：定义数据的处理逻辑

     这三者之间的关系可以概括为：**算法通过迭代器与容器进行交互，迭代器作为容器和算法之间的桥梁**

   - 结合方式

     1. 容器调用`begin()`、`end()`产生迭代器，标记出待操作的数据区间
     2. STL 算法接收迭代器作为参数，以此确定操作范围
     3. 算法通过迭代器实现元素遍历、读写访问，完成查找、排序、移除等逻辑处理
     4. 依托这套机制，同一套算法可以适配多种不同容器，实现代码通用复用