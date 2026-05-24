# Day21_STL标准模板库-序列式容器

## 一、标准模板库与STL六大组件

1. **STL标准模板库**

   - **标准模板库(Standard Template Library)**，简称STL，是一个具有工业强度的，高效的C++程序库。它被容纳于C++标准库中，是ANSI/ISO C++标准中最新的也是极具革命性的一部分。该库包含了诸多在计算机科学领域里所常用的基本数据结构和基本算法。为广大C++程序员们提供了一个可扩展的应用框架，高度体现了软件的可复用性
   - 与之前学到的编程思想面向对象编程不一样，STL采用的是一种新的编程模式：**泛型编程**。它允许程序员编写通用的代码，即可适用于不同的数据类型，而不必为每种类型编写不同的代码。这种编程方法的基本思想是将数据类型抽象化，使用泛型来表示数据类型，并在编写代码时使用泛型来代替具体的数据类型。本章重点在于介绍泛型编程的思想和本质，介绍一些常用的方法

2. **STL六大组件**

   1. **容器：用来存储数据，即数据结构**

      - **序列式容器**
        1. array(C++11) -- 静态的连续数组
        2. **vector - 动态的连续数组**
        3. **deque -- 双端队列**
        4. forward_list(C++11) -- 单链表
        5. **list -- 双链表**
      - **关联式容器：底层采取红黑树**
        1. set
        2. multiset
        3. map
        4. multimap
      - **无序关联式容器：底层采用哈希表**
        1. unordered_set
        2. unordered_map
        3. unordered_multiset
        4. unordered_multimap

   2. **迭代器：为了访问容器中的元素，可以将其看成是一种指针，称为泛型指针**

      ```cpp
      vector<int> nums = {1,2,3};
      vector<int>::iterator it = nums.begin();
      ```

   3. **算法：一些普通函数，可以操作容器中的元素**

      ```cpp
      std::sort(vec.begin(),vec.end());
      ```

   4. **适配器：起到适配的作用**

      - 容器适配器  stack、queue、priority_queue
      - 迭代器的适配器
      - 函数适配器   bind、bind1st、bind2nd、function等

   5. **函数对象：做定制化的操作**

   6. **空间配置器：管理内存**

3. **数据结构 + 算法 = 程序**

   ![image-20260302155445054](..\0.TyporaPicture\image-20260302155445054.png)

4. **STL六大组件之间的关系**

   - 容器作为STL的主体，是许多不同的数据结构 
   - 分配器为容器的实现分配应有的空间 

   - 泛型算法用来处理容器中的数据 

   - 迭代器是泛型算法和容器之间的桥梁

   - 仿函数使得算法可以有更加灵活的自定义模式 

   - 适配器保证了自定义的功能可以和STL中现有的功能相融合

## 二、序列式容器

### **1.基本操作**

#### 1.1 初始化

```cpp
// 1.无参构造
vector<int> box1; // vector<int> box1(); 是声明函数不是初始化
// 2.初始化列表
vector<int> box2 {1,2,3,4,5}; // 或 ({})
// 3.拷贝构造
vector<int> box3{box2}; // 或 vector<int> box3 = box2;
// 4.迭代器范围
vector<int> box4{box2.begin(), box2.end()}; // 左闭右开[,)
// 5.cout个value
vector<int> box5(3, 100); // 3个100
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list** 都具备五种初始化方式：
  1. 无参
  2. 初始化列表
  3. 拷贝或移动
  4. 迭代器范围
  5. count个value

#### 1.2 遍历

```cpp
vector<int> box1 {1,2,3,4,5};
// [下标]for i
for (int i = 0; i < box1.size(); ++i) {
    cout << box1[i] << " ";
}    
cout << endl;
// 增强for循环foreach
for (auto& e : box1) {
    cout << e << " ";
}
cout << endl;
// 迭代器
for (auto it = box1.begin(); it != box1.end(); ++it) {
    cout << *it << " ";
}
cout << endl;
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list 都支持使用增强for循环与迭代器**方式进行遍历
- 因为list不支持下标，所以**==仅list不能使用下标进行遍历==，vector与deque均可以通过[下标]进行遍历**

#### 1.3 在尾部进行插入与删除

```cpp
list<int> box{1,2,3};
box.push_back(4); // 1 2 3 4
box.push_back(5); // 1 2 3 4 5
box.pop_back(); // 1 2 3 4
box.pop_back(); // 1 2 3 4 5
// push_back 与 pop_back 的返回值类型均为 void
```

