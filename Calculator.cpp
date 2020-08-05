#include "./Calculator.h"
#include "./Parser.h"
#include "./Exception.h"
#include "./Command.h"
#include <string>
#include <iostream>

using namespace gcalc;
using namespace std;

Calculator::Calculator()
{
}

void Calculator::interactive()
{
    Parser parse = Parser();
    std::string cmd;
    while (cmd != "quit")
    {
        std::cout << "Gcalc>";
        std::getline(std::cin, cmd);
        try
        {
            parse.command(cmd, graphs, IContextParams());
        }
        catch (gcalc::Exception *e)
        {
            std::cout << "Error: " << (*e).what() << std::endl;
        }
    }

    // quit program; destroy;
}