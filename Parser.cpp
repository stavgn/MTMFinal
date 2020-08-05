#include "./Parser.h"
#include "./Command.h"
#include "./Exception.h"
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

bool Parser::isConatainingReservedChars(std::string cmd)
{
    std::string chars[8] = {"{", "}", "+", "^", "-", "<", ">", "|"};
    for (int i = 0; i < 8; i++)
    {
        if (cmd.find(chars[i]) != string::npos)
        {
            return true;
        }
    }
    return false;
}

std::string Parser::parseTerminalName(std::string terminal)
{

    terminal = trim(terminal, " ");
    if (terminal.find(" ") != string::npos || terminal == "")
    {
        throw new Exception("Bad Syntax. Bad Terminal name. space or empty");
    }
    return terminal;
}

EvalCommand Parser::parseEvalExpression(std::string cmd)
{
    EvalCommand eval = EvalCommand();
    if (cmd.find("{") != string::npos && cmd.find("}") != string::npos && cmd.find("{") < cmd.find("}"))
    {
        std::string graph_literal = cmd.substr(cmd.find("{") + 1, cmd.find("}") - cmd.find("{") - 1);
        if (trim(graph_literal, " ") == "")
        {
            return eval;
        }
        if (cmd.find("|") == string::npos)
        {
            throw new Exception("Bad Syntax. Missing |");
        }
        std::string vertices = cmd.substr(cmd.find("{") + 1, cmd.find("|") - cmd.find("{") - 1);
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
        std::string edges = cmd.substr(cmd.find("|") + 1, cmd.find("}") - cmd.find("|") - 1);
        while (true && edges != "")
        {
            std::string firstVertex = parseTerminalName(edges.substr(edges.find("<") + 1, edges.find(",") - edges.find("<") - 1));
            std::string secondVertex = parseTerminalName(edges.substr(edges.find(",") + 1, edges.find(">") - edges.find(",") - 1));
            CreateAndAssignEdgeCommand edge = CreateAndAssignEdgeCommand(firstVertex, secondVertex);
            eval.addCommand(edge);
            edges.replace(0, edges.find(">") - edges.find("<") + 1, "");
            if (edges.find(",") == string::npos)
            {
                break;
            }
            edges = edges.substr(edges.find(",") + 1);
        }
    }
    else if (cmd.find("+") != string::npos)
    {
        std::string lstatement = cmd.substr(0, cmd.find("+"));
        std::string rstatement = cmd.substr(cmd.find("+") + 1);
        eval.addCommand(OperationCommand(parseTerminalName(lstatement), parseTerminalName(rstatement), "+"));
    }
    else if (cmd.find("^") != string::npos)
    {
        std::string lstatement = cmd.substr(0, cmd.find("^"));
        std::string rstatement = cmd.substr(cmd.find("^") + 1);
        eval.addCommand(OperationCommand(parseTerminalName(lstatement), parseTerminalName(rstatement), "^"));
    }
    else if (cmd.find("-") != string::npos)
    {
        std::string lstatement = cmd.substr(0, cmd.find("-"));
        std::string rstatement = cmd.substr(cmd.find("-") + 1);
        eval.addCommand(OperationCommand(parseTerminalName(lstatement), parseTerminalName(rstatement), "-"));
    }
    else if (cmd.find("*") != string::npos)
    {
        std::string lstatement = cmd.substr(0, cmd.find("*"));
        std::string rstatement = cmd.substr(cmd.find("*") + 1);
        eval.addCommand(OperationCommand(parseTerminalName(lstatement), parseTerminalName(rstatement), "*"));
    }
    else if (cmd.find("!") != string::npos)
    {
        std::string lstatement = cmd.substr(0, cmd.find("!"));
        std::string rstatement = cmd.substr(cmd.find("!") + 1);
        eval.addCommand(OperationCommand(parseTerminalName(rstatement), "", "!"));
    }
    else if (parseTerminalName(cmd) != "" && !isConatainingReservedChars(parseTerminalName(cmd)))
    {
        FindGraphCommand find(parseTerminalName(cmd), "");
        eval.addCommand(find);
    }
    else
    {
        throw new Exception("Bad Syntax. no valid left side assignmet found.");
    }

    return eval;
}

PrintCommand Parser::parsePrintCommand(std::string cmd)
{
    if (cmd.find("print()") == string::npos && cmd.find("print(") != string::npos && cmd.find(")") != string::npos && cmd.find("print(") < cmd.find(")"))
    {
        std::string printCommandParam = cmd.substr(cmd.find("print(") + 6, cmd.find(")") - cmd.find("print(") - 6);
        if (trim(printCommandParam, " ") == "")
        {
            throw new Exception("Bad Syntax. print function. No valid graph found");
        }
        EvalCommand evalExpression = parseEvalExpression(printCommandParam);
        return PrintCommand(evalExpression);
    }
    else
    {
        throw new Exception("Bad Syntax. print function");
    }
}

DeleteCommand Parser::parseDeleteCommand(std::string cmd)
{
    if (cmd.find("delete()") == string::npos && cmd.find("delete(") != string::npos && cmd.find(")") != string::npos && cmd.find("delete(") < cmd.find(")"))
    {
        std::string deleteCommandParam = cmd.substr(cmd.find("delete(") + 7, cmd.find(")") - cmd.find("delete(") - 7);
        if (trim(deleteCommandParam, " ") == "")
        {
            throw new Exception("Bad Syntax. print function. No valid graph found");
        }
        return DeleteCommand(deleteCommandParam);
    }
    else
    {
        throw new Exception("Bad Syntax. print function");
    }
}

void Parser::command(std::string cmd, std::map<std::string, shared_ptr<Graph>> &context, IContextParams params)
{
    if (cmd.find('=') != string::npos)
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
    else if (trim(cmd, " ") == "who")
    {
        WhoCommand().exec(context, params);
    }
    else if (trim(cmd, " ") == "reset")
    {
        ResetCommand().exec(context, params);
    }
    else
    {
        throw new Exception("Bad Syntax. no function found.");
    }
}

//b = {x,y|<x,y>}
//w = {a,b|<a,b>}
//a = {z|}
//c = b-a