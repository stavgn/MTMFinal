
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
        std::string trim(std::string &str, std::string whitespace);

    private:
        std::string parseTerminalName(std::string cmd);
        std::string parseFileName(std::string filename);
        EvalCommand parseEvalExpression(std::string cmd);
        EvalCommand parseEvalExpression2(std::string cmd);
        PrintCommand parsePrintCommand(std::string cmd);
        SaveCommand parseSaveCommand(std::string cmd);
        bool is_valid_cmd_opener(std::string cmd, bool with_literal);
        DeleteCommand parseDeleteCommand(std::string cmd);
        EvalCommand builFindCommand(std::string terminal);
        LoadCommand handleLoadCommand(std::string cmd);
        OperationCommand handleComplementCommand(std::string cmd);
        EvalCommand handleGraphLiteralCommand(std::string cmd);
        int find_next_op_index(std::string current, std::string cmd, bool &isFound);
    };

} // namespace gcalc

#endif