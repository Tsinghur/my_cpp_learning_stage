# 文本查询程序

这个目录包含 3 个逐步演进的文本查询程序版本，目标是从最基础的词频统计，逐步过渡到带有查询结果封装、智能指针共享和交互式查询能力的现代 C++ 实现。

## 目录结构

```text
.
├── README.md
├── V1
│   ├── text_query_V1
│   └── text_query_V1.cc
├── V2
│   ├── text_query_V2
│   └── text_query_V2.cc
└── V3
    ├── text_query_V3
    └── text_query_V3.cc
```

## 整体演进路线

```text
V1: 词频统计
    map<string, int>

V2: 在词频统计基础上增加“行号索引 + 查询输出”
    map<string, int> + map<string, set<int>> + vector<string>

V3: 在 V2 基础上做面向对象重构
    TextQuery + QueryResult + shared_ptr + 交互式查询
```

## V1：基础词频统计

源码：`V1/text_query_V1.cc`

### 功能

- 读取文本文件中的单词
- 对单词做清洗：只保留字母字符，并统一转成小写
- 统计每个单词出现的次数
- 将统计结果输出到文件

### 核心设计

- `Dictionary` 类负责整个流程
- `read()`：读取文本并统计词频
- `store()`：将 `map<string, int>` 中的数据写入输出文件
- `cleanWord()`：移除标点和非字母字符，例如 `Hello,` 会被处理成 `hello`

### 数据结构

```cpp
map<string, int> m_dict;
```

键是单词，值是该单词出现的次数。

### 代码特点

- 这是最朴素的实现，只关心“单词出现了多少次”
- 不保留原始行内容，因此无法回答“这个单词出现在哪几行”
- `main()` 中输入文件路径是硬编码的：

```cpp
dictionary.read("/home/gzh/The_Holy_Bible.txt");
dictionary.store("dict2.txt");
```

因此这个版本更适合作为“词典统计程序”而不是完整查询程序。

### 编译运行

```bash
g++ -std=c++11 -Wall -Wextra -o V1/text_query_V1 V1/text_query_V1.cc
./V1/text_query_V1
```

运行前需要先把源码中的输入文件路径改成你本机实际存在的文本文件。

## V2：增加按词查询与行号追踪

源码：`V2/text_query_V2.cc`

### 功能

在 V1 的基础上，V2 不再只做词频统计，而是支持：

- 统计单词出现次数
- 记录单词出现过的所有行号
- 输出这些行号对应的完整文本内容

示例输出逻辑如下：

```text
---------------------------------------------
word occurs N times.
(line 3) ...
(line 8) ...
---------------------------------------------
```

### 核心设计

- `TextQuery` 类统一负责读取、建索引和查询
- 使用 `std::getline` 按行读取整个文件
- 使用 `std::istringstream` 对每一行再做单词切分
- `query()` 根据查询词输出词频和对应行内容

### 数据结构

```cpp
vector<string> m_lines;
map<string, set<int>> m_wordNumbers;
map<string, int> m_dict;
```

含义分别是：

- `m_lines`：保存文件每一行的原文
- `m_wordNumbers`：保存某个单词出现过的所有行号
- `m_dict`：保存某个单词出现的总次数

### 相比 V1 的改进

- 从“只统计次数”升级为“可以定位到原文行”
- 不再依赖硬编码查询词
- 支持命令行参数传入输入文件和查询单词
- 增加了文件打开失败时的报错处理

### 单词清洗规则

V2 的 `cleanWord()` 与 V1 基本一致：

- 只保留字母
- 转为小写
- 纯标点内容会被跳过

例如：

- `Hello,` -> `hello`
- `world!` -> `world`
- `C++` -> `c`

### 编译运行

```bash
g++ -std=c++11 -Wall -Wextra -o V2/text_query_V2 V2/text_query_V2.cc
./V2/text_query_V2 <文件路径> <查询词>
```

例如：

```bash
./V2/text_query_V2 article.txt china
```

### 局限

- 查询结果是直接在 `query()` 中输出的，数据与展示没有分离
- 一次程序运行只能查一个词
- 虽然功能已经更像“文本查询”，但类职责仍然比较集中

## V3：面向对象重构与现代 C++

源码：`V3/text_query_V3.cc`

