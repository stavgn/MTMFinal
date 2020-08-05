#include "./Exception.h"

using namespace gcalc;
using namespace std;

Exception::Exception(std::string desc) : desc(desc)
{
}
std::string Exception::what()
{
    return desc;
}