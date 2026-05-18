#include <iostream>

using std::cout;
using std::endl;

/*
 * 多态: 统一指令, 针对不同的子类的对象, 表现出不同的行为
 *
 * 代码中的体现:
 * 继承的前提条件下, 父类型接收子类对象, 通过父类型的指针
 * 或者引用调用父子同名的虚函数, 体现出不同的子类行为
 *
 */

class Phone
{
public:
    virtual  // 虚函数
    void aiAssitant() = 0;

};

class Xiaomi : public Phone
{
public:
    // 在子类中重写虚函数
    virtual void aiAssitant()
    {
        cout << "小爱同学, 今天天气怎么样?" << endl;
    }
};

class Huawei : public Phone
{
public:
    virtual void aiAssitant()
    {
        cout << "小艺小艺, 今天星期几?" << endl;
    }
};

class Apple : public Phone
{

public:
    virtual void aiAssitant()
    {
        cout << "嘿siri, 今天晚上有没有作业?" << endl;
    }
};

class Vivo : public Phone
{
public:
    virtual void aiAssitant()
    {
        cout << "小v, 今天晚上有没有作业?" << endl;
    }
};


void test1()
{
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    Phone * p;
    // 父类型的指针或引用接收子对象
    p = &phone1;

    // 通过父类型的指针或引用调用同名的虚函数
    p->aiAssitant();

    p = &phone2;
    p->aiAssitant();

    p = &phone3;
    p->aiAssitant();
}

// 处理小米手机
void handlePhone1(Xiaomi * p)
{
    p->aiAssitant();
}

void handlePhone2(Apple * p)
{
    p->aiAssitant();
}

void handlePhone3(Huawei * p)
{
    p->aiAssitant();
}

void handlePhone4(Vivo * p)
{
    p->aiAssitant();
}


// 提供一个函数可以进行复用 处理所有的手机
// 扩展性更好
void handlePhone(Phone * p)
{   
    // Phone * p = apple
    p->aiAssitant();
}

void test2()
{
    Xiaomi phone1;
    Huawei phone2;
    Apple phone3;
    /* handlePhone1(&phone1); */
    /* handlePhone2(&phone3); */
    /* handlePhone3(&phone2); */
    handlePhone(&phone1);
    handlePhone(&phone2);
    handlePhone(&phone3);
}

int main(int argc, char * argv[])
{
    test1();
    /* test2(); */
    return 0;
}

