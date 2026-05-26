# Day23_STL标准模板库3-迭代器

## 一、迭代器

### 1.概念

可以将迭代器看成是一种指针，但是不完全是指针，因为**有些时候迭代器是一个类类型，然后重载了指针的功能，所以迭代器可以像指针一样使用**

- C++为什么要设计迭代器

  迭代器算是C++一个非常重要的抽象概念，它的意义在于：

  1. **为访问容器中的元素提供了统一的方式**

     比如，vector/deque/list三种容器存储元素的方式完全不同，存储元素的类型也可能不同，但是都可以用迭代器来遍历和操作容器中的元素，而不需要关心容器的具体实现细节

  2. **使算法能够独立于容器进行设计和实现**

     例如，std::sort算法可以对任何支持随机访问迭代器的容器进行排序，而不需要为每种容器单独实现排序算法。这样可以提高代码的可复用性和灵活性。

  也就是说**C++通过迭代器把不同的容器的元素的访问逻辑抽象了出来**

### 2.迭代器的类型

1. 输入迭代器(InputIterator)
2. 输出迭代器(OutputIterator)
3. 前向迭代器(ForwardIterator)
4. 双向迭代器(BidirectionIterator)
5. 随机访问迭代器(RandomAccessIterator)

<img src="..\0.TyporaPicture\image-20250102105616784.png" alt="image-20250102105616784" style="zoom:80%;" />

- **五种迭代器之间的关系（逻辑层面上近似于继承关系）**

  <img src="..\0.TyporaPicture\image-20240809114205549-1733126659853-98.png" alt="image-20240809114205549" style="zoom:67%;" />

  > 举个简单的例子，根据我们对继承关系的了解，我们可以推测出：
  >
  > ![image-20250102114216223](..\0.TyporaPicture\image-20250102114216223.png)

- **为什么要定义这么多种迭代器**

  为了物尽其用，使得具体的操作使用具体类型的迭代器，避免迭代器的功能太大或者太小，导致使用起来不方便。每个容器及其对应的迭代器的类型图表如下：

  <img src="..\0.TyporaPicture\image-20250102114702572.png" alt="image-20250102114702572" style="zoom: 67%;" />

- **总结**

  迭代器就是访问容器中元素的手段，大多数时候并不需要研究迭代器的具体实现，能够根据容器的迭代器类型进行正确的使用即可

  > 1. **输入迭代器**（Input Iterator）
  >
  >    - **特点**：==用于读取容器中的元素，只能向前移动，支持自增操作（`++`）来指向下一个元素，**可进行解引用，但不能修改元素的值**==（`*`）操作来访问当前元素的值，还能进行相等（`==`）和不等（`!=`）比较以判断两个迭代器是否指向同一位置。
  >    - **应用场景**：常用于只读算法，如 `std::find`、`std::count` 等，这些算法只需要从容器中读取元素，不需要修改元素的值。
  >
  > 2. **输出迭代器**（Output Iterator）
  >
  >    - **特点**：==用于向容器中写入元素，只能向前移动，支持自增操作（`++`），**可通过解引用**（`*`）操作来**修改元素的值，但不能读取元素的值**==。输出迭代器不支持比较操作。
  >
  >    - **应用场景**：常用于输出算法，如 `std::copy` 算法可以将一个范围的元素复制到另一个由输出迭代器指定的位置。
  >
  > 3. **前向迭代器**（Forward Iterator）
  >
  >    - **特点**：结合了输入迭代器和输出迭代器的功能，既能读取又能写入元素，并且可以多次读取同一个元素。它==仅可以向前移动，仅支持自增操作（`++`）==，**也支持解引用（`*`）操作，还能进行相等（`==`）和不等（`!=`）比较**。
  >
  >    - **应用场景**：适用于需要对容器元素进行读写操作，且只需要单向遍历容器的场景，例如对单链表的遍历和操作。
  >
  > 4. **双向迭代器**（Bidirectional Iterator）
  >
  >    - **特点**：在向前迭代器的基础上，==增加了向后移动的功能，支持自减操作（`--`）==，可以方便地在容器中前后移动，进行元素的访问和修改。
  >
  >    - **应用场景**：常用于需要双向遍历容器的算法，如 `std::reverse` 算法用于反转容器中元素的顺序，就需要双向迭代器来从两端向中间进行元素交换。
  >
  > 5. **随机访问迭代器**（Random Access Iterator）
  >
  >    - **特点**：具有最强的功能，除了支持双向迭代器的所有操作外，==还支持随机访问元素，就像数组下标访问一样，可以通过偏移量直接访问容器中的任意元素==。支持加法（`+`）、减法（`-`）操作来计算迭代器之间的距离，也支持比较操作（`<`、`>`、`<=`、`>=`）来判断两个迭代器的相对位置。
  >
  >    - **应用场景**：适用于需要快速随机访问元素的算法，如 `std::sort` 算法对容器中的元素进行排序，通常要求迭代器具有随机访问能力，以便高效地进行元素的比较和交换。

