
#ifndef GCALC_COMMAND_H
#define GCALC_COMMAND_H

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "./Graph.h"

using std::shared_ptr;

namespace gcalc

{
    struct IContextParams
    {
        std::string graphName = "";
        std::string temp_graphName = "";
        std::string graphNameToPrint = "";
    };

    class Command
    {
    public:
        Command();
        ~Command() = default;
        void virtual exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params);
    };

    class CreateAndAssignVertexCommand : public Command
    {
        std::string vertexName;

    public:
        CreateAndAssignVertexCommand(std::string vertexName);
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class CreateAndAssignEdgeCommand : public Command
    {
        std::string v1_name;
        std::string v2_name;

    public:
        CreateAndAssignEdgeCommand(std::string v1_name, std::string v2_name);
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class LeftOpperandAssignmentCommand : public Command
    {
    public:
        std::string graphName;
        LeftOpperandAssignmentCommand(std::string graphName);
        ~LeftOpperandAssignmentCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class FindGraphCommand : public Command
    {
        std::string graphName;
        std::string attribute;

    public:
        FindGraphCommand(std::string graphName, std::string attribute);
        ~FindGraphCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class EvalCommand : public Command
    {
    public:
        std::vector<CreateAndAssignVertexCommand> VertexCommands;
        std::vector<CreateAndAssignEdgeCommand> EdgeCommands;
        std::vector<FindGraphCommand> FindCommands;
        std::vector<EvalCommand> SubEvalCommands;

        EvalCommand();
        ~EvalCommand() = default;
        void addCommand(CreateAndAssignVertexCommand command);
        void addCommand(CreateAndAssignEdgeCommand command);
        void addCommand(FindGraphCommand command);
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class AssignmentCommand : public Command
    {
        LeftOpperandAssignmentCommand c1;
        EvalCommand c2;

    public:
        AssignmentCommand(LeftOpperandAssignmentCommand c1, EvalCommand c2);
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class PrintCommand : public Command
    {
        EvalCommand evalCommand;

    public:
        PrintCommand(EvalCommand evalCommand);
        ~PrintCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class WhoCommand : public Command
    {
    public:
        WhoCommand();
        ~WhoCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class ResetCommand : public Command
    {
    public:
        ResetCommand();
        ~ResetCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class DeleteCommand : public Command
    {
        std::string graphName;

    public:
        DeleteCommand(std::string graphName);
        ~DeleteCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

} // namespace gcalc

#endif
