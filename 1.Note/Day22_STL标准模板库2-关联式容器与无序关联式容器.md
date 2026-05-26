# Day22_STL标准模板库2-关联式容器与无序关联式容器

## 一、关联式容器

**关联式容器包括：set、multiset、map、multimap四种**。它们的底层使用的数据结构都是**红黑树**。要学习它们的使用，可以从：**初始化、遍历、查找、插入、删除、针对自定义类型的处理**等方面进行学习。

> - set特征
>   存放的是**key类型**，key值是**唯一**的，**不能重复**
> - multiset特征
>   存放的是**key类型**，key值**不一定唯一**，**可以重复**
> - map的特征
>   存放的是**key-value类型**，key值是**唯一**的，**不能重复**，**value没有要求是否唯一**
> - multimap的特征
>   存放的是**key-value类型**，key值**不一定唯一**，**可以重复**，**value没有要求是否唯一**
>
> 且以上均为**默认按照关键字key进行升序排列**

## 1.set的使用

### 1.1 构造

![image-20250317175534262](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250317175534262.png)

- **无参构造**

- **迭代器方式进行构造，传入一个first迭代器，传入一个last迭代器**

- **拷贝构造**

- **标准初始化列表（大括号的形式）**

### 1.2 基本特征

![image-20240807115258806](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807115258806-1733124502629-22.png)

### 1.3 查找

![image-20240807112809259](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807112809259-1733124502628-19.png)

### 1.4 insert操作

![image-20240807113245685](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807113245685-1733124502629-20.png)

![image-20240807114212763](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807114212763-1733124502629-21.png)

==**注意：关联式容器都没有头部插入/删除或者尾部插入/删除的函数（因为插入之后是自动排序的，根本不需要关心一开始插入的位置）**==

### 1.5 erase操作

![image-20240807114416260](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807114416260-1733124502629-23.png)

> <span style=color:red;background:yellow>**注意**</span>
>
> - **set不支持下标操作，因为没有operator[]函数**
>
>   ![image-20240807114916461](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807114916461-1733124502629-25.png)
>
>   所以**访问set的元素只能通过迭代器方式**，但通过迭代器访问到的元素**只能进行读操作**
>
> - **set的元素不支持修改**
>
>   ![image-20240807115114358](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240807115114358-1733124502629-24.png)

### ==1.6 针对于自定义类型的写法==

![image-20240808102542239](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808102542239-1733124502629-26.png)

对于set而言，因为第二个模板参数Compare默认会采用std::less，但是std::less针对的Key如果不能比较大小即当Key类型是类类型的时候，就需要进行改写

因为直接定义一个存放Point的set，编译一定会报错，根本原因在于默认的std::less针对Point对象并不知道该如何比较大小

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250317183935132.png" alt="image-20250317183935132" style="zoom:67%;" />

改写的方式有三种：<span style=color:red;background:yellow>**模板的特化、运算符的重载、函数对象**</span>

1. **模板的特化**

  std::less是一个通用模板类，针对解决不了的特殊类型，可以想到<span style=color:red;background:yellow>**特化模板**</span>

  **为std::less准备一个特化版本，这个特化模板类中定义函数调用运算符重载函数，定义一套Point对象的比较规则**

  ![image-20250318150258925](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318150258925.png)

    > 自定义对象的**比较规则当然也是自定义的**，例如：
    >
    > 先比较到原点的距离（定义getDistance获取点到原点的距离），如果相同再比较横坐标，如果再相同再比较纵坐标。
    >
    > ![image-20250318150348968](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318150348968.png)
    >
    > <span style=color:red;background:yellow>**注意：**</span>
    >
    > - 在operator()函数中需要访问Point的私有成员，可以有两个思路：
    >
    >   1. 在自定义类中中作相应的友元声明；
    >
    >      <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20241226224935206.png" alt="image-20241226224935206" style="zoom:67%;" />
    >
    >   2. 给Point提供公有的get系列函数，间接访问Point的私有数据成员
    >
    > - 函数调用运算符重载函数(即operator())最好设为**const函数**
    >
    >   因为在 C++17 中，std::set 要求比较对象必须是 **常量可调用** 的。模板参数列表中的class Compare在set的底层实现中会创建出对象，并作为函数对象使用，也就是调什用operator()函数，这个函数需要是const成员函数
    >
    >   - 参考std::less的operator()函数
    >
    >
    >   ![image-20250317193513788](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250317193513788.png)
    >
    >   - 这涉及了set的内部实现的版本演变，不做探究
    >
    >
    >   <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250317192201592.png" alt="image-20250317192201592" style="zoom:67%;" />