### 3.流迭代器

#### 3.1 输出流迭代器

- **流迭代器是特殊的迭代器，其作用有：**

  1. 可以将输入/输出流作为**容器**看待(因为输入输出流都有**缓冲区**的概念，也可以视为存一些数据)，流迭代器可以用来访问输入输出流这种“容器”中的数据。

  2. STL 中有许多算法都是基于迭代器设计的，输入流迭代器和输出流迭代器使得这些算法能够直接应用于输入输出流。因此任何接受迭代器参数的算法都可以和流一起工作。

- **通过cpp参考文档查看输出流迭代器构造函数的说明：**

  <img src="..\0.TyporaPicture\image-20250102152744535.png" alt="image-20250102152744535" style="zoom:67%;" />

  > `std::ostream_iterator` 是模板类，定义在 `<iterator>` 头文件中，**有两个公开构造函数**：
  >
  > ```cpp
  > // 1. 无分隔符构造函数
  > ostream_iterator(ostream_type& __s);
  > 
  > // 2. 带分隔符构造函数
  > ostream_iterator(ostream_type& __s, const char* __delim);
  > ```
  >
  > 
  >
  > 尝试使用一下输出流迭代器，如下（使用了algorithm提供的==**copy函数**==）
  >
  > 最常用的一种使用方式：使用 `std::copy` 算法通过输入流迭代器从文件中读取数据，然后通过输出流迭代器将数据输出到控制台，就像操作普通容器一样
  >
  > ![image-20250318195617489](..\0.TyporaPicture\image-20250318195617489.png)
  >
  > <img src="..\0.TyporaPicture\image-20250102153042767.png" alt="image-20250102153042767" style="zoom:67%;" />
  >
  > 
  >
  > <img src="..\0.TyporaPicture\image-20250102152333957.png" alt="image-20250102152333957" style="zoom:67%;" />
  >
  > 其实结果很容易推测出来。**至此，我们发现又多了一种遍历容器元素的方式**，那么这个输出的效果是怎么实现的呢？

