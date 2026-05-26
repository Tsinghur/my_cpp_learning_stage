#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::remove_if;
using std::bind1st;
using std::less;
using std::copy;
using std::ostream_iterator;

void test1() {
    vector<int> box{1, 2, 3, 4, 5};
    // auto it = remove_if(box.begin(), box.end(), less()); // 报错，因为less是二元函数对象，而remove_if要求绑定的是一个一元函数对象
    auto it = remove_if(box.begin(), box.end(), bind1st(less<int>(), 3)); // bind1st要求绑定的是一个有嵌套类型定义的二元函数对象,比如 std::less<int>
                                                                          // 所以std::less()必须要有模板参数即std::less<int>()
    box.erase(it, box.end());
    copy(box.begin(), box.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main() {
    test1();
    
    return 0;
}