<span style=color:red;background:yellow>**总结：**</span>

- 三种序列式容器 **vector、deque、list 均支持在尾部进行插入与删除**

#### 1.4 在头部进行插入与删除

```cpp
list<int> box{1,2,3};
box.push_front(4); // 4 1 2 3
box.push_front(5); // 5 4 1 2 3
box.pop_front(); // 4 1 2 3
box.pop_front(); // 1 2 3
// push_front 与 pop_front 的返回值类型均为 void
```

<span style=color:red;background:yellow>**总结：**</span>

**vector 不支持在头部进行插入与删除，deque、list 均支持**

#### 1.5 模型理解

- **vector**

  ![image-20250314113757563](..\0.TyporaPicture\image-20250314113757563.png)

  vector头部是固定的，不能通过`push_front`与`pop_front`进行插入与删除，因为其没有这两个成员函数，只提供了在尾部进行插入与删除的操作，如果真的要在头部插入或者删除，必须用通用的 **`insert()`** 和 **`erase()`**，但是这样的话，其他的元素会发生移动，这样操作就比较复杂（时间复杂度O(n)）

  **实现效果**是**动态数组**

  **底层实现**是**一块连续堆内存、三个指针（start, finish, end_of_storage）**

- **deque**

  ![image-20250314113918079](..\0.TyporaPicture\image-20250314113918079.png)

  **实现效果**是**双端队列**

  **底层实现**是**分段连续的动态数组（中控器 + 多个缓冲区）**

- **list**

  ![image-20250314114024724](..\0.TyporaPicture\image-20250314114024724.png)

  list的**实现效果**是**双向链表**

  **底层实现**是**带哨兵头结点的双向循环链表**

#### 1.6 源码阅读

- **vector**

  1. 继承图

     ![image-20241114211419722](..\0.TyporaPicture\image-20241114211419722.png)

  2. 源码

     ```cpp
     // 模板参数：_Tp 元素类型，_Alloc 空间分配器，默认为标准分配器
     template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
     class vector {
     public:
         // 1.基础类型别名（为容器和算法提供类型萃取的能力）
         typedef _Tp         value_type;          // 值类型，即容器中存放的元素类型
         typedef value_type* pointer;             // 指针类型，指向元素的指针
         typedef const value_type* const_pointer; // 指向 const 元素的指针
         // ★重点：vector的迭代器就是原生指针！
         // 因为 vector 的元素是连续存储的，指针完全满足随机访问迭代器的要求
         typedef value_type* iterator;            	// 可变迭代器，本质就是 _Tp*
         typedef const value_type* const_iterator;	// 只读迭代器，本质就是 const _Tp*
         typedef value_type& reference;           	// 元素引用类型
         typedef const value_type& const_reference;	// const 元素引用类型
         typedef size_t     size_type;            	// 大小类型（通常为 unsigned 整型）
         typedef ptrdiff_t  difference_type;      	// 差值类型（两个迭代器相减的结果类型，有符号整型）
     	// vector<int>::iterator it; // iterator相当于vector的内部
         // 后面还会有容量、修改操作等成员函数……
     };
     ```

     在源码中，除了vector的数据成员，还可以看到一些成员函数的实现，比如push_back有可能发生的动态扩容，2倍扩容的机制就写在源码中（主流实现分**1.5倍(MSVC)**和**2倍(GCC、Clang)**）

  3. 获取vector的第一个元素的首地址，应该怎么做？

     ![image-20240806111634713](..\0.TyporaPicture\image-20240806111634713.png)

     验证如下：

     ![image-20250314144207535](..\0.TyporaPicture\image-20250314144207535.png)

     vector中`at()`与`operator[]`都具备随机访问的含义，但是**operator[]完全不做范围检查**，存在越界的风险，也就是不安全，但是**at具备范围限制，更加安全**，测试如下：

     ![image-20250314144256583](..\0.TyporaPicture\image-20250314144256583.png)

     > - **迭代器 ≠ 原生地址**，它是**对指针 / 节点的封装（抽象化的指针）**
     >
     > - **只有 vector 的迭代器**（GCC/Clang 实现）**本质是原生指针**，可以直接输出地址
     >
     >   **list /deque/map 等所有其他容器**的迭代器是**类对象**，**不能直接用 cout 输出**（编译报错）
     >
     > - 想**通用、标准地获取元素的首地址**，永远用 `&*it`，而不是直接输出迭代器

