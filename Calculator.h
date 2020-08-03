
#ifndef GCALC_CALCULATOR_H
#define GCALC_CALCULATOR_H

#include <set>
#include <memory>
#include "./Graph.h"

namespace gcalc
{
    class Calculator
    {
        std::set<std::shared_ptr<Graph>> graphs;

    public:
        Calculator();
        ~Calculator() = default;
        void interactive();
        void batch(std::string src, std::string out);
    };

} // namespace gcalc

#endif