- **通过copy源码来认识如何将数据输出到控制台**

     1. 输出流迭代器的类模板形式：

         > **补充**
         >
         > `_Traits` 必须是一个类似 `std::char_traits` 的类，里面定义了一系列静态方法，告诉标准库如何处理字符，例如：
         >
         > - 怎么**比较**两个字符/字符串
         > - 怎么**复制/移动**字符序列
         > - 文件结束符 **EOF** 是哪个值
         > - 怎么**查找**字符长度
         >
         > 默认情况下，`_Traits` 取 `char_traits<_CharT>`，也就是**用 _CharT 对应的标准特性**。比如：
         >
         > - 当 `_CharT` 是 `char` 时，`_Traits` 默认为 `std::char_traits<char>`（窄字符规则）
         > - 当 `_CharT` 是 `wchar_t` 时，`_Traits` 默认为 `std::char_traits<wchar_t>`（宽字符规则）
     
         ```C++
         // 类模板定义
         // _Tp     : 要输出的数据类型（例如 int, string）
         // _CharT  : 字符类型（默认 char）
         // _Traits : 字符特性类（默认 char_traits<_CharT>）
         template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT> >
         class ostream_iterator {
         public:
             // 为方便使用，定义流类型的别名
             // （源码中一般会有这行，这里补充并注释）
             typedef basic_ostream<_CharT, _Traits> ostream_type;
         
             // ---------- 构造函数 ----------
             // 参数：
             //   __s : 输出流对象（如 std::cout）
             //   __c : 分隔字符串指针（如 " "），可为空指针（表示无分隔）
             // 初始化列表：
             //   _M_stream 指向输出流的指针
             //   _M_string 指向分隔字符串（浅拷贝，需保证生命周期）
             ostream_iterator(ostream_type& __s, const _CharT* __c) 
                 : _M_stream(&__s)   // 保存流地址
                 , _M_string(__c)    // 保存分隔符地址
             {}
         
             // ---------- 迭代器必需操作 ----------
             // 解引用操作符：标准要求返回自身引用
             // 这里不进行实际输出，仅返回迭代器本身
             ostream_iterator<_Tp>& operator*() { return *this; }
         
             // 前置递增：标准要求返回自身引用，不做额外操作
             ostream_iterator<_Tp>& operator++() { return *this; }
         
             // 后置递增：标准要求返回自身引用，不做额外操作
             ostream_iterator<_Tp>& operator++(int) { return *this; }
         
             // ---------- 核心赋值操作 ----------
             // 当执行 *it = value 时，实际调用此赋值运算符
             // 1. 将 value 输出到绑定的流中
             // 2. 如果分隔字符串非空，则再输出分隔字符串
             ostream_iterator<_Tp>& operator=(const _Tp& __value) { 
                 *_M_stream << __value;               // 输出数据，如: cout << 1
                 if (_M_string)                       // 判断分隔符是否存在
                     *_M_stream << _M_string;         // 输出分隔符，如: cout << "  "
                 return *this;                        // 返回自身引用，支持链式赋值
             }
         
         private:
             ostream_type* _M_stream;   // 指向关联的输出流
             const _CharT* _M_string;   // 指向分隔字符串（空指针表示无分隔）
         };
         ```
     
     1. copy函数的实现（cpp参考文档相关页直接给出）
     
        ```C++
        template<class InputIt, class OutputIt>
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                *d_first++ = *first++;
            }
            return d_first;
        }
        ```
     
     1. 以上述例子为参考进行分析

        ``` c++
        // copy(vec.begin(), vec.end(), osi);
        // first = vec.begin();
        // last = vec.end()
        // d_first = osi 
        OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
            while (first != last) {
                //需要查看ostream_iterator的后置++与解引用（相应的运算符重载函数） 
                *d_first++ = *first++;//++优先级高于解引用
            }
            return d_first;
        }
        
        //	*******分析过程*******
        osi = 1 // ostream_iterator调用operator=函数
                last
        1 5 9 7
        f ------> f
        ```

#### 3.2 输入流迭代器

- **构造函数**

  <img src="..\0.TyporaPicture\image-20250103091012302.png" alt="image-20250103091012302" style="zoom:67%;" />