2. **(对象)运算符重载**

   当然，如果让std::less通用模板知道Point对象该怎么比较大小可以做到吗？当然可以，使用<span style=color:red;background:yellow>**运算符重载**</span>就行

   operator< 以友元方式重载：（也可以重载为类的成员函数）

   ![image-20240808102807663](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808102807663-1733124502629-28.png)

   **这个场景下，如果特化模板与运算符重载同时存在，==模板特化优先级高于运算符重载==**

3. **(比较)函数对象(即自定义比较器)**

   上面两种方法都是围绕着std::less想办法，我们也可以自已准备Compare类（类似于智能指针的删除器，也可以理解为自定义比较器）

   Compare类重载函数调用运算符，set的底层实现中使用Compare类对象作为<span style=color:red;background:yellow>**函数对象**</span>，以此来规定元素的排序

   ![image-20240808102837821](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808102837821-1733124502629-29.png)

## 2.multiset的使用

### 2.1 基本特征

包含于`<set>`头文件

![image-20240808110150953](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808110150953-1733124502629-30.png)

### 2.2 其他功能

multiset的**查找功能（count、find）、插入功能（insert）、删除功能（erase）与set是一样的**

multiset**也没有[]下标操作，也同样不支持使用迭代器修改元素**

### 2.3 bound系列函数

注意：**equal_range返回的范围仍然是前闭后开的范围（返回的是一对数据即一个pair对象，其中包含两个迭代器）**

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20241210101903143.png" alt="image-20241210101903143" style="zoom:67%;" />

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318143726479.png" alt="image-20250318143726479"  />

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318143624627.png" alt="image-20250318143624627"  />

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318143647024.png" alt="image-20250318143647024"  />

> 如下，可以用**两种方式找出multiset中所有等于key的元素**
>
> 1. **[it11, it22)**
> 2. **(std::pair)ret**
>
> ![image-20240808111636211](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808111636211-1733124502630-31.png)

### 2.4 针对于自定义类型

multiset**针对于自定义类型的用法**与set完全一样，**也有三种形式：模板的特化、函数对象的形式、运算符重载**

## **3.map的使用**

### 3.1 基本特征

![image-20240808113609526](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808113609526-1733124502630-32.png)

### 3.2 查找

<img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318145851453.png" alt="image-20250318145851453"  />

![image-20240808113855833](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808113855833-1733124502630-33.png)

### 3.3 insert操作

![image-20250318145655104](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20250318145655104.png)

map**也有三种插入的方式：插入一个元素、插入迭代器范围的元素、插入大括号范围的元素**

> **注意**
>
> 插入时是**要插入一个或多个pair(包含一个key+一个value)**，**而不是插入key或者插入value**
>
> ==插入单个元素可能不成功（即这个元素已经存在于map中）==
>
> ![image-20240808114453984](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808114453984-1733124502630-34.png)

### 3.4 erase操作

![image-20240808114701760](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808114701760-1733124502630-35.png)

**map可以删除==迭代器指向的元素==、以及==迭代器范围的元素==**

### 3.5 下标操作（重要）

![image-20240808121115356](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808121115356-1733124502630-36.png)

<span style=color:red;background:yellow>**注意：**</span>

使用下标操作时，如果下标传入的是不存在的key，那么会将这个新的key和value的默认值组合成一个pair，插入到map之中

==这就有一个要求：**value对应的类型能够产生一个默认值**==

### 3.6 针对于自定义类型

![image-20240808144703570](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808144703570-1733124502630-37.png)

- 如果**key本身是可比较类型(即key是内置类型)**或**仅value是自定义类型**，其实不需要额外的操作，map可以正常进行遍历

  ![image-20240808144700093](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808144700093-1733124502630-38.png)

