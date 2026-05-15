#include <iostream>

using std::cout;
using std::endl;

class Animal {
public:
    void speak() {
        cout << "Animal speak" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() {
        cout << "Dog barks" << endl;
    }
};

int main() {
    Dog dog;
    dog.speak();
    dog.Animal::speak();

    return 0;
}