- **deque**

  > **数组中控器（map）+ 多个缓冲区片段**的**分段连续内存结构**，**块内连续、块间不连续，整体物理上不连续，逻辑上连续**
  >
  > 1. 数据缓冲区
  >
  >    - 每个缓冲区是**固定大小的连续数组**（SGI 实现默认 512 字节）
  >    - 元素真实存在这些小块里，**块内地址连续**
  >    - 块与块之间**地址不连续**
  >
  > 2. 数组中控器（map，即指针数组）
  >
  >    - `T** map;`：每个元素是一个 `T*`，指向一块缓冲区
  >    - 相当于一个**动态的二维数组**：`map[i]` 指向第 i 个数据块
  >
  > 3. 头尾插入
  >
  >    - `push_back`：尾块有空间直接写；满了就**新开一块**，放到 `map` 尾部
  >    - `push_front`：头块有空间直接写；满了就**在 map 头部插入新块**
  >    - 只新增 / 删除指针和小块，**不移动大量元素**，效率远高于 vector 的头插
  >
  > 4. 中控 map 扩容
  >
  >    当 map数组满了（指针不够用）：
  >
  >    - 重新分配一个**更大的指针数组**
  >    - 把旧指针复制过去
  >    - 旧 `map` 释放，**数据块本身不需要拷贝**
  >
  > 5. 迭代器
  >
  >    - `cur`：当前元素指针
  >    - `first`/`last`：当前块首尾
  >    - `node`：指向 `map` 中当前块的指针
  >
  > deque 底层采用 “中控指针数组 + 固定大小数据块” 的分段连续存储，块内连续、块间不连续；通过中控数组实现 O (1) 随机访问，头尾增删 O (1)，兼顾 vector 的随机访问和 list 的头尾高效操作

  1. 继承图

     ![image-20250324164403999](..\0.TyporaPicture\image-20250324164403999.png)

  2. 原理

     deque是由多个片段组成的，**片段内部连续**，**片段之间不连续**，多个片段被一个称为中控器的结构控制（也称为map，但是跟容器std::map不是一回事）

     所以说deque是<font color=red>**在物理上是不连续的，但是逻辑上是连续的**</font>

     - 初始化

       初始化deque时，根据元素的个数分配一个/多个缓冲区片段，在缓冲区片段中存放实际的元素，这里以int型元素为例。**通常情况下，在初始化时第一个元素会被放置在第一个缓冲区中相对靠前的位置（而非第一个缓冲区的首地址，这样方便在头部添加元素）**，前后相邻的两个元素在逻辑上是连续的，但是物理层面上可能并不是连续的

       同时还会生成一个**数组中控器（map），存放每个缓冲区片段的首地址**（注意map中的元素是`int* p`，而不是严格意义的数组指针即`int (*p)[]`，这一点从源码中可以进行理解），**通常情况下，第一个缓冲区片段的首地址被放在中控器map的居中位置**

     - 插入元素

       deque初始化完成后，进行添加元素的操作：

       1. **如果在尾部添加元素value**

          找到最后一个存放着元素的缓冲区片段，在其中最后一个元素的后面添加元素value

          **如果此时最后的缓冲区片段是满的**，那么就再**申请一个新的缓冲区片段（作为最后一个片段）**，**将要添加的元素value存放在新片段的首个位置**。同时中控器也加上一个元素（新片段的首地址），让中控器与新片段联系起来

       2. **如果是在deque的头部添加元素value**

          找到已经存储的第一个元素的位置，在它的前面存放新元素value

          经过若干次头部添加元素之后，**如果第一个缓冲区片段满了**，还要继续在头部添加元素，则**新开辟一个缓冲区片段（作为第一个片段）**，**将value存在新片段中的最后一个位置**。同时在中控器的相应位置存放新的缓冲片段的首地址

       3. **那么这里会有一个小小的问题（数组中控器map扩容）**

          如果一直往deque头部添加元素，中控器的前半部分已经满了，后半部分还没满，会怎么样呢？

          这种情况会通过一个reallocate_map函数来管理中控器的设置，**先做一个判断，我们可以简单理解为如果中控器后半部分的空位较多，那么就将中控器中记录的地址全都后移若干位**，这样中控器的前半部分就有空位了。**如果中控器后半部分的空位较少，就再开辟新的更大的空间作为中控器，将原本中控器中记录的地址复制到新的中控器中**

          同理，如果一直往deque尾部添加元素，中控器的后半部分已经满了，前半部分还没满，也是一样的处理流程

       4. **注意：**

          在deque头部添加元素或者尾部添加元素的过程中，原本已经存在deque中的元素始终没有改变位置，这一点与vector形成很大的区别

          ![image-20250315160520768](..\0.TyporaPicture\image-20250315160520768.png)

     - 每个缓冲区片段的元素个数

       每个缓冲区是**固定大小的连续数组**（SGI 实现默认 512 字节）

       ![image-20250314162540413](..\0.TyporaPicture\image-20250314162540413.png)

       如果deque存放的元素类型的大小小于 512 字节。每个缓冲区片段的大小为 512 字节，512 除以元素类型的大小，就可以得到每个缓冲区片段能够存放的元素数量

       例如元素类型是 int，在 64 位系统中，sizeof(int)= 4 字节。**那么 deque_buf_size(4) 的结果就是 512 / 4 = 128，即每个缓冲区片段可以存放 128 个 int 类型的元素**

       这种设计的好处是，对于较小的元素类型，每个缓冲区可以存放较多的元素，减少了缓冲区的数量，从而降低了中控器（用于管理缓冲区的数组）的管理开销

       如果元素类型大小大于等于 512 字节，函数返回 1。这表示每个缓冲区片段只存放一个元素，比如自定义类型A的对象作为deque的元素，单个元素的大小超过了 512 字节，那么 __deque_buf_size(sizeof(A)) 的结果就是 1，每个缓冲区片段只会存放一个 A类型的元素

     - deque的迭代器底层

       deque的迭代器比vector的迭代器复杂得多，`vector<T>`的迭代器实际是对T*的包装，但deque的迭代器实际应该视为对象，数据成员包含四个指针，并且进行了一系列的运算符重载，使得迭代器能够像指针一样被使用

       ![image-20250315161915597](..\0.TyporaPicture\image-20250315161915597.png)

       ![image-20250315161952642](..\0.TyporaPicture\image-20250315161952642.png)

