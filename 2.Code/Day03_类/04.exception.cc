#include <iostream>

using namespace std;

double division(double x,double y){
    if(y == 0){
        throw "Deivision by zero";
    }
    return x/y;
}

void test0(){
    double x = 100, y = 0;
    try{
        cout << "before" << endl;
        cout << division(x,y) << endl;//异常行后的代码不会执行
        cout << "after" << endl;
    }catch(const char * msg){ //catch的小括号里是类型
    	cout << "hello" << endl;
        cout << "hello," << msg << endl;
    }catch(double x){
        cout << "double" << endl;
    }catch(int x){
        cout << "int" << endl;
    }
    cout << "end test" << endl;
}

int main() {
    test0();

    return 0;
}