- **使用示例**

  可以利用一个通用输入流对象初始化istream_iterator

  <img src="..\0.TyporaPicture\image-20250103090859551.png" alt="image-20250103090859551" style="zoom:67%;" />

  可能出现的段错误

  <img src="..\0.TyporaPicture\image-20250103114516852.png" alt="image-20250103114516852" style="zoom:67%;" />

  > **解析**
  >
  > `std::copy` 是一个**模板函数**，只有**唯一的通用原型**
  > 两个调用的区别：只是**模板参数类型不同**（编译器自动推导）
  >
  > 通用——第1个参数：起点迭代器；第2个参数：终点迭代器（尾后迭代器）
  >
  > 1. `std::copy(isi, istream_iterator<int>(), vec.begin());`
  >
  >    - 第一个参数 `isi`
  >
  >      绑定了标准输入 `cin` 的**有效输入迭代器**，代表**要读取的第一个数据的起始位置**，每次解引用 `*isi` 就会从键盘读一个 int
  >
  >    - 第二个参数 `istream_iterator<int>()`
  >
  >      这是**默认构造的流迭代器**，代表 **流结束标记（EOF）**，是遍历的**终止条件**。
  >
  >      当控制台没有数据可读时（Windows 按 `Ctrl+Z`，Linux/Mac 按 `Ctrl+D`），`isi` 就会等于这个终止迭代器，`copy` 停止循环
  >
  >    - 第三个参数错误
  >
  >      `std::copy` 的工作逻辑是：
  >
  >      ```cpp
  >      template<class InputIt, class OutputIt>
  >      OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
  >      {
  >          while (first != last) {
  >              *d_first++ = *first++; // 核心：直接对目标迭代器做赋值操作
  >              ++first;
  >              ++d_first;
  >          }
  >          return d_first;
  >      }
  >      ```
  >
  >      它会**直接对目标迭代器 `d_first` 执行赋值操作**，**不会自动帮你扩展容器的大小**
  >
  >      而代码里：
  >
  >      - `vec` 是空的（`size=0`），`vec.begin()` 指向的是一个**不存在的元素位置**
  >      - `std::copy` 试图向这个位置写入数据，就会越界访问内存 → 触发 **Segmentation fault**
  >
  >      ==为什么会段错误？==
  >
  >       把`vector<int>` 想象成一个数组：
  >
  >      - 空 `vector` 相当于一个长度为 0 的数组，没有分配任何可写入的元素空间
  >      - `vec.begin()` 就像指向数组第 0 个元素的指针，但这个元素根本不存在
  >      - `std::copy` 执行 `*d_first++ = *first++;` 时，相当于对一个空指针 / 无效地址做写入，直接触发段错误
  >
  >      ==修正方案==
  >
  >      要解决这个问题，需要让 `std::copy` 在写入时自动向 `vector` 添加元素。C++ 提供了`std::back_inserter`（属于插入迭代器），它会在每次赋值时调用 `push_back`，自动扩展容器
  >
  > 2. `copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));`
  >
  >    - 第一个参数：`vec.begin()`
  >
  >      - **类型**：`vector<int>` 的迭代器（**输入迭代器**，负责读数据）
  >
  >      - **作用**：**数据源的起始位置**
  >
  >      - **通俗理解**：从 vector 的**第一个元素**开始复制数据
  >
  >    - 第二个参数：`vec.end()`
  >
  >      - **类型**：`vector<int>` 的迭代器
  >      - **作用**：**数据源的尾后位置**（STL 固定规则：**前闭后开区间 `[begin, end)`**）
  >      - **通俗理解**：复制到 vector 末尾**就停止**，**不包含**这个位置
  >      - **关键**：这是 STL 所有算法的统一规则，不是这个函数独有！
  >
  >    - 第三个参数：`ostream_iterator<int>(cout, " ")`
  >
  >      - **类型**：**输出流迭代器**（**输出迭代器**，负责写数据）
  >
  >      - **作用**：**数据要写入的目标起始位置**
  >
  >      - **拆解细节**：
  >
  >        1. `ostream_iterator<int>`：专门往**输出流**写 `int` 数据的迭代器
  >
  >        2. `cout`：绑定控制台输出（写到屏幕）
  >
  >        3. `" "`：每写一个数字，**自动追加一个空格**
  >
  >           **对应之前知识点**：输出迭代器**只能写、不能读**
  >
  >    整行代码的执行流程
  >
  >    1. 从 `vec` 的第一个元素开始拿数据
  >    2. 一直拿到 `vec` 的最后一个元素（遇到 `vec.end()` 停止）
  >    3. 把每一个元素，**通过输出迭代器写到控制台**，并且数字之间用空格隔开

  正确使用（用到了一个函数==**back_inserter——生成(插入)迭代器适配器的快捷函数**==）

  > | 名称                       | 类型         | 作用                                               |
  > | -------------------------- | ------------ | -------------------------------------------------- |
  > | **`back_insert_iterator`** | **类模板**   | **迭代器适配器本体**，包装容器，实现尾插逻辑       |
  > | **`back_inserter`**        | **函数模板** | 辅助工具，**快速创建** `back_insert_iterator` 对象 |

  <img src="..\0.TyporaPicture\image-20250103114847667.png" alt="image-20250103114847667" style="zoom:67%;" />