#### ==1.7 insert操作==

之前的push_back和push_front尽管可以插入元素，但是插入的位置都比较固定

实际上三种序列式容器都允许在任意位置插入元素，使用insert成员函数即可

- 它们都具备以下四种插入的功能

  ![image-20240806144651816](..\0.TyporaPicture\image-20240806144651816.png)

  ```cpp
  vector<int> box{1,2,3,4,5};
  cout <<"size=" << box.size() << endl; // 5
  cout << "capacity=" << box.capacity() << endl; // 5
  print(box); // 1 2 3 4 5
  // 1.给定位置，插入单个元素
  auto it =box.begin();
  ++it;
  // box.insert(it, 100); 由于扩容机制，所以可能会有迭代器失效的问题
  it = box.insert(it, 100); // 所以必须更新迭代器
  cout <<"size=" << box.size() << endl; // 6
  cout << "capacity=" << box.capacity() << endl; // 10
  print(box); // 1 100 2 3 4 5
  cout << "*it=" << *it << endl; // 100
  // 2.给定位置，插入多个元素 
  it = box.insert(it, 2, 200); // 更新迭代器
  print(box); // 1 200 200 100 2 3 4 5
  cout << "*it=" << *it << endl; // 200
  ++it;
  cout << "*it=" << *it << endl; // 200
  ++it;
  cout << "*it=" << *it << endl; // 100
  // 3.给定位置，插入迭代器范围
  auto it2 = box.begin();
  ++it2;
  vector<int> box2{10,20,30};
  it2 = box.insert(it2, box2.begin(), box2.end());
  print(box); // 1 10 20 30 200 200 100 2 3 4 5
  // 4.给定位置, 用初始化列表插入
  it2 = box.insert(it2, {1000,2000});
  print(box); // 1 1000 2000 10 20 30 200 200 100 2 3 4 5
  cout << "*it2=" << *it2 << endl; // 1000
  ```
  
