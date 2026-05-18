#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


/*
 * 继承的意义:
 * 子类可以复用父类中的成员
 *
 */

//父类 或者 基类 
class Animal
{
public:
    string name;
    int age;
    void eat()
    {
        cout << "eat ...." << endl;
    }
};


// Dog类继承了Animal
// 子类 或者 派生类
class Dog : public Animal
{

};

class Cat : public Animal
{

};


void test1()
{
    Dog dog;
    dog.eat();

    Cat cat;
    cat.eat();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