- 如果Key对应的是自定义类型

  1. 之前写的函数模板可以遍历前面五种容器的元素，但是map不行，因为map的元素都是pair，而**pair不能直接用输出流运算符进行输出**

     ![image-20241210115238336](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20241210115238336.png)

     此时有两个display构成**函数模板的重载**，第一个适用于任意的容器类型，**第二个专门用于map类型**

     在**调用display时会首先尝试调用第二个**，如果能匹配则使用，如上图的`mps`是一个map对象，正好可以使用，**如果不能匹配则尝试调用其他的display模板**，如上图的`pts`显然是无法匹配map<T1,T2>的，所以无法使用第二个模板，当然如果想要使用第一个函数模板，还需要为Point重载输出流运算符

  2. 上述讨论仅仅是解决map元素的遍历问题，**想要完成创建**，仍然要让编译器能够根据key值给map的元素排序。

     - **给Point重载<运算符**，或者**针对Point特化std::less**，代码都可以直接通过

     - 但如果用的是**函数对象**的方法，**在遍历时还需要一点改动（==即增添一个模板参数==）**

       <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20241210171242405.png" alt="image-20241210171242405" style="zoom:67%;" />

## 4.multimap的使用

### 4.1 基本特征

![image-20240808145243572](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808145243572-1733124502630-39.png)

### 4.2 其他操作

multimap的**查找功能（count、find）、插入功能（insert）、删除功能（erase）与map是一样的**

### 4.3 不支持下标

![image-20240808145436542](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\0.TyporaPicture\image-20240808145436542-1733124502630-40.png)

### 4.4 针对于自定义类型

**使用方式与map完全一样**

## 5.总结

- 关联式容器中的元素会按照key进行排序


- 底层使用的都是红黑树数据结构


- <font color=red>**map是具备下标的，其他三种关联式容器没有下标**</font>

## 二、无序关联式容器



<img src="D:\Typora Picture\image-20241210143437004.png" alt="image-20241210143437004" style="zoom: 80%;"/>

无序关联式容器底层是哈希表实现的。

首先来回顾一下哈希表

## 1.哈希

### 1.1 哈希相关的概念

- **哈希(过程)**

  哈希是一种可以接受各种类型、大小的输入，输出一个固定长度整数的过程

  可以将哈希理解成一种特殊的映射，将一个理论无限的集合A映射到有限整数集合B上

- **哈希函数**

  哈希函数是哈希过程的核心，它决定了**哈希映射过程的规则**

  可以通过key找到在表中的位置：`index = H(key)`

- **哈希冲突**

  哈希是一种化无限为有限的映射。理想中的映射应该做到一一对应，即“不同的输入一定得到不同的输出，同样的输入一定得到同样的输出”。但这种理想情况其实是做不到的。退而求其次，在实际使用中我们允许出现多对一（不同输入得到相同输出），但绝不允许出现一对多（相同输入得到不同输出）

  若**映射中出现多对一，就是哈希冲突，哈希冲突可以减少，但绝不可能没有**

  ```cpp
  // 不同的key值所对应的位置一样，这就是哈希冲突
  key1 != key2
  H(key1) = H(key2)  
  ```

- <span style=color:red;background:yellow>**如何构建哈希函数**</span>

  1. 定址法： H(key) = a * key + b
  2. <font color=red>**平方取中法**</font>： key^2 = 1234^2 = 1522756 ------>227
  3. 数字分析法：H(key) = key % 10000；
  4. 除留取余法：H(key) = key mod p (p <= m, m为表长)  

  **哈希函数之所以要设计得这么复杂，就是为了尽量减少哈希冲突**

- <font color=red>**装载因子(装填因子)**</font>

  那么表长应该如何设计比较合理？比如说针对上面这点元素，我准备一个容量为1000的表，选择一种哈希函数，能够让出现冲突的概率很低，但是又显得没有必要（为10个元素准备长度为1000的表，太浪费了）

  装载因子a = 元素的个数/表长，一般是一个小于1的小数。（因为如果大于1，代表着元素个数大于表长，那肯定会有哈希冲突，太小的表长显然不够）

  如果装载因子的值比较大，冲突的概率比较大，空间利用率比较高；如果装载因子的值比较小，冲突的概率比较低，空间利用率比较低；需要做一个权衡，一般设置在0.5~0.75左右

### 1.2 如何解决哈希冲突

开放定址法
<font color=red>**链地址法 **</font>(推荐使用这种，这也是STL中使用的方法)
再散列法
建立公共溢出区  



链地址法：

