# Day14_关联式容器-set&map

## 一、关联式容器-set

1. **特点**

   - set中存放的元素是唯一的，不能重复
   - **默认按元素进行升序排列**

2. **使用场景**

   - 去重
   - 排序

3. **set的构造**

   包含在头文件< set >，打开C++参考文档，主要关注这样的几个构造函数

   ![image-20241206105537432](..\0.TyporaPicture\image-20241206105537432.png)

   ```cpp
   // set容器的构造
   /*
   关联容器初始化最好不要使用()
   std::set<int> box(1); // error：set没有「接收单个数值」的构造，而vector(5)合法：vector有「指定元素个数」的构造
   std::set<int> box({1}); // right
   */
   void test1() {
       // 1.无参构造函数—— >空容器
       std::set<Student> box1;
       // 2.初始化列表方式
       /* std::set<Student> box2(Student{1, "zs", 18}); // error */
       /* std::set<Student> box2({Student{1, "zs", 18}}); // right */
       std::set<Student> box2{Student{1, "zs", 18}};
       // std::set<Student> box2{{1, "zs", 18}};
       std::set<Student> box{{1, "zs", 18}, {3, "ww", 20}, {2, "ls", 19}};
       // 3.拷贝构造
       std::set<Student> box3 = box2;
       // 4.迭代器方式
       std::set<Student> box4(box.begin(), box.end());
   }
   ```

4. **set的查找操作**

   1. count成员函数

      ![image-20241206115827359](..\0.TyporaPicture\image-20241206115827359.png)

      **参数key**：要查找的数据元素

      **返回值(类型size_type)**：元素数，有就返回1，没有就返回0

   2. find成员函数

      ![image-20241206115853634](..\0.TyporaPicture\image-20241206115853634.png)

      **参数key**：要查找的数据元素

      **返回值(类型iterator)**：如果找到返回对应元素的迭代器，没找到返回end()获取的迭代器

5. **set的插入操作**

   - pair

       pair定义在头文件<utility>中，类似于结构体，可以存储两种不同类型的变量

       当然，C++中结构体已经演变为了类，所以可以认为一个特定的pair是一个类，包含两个对象成员(它们的类型在定义pair时给出)

       ==**pair的对象成员如何访问**==

       ```cpp
       // pair：存储一对数据，first、second
       std::pair<string, int> p{"age", 20};
       cout << p.first << endl;
       cout << p.second << endl;
       ```
       
   - 插入单个元素

     ![image-20231031163352909](..\0.TyporaPicture\image-20231031163352909.png)

     insert函数的第一种形式中：
     **参数：key**
     **返回值：pair类型(包含一个对应set的迭代器和一个bool值)**

     插入成功：返回<span style=color:red;background:yellow>**插入元素对应迭代器  **</span> 和 <font color=red>**true**</font>
     插入失败：返回<span style=color:red;background:yellow>**阻止插入的元素(原本就有的这个元素)对应迭代器**</span> 和 <font color=red>**false**</font>
     
     ```cpp
     std::set<Student> box;
     box.insert(Student{2, "zs", 18});
     /* box.insert({2, "zs", 18}); */
     
     std::set<int> box;
     /* box.insert(100); // 重复插入就会插入失败 */
     std::pair<std::set<int>::iterator, bool> p2 = box.insert(100);
     if (p2.second) {
         cout << "insert success" << endl;
         cout << *p2.first << endl;
     } else {
         cout << "insert failed" << endl;
     }
     ```
     
   - 插入多个元素

     ![image-20241206152508731](..\0.TyporaPicture\image-20241206152508731.png)

     1. 传入大括号列表，尝试插入列表中的元素
     2. 传入两个迭代器(首迭代器和尾后迭代器)，尝试插入这两个迭代器范围中的元素；**[ , )左闭右开区间**

     ```cpp
     // 批量数据插入
     // 1.初始化列表方式
     std::set<Student> box;
     /* box.insert({1, "ls", 19}, {"3", "ww", 20}); // error */
     box.insert({{1, "ls", 19}, {3, "ww", 20}}); // right
     // 2.还可使用迭代器方式
     std::set<int> box1{10, 11, 12};
     std::set<int> box2;
     box2.insert(box1.find(11), box1.end());
     ```

6. **set的删除操作**

  ```cpp
  // set容器的数据删除：erase成员函数
  std::set<int> box{1, 2, 3, 4, 5};
  auto it = box.begin();
  it++;
  it++;
  box.erase(it); // 3被删除
  ```

## 二、关联式容器-map

1. **特点**
   - **有序容器**：`std::map` 会按照键的大小顺序对元素进行排序，==**默认按键(key)升序排序**==。如果需要降序排序，可以使用自定义比较函数
   - **唯一的键**：`std::map` 中的==**每个键(key)必须是唯一的(value无所谓)**==。如果你尝试插入一个已有键的元素，插入操作将不会成功
   - **键和值**：**每个键都会关联一个值，类型为 `pair<const Key, T>`**，其中 `Key` 是键的类型，`T` 是值的类型——即**存的是pair对象(一对数据)**
   - **自动排序**：元素会根据键(key)的顺序自动排序, 也可以自定义排序(后面学)
   - **支持迭代器**：你可以通过迭代器遍历 `map` 中的元素

