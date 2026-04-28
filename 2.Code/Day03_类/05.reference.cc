#include <iostream>

using namespace std;

void test() {

}

int main() {
    static int hot = 200;
    int & rad = hot;
    hot = hot + 100;
    cout << rad << endl;

    return 0;
}

