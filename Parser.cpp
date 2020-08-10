#include "./Parser.h"
#include "./Command.h"
#include "./Exception.h"
#include "./Helpers.h"
#include <iostream>

using namespace gcalc;
using namespace std;
using std::shared_ptr;

Parser::Parser()
{
}

std::string Parser::trim(std::string &str, std::string whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    int strEnd = str.find_last_not_of(whitespace);
    int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

bool Parser::is_valid_cmd_opener(std::string cmd, bool with_literal)
{
    std::string chars[9] = {"+", "^", "-", "<", ">", "|", "*", "{", "}"};

    for (int i = 0; i < (with_literal ? 7 : 9); i++)
    {
        if (cmd.find(chars[i]) != string::npos)
        {
            return false;
        }
    }
    return true;
}

std::string Parser::parseTerminalName(std::string terminal)
{
    terminal = trim(terminal, " ");
    if (terminal.find(" ") != string::npos || terminal == "")
    {
        throw Exception("Bad Syntax. Bad Terminal name. space or empty");
    }
    return terminal;
}

int Parser::find_next_op_index(std::string current, std::string cmd, bool &isFound)
{
    char chars[4] = {'+', '^', '-', '*'};
    unsigned int i;
    if (current == "!" && cmd[1] == '(')
    {
        i = 1 + findClosingParen(cmd, 1);
    }
    else if (cmd.substr(0, 5) == "load " || cmd.substr(0, 5) == "load(")
    {
        int open = cmd.find_first_of('(');
        i = 1 + findClosingParen(cmd, open);
    }
    else
    {
        i = 0;
    }
    for (; i < cmd.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (cmd[i] == chars[j])
            {
                isFound = true;
                return i;
            }
        }
    }
    isFound = false;
    return 0;
}

std::string Parser::parseFileName(std::string filename)
{
    filename = trim(filename, " ");
    if (filename == "")
    {
        throw Exception("Bad Syntax. Bad Terminal name. space or empty");
    }
    return filename;
}

OperationCommand Parser::handleComplementCommand(std::string cmd)
{
    EvalCommand find;
    if (cmd[1] == '(')
    {
        find = parseEvalExpression(cmd.substr(1));
    }
    else
    {
        find = builFindCommand(cmd.substr(1));
    }
    return OperationCommand(find, find, "!");
}

EvalCommand Parser::builFindCommand(std::string terminal)
{
    terminal = trim(terminal, " ");
    EvalCommand eval = EvalCommand();
    if (terminal.substr(0, 5) == "load " || terminal.substr(0, 5) == "load(")
    {
        LoadCommand load = handleLoadCommand(terminal);
        eval.addCommand(load);
        return eval;
    }
    if (terminal[0] == '!')
    {
        OperationCommand op = handleComplementCommand(terminal);
        eval.addCommand(op);
        return eval;
    }
    if (terminal[0] == '{')
    {
        return handleGraphLiteralCommand(terminal);
    }
    FindGraphCommand find(parseTerminalName(terminal), "");
    eval.addCommand(find);
    return eval;
}

LoadCommand Parser::handleLoadCommand(std::string cmd)
{
    if (cmd[cmd.find_first_not_of(" ", 4)] != '(')
    {
        throw Exception("Bad Syntax. load function");
    }
    if (cmd[6] == ')')
    {
        throw Exception("Bad Syntax. Empty file name");
    }
    if (cmd.find(")") == string::npos)
    {
        throw Exception("Bad Syntax. load function is not closed.");
    }
    std::string filename = cmd.substr(cmd.find_first_not_of(" ", 4) + 1, cmd.find(")") - cmd.find_first_not_of(" ", 4) - 1);
    if (filename.find(',') != string::npos)
    {
        throw Exception("Bad Syntax. no filename with comma allowed");
    }
    return LoadCommand(parseFileName(filename));
}

