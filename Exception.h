
#ifndef GCALC_EXECPTION_H
#define GCALC_EXECPTION_H

#include <set>
#include <memory>
#include <string>

namespace gcalc
{
    class Exception : public std::exception
    {
        std::string desc;

    public:
        Exception(std::string desc);
        ~Exception() = default;
        std::string what();
    };

} // namespace gcalc

#endif