- 以list为例

  1. 双向链表由于其底层结构的原因，插入是非常方便的

     ![image-20241203105613687](..\0.TyporaPicture\image-20241203105613687.png)

  2. 从参考文档出发可知三种序列式容器都有这样的插入方式，但insert过程中的细节却值得注意

     ![image-20241203112930981](..\0.TyporaPicture\image-20241203112930981.png)

  3. 如果把list换成deque，情况会有所不同

     ![image-20241203151641204](..\0.TyporaPicture\image-20241203151641204.png)

  4. 在利用迭代器遍历容器元素并做出处理时，往往需要更新迭代器

     <span style=color:red;background:yellow>**虽然insert函数有多种形式，但它们的返回值都是指向第一个被插入元素的迭代器**</span>

     ![image-20241203152546132](..\0.TyporaPicture\image-20241203152546132.png)
  
  5. 对于vector，insert操作执行过程中还存在着更大的隐患，可能导致<span style=color:red;background:yellow>**迭代器失效**</span>
  
     ![image-20241203162022141](..\0.TyporaPicture\image-20241203162022141.png)
  
     这是因为当vector使用insert进行插入时，可能会发生动态扩容。比如上述的nums是一个“存满”状态的vector，此时size和capacity的结果是一样的。增加新的元素会进行扩容
  
     扩容的过程中会申请一块新的空间，然后将老的空间上的元素拷贝到新的空间来，然后会清理老的空间、这时如果还继续使用原本的迭代器，对应的也就是老的空间的地址，会出现问题，因为此时迭代器已经失效了
  
     <span style=color:red;background:yellow>**所以，每次在使用迭代器进行insert操作时，更新迭代器（重新置位）**</span>
  
     ![image-20241203175553874](..\0.TyporaPicture\image-20241203175553874.png)
  
     > <span style=color:red;background:yellow>**补充**</span>
     >
     > 之前在学习vector的push_back操作时，我们了解了2倍扩容机制。而insert导致的扩容，规则更复杂一些。
     >
     > **vector的insert扩容（仅作了解）**
     >
     > ``` cpp
     > nums.size() = m
     > nums.capacity() = n;
     > // 要插入的元素的个数为t
     > // (1) t < n - m       	不会扩容
     > // (2) n - m < t < m   	按照2*size()进行扩容
     > // (3) n - m < t, m < t	按照t + m进行扩容，即新插入的元素的数量大于当前元素个数，仅将容量单纯扩大为当前元素个数的2倍仍装不下
     > ```
     >

#### ==1.8 erase操作==

三种序列式容器都可以进行erase操作，用来删除容器中的单个元素或多个元素

![image-20240806160154610](..\0.TyporaPicture\image-20240806160154610.png)

- **list的erase操作**

  由于list的原理，list中的元素无论是插入还是删除都非常的方便，erase后迭代器it仍然指向原本的地址（<font color=red>**实际已经不属于list元素的空间，也可以归为一种迭代器失效问题**</font>），想要继续正常使用it，需要进行迭代器更新

  <span style=color:red;background:yellow>**erase函数的返回值为被删除元素后一位元素对应的迭代器**</span>

  ![image-20241202175257615](..\0.TyporaPicture\image-20241202175257615.png)

- **deque的erase操作**

  deque的erase操作后，迭代器it仍然指向原本的位置。但是原本的位置上存放的是什么，**取决于删除的元素属于前半段还是后半段**

  > `deque` 是分段连续空间——由多个固定大小的数组（缓冲区）通过一个中控器（指针数组）串联而成
  > 这导致它**不能像 `vector` 那样直接通过一个指针偏移来整体搬移元素**，因为元素可能跨缓冲区
  >
  > 因此，当在中间删除一个元素时，必须移动后续所有元素来填补空位，但往哪边移动就成了一个选择：
  >
  > - 可以把**被删位置前面的元素整体往后移一位**（覆盖被删元素）
  > - 或者把**被删位置后面的元素整体往前移一位**（覆盖被删元素）

  ![image-20241203093724218](..\0.TyporaPicture\image-20241203093724218.png)

  如果想要在erase之后继续正常使用it这个迭代器，那么同样建议进行迭代器更新

  ![image-20241203093928234](..\0.TyporaPicture\image-20241203093928234.png)