EvalCommand Parser::handleGraphLiteralCommand(std::string cmd)
{
    cmd = trim(cmd, " ");
    EvalCommand eval = EvalCommand();
    if (cmd.find("{") != string::npos && cmd.find("}") != string::npos && cmd.find("{") < cmd.find("}"))
    {
        std::string remainder = cmd.substr(cmd.find("}") + 1);
        if (trim(remainder, " ") != "")
        {
            throw Exception("Bad Syntax. Invalid Graph Literal definition.");
        }

        std::string graph_literal = cmd.substr(cmd.find("{") + 1, cmd.find("}") - cmd.find("{") - 1);
        if (trim(graph_literal, " ") == "" || trim(graph_literal, " ") == "|")
        {
            return eval;
        }

        std::string vertices = cmd.substr(cmd.find("{") + 1, (cmd.find("|") == string::npos ? cmd.find("}") : cmd.find("|")) - cmd.find("{") - 1);
        while (true)
        {
            CreateAndAssignVertexCommand vertex = CreateAndAssignVertexCommand(parseTerminalName(vertices.substr(0, vertices.find(","))));
            eval.addCommand(vertex);
            if (vertices.find(",") == string::npos)
            {
                break;
            }
            vertices = vertices.substr(vertices.find(",") + 1);
        }
        if (cmd.find("|") == string::npos)
        {
            return eval;
        }
        std::string edges = cmd.substr(cmd.find("|") + 1, cmd.find("}") - cmd.find("|") - 1);
        while (true && trim(edges, " ") != "")
        {
            if (edges.find("<") == string::npos || edges.find(">") == string::npos)
            {
                throw Exception("Bad Syntax. Invalid Edge definition.");
            }
            std::string firstVertex = parseTerminalName(edges.substr(edges.find("<") + 1, edges.find(",") - edges.find("<") - 1));
            std::string secondVertex = parseTerminalName(edges.substr(edges.find(",") + 1, edges.find(">") - edges.find(",") - 1));
            CreateAndAssignEdgeCommand edge = CreateAndAssignEdgeCommand(firstVertex, secondVertex);
            eval.addCommand(edge);
            edges.replace(0, edges.find(">") + 1, "");
            if (trim(edges, " ") == ",")
            {
                throw Exception("Bad Syntax. Invalid Edge definition. Extra comma");
            }
            if (edges.find(",") == string::npos)
            {
                if (trim(edges, " ") == "")
                {
                    break;
                }
                throw Exception("Bad Syntax. Invalid Edge definition. missing comma");
            }
            edges = edges.substr(edges.find(",") + 1);
        }
        return eval;
    }
    throw Exception("Bad Syntax. Invalid Graph literal definition.");
}

