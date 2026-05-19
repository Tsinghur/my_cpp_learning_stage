#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

template <typename T>
/* T two_add(T t1, T t2) { */
T two_add(const T& t1, const T& t2) {
    return t1 + t2;
}

template <>
/* set two_add<set>(set t1, set t2) { // error:std::set 本身是一个类模板，不是一个具体的类型 */
/* set<int> two_add<set<int>>(set<int> s1, set<int> s2) { // right */
set<int> two_add<set<int>>(const set<int>& s1, const set<int>& s2) { // 优化
    set<int> s;
    // 形式1
    /* auto it1 = s1.begin(); */
    /* auto it2 = s2.begin(); */
    /* while (it1 != s1.end() && it2 != s2.end()) { */
    /*     s.insert(*it1 + *it2); */
    /*     it1++; */
    /*     it2++; */
    /* } */
    /* auto it = it1 == s1.end() ? it2 : it1; */
    /* auto end = it1 == s1.end() ? s2.end() : s1.end(); */
    /* while (it != end) { */
    /*     s.insert(*it); */
    /*     it++; */
    /* } */
    // 形式2
    s = s1;
    s.insert(s2.begin(), s2.end());

    return s;
}

void test1() {
    cout << two_add(1, 2) << endl;
    cout << two_add(1.1, 2.2) << endl;
    set<int> s1{1, 2};
    set<int> s2{3, 4};
    set<int> s = two_add(s1, s2);
    for (auto& e : s) {
        cout << e << endl;
    }
}

int main() {
    test1();

    return 0;
}
