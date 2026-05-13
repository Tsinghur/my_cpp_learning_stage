# Easy

## 1.[1757. 可回收且低脂的产品](https://leetcode.cn/problems/recyclable-and-low-fat-products/)

```mysql
SELECT product_id 
FROM Products 
WHERE low_fats = 'Y' AND recyclable = 'Y';
```

## 2.[584. 寻找用户推荐人](https://leetcode.cn/problems/find-customer-referee/)

```mysql
SELECT name
FROM Customer
WHERE referee_id != 2 OR referee_id IS NULL; # 或 <=> NULL
-- != null 不合法
-- 要找 NULL 值：必须用 IS NULL 或 MySQL 的 <=> NULL
-- 要找非 NULL 值：用 IS NOT NULL
```

## 3.[595. 大的国家](https://leetcode.cn/problems/big-countries/)

```mysql
SELECT name, population, area
FROM World
WHERE area >= 3000000 OR population >= 25000000;
```

## 4.[[+]1148. 文章浏览 I](https://leetcode.cn/problems/article-views-i/)

```sql
Views 表：
+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| article_id    | int     |
| author_id     | int     |
| viewer_id     | int     |
| view_date     | date    |
+---------------+---------+
此表可能会存在重复行。（换句话说，在 SQL 中这个表没有主键）
此表的每一行都表示某人在某天浏览了某位作者的某篇文章。
请注意，同一人的 author_id 和 viewer_id 是相同的。

请查询出所有浏览过自己文章的作者。
结果按照作者的 id 升序排列。

查询结果的格式如下所示：
示例 1：
输入：
Views 表：
+------------+-----------+-----------+------------+
| article_id | author_id | viewer_id | view_date  |
+------------+-----------+-----------+------------+
| 1          | 3         | 5         | 2019-08-01 |
| 1          | 3         | 6         | 2019-08-02 |
| 2          | 7         | 7         | 2019-08-01 |
| 2          | 7         | 6         | 2019-08-02 |
| 4          | 7         | 1         | 2019-07-22 |
| 3          | 4         | 4         | 2019-07-21 |
| 3          | 4         | 4         | 2019-07-21 |
+------------+-----------+-----------+------------+
输出：
+------+
| id   |
+------+
| 4    |
| 7    |
+------+
```

```mysql
SELECT DISTINCT author_id AS id
FROM Views
WHERE author_id = viewer_id ORDER BY author_id ASC;
-- 不要忘记输出时起别名
-- 只有 SELECT 子句中定义的别名，才会成为查询结果中显示的列名
```

## 5.[[+]1683. 无效的推文](https://leetcode.cn/problems/invalid-tweets/)

```mysql
SELECT tweet_id
FROM Tweets
WHERE CHAR_LENGTH(content) > 15;
```