如下，假设有19 1 23 37 68 55 11  14 86这些元素，表长为11

19 mod 11 = 8，挂载在下标8位置

1 mod 11 = 1，挂载在下标1位置；23 mod 11 = 1，用链表的形式挂在元素1的后面

![image-20240808151302071](D:\Typora Picture\image-20240808151302071-1733125193831-63.png)

## 2.unordered_set的使用



unordered_set在使用时除了元素的类型，还需要关注几个模板参数

Hash决定了具体使用怎样的哈希函数，通过Hash类的operator()函数确定，而哈希冲突的解决方式则是由容器内部的实现机制确定的；

KeyEqual决定了元素的判重方式，同样也是通过operator()函数确定。

对于内置类型和指针类型，可以直接使用这一容器，如果是自定义类型对象作为元素，则需要为其准备这些模板参数。

<img src="D:\Typora Picture\image-20241212113324137.png" alt="image-20241212113324137" style="zoom:67%;" />





##### 基本特征

创建unorder_set的方式和之前的容器没有多大区别。

![image-20240808153120111](D:\Typora Picture\image-20240808153120111-1733125234824-65.png)

<img src="D:\Typora Picture\image-20241212115621977.png" alt="image-20241212115621977" style="zoom:80%;" />

无序 + 去重的效果





##### 其他操作

unordered_set的查找（count、find）、插入（insert）、删除（erase）等常用操作与set完全一样。也不支持下标。



##### 针对于自定义类型（重要）

![image-20240808155505140](D:\Typora Picture\image-20240808155505140-1733125234824-68.png)

针对于自定义类型而言，可能需要改写第二个模板参数Hash与第三个模板参数KeyEqual。



> Hash的默认采用的是std::hash，所以可以改写的方案有两种：模板的特化、函数对象的形式，与运算符重载没有什么关系。
>
> ![image-20240808163638815](D:\Typora Picture\image-20240808163638815-1733125234824-66.png)
>
> **如图，对横纵坐标分别进行左移再异或，其本质实际就是任意设计出一套哈希函数。**
>
> 
>
> ![image-20240808163705044](D:\Typora Picture\image-20240808163705044-1733125234824-67.png)





> 第三个模板参数KeyEqual的传参有三种方式：模板的特化、函数对象的形式、运算符重载。
>
> <font color=red>**注意：在operator()函数中加上打印语句后，可以观察打印的次数，进而分析什么时候才会用上equal_to函数对象**</font>
>
> ![image-20240808163825379](D:\Typora Picture\image-20240808163825379-1733125234824-70.png)
>
> ![image-20240808163848707](D:\Typora Picture\image-20240808163848707-1733125234824-69.png)
>
> ![image-20240808163930278](D:\Typora Picture\image-20240808163930278-1733125234824-71.png)









## 3.unordered_multiset的使用

##### 基本特征

![image-20240808170654309](D:\Typora Picture\image-20240808170654309-1733125234824-72.png)

##### 其他操作

unordered_multiset的查找（count、find）、插入（insert）、删除（erase）与multiset完全一样。也不支持下标。

##### 针对于自定义类型

unordered_multiset针对于自定义类型的写法与unordered_set的用法一样，需要改写第二个参数Hash与第三个参数KeyEqual。





## 4.unordered_map的使用

##### 基本特征

![image-20240808171339880](D:\Typora Picture\image-20240808171339880-1733125234824-73.png)

##### 其他操作

unordered_map的查找（count、find）、插入（insert）、删除（erase）与map是完全一样的。

##### 支持下标（==重要==）

![image-20240808171527718](D:\Typora Picture\image-20240808171527718-1733125234824-74.png)



## 5.unordered_multimap的使用

##### 基本特征

![image-20240808172135639](D:\Typora Picture\image-20240808172135639-1733125234825-75.png)

##### 其他操作

unordered_multimap的查找（count、find）、插入（insert）、删除（erase）与multimap是完全一样的。

##### 不支持下标

![image-20240808172248938](D:\Typora Picture\image-20240808172248938-1733125234825-76.png)

## 6.总结

- 无序关联式容器中的元素是**没有顺序的**

- 底层使用的都是**哈希表**数据结构

- unordered_map是具备下标的，其他三种无序关联式容器没有下标

## ==三、容器的选择==



## 四、容器适配器

