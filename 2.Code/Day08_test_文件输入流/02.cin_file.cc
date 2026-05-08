#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream ifs("test.c");
    string line;
    /* while (getline(ifs, line)) { */
    /* while (getline(ifs, line).good()) { */
    while (!getline(ifs, line).eof()) {
        cout << line << endl;
    }

    return 0;
}
