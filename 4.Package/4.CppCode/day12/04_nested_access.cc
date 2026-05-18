#include <iostream>

using std::cout;
using std::endl;

/*
 * 嵌套类的访问规则
 * 
 * 1.在外部类的外部访问内部类的成员
 *   public的内部类, 可以创建对象 , 通过对象.访问, public的成员可以访问, private不行, 除非友元
 *   private的内部类,不能直接创建对象, 因为没有权限, 除非使用友元
 *      然后再通过对象.方式进行访问 , public的成员可以访问, private不行,除非再使用友元
 *
 * 2.在外部类的内部 访问内部类的成员
 *      创建内部类的对象Inner inner; 通过对象.方式访问内部类的成员, public成员 Ok , private NO
 *      非要访问私有的 可以使用友元
 *      
 *      修饰内部类的权限是public或者是private已经无意义了 
 *
 * 3.在内部类的内部 访问外部类的成员
 *      可以直接创建外部类的对象Outer outer; 通过对象.方式进行访问
 *      不受外部类成员权限的影响
 */

// 外部类
class Outer
{
public:
    // 内部类
    class Inner1
    {
    public:
        void inner1Method1()
        {
            cout << "inner1Method1()" << endl;
            // 内部类的内部 访问外部类的成员
            // 创建外部类的对象
            Outer outer;
            outer.m_outerNum1;// public成员OK
            outer.m_outerNum2;// private OK
            outer.outerMethod1();
            outer.outerMethod2();
            // 无论外部类的成员是什么权限 都可以访问
        }
        int m_inner1Num1;

        friend void test1();
    private:
        void inner1Method2()
        {
            cout << "inner1Method1()" << endl;
        }
        int m_inner1Num2;

    };
private:
    // 内部类
    class Inner2
    {
    public:
        void inner2Method1()
        {
            cout << "inner2Method1()" << endl;
            // 内部类的内部 访问外部类的成员
            // 创建外部类的对象
            Outer outer;
            outer.m_outerNum1;
            outer.m_outerNum2;
            outer.outerMethod1();
            outer.outerMethod2();

        }
        int m_inner2Num1;
    private:
        void inner2Method2()
        {
            cout << "inner2Method1()" << endl;
        }
        int m_inner2Num2;

    };    

public:
    // 外部类的成员
    int m_outerNum1;
    void outerMethod1()
    {
        cout << "outerMethod1()" << endl;
        // 在外部类的内部 访问内部类的成员
        // 创建内部类对象
        // public修饰的内部类
        Inner1 inner1;
        inner1.m_inner1Num1;// public的成员OK
        /* inner1.m_inner1Num2;// private的成员No 除非友元*/
        inner1.inner1Method1();
        /* inner1.inner1Method2(); */


        // private修饰的内部类
        Inner2 inner2;
        inner2.m_inner2Num1; // public OK 
        /* inner2.m_inner2Num2;// private NO */ 
    }
private:

    void outerMethod2()
    {
        cout << "outerMethod1()" << endl;
    }
    int m_outerNum2;

    // 将test1声明为友元函数 为了能够在外部访问Inner2
    friend void test1();
};

void test1()
{
    // 在外部类的外部访问内部类的成员
    // 通过创建内部类的对象, 通过对象.方式访问
    // 使用类名作用域, 标记一下这个内部类是在哪个外部类中定义的
    // public修饰的Inner1
    Outer::Inner1 inner1;
    inner1.m_inner1Num1; // public修饰的成员OK
    inner1.m_inner1Num2; // private修饰的成员NO--->可以使用友元
    inner1.inner1Method1();
    inner1.inner1Method2();

    // private修饰的Inner2类
    // 创建内部类对象
    Outer::Inner2 inner2;
    inner2.m_inner2Num1;// public OK
    /* inner2.m_inner2Num2;// private No */ 
    inner2.inner2Method1();
    /* inner2.inner2Method2(); */
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}