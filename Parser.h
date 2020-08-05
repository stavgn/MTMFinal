
#ifndef GCALC_PARSER_H
#define GCALC_PARSER_H

#include <set>
#include <memory>
#include <string>
#include "./Command.h"

using std::shared_ptr;

namespace gcalc
{
    class Parser
    {
        std::string literals[1] = {"quit"};

    public:
        Parser();
        ~Parser() = default;
        void command(std::string cmd, std::map<std::string, shared_ptr<Graph>> &context, IContextParams params);

    private:
        std::string parseTerminalName(std::string cmd);
        std::string trim(std::string &str, std::string whitespace);
        EvalCommand parseEvalExpression(std::string cmd);
        PrintCommand parsePrintCommand(std::string cmd);
    };

} // namespace gcalc

#endif