- **源码**

  ```cpp
  // 模板参数：
  // _Tp    ：要从流中读取的数据类型
  // _CharT ：流使用的字符类型，默认 char
  // _Traits：字符特性类，默认 char_traits<_CharT>
  // _Dist  ：迭代器距离类型，通常 ptrdiff_t（这里未使用）
  template <class _Tp,
            class _CharT = char, class _Traits = char_traits<_CharT>,
            class _Dist = ptrdiff_t>
  class istream_iterator
  {
  public:
      // 为了方便使用，通常会有以下类型别名（原代码略）
      // typedef _Tp value_type;
      // typedef _Tp& reference;
      // typedef basic_istream<_CharT, _Traits> istream_type;
  
      //----------------------------------------------
      // 1. 默认构造函数 —— 创建“结束标记”迭代器
      //----------------------------------------------
      istream_iterator()
          : _M_stream(nullptr),   // 不关联任何输入流
            _M_ok(false)          // 标记读取失败，这是一个“尾后”迭代器
      {}
  
      //----------------------------------------------
      // 2. 带流引用的构造函数 —— 创建“开始”迭代器
      //    __s 通常是 cin 或文件流
      //----------------------------------------------
      istream_iterator(istream_type& __s)
          : _M_stream(&__s)       // 记录流的地址
      {
          _M_read();              // 立即尝试读取第一个元素，惰性求值
      }
  
      //----------------------------------------------
      // 核心读取函数：从流中提取一个数据项到 _M_value，
      // 并更新状态标记 _M_ok
      //----------------------------------------------
      void _M_read()
      {
          // 如果流指针有效且流本身处于可用状态，才尝试读取
          _M_ok = (_M_stream && *_M_stream) ? true : false;
  
          if (_M_ok)
          {
              // 执行输入操作：将流中的数据读入 _M_value
              *_M_stream >> _M_value;
  
              // 读取后再次检查流状态：
              // 如果读取成功（状态为 goodbit），_M_ok 保持 true；
              // 若遇到 EOF、类型不匹配等错误，流会变为非 goodbit，_M_ok 变为 false。
              _M_ok = *_M_stream ? true : false;
          }
      }
  
      //----------------------------------------------
      // 判断两个流迭代器是否“相等”
      // 用于结束条件判断
      //----------------------------------------------
      bool _M_equal(const istream_iterator& __y) const
      {
          // 两个迭代器相等当且仅当：
          // 1. 它们的有效标志位 _M_ok 相同（都为 true 或都为 false）
          // 2. 并且：
          //    - 如果 _M_ok 为 false（即双方都是结束迭代器），则认为相等（! _M_ok 为 true）；
          //    - 如果 _M_ok 为 true，则要求它们关联的是同一个流对象。
          // 这种设计使得：所有默认构造的迭代器彼此相等，且与任何已“读完”的流迭代器相等。
          return (_M_ok == __y._M_ok) && (!_M_ok || _M_stream == __y._M_stream);
      }
  
      //----------------------------------------------
      // 后置递增运算符：返回旧值，然后前进（读取下一个元素）
      //----------------------------------------------
      istream_iterator operator++(int)
      {
          istream_iterator __tmp = *this;  // 保存当前状态（含当前值 _M_value）
          _M_read();                       // 从流中读取下一个元素
          return __tmp;                    // 返回未递增前的副本
      }
  
      // 前置递增（通常也需实现，这里略）
      // istream_iterator& operator++() { _M_read(); return *this; }
  
      // 解引用操作符：返回当前缓存的元素
      reference operator*() const { return _M_value; }
  
  private:
      istream_type* _M_stream;  // 指向关联的输入流
      _Tp           _M_value;   // 缓存最近一次成功读取的值
      bool          _M_ok;      // 当前读取状态是否有效
  };
  
  //----------------------------------------------
  // 全局 operator!=：依赖 _M_equal 成员函数
  //----------------------------------------------
  inline bool operator!=(const istream_iterator& __x, const istream_iterator& __y)
  {
      return !__x._M_equal(__y);
  }
  
  //==============================================
  // 使用示例：std::copy(isi, istream_iterator<int>(), std::back_inserter(vec));
  //==============================================
  /*
   * 假如我们有：
   *   istream_iterator<int> isi(cin);     // 开始迭代器，构造时立刻读取第一个整数
   *   istream_iterator<int> end;          // 结束标记迭代器
   *
   * 调用 std::copy(isi, end, back_inserter(vec)) 实际执行的算法如下：
   */
  
  // first = isi （开始迭代器）
  // last  = istream_iterator<int>() （结束标记）
  // d_first = back_inserter(vec)  （输出迭代器，负责向 vec 末尾添加元素）
  OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
  {
      // 循环条件：first != last
      // 利用上述 operator!= 进行比较，本质是调用 first._M_equal(last)
      // 只要流还在有效状态且未遇到结束迭代器，循环就继续
      while (first != last)
      {
          // *d_first++ = *first++;
          // 分解步骤：
          // 1. *first   ：取出当前缓存的元素（上一次 _M_read 读到的值）
          // 2. *d_first++  = 值 ：将该值通过 back_insert_iterator 追加到容器，然后移动输出迭代器
          // 3. first++  ：后置递增，触发 _M_read()，尝试从流中读取下一个元素。
          //    若读取失败（EOF/错误），first 的 _M_ok 变为 false，
          //    导致下一次 while 条件判断时 first != last 变为 false，循环终止。
          *d_first++ = *first++;
      }
      return d_first;
  }
  
  // back_inserter 辅助函数：创建 back_insert_iterator 对象
  template <class _Container>
  inline back_insert_iterator<_Container> back_inserter(_Container& __x)
  {
      // back_insert_iterator 的 operator= 内部会调用 __x.push_back(value)
      return back_insert_iterator<_Container>(__x);
  }
  ```
  
  **back_insert_iterator(==迭代器适配器-类模板==)的实现**
  
  ```cpp
  template <class _Container>
  class back_insert_iterator {
  protected:
      _Container* container;  // 指向目标容器的指针
  
  public:
      // 在实际的 C++ 标准库中，还需要提供一些迭代器所需的类型别名，例如：
      // using iterator_category = output_iterator_tag;
      // using value_type      = void;
      // using difference_type = void;
      // using pointer         = void;
      // using reference       = void;
      // 因为它是输出迭代器，这些类型通常不重要，这里略去。
  
      //----------------------------------------------
      // 构造函数：接收容器引用，保存其地址
      // 例如：back_insert_iterator(vec) 会使 container = &vec
      // 注意：该构造函数通常声明为 explicit，防止意外的隐式转换
      //----------------------------------------------
      explicit back_insert_iterator(_Container& __x)
          : container(&__x)
      {}
  
      //----------------------------------------------
      // 赋值运算符：核心操作
      // 当执行 *it = value 时，实际调用本函数，
      // 将 value 追加到容器尾部。
      //----------------------------------------------
      back_insert_iterator<_Container>&
      operator=(const typename _Container::value_type& __value)
      {
          container->push_back(__value);   // 向关联容器尾部添加元素
          return *this;
      }
  
      // 移动赋值版本（C++11起），此处省略，原理类似，调用 push_back 的右值版本。
  
      //----------------------------------------------
      // operator* ：解引用操作
      // 对于纯输出迭代器，此操作通常返回迭代器自身，
      // 因为真正的工作发生在随后的赋值操作中。
      //----------------------------------------------
      back_insert_iterator<_Container>& operator*()
      {
          return *this;
      }
  
      //----------------------------------------------
      // operator++（前置）与 operator++(int)（后置）
      // 对于输出迭代器，递增操作一般也是空操作，
      // 返回自身即可，因为迭代器并不真正“移动”到下一个位置。
      //----------------------------------------------
      back_insert_iterator<_Container>& operator++()
      {
          return *this;
      }
  
      back_insert_iterator<_Container>& operator++(int)
      {
          return *this;
      }
  };
  
  // 辅助函数 back_inserter —— 创建 back_insert_iterator 的便捷接口
  // template <class _Container>
  // inline back_insert_iterator<_Container> back_inserter(_Container& __x)
  // {
  //     return back_insert_iterator<_Container>(__x);
  // }
  ```

