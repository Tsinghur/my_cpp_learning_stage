# Day26_STL标准模板库6-空间适配器

# 一、空间配置器

**在C++中所有STL容器的空间分配其实都是使用的std::allocator**

std::allocator是**可以感知类型的空间分配器**，将**空间的申请**与**对象的构建**、以及**空间的回收**与**对象的销毁**==严格分离==

以前我们知道使用**new创建单个对象**的时候，**空间的申请与对象的构造实际也是分开的**（可以回顾new表达式的工作步骤）

> 那么为什么要将空间的申请与对象的构建分开呢？
>
> 1. **减少不必要的对象构造和析构**：在**容器的使用过程中，有时只是需要预留一些空间，而并不需要立即在这些空间上构造对象**。例如，std::vector 的 reserve 函数，它的作用是为容器预留足够的内存空间，但不会构造任何对象。如果不将空间申请和对象构建分开，每次预留空间时都会构造对象，之后又可能因为不需要这些对象而进行析构，这会带来不必要的性能开销
> 2. **方便实现复杂的容器操作**：**在实现容器的一些操作，如插入、删除元素时，将空间申请和对象构建分开可以更方便地处理各种情况**。例如，在插入元素时，如果当前空间不足，容器可以先申请新的空间，然后将原有元素移动到新空间，最后在合适的位置构造新的对象，这样的操作更加灵活和高效。（比如vector的动态扩容机制背后就使用了空间配置器）

## 1.函数使用

- **std::allocator最重要的成员函数：**

  <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124102502538.png" alt="image-20250124102502538" style="zoom:67%;" />

  ```cpp
  // 申请空间
  T* allocate( std::size_t n );
  
  // 构建对象
  void construct( pointer p, const_reference val );
  
  // 执行析构
  void destroy( pointer p ); // p->~T()
  
  // 释放空间
  void deallocate( T* p, std::size_t n );
  ```

- 来尝试完成一个任务，实现自定义的vector，首先给出如下的代码接口

  ```cpp
  template <class T>
  class MyVector {
  public:
      MyVector();
      ~MyVector();
  
      void push_back(const T &);
      void pop_back();
      int size() const;
      int capacity() const;
  private:
      // 重新分配内存，动态扩容要用的
      void reallocate(); 
  
      // 空间的申请与对象的构建分开
      static std::allocator<T> _alloc;
  
      T* _start;
      T* _finish;
      T* _end_of_storage;
  };
  ```

  1. 先完成比较简单的

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124103233188.png" alt="image-20250124103233188" style="zoom:67%;" />

  2. 尾部插入元素、删除元素，模拟vector的核心问题就是动态扩容

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124103731526.png" alt="image-20250124103731526" style="zoom:67%;" />

  3. 完成动态扩容的功能

     ```cpp
     template <class T>
     void MyVector<T>::reallocate() {
         // 1.申请两倍的新的空间
         int oldCapacity = size();
         int newCapacity = oldCapacity > 0 ? 2 * oldCapacity : 1;
     
         T * ptmp = _alloc.allocate(newCapacity);
     
         if(_start) {
             // 2.使用算法库的函数将老的空间上的元素拷贝到新的空间
             std::uninitialized_copy(_start,_finish,ptmp);
     
             // 3.老的空间上的元素需要销毁，
             // 同时老的空间也要回收
             while (_start != _finish) {
                 /* _alloc.destroy(_start++); */
                 // 注意一下边界问题，这样写是完善的
                 _alloc.destroy(--_finish);
             }
     
             // 参数为指针(T*)和偏移量(size_t)
             // 如果从_finish开始，偏移量为负数，而size_t不好表达
             // 如果从_start开始,偏移量为正数，更方便
             // 所以选择_start固定，移动_finish;
             _alloc.deallocate(_start,oldCapacity);
         }
     
         // 4.三个指针与新的空间之间产生联系
         _start = ptmp;
         _finish = ptmp + oldCapacity;
         _end_of_storage = ptmp + newCapacity;
     }
     
     ```

  4. 析构函数的逻辑类似，也是销毁元素、回收空间

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124104636381.png" alt="image-20250124104636381" style="zoom:67%;" />

  5. 测试效果并发现不足

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124105021706.png" alt="image-20250124105021706" style="zoom:67%;" />

     如果想遍历容器中的元素，首先想到的肯定是增强for循环方式（没有实现取下标，也没有实现迭代器相关的函数），但会出现错误，说明增强for循环的底层实际上也是通过迭代器实现的

     ![image-20250124105645274](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124105645274.png)

  6. 完成迭代器相关函数

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124110222143.png" alt="image-20250124110222143" style="zoom:67%;" />

  7. 最终测试

     <img src="D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20250124110309969.png" alt="image-20250124110309969" style="zoom:67%;" />

  完成了简单的模拟后，其实还有很多可以完善的地方，比如取下标、比如insert，可以自行完善，本章主要借此展示了alloctor空间配置器的基本使用

## 2.原理

- 空间配置器分为两级：

  1. **一级空间配置器使用类模板malloc_alloc_template**，其**底层使用的是malloc/free进行空间的申请与释放**

  2. **二级空间配置器使用类模板default_alloc_template（默认空间配置器）**，其底层根据申请空间大小又分为两个分支

     - 当**申请的空间大于128字节**的时候，**还是走malloc_alloc_template** 

     - 当**申请的空间小于或等于128字节**的时候，使用**内存池 + 自由链表**的方法申请空间

       <span style=color:red;background:yellow>**注意：这里提到的自由链表实际是一个容量为16的指针数组，在源码中使用了_S_free_list这个名字，直译为自由链表**</span>

- **二级空间配置器的内存池+自由链表方法**

  有一个容量为16的指针数组，每个元素（指针）指向一个链表 ，用于管理不同大小的内存块。这 16 个指针所指向的链表，分别对应 8、16、24、32、40、48、56、64、72、80、88、96、104、112、120、128 字节的内存块

  每当程序申请小于 128 字节的内存时，二级空间配置器会先将申请的内存大小上调为 8 的倍数，再根据上调后的大小（8的整数倍）找到对应的链表。

  > **示例**
  >
  > 1. 数组中下标为3的指针，代表着会按照8 * (3 + 1) = 32字节为基本单位申请空间，第一次申请32个字节空间的时候，一次性申请很大一片空间（比如32 * 20 = 640个字节），然后按照32字节为一个等分，分成多个等分，然后挂接在下标为3的指针下面，形成链表形式
  >
  >    以后需要32字节的时候，直接在下标为3的下面取出一个节点即可，就是32个字节的内存空间
  >
  > 2. 如果申请64字节空间，第一次申请时也申请很大一片空间，同样按照64字节为一个等分，分成多个等分，挂载在数组中下标为7的指针之下
  >
  >    以后如果需要申请64字节时，就在下标为7的下面取出一个节点即可
  >
  > 3. 其他下标的处理方式完全一致

- **自由链表的工作示意图**

  第一次申请空间时比较麻烦，后续再此申请同等大小的空间可以以O(1)的时间复杂度完成申请。

  ![image-20240813115402461](D:\训练营\0.Git本地仓库\个人仓库\my_cpp_learning_stage\1.Note\image-20240813115402461-1733127460324-147.png)

- **内存池+自由链表的意义**

  为什么不每次直接申请相应大小的空间？

  如果频繁申请小片空间，可能会出现内存碎片的问题，这样导致空间的利用率低，会在内核态与用户态之间进行频繁的切换，时间消耗也比较大