- **vector的erase操作**

  如果将上述例子中的容器换成vector，似乎不会出现问题：

  删除掉一个元素后，如果不更新迭代器，后面的元素往前移，迭代器仍指向原本的位置，对应的就是被删除的元素后一位的元素，如果更新迭代器，迭代器指向也能够确保是后一位的元素

  也就是说，**对于vector而言，使用erase删除单个元素时，是否更新迭代器效果是一样的**

  > **注意：在删除连续重复元素时，可能出现的逻辑上的错误**
  >
  > - 例如：使用vector时很可能写出这样的代码
  >
  >   ![image-20241204110148074](..\0.TyporaPicture\image-20241204110148074.png)
  >
  >   此时通过`it = nums.erase(it)`这样简单更新迭代器并不能解决问题（效果一样）。问题的**根本在于无论是对于该删除的元素还是不该删除的元素，迭代器的偏移采取的是统一的方式**
  >
  >   因为在vector在物理存储上是连续的，如果删掉某个元素，后面的元素前移，如果此时迭代器依然往后移动一次，那么就会跳过一个元素
  >
  >   **解决方式：在==删除元素时，不移动迭代器==，从逻辑的角度上来说，对应的元素已经变成了被删元素的下一位**
  >
  > - list进行erase时，**还需要更新迭代器**
  >
  >   因为list在物理存储上是不连续的，所以erase后仍旧指向已经失效的被删除元素，所以需要更新erase即向后移动一次
  >
  >   ![image-20241204115650449](..\0.TyporaPicture\image-20241204115650449.png)

#### 1.9 元素的清空

![image-20240806162826639](..\0.TyporaPicture\image-20240806162826639.png)

![image-20240806162838101](..\0.TyporaPicture\image-20240806162838101.png)

![image-20240806162848551](..\0.TyporaPicture\image-20240806162848551.png)

<span style=color:red;background:yellow>**总结**</span>：

- 三种序列式容器 **vector、deque、list 都有`clear()`**清空元素、以及获取元素个数的函数**`size()`**
- 对于 **vector与deque，还有**回收多余空间的函数**`shrink_to_fit()`**
- 对于 **vector** 还有记录容量大小的函数**`capacity`**

#### 1.10 其它成员函数

```cpp
// 三种序列式容器均具备的：
// 交换
void swap( list& other ); // 此处的list可以改为vector或者deque，注意：交换的两个容器类型要完全相同
// 改变元素个数
void resize( size_type count, T value = T() );
void resize( size_type count );
void resize( size_type count, const value_type& value )
// 获取容器的第一个元素与最后一个元素
reference front(); 
const_reference front() const;
reference back();
const_reference back() const;    
```

#### 1.11 emplace(_back)函数

这三种序列式容器还有两个值得关注的函数：`emplace` 和 `emplace_back`

- `emplace` 与 `insert`对比，前者是直接在指定位置构造对象，后者是将一个已存在的对象复制并插入到容器中指定位置
- `emplace_back` 与 `push_back`对比， 前者是直接在容器尾部构造对象，后者是将一个已存在的对象复制并插入到容器末尾

![image-20250317095728675](..\0.TyporaPicture\image-20250317095728675.png)

- `emplace_back`的效果

  ![image-20240806164845608](..\0.TyporaPicture\image-20240806164845608.png)

- `emplace`的效果

  ![image-20250317104810864](..\0.TyporaPicture\image-20250317104810864.png)

> 补充：**STL中的emplace_back和push_back有什么区别？**
>
> 1. 构造方式不同
>
>    - **push_back**：
>
>      先在容器**外部**构造一个完整对象（或传入已存在的对象），然后将该对象**拷贝或移动**到容器尾部
>
>    - **emplace_back**：
>      直接在容器**内部内存空间**中，用传入的参数**原地构造对象**，不产生临时对象
>
> 2. 参数形式不同
>
>    - **push_back**：接收**一个已构造好的对象**（值、左值引用或右值引用）
>    - **emplace_back**：接收**元素构造函数的参数列表**（支持多参数、可变参数）
>
> 3. 性能差异
>
>    - **push_back**：
>      至少一次**拷贝构造**或**移动构造**，还可能产生临时对象并析构，开销较大
>    - **emplace_back**：
>      **仅一次构造函数调用**，无临时对象、无额外拷贝 / 移动，效率更高；对象越复杂，性能优势越明显

### ==2.list的特殊操作==

list还具有一些vector与deque没有的**独占成员函数**

#### 2.1 sort——排序

> 注意：vector和deque没有此**成员函数**，通过**全局算法函数**`std::sort(vec.begin(),vec.end());`来对容器内的元素进行排序

- **函数原型**

  将list中的元素排序

  ![image-20241205154048844](..\0.TyporaPicture\image-20241205154048844.png)

- **无参版本的示例**

  如果使用**无参版本的sort函数**，则list中的元素**默认以升序排列**

  ![image-20241205154657832](..\0.TyporaPicture\image-20241205154657832.png)