### 4.迭代器适配器

#### 4.1 三组插入迭代器适配器

- **三组插入迭代器适配器**

  <img src="..\0.TyporaPicture\image-20250103181150482.png" alt="image-20250103181150482" style="zoom:67%;" />

  1. back_inserter是**便捷函数**，该函数返回类型是back_insert_iterator，它们的底层会调用容器的push_back

  2. front_inserter是函数，该函数的返回类型是front_insert_iterator，它们的底层会调用容器的push_front
  3. inserter是函数，该函数的返回类型是insert_iterator，它们的底层会调用容器的insert

- **简单示例：**

  将list的元素插入到vector尾部

  **除了以往的常规方式（遍历list的元素，再使用vector的push_back函数添加这些元素），还可以使用迭代器**

  <img src="..\0.TyporaPicture\image-20250106111219439.png" alt="image-20250106111219439" style="zoom:67%;" />

    > **上面两行copy语句是等价的，它们实现的功能一模一样，只是写法上的 “便捷版” 和 “完整版” 区别**
    >
    > 1. **`back_inserter(vec)` 是便捷函数**
    >
    >    `std::back_inserter` 是 C++ 标准库提供的一个**模板辅助函数**
    >
    >    它的作用就是帮你自动推导容器类型，生成对应的 `std::back_insert_iterator` 对象
    >
    >    底层实现：
    >
    >    ```cpp
    >    template <class Container>
    >    std::back_insert_iterator<Container> back_inserter(Container& c) {
    >        return std::back_insert_iterator<Container>(c);
    >    }
    >    ```
    >
    > 2. **`back_insert_iterator<vector<int>>(vec)` 是显式构造**
    >
    >    这是直接手动构造了一个 `back_insert_iterator` 模板类的对象，明确指定了容器类型为 `vector<int>`，效果和 `back_inserter(vec)` 完全一致
    >
    > 作为 `std::copy` 的第三个参数，它们的功能都是：
    >
    > - 生成一个**输出迭代器**
    > - 每次拷贝元素时，自动调用 `vec.push_back(元素)`，将元素追加到 `vec` 的末尾

    再将vector的元素插入到list头部

    <img src="..\0.TyporaPicture\image-20250106111304333.png" alt="image-20250106111304333" style="zoom:67%;" />

    <img src="..\0.TyporaPicture\image-20250106144924432.png" alt="image-20250106144924432" style="zoom:67%;" />

    从得到的结果可以想到，执行的过程是从头到尾遍历vector的元素，然后一次次执行了push_front函数

    > **补充**
    >
    > 1. 可不可以将list元素插入到vector头部呢？
    >
    >    - 可以把 list 的元素插到 vector 头部，但不能用 front_inserter，而且效率很低
    >
    >      1. 但是不能使用 front_inserter 往 vector 头插
    >
    >        `std::front_inserter` 内部调用的是 `push_front()`。
    >
    >        **vector 没有 push_front**，只有 list、deque 才有。
    >
    >        所以下面这种写法**编译不通过**：
    >
    >        ```cpp
    >        std::list<int> lst = {1,2,3};
    >        std::vector<int> vec;
    >        // 错误：vector 不能用 front_inserter
    >        std::copy(lst.begin(), lst.end(), std::front_inserter(vec));
    >        ```
    >
    >      2. 应该使用 insert + 反向迭代器
    >
    >        想把整个 list 一次性插到 vector 头部，可以用 `vec.insert`，并注意**顺序**：
    >
    >        ```cpp
    >        #include <vector>
    >        #include <list>
    >        #include <algorithm>
    >                  
    >        int main() {
    >            std::list<int> lst = {1,2,3};
    >            std::vector<int> vec = {10,20,30};
    >                  
    >            // 把 list 元素整体插到 vector 头部
    >            vec.insert(vec.begin(), lst.begin(), lst.end());
    >            // vec 现在：1,2,3,10,20,30
    >        }
    >        ```
    >
    >        如果希望**逆序插入**（类似 front_inserter 的效果）：
    >
    >        ```cpp
    >        vec.insert(vec.begin(), lst.rbegin(), lst.rend());
    >        // vec 变成：3,2,1,10,20,30
    >        ```
    >
    >
    >    - 效率问题与更好的方案
    >
    >      > vector 是**连续数组**，头部插入会让**所有元素后移**
    >      >
    >      > 每次 `insert(vec.begin(), ...)` 的复杂度是 **O(n)**
    >      >
    >      > 如果循环逐个头插：
    >      >
    >      > ```cpp
    >      > for (auto x : lst) vec.insert(vec.begin(), x);
    >      > ```
    >      >
    >      > 会变成 **O(n²)**，数据量大时很慢
    >
    >      1. **对于少量数据**：
    >
    >         直接用 `vec.insert(vec.begin(), lst.begin(), lst.end())` 无所谓
    >
    >      2. **而对于大量数据**：
    >
    >         - 先把 list 拷贝到临时 vector；
    >
    >         - 再 `reserve` 扩容；
    >
    >         - 最后 `insert` 一次性合并。
    >
    >      3. **频繁头插**：**别用 vector**，改用 `std::deque`（支持 O (1) push_front）
    >
    > 2. 将list的元素插入到set中
    >
    >    ![image-20240809164112172](..\0.TyporaPicture\image-20240809164112172-1733126659852-96.png)
    >
    > <font color=red>**所以：使用上述三种插入迭代器的时候，如果容器本身不具备对应插入函数的话，那么就不能乱用**</font>

