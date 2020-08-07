
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

    class EvalCommand;

    class OperationCommand : public Command
    {
        shared_ptr<EvalCommand> exp1;
        shared_ptr<EvalCommand> exp2;
        std::string op;

    public:
        OperationCommand(EvalCommand ex1, EvalCommand ex2, std::string op);
        ~OperationCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class LoadCommand : public Command
    {
        std::string filename;

    public:
        LoadCommand(std::string filename);
        ~LoadCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

    class EvalCommand : public Command
    {
    public:
        std::vector<shared_ptr<CreateAndAssignVertexCommand>> VertexCommands;
        std::vector<shared_ptr<CreateAndAssignEdgeCommand>> EdgeCommands;
        std::vector<shared_ptr<FindGraphCommand>> FindCommands;
        std::vector<shared_ptr<EvalCommand>> SubEvalCommands;
        std::vector<shared_ptr<OperationCommand>> OperationCommands;
        std::vector<shared_ptr<LoadCommand>> LoadCommands;

        EvalCommand();
        ~EvalCommand() = default;
        //EvalCommand(EvalCommand &e) = default;
        void addCommand(CreateAndAssignVertexCommand command);
        void addCommand(CreateAndAssignEdgeCommand command);
        void addCommand(FindGraphCommand command);
        void addCommand(EvalCommand command);
        void addCommand(OperationCommand command);
        void addCommand(LoadCommand command);

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

    class SaveCommand : public Command
    {
        std::string filename;
        EvalCommand evalCommand;

    public:
        SaveCommand(std::string filename, EvalCommand evalCommand);
        ~SaveCommand() = default;
        void exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params) override;
    };

} // namespace gcalc

#endif
