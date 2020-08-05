
#ifndef GCALC_CALCULATOR_H
#define GCALC_CALCULATOR_H

#include <map>
#include "./Graph.h"

namespace gcalc
{
    class Calculator
    {

        std::map<std::string, std::shared_ptr<Graph>> graphs;

    public:
        Calculator();
        ~Calculator() = default;
        void interactive();
        void batch(std::string input, std::string output);

        //void batch(std::string src, std::string out);
    };

} // namespace gcalc

#endif