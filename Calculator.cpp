#include "./Calculator.h"
#include "./Parser.h"
#include "./Exception.h"
#include "./Command.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace gcalc;
using namespace std;

Calculator::Calculator()
{
}

void Calculator::interactive()
{
    Parser parse = Parser();
    std::string cmd;
    while (true)
    {
        std::cout << "Gcalc>";
        std::getline(std::cin, cmd);
        try
        {
            if (parse.trim(cmd, " ") == "quit")
            {
                break;
            }
            parse.command(cmd, graphs, IContextParams());
        }
        catch (gcalc::Exception *e)
        {
            std::cout << "Error: " << e->what() << std::endl;
        }
        catch (gcalc::Exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

void Calculator::batch(std::string input, std::string output)
{
    Parser parse = Parser();
    std::ifstream in(input);
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(in.rdbuf());

    std::ofstream out(output);
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    std::string cmd;
    while (std::getline(std::cin, cmd))
    {
        try
        {
            if (parse.trim(cmd, " ") == "quit")
            {
                in.close();
                out.close();
                break;
            }
            parse.command(cmd, graphs, IContextParams());
        }
        catch (gcalc::Exception *e)
        {
            std::cout << "Error: " << e->what() << std::endl;
        }
        catch (gcalc::Exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
}