EvalCommand Parser::parseEvalExpression(std::string cmd)
{
    if (cmd == "")
    {
        throw Exception("Bad Syntax. Empty/Incomplete expression found.");
    }

    EvalCommand eval = EvalCommand();
    EvalCommand prependEval = EvalCommand();
    std::string selectedOp = "";
    cmd = trim(cmd, " ");

    for (unsigned int i = 0; i < cmd.size(); i++)
    {
        std::string s = char_to_string(cmd[i]);
        if (!is_valid_cmd_opener(s, true))
        {
            throw Exception("Bad Syntax. operations abuse.");
        }

        if (s == " ")
        {
            continue;
        }

        if (selectedOp != "")
        {
            EvalCommand rstatement;
            EvalCommand nextPrependEval;

            if (s == "(")
            {
                int matchingClosingBracket = findClosingParen(cmd, i);
                bool isFound;
                int nextOpIndex = find_next_op_index(s, cmd.substr(matchingClosingBracket), isFound) + matchingClosingBracket;
                rstatement = parseEvalExpression(cmd.substr(i + 1, matchingClosingBracket - i - 1));

                if (!isFound)
                {
                    eval.addCommand(OperationCommand(prependEval, rstatement, selectedOp));
                    break;
                }

                nextPrependEval.addCommand(OperationCommand(prependEval, rstatement, selectedOp));
                prependEval = nextPrependEval;
                selectedOp = cmd.substr(nextOpIndex, 1);
                i = nextOpIndex;
                continue;
            }
            else
            {
                bool isFound;
                int nextOpIndex = find_next_op_index(s, cmd.substr(i), isFound) + i;
                if (!isFound)
                {
                    rstatement = builFindCommand(cmd.substr(i));
                }
                else
                {
                    rstatement = builFindCommand(cmd.substr(i, nextOpIndex - i));
                }
            }
            bool isFound;
            int nextOpIndex = find_next_op_index(s, cmd.substr(i), isFound) + i;
            if (!isFound) //case: this is the last op in cmd
            {
                eval.addCommand(OperationCommand(prependEval, rstatement, selectedOp));
                break;
            }
            nextPrependEval.addCommand(OperationCommand(prependEval, rstatement, selectedOp));
            prependEval = nextPrependEval;
            selectedOp = cmd.substr(nextOpIndex, 1);
            i = nextOpIndex;
            continue;
        }
        if (s == "(")
        {
            int matchingClosingBracket = findClosingParen(cmd, i);
            std::string ParenExpression = cmd.substr(i + 1, matchingClosingBracket - i - 1);
            bool isFound;
            int nextOpIndex = find_next_op_index(s, cmd.substr(matchingClosingBracket), isFound) + i + matchingClosingBracket;
            if (!isFound)
            {
                eval.addCommand(parseEvalExpression(ParenExpression));
                break;
            }
            std::string op = cmd.substr(nextOpIndex, 1);
            std::string remainder = cmd.substr(nextOpIndex + 1);
            int remainderFirstCharIndex = remainder.find_first_not_of(" ") + nextOpIndex + 1;
            bool isFoundNext;
            int nextNextOpIndex;
            if (cmd[remainderFirstCharIndex] == '(')
            {
                int remainderMatchingParenIndex = findClosingParen(cmd, remainderFirstCharIndex);
                std::string remainderAfterSecondParen = cmd.substr(remainderMatchingParenIndex + 1);
                nextNextOpIndex = find_next_op_index(s, remainderAfterSecondParen, isFoundNext) + i + remainderMatchingParenIndex;
            }
            else
            {
                nextNextOpIndex = find_next_op_index(s, remainder, isFoundNext) + i + nextOpIndex + 1;
            }
            if (!isFoundNext)
            {
                EvalCommand lstatement = parseEvalExpression(ParenExpression);
                EvalCommand rstatement = parseEvalExpression(cmd.substr(nextOpIndex + 1));
                eval.addCommand(OperationCommand(lstatement, rstatement, op));
                break;
            }
            if (cmd[remainderFirstCharIndex] == '(')
            {
                EvalCommand lstatement = parseEvalExpression(ParenExpression);
                EvalCommand rstatement = parseEvalExpression(cmd.substr(nextOpIndex + 1, nextNextOpIndex - nextOpIndex - 1));
                prependEval.addCommand(OperationCommand(lstatement, rstatement, op));
            }
            else
            {
                EvalCommand lstatement = parseEvalExpression(ParenExpression);
                EvalCommand rstatement = builFindCommand(cmd.substr(nextOpIndex + 1, nextNextOpIndex - nextOpIndex - 1));
                prependEval.addCommand(OperationCommand(lstatement, rstatement, op));
            }
            selectedOp = cmd.substr(nextNextOpIndex, 1);
            i = matchingClosingBracket;
            continue;
        }
        bool isFound;
        int nextOpIndex = find_next_op_index(s, cmd.substr(i), isFound) + i;
        if (!isFound) // case: all of cmd is a terminal name
        {
            eval.addCommand(builFindCommand(cmd.substr(i)));
            break;
        }
        std::string terminal = cmd.substr(i, nextOpIndex - i);
        EvalCommand lstatement = builFindCommand(terminal);
        std::string op = cmd.substr(nextOpIndex, 1);
        std::string remainder = cmd.substr(nextOpIndex + 1);
        if (trim(remainder, " ") == "") //case: couldnt find a matching right-expression for an op. e.g: G +
        {
            throw Exception("Bad Syntax. Missing value for operation");
        }
        int nextNextOpIndex;
        bool isFoundNext;
        int remainderFirstCharIndex = remainder.find_first_not_of(" ") + nextOpIndex + 1;
        if (cmd[remainderFirstCharIndex] == '(')
        {
            int remainderMatchingParenIndex = findClosingParen(cmd, remainderFirstCharIndex);
            std::string remainderAfterSecondParen = cmd.substr(remainderMatchingParenIndex + 1);
            nextNextOpIndex = find_next_op_index(s, remainderAfterSecondParen, isFoundNext) + i + remainderMatchingParenIndex + 1;
        }
        else
        {
            nextNextOpIndex = find_next_op_index(s, remainder, isFoundNext) + i + nextOpIndex + 1;
        }
        if (!isFoundNext) //case: this is the last op in cmd
        {
            EvalCommand rstatement = parseEvalExpression(remainder);
            eval.addCommand(OperationCommand(lstatement, rstatement, op));
            break;
        }
        if (cmd[remainderFirstCharIndex] == '(')
        {
            int remainderMatchingParenIndex = findClosingParen(cmd, remainderFirstCharIndex);
            std::string terminal2 = cmd.substr(remainderFirstCharIndex + 1, remainderMatchingParenIndex - remainderFirstCharIndex - 1);
            std::string gapToNextOp = cmd.substr(remainderMatchingParenIndex + 1, nextNextOpIndex - remainderMatchingParenIndex - 1);
            if (trim(gapToNextOp, " ") != "")
            {
                throw Exception("Couldn't parse.");
            }
            EvalCommand rstatement = parseEvalExpression(terminal2);
            prependEval.addCommand(OperationCommand(lstatement, rstatement, op));
        }
        else
        {
            std::string terminal2 = cmd.substr(nextOpIndex + 1, nextNextOpIndex - nextOpIndex - 1);
            EvalCommand rstatement = builFindCommand(terminal2);
            prependEval.addCommand(OperationCommand(lstatement, rstatement, op));
        }
        selectedOp = cmd.substr(nextNextOpIndex, 1);
        i = nextNextOpIndex;
    }

    return eval;
}