- **有参版本**

  第二个版本的sort函数有一个参数，参数为Compare类型的对象。关于Compare，第一次见到应该是在set类模板声明中

  ![image-20241206162659730](..\0.TyporaPicture\image-20241206162659730.png)

  之前在简单使用set时我们知道元素会默认按照升序排序，这里就**是使用了`std::less<key>`的效果**：

  ![image-20241206162926925](..\0.TyporaPicture\image-20241206162926925.png)

  效果和无参的sort版本是一样的，同样采用升序排序

  **这里对std::less的使用与之前unique_ptr的默认删除器的使用是很相似的**

  ![image-20241206163620509](..\0.TyporaPicture\image-20241206163620509.png)

  - `std::less`类的内部

    通过cpp参考文档能够了解到std::less进行了函数调用运算符的重载，在`operator()`函数中接受两个参数，代表两个元素，在函数定义中对两个元素进行了比较

    ![image-20241206164121319](..\0.TyporaPicture\image-20241206164121319.png)

  - 降序排列

    如果想要按照降序排列，对应位置可以换成std::greater

    ![image-20241209102349777](..\0.TyporaPicture\image-20241209102349777.png)

  - 定制化Compare

    当然，针对需要排序的各种元素类型，可能需要更灵活的Compare，那么我们可以像定制化删除器一样定制化Compare

    ![image-20241209105703516](..\0.TyporaPicture\image-20241209105703516.png)

    会发现自定义的Compare对象被当成函数调用了很多次，可以简单阅读list的**sort**函数源码，发现**其底层实现实际是一种基于归并排序的做法**

    ```cpp
    // 两个template关键字，是因为这里定义的是类模板的成员函数模板，而且在类外定义。此为C++语法规定的写法
    
    template <class _Tp, class _Alloc>
    template <class _StrictWeakOrdering>
    void list<_Tp, _Alloc>::sort(_StrictWeakOrdering __comp) 
    {
        // 如果链表长度 <= 1，则已经有序，直接返回
        // _M_node 是链表的尾后哨兵节点，_M_node->_M_next 是真正的头节点
        // 条件: 头节点不是哨兵 (链表非空) 且 头节点的下一个不是哨兵 (长度 >= 2)
        if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node) 
        {
            list<_Tp, _Alloc> __carry;          // 临时存放当前待归并的小段
            list<_Tp, _Alloc> __counter[64];    // 归并桶数组，counter[i] 最多存 2^i 个元素
            int __fill = 0;                     // 当前使用到的最大桶索引 + 1
    
            // 不断从原链表中剥离第一个元素，放入 __carry 作为长度为 1 的有序段
            while (!empty()) 
            {
                // 将 *this 的第一个元素剪切到 __carry 的头部
                __carry.splice(__carry.begin(), *this, begin());
    
                int __i = 0;
                // 像二进制加法一样，若当前桶 i 非空，则与 __carry 合并，并进位到下一桶
                while (__i < __fill && !__counter[__i].empty()) 
                {
                    // 将 __carry 合并到 __counter[__i] 中，结果留在 __counter[__i]
                    __counter[__i].merge(__carry, __comp);
                    // 交换 __carry 与 __counter[__i]，现在 __carry 持有合并后更大的有序段
                    __carry.swap(__counter[__i++]);
                }
                // 将进位得到的 __carry 放入空桶 __counter[__i]
                __carry.swap(__counter[__i]);
                // 如果进位到了更高的空桶，更新 __fill
                if (__i == __fill) 
                    ++__fill;
            }
    
            // 此时，所有元素已分布在不同大小的桶中（counter[0] ~ counter[fill-1]）
            // 需要将所有桶从低到高依次合并，最终结果汇聚在 counter[fill-1]
            for (int __i = 1; __i < __fill; ++__i)
                __counter[__i].merge(__counter[__i - 1], __comp);
    
            // 将最终结果交换回 *this
            swap(__counter[__fill - 1]);
        }
    }
    
    template <class _Tp, class _Alloc>
    template <class _StrictWeakOrdering>
    void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x,
                                  _StrictWeakOrdering __comp) 
    {
        iterator __first1 = begin();    // 当前链表起始位置
        iterator __last1  = end();      // 当前链表尾后哨兵
        iterator __first2 = __x.begin();// __x 起始位置
        iterator __last2  = __x.end(); // __x 尾后哨兵
    
        // 两个链表都还有元素时，比较头部元素
        while (__first1 != __last1 && __first2 != __last2)
        {
            // 若 __x 的头元素更小（按严格弱序），将其转移到当前链表的 __first1 之前
            if (__comp(*__first2, *__first1)) 
            {
                iterator __next = __first2;      // 暂存当前节点
                // transfer: 将 [__first2, ++__next) 即单个元素移动到 __first1 之前
                transfer(__first1, __first2, ++__next);
                // 更新 __first2 为下一个节点（transfer 后原 __first2 已移走）
                __first2 = __next;
            }
            else 
            {
                // 否则当前链表元素更小（或相等），直接后移 __first1
                ++__first1;
            }
        }
    
        // 如果 __x 还有剩余元素，全部粘接到当前链表尾部
        if (__first2 != __last2)
            transfer(__last1, __first2, __last2);
    }
    ```

