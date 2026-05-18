#include "Line.hpp"
#include <iostream>

using std::cout;
using std::endl;

void test1()
{
    Line line{1,2,3,4};
    line.printLine();
}

int main(int argc, char * argv[])
{
    test1();
    return 0;
}