- **copy、front_inserter、front_insert_iterator的源码：**

    ```cpp
    // ==============================================
    // 1. std::copy 算法的实现
    // 将 [first, last) 范围内的元素依次复制到 d_first 开始的位置
    // ==============================================
    template<class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        while (first != last) {
            // 核心循环：
            // *d_first++ = *first++;
            // 1. *first  : 获取当前输入位置的元素
            // 2. first++ : 输入迭代器前进（后置递增，返回原值后移动）
            // 3. *d_first++ = 值 : 将值赋给输出迭代器的当前位置，然后输出迭代器前进
            // 
            // 对于 front_insert_iterator，*d_first 返回迭代器自身，
            // ++ 也是空操作，真正的插入发生在赋值运算符中（调用 push_front）
            *d_first++ = *first++;
        }
        return d_first;
    }
    
    // ==============================================
    // 2. front_inserter 辅助函数
    // 用于方便地创建 front_insert_iterator 对象
    // ==============================================
    template <class _Container>
    inline front_insert_iterator<_Container> front_inserter(_Container& __x)
    {
        // 将容器的引用传递给 front_insert_iterator 的构造函数，
        // 使其持有指向该容器的指针。
        return front_insert_iterator<_Container>(__x);
    }
    
    // ==============================================
    // 3. front_insert_iterator 类模板
    // 输出迭代器，专用于在容器前端插入元素
    // ==============================================
    template <class _Container>
    class front_insert_iterator {
    protected:
        _Container* container;  // 指向目标容器的指针
    
    public:
        // ---- 迭代器特征类型定义 ----
        typedef _Container          container_type;
        typedef output_iterator_tag iterator_category; // 标记为输出迭代器
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;
    
        // 构造函数：接收容器引用，保存其地址
        // 使用 explicit 避免隐式转换
        explicit front_insert_iterator(_Container& __x) : container(&__x) {}
    
        // ---- 赋值运算符：核心操作 ----
        // 当执行 *it = value 时调用此函数
        front_insert_iterator<_Container>&
        operator=(const typename _Container::value_type& __value)
        {
            // 在容器头部插入元素
            // 要求容器支持 push_front 操作（如 list, deque, forward_list 等）
            container->push_front(__value);
            return *this;
        }
    
        // ---- 以下三个运算符是输出迭代器的接口要求，实现为空操作 ----
        // operator*：解引用，返回迭代器自身，以便后续赋值
        front_insert_iterator<_Container>& operator*() { return *this; }
    
        // operator++（前置）：前进到下一位置，在此无实际位置概念
        front_insert_iterator<_Container>& operator++() { return *this; }
    
        // operator++(int)（后置）：同样返回自身，维持链式语法兼容性
        front_insert_iterator<_Container>& operator++(int) { return *this; }
    };
    ```

#### 4.2 反向迭代器适配器

![image-20240809170644459](..\0.TyporaPicture\image-20240809170644459-1733126659852-95.png)

**注意遍历时偏移的方式，仍然是自增（只不过这里的自增对应的是向左移动）**

![image-20240809171255460](..\0.TyporaPicture\image-20240809171255460-1733126659853-99.png)