PrintCommand Parser::parsePrintCommand(std::string cmd)
{
    if (cmd.find("print()") == string::npos)
    {
        int openPIndex = cmd.find_first_not_of(" ", cmd.find("print") + 5);
        if (cmd[openPIndex] == '(' && cmd[cmd.find_first_not_of(" ", openPIndex + 1)] != ')')
        {
            int matchingClosingBracket = findClosingParen(cmd, openPIndex);
            std::string printCommandParam = cmd.substr(openPIndex + 1, matchingClosingBracket - openPIndex - 1);
            if (trim(printCommandParam, " ") == "")
            {
                throw Exception("Bad Syntax. print function. No valid graph found");
            }
            EvalCommand evalExpression = parseEvalExpression(printCommandParam);
            return PrintCommand(evalExpression);
        }
    }
    throw Exception("Bad Syntax. print function");
}

DeleteCommand Parser::parseDeleteCommand(std::string cmd)
{
    if (cmd.find("delete()") == string::npos)
    {
        int openPIndex = cmd.find_first_not_of(" ", cmd.find("delete") + 6);
        if (cmd[openPIndex] == '(' && cmd[cmd.find_first_not_of(" ", openPIndex + 1)] != ')')
        {
            std::string deleteCommandParam = cmd.substr(openPIndex + 1, cmd.find(")", openPIndex) - openPIndex - 1);
            if (trim(deleteCommandParam, " ") == "")
            {
                throw Exception("Bad Syntax. print function. No valid graph found");
            }
            return DeleteCommand(deleteCommandParam);
        }
    }
    throw Exception("Bad Syntax. print function");
}

SaveCommand Parser::parseSaveCommand(std::string cmd)
{
    if (cmd.find("save()") == string::npos)
    {
        int openPIndex = cmd.find_first_not_of(" ", cmd.find("save") + 4);
        if (cmd[openPIndex] == '(' && cmd[cmd.find_first_not_of(" ", openPIndex + 1)] != ')')
        {
            if (cmd.find_last_of(',') != string::npos)
            {
                int comma = cmd.find_last_of(',');
                std::string e = cmd.substr(openPIndex + 1, comma - openPIndex - 1);
                EvalCommand evalExpression = parseEvalExpression(e);
                std::string filename = cmd.substr(comma + 1, cmd.find(")", comma) - comma - 1);
                std::string remainder = cmd.substr(cmd.find(")", comma) + 1);
                if (filename.find(',') == string::npos && trim(remainder, " ") == "")
                {
                    return SaveCommand(parseFileName(filename), evalExpression);
                }
            }
        }
    }

    throw Exception("Bad Syntax. save function");
}

void Parser::command(std::string cmd, std::map<std::string, shared_ptr<Graph>> &context, IContextParams params)
{
    if (cmd.find("()") != string::npos || !areParanthesisBalanced(strip_to_parantheiss_only(cmd, '(', ')')))
    {
        throw Exception("Bad Syntax. Empty or Unbalanced Paranthesis");
    }
    else if (cmd.find('=') != string::npos)
    {
        std::string graphName = parseTerminalName(cmd.substr(0, cmd.find('=')));
        LeftOpperandAssignmentCommand lo = LeftOpperandAssignmentCommand(graphName);
        EvalCommand ro = EvalCommand(parseEvalExpression(cmd.substr(cmd.find('=') + 1)));
        AssignmentCommand assignment = AssignmentCommand(lo, ro);
        assignment.exec(context, params);
    }
    else if (cmd.find("print") != string::npos && cmd[cmd.find_last_not_of(" ")] == ')')
    {
        parsePrintCommand(cmd).exec(context, params);
    }
    else if (cmd.find("delete") != string::npos && cmd[cmd.find_last_not_of(" ")] == ')')
    {
        parseDeleteCommand(cmd).exec(context, params);
    }
    else if (cmd.find("save") != string::npos && cmd[cmd.find_last_not_of(" ")] == ')')
    {
        parseSaveCommand(cmd).exec(context, params);
    }
    else if (trim(cmd, " ") == "who")
    {
        WhoCommand().exec(context, params);
    }
    else if (trim(cmd, " ") == "reset")
    {
        ResetCommand().exec(context, params);
    }
    else if (trim(cmd, " ") == "")
    {
        return;
    }
    else
    {
        throw Exception("Bad Syntax. no function found.");
    }
}