V3 在功能层面延续 V2，但在结构上更接近《C++ Primer》中的经典 `TextQuery` 设计。

### 主要改进

- 引入 `QueryResult` 类封装查询结果
- `TextQuery::query()` 不再直接打印，而是返回结果对象
- 使用 `shared_ptr` 共享文件内容和行号集合，避免不必要拷贝
- 查询流程改成交互式：可连续查询多个单词，输入 `q` 退出
- `cleanWord()` 保留连字符 `-`，能更好处理 `state-of-the-art` 这类单词

### 类关系

```text
ifstream
   │
   ▼
TextQuery
   │ query(word)
   ▼
QueryResult
   │
   ▼
print(ostream&, QueryResult)
```

### `TextQuery` 的职责

- 构造时直接读取文件并建立索引
- 保存原始文本内容
- 保存单词到行号集合的映射
- 保存单词出现次数
- 对外提供 `query()` 接口

核心成员如下：

```cpp
shared_ptr<vector<string>> m_file;
map<string, shared_ptr<set<int>>> m_wordLineNumbers;
map<string, int> m_wordCounts;
```

这里的设计重点是：

- `m_file` 由多个查询结果共享
- 每个单词对应的行号集合也通过 `shared_ptr` 共享
- 若单词不存在，则返回一个静态的空集合 `nodata`

### `QueryResult` 的职责

`QueryResult` 是一个结果对象，用来保存：

- 查询词
- 出现次数
- 行号集合
- 原始文件内容

这样就把“查询数据的生产”和“结果的展示”拆开了。

### 输出逻辑

展示逻辑被单独放在友元函数 `print()` 中：

```cpp
ostream& print(ostream& os, const QueryResult& qr)
```

这意味着：

- `TextQuery` 只负责建立索引与查找
- `print()` 只负责格式化输出
- 结构比 V2 更清晰，后续更容易扩展成别的输出形式

### 交互方式

V3 通过 `runQuries()` 进入循环查询模式：

```text
enter word to look for, or q to quit:
```

用户可以连续输入多个单词，而不是像 V2 那样每次只查询一次。

### 单词清洗规则变化

V3 中：

```cpp
if (std::isalpha(c) || c == '-')
```

因此它会保留连字符，适合处理复合词，例如：

- `state-of-the-art` -> `state-of-the-art`

但像数字、其他标点仍然会被移除。

### 编译运行

```bash
g++ -std=c++11 -Wall -Wextra -o V3/text_query_V3 V3/text_query_V3.cc
./V3/text_query_V3 <文件路径>
```

例如：

```bash
./V3/text_query_V3 article.txt
```

进入程序后输入要查询的单词，输入 `q` 退出。

## 三个版本对比

| 版本 | 主要目标 | 是否保留原文行 | 是否支持查询 | 是否支持连续查询 | 关键特征 |
|------|----------|----------------|--------------|------------------|----------|
| V1 | 统计词频 | 否 | 否 | 否 | `map<string, int>` |
| V2 | 查询单词出现位置 | 是 | 是 | 否 | `vector + map + set` |
| V3 | 优化架构与共享数据 | 是 | 是 | 是 | `QueryResult + shared_ptr` |

## 这个目录适合学习的知识点

- `map`、`set`、`vector` 的组合使用
- 文本文件读取：`ifstream`、`getline`
- 行内分词：`istringstream`
- 单词清洗与大小写归一化
- 命令行参数处理
- 面向对象拆分职责
- `shared_ptr` 的共享所有权语义
- RAII 风格的资源管理
- 查询结果对象与输出逻辑分离

## 可继续改进的方向

- 将 V1 也改成支持命令行文件路径输入
- 统一三个版本的输入清洗规则
- 把 `runQuries()` 更名为 `runQueries()`
- 为查询结果增加“不存在单词”的统一输出格式
- 将源码拆分为头文件和实现文件
- 为单词清洗、查询结果和异常输入补充测试

## 总结

这三个版本展示了一条很典型的学习路径：

- V1 先解决“统计”
- V2 再解决“定位与查询”
- V3 最后解决“抽象、复用和现代 C++ 风格”

如果把它们连起来看，重点不只是功能增加，更重要的是代码组织方式在逐步变得更合理。