2. **应用场景**

   1. 数据是 **一个键对应一个值**

   2. 需要 **通过键快速找值**

   3. 需要 **键自动排序 / 去重**

   4. 需要 **方便地修改 / 新增键值对**

3. **map的构造**

   map中**存放的元素的类型是pair类型（键值对）**，构造map需要关注三种方式，也可以把它们结合到一起

   ```cpp
   // map的构建
   void test1() {
       // 1.无参构造
       std::map<int, string> m1;
       // 2.通过初始化列表方式构造
       std::map<int, string> m2({
           std::pair<int, string>{2, "zs"},
           std::pair<int, string>{1, "ls"},
           std::pair<int, string>{3, "ww"}
       }); // ()可省略，在初始化时即构造函数中{}有()的功效
           // ！但是，不能外层是{}内层是()，这样的话只能成功插入{3, "ww"}
       // 初始化列表方式的简写形式
       std::map<int, string> m3{
           {2, "zs"},
           {1, "ls"},
           {3, "ww"}
       };
       // 3.通过make_pair创建一个pair对象，其为函数—— 所以{}替换为()
       std::map<int, string> m4{
           std::make_pair(2, "zs"),
           std::make_pair(1, "ls"),
           std::make_pair(3, "ww")
       };
       // 4.通过拷贝构造函数
       /* std::map<int,string> m5 = m4; */
       /* std::map<int,string> m5(m4); */
       std::map<int,string> m5{m4};
       // 5.通过迭代器方式构建
       /* std::map<int,string> m6{(m5.begin(), m5.end())}; // error */
       /* std::map<int,string> m6({m5.begin(), m5.end()}); // right */
       /* std::map<int,string> m6{m5.begin(), m5.end()}; // right */
       std::map<int,string> m6(m5.begin(), m5.end()); // 最标准做法
   }
   ```

4. **map的查找操作**

   根据key值在map中进行查找

   - `count`函数的返回值：如果找到返回1，如果没找到返回0（size_t类型）
   - `find`函数的返回值：如果找到返回相应元素的迭代器，如果没找到返回end( )的结果

   ```cpp
   void checkFind(map<int,string>& rhs, int key) {
       // 完整类型
       // map<int,string>::iterator it = rhs.find(key);
       // auto简化
       auto it = rhs.find(key);
       if (it != rhs.end()) {
           cout << it->first << "=" << it->second << endl;
       } else {
           cout << "not stroe" << endl;
       }
   }
   ```

5. **map的插入操作**

   ![image-20241206175902177](..\0.TyporaPicture\image-20241206175902177.png)

   - 插入单个元素

     **返回值**是一个pair（第一个对象成员是map元素相应的迭代器，第二个对象成员是bool值）

     ```cpp
     std::map<int, string> m;
     // 单个数据的插入
     /* m.insert(3, "ww"); // error */
     /* m.insert{3, "ww"}; // error */
     /* m.insert(pair<int,string>{3, "ww"}); // right */
     m.insert({3, "ww"}); // 上一行简写
     ```

   - 插入多个元素

     1. 初始化列表方式
     2. 迭代器方式

     ```cpp
     // 批量插入
     // 1.初始化列表方式
     std::map<int, string> m;
     /* m.insert({1, "zs"}, {2, "ls"}); // error */
     /* m.insert{{1, "zs"}, {2, "ls"}}; // error */
     m.insert({{1, "zs"}, {2, "ls"}}); // right
     // 2.迭代器方式
     std::map<int, string> m2;
     m2.insert(m.begin(), m.end());
     ```

6. **map的下标操作operator[]——根据key获取对应value**

   - map下标操作**返回**的是map中元素(pair)的**value**

   - **下标访问运算符中的值代表key**，而**不是传统意义上的下标**

   - 如果进行下标操作时下标值传入一个不存在的key，那么会将这个key和空的value**（默认的value值）**插入到map中

     > ```cpp
     > // map对象[不存在的键];
     > // 1.插入这个新键（key）
     > // 2.给对应的值（value）赋默认值
     > //      string 的默认值 = 空字符串 ""
     > //      int 的默认值 = 0
     > ```

   - **下标访问可以进行写操作**（**只对value进行写操作**，**不影响排序**）

> map的元素是pair(key-value)，**key和value的类型可以自由选择**，但**要保证key的类型可以进行判重和排序**
>
> ```cpp
> // key:char  value:string
> map<char,string> container2{
>     {'a',"abc"},
>     {'c',"bcd"},
>     {'d',"eee"},                                          
>     {'b',"fff"}
> };
> // 根据key访问对应value
> cout << container2['a'] << endl;
> cout << container2['b'] << endl;
> cout << container2['d'] << endl;
> ```
>
> 只有key为自定义类型时，才需要对operator<重载

## 三、补充

1. **关于[]下标访问**
   - map 是「查字典」（拼音→汉字），所以需要下标 `[]`
   - set 是「花名册」（只有名字），下标没用，所以不支持