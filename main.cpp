#include "./Calculator.h"
#include "./Exception.h"
#include <iostream>

using namespace gcalc;

int main(int argc, char **argv)
{
    Calculator calc = Calculator();
    if (argc == 1)
    {
        calc.interactive();
    }
    if (argc == 3)
    {
        calc.batch(argv[1], argv[2]);
    }
    else
    {
        throw Exception("False num of args");
    }
    return 0;
}