#### 2.2 reverse——将list中所有元素顺序反转

![image-20241209114609938](..\0.TyporaPicture\image-20241209114609938.png)

> 注意和vector的reserve函数(预留空间)区分，拼写上非常相似

![image-20250317155350549](..\0.TyporaPicture\image-20250317155350549.png)

#### 2.3 unique——去重list中重复的元素

**必须先排序**（无论是从小到大还是从大到小），才能够实现效果

![image-20250317154753075](..\0.TyporaPicture\image-20250317154753075.png)

#### 2.4 merge——将一个list合并到当前list中

**合并结果**：lst2中的元素合并到lst1中，**lst2的元素被清空**

> 注意：如果合并前的list是无序的，合并后的list整体也是无序的
>
> 想要合并后的list结果是有序的，需要<span style=color:red;background:yellow>**合并前两个list中的元素先排好序**</span>

![image-20250818212441074](..\0.TyporaPicture\image-20250818212441074.png)

![image-20250818212500682](..\0.TyporaPicture\image-20250818212500682.png)

#### 2.5 remove & remove_if——移除元素

- remove函数能够**移除所有等于 value 的元素**

- remove_if函数能够**移除所有符合条件的元素**，==需要传入一个一元谓词（返回值为bool的一元函数）——如果某元素作为函数参数能够返回true，则判定为应该删除的元素==

  ![image-20250808154243844](..\0.TyporaPicture\image-20250808154243844.png)

#### 2.6 splice——移动元素

> `splice` 是**直接修改原数组**的方法，它会从数组中**物理移除**元素，返回的是被移除元素组成的新数组

![image-20240807100112283-1733123638304-4](..\0.TyporaPicture\image-20240807100112283-1733123638304-4.png)

==第一个参数相当于是移动的目的地==

![image-20240807100952020-1733123638304-5](..\0.TyporaPicture\image-20240807100952020-1733123638304-5.png)

![image-20240807101035059-1733123638304-6](..\0.TyporaPicture\image-20240807101035059-1733123638304-6.png)

<span style=color:red;background:yellow>**注意：**</span>如果在同一个链表中进行splice操作

![image-20240807101633898-1733123638304-7](..\0.TyporaPicture\image-20240807101633898-1733123638304-7.png)

**可能会出现问题（取决于范围有没有交叉）**

类似于strcpy，目的字符串与源字符串不要有交叉，同理还有memcpy也是要注意这个问题

> 补充：
>
> - splice函数可以帮助我们很方便地实现LRU(Least Recently used)
>
>
> - <span style=color:red;background:yellow>**LRU:最近最少使用算法**</span>
>
>   一种常用的页面置换算法，用于在有限的内存空间中管理数据缓存，以提高系统性能
>
>   LRU 算法基于一个假设：如果一个数据在最近一段时间内没有被访问，那么在未来它被访问的概率也相对较低。因此，当内存空间不足时，LRU 算法会选择淘汰最近最少使用的数据，为新的数据腾出空间
>
>   ```cpp
>   思想：新元素放在前面，老的元素放在后面
>   比如现在有 1 2 3 4 四个元素逐一存到容器中，限制容量为4
>   刚存放完       插入元素3      插入元素5      插入元素4
>   4 3 2 1 ----> 3 4 2 1 ----> 5 3 4 2  ---> 4 5 3 2
>   
>   // 假设现在插入元素2   
>   int number = tmp.back();
>   tmp.pop_back();
>   tmp.push_front(number);
>   
>   // 如果明确了是用list存储，可以使用splice函数，
>   tmp.splice(tmp.begin(), tmp, --tmp.end());
>   ```
