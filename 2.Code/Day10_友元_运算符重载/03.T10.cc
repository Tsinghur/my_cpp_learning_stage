#include <iostream>

using std::cout;
using std::endl;

class Data {
public:
    Data(int data)
    : _data(data)
    {}
    int getData() const {
        return _data;
    }
private:
    int _data;
};

class MiddleLayer {
public:
    MiddleLayer(Data * p)
    : _pdata(p)
    {}
    Data* operator->() { // 仅最内层返回对象指针
        return _pdata;
    }
    ~MiddleLayer() {
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }
private:
    Data * _pdata;
};

class ThirdLayer {
public:
    ThirdLayer(MiddleLayer * pm) 
    : _pml(pm)
    {}
    MiddleLayer& operator->() { // 除了最内层其余层均返回对象而不是对象指针，
                                // 这样能一直调用operator->()函数，而不是在当前层对象中通过->调用getData()，因为只有最内层才存在getData
        return *_pml;
    }
    ~ThirdLayer() {
        if (_pml) {
            delete _pml;
            _pml = nullptr;
        }
    }
private:
    MiddleLayer * _pml;
};

void test() {
    /* Data* p = new Data(1); */
    /* MiddleLayer m(p); //这样的话，在ThirdLayer的析构函数中就会发生delete一个栈对象—— 未定义行为 */
    /* ThirdLayer t(&m); */
    // 除了最外层（ThirdLayer）是栈对象，其余内层对象（MiddleLayer、Data）都必须用new创建在堆上
    // 假如部分内层对象改为引用或不需要释放的指针（即析构不需要delete），则它们也可以不是堆对象，但必须保证被引用对象的生命周期长于使用它的对象
    ThirdLayer t(new MiddleLayer(new Data(111)));
    // 多层 operator-> 重载的链条中，只有"终点站"返回指针，中间的每一站都必须返回类类型的对象（或引用），才能让链条继续传递下去
    cout << t->getData() << endl;
}

int main() {
    test();

    return 0;
}
