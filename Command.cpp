#include "./Exception.h"
#include "./Graph.h"
#include "./Vertex.h"
#include <map>
#include "./Command.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace gcalc;
using namespace std;
using std::shared_ptr;

AssignmentCommand::AssignmentCommand(LeftOpperandAssignmentCommand c1, EvalCommand c2) : c1(c1), c2(c2)
{
}

void AssignmentCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    try
    {
        params.temp_graphName = "temp000" + (c1.graphName != "" ? c1.graphName : std::to_string((rand() % 10000)));
        params.graphName = c1.graphName;
        shared_ptr<Graph> g = shared_ptr<Graph>(new Graph(params.temp_graphName));
        std::pair<std::string, shared_ptr<Graph>> p = std::make_pair(params.temp_graphName, g);
        context.insert(p);
        c2.exec(context, params);
        c1.exec(context, params);
        context.erase(params.temp_graphName);
    }
    catch (gcalc::Exception *e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
    catch (gcalc::Exception &e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
}

LeftOpperandAssignmentCommand::LeftOpperandAssignmentCommand(std::string graphName) : graphName(graphName)
{
}

void LeftOpperandAssignmentCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::map<std::string, shared_ptr<Graph>>::iterator graph;
    std::map<std::string, shared_ptr<Graph>>::iterator temp_graph;
    graph = context.find(graphName);
    temp_graph = context.find(params.temp_graphName);
    if (graph == context.end())
    {
        shared_ptr<Graph> g = shared_ptr<Graph>(new Graph(graphName));
        std::pair<std::string, shared_ptr<Graph>> p = std::make_pair(graphName, g);
        *g = *temp_graph->second;
        context.insert(p);
    }
    else
    {
        graph->second = temp_graph->second;
    }
}

EvalCommand::EvalCommand()
{
}

Command::Command()
{
}

void Command::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
}

void EvalCommand::addCommand(CreateAndAssignEdgeCommand command)
{
    EdgeCommands.push_back(shared_ptr<CreateAndAssignEdgeCommand>(new CreateAndAssignEdgeCommand(command)));
}

void EvalCommand::addCommand(OperationCommand command)
{
    OperationCommands.push_back(shared_ptr<OperationCommand>(new OperationCommand(command)));
}

void EvalCommand::addCommand(FindGraphCommand command)
{
    FindCommands.push_back(shared_ptr<FindGraphCommand>(new FindGraphCommand(command)));
}

void EvalCommand::addCommand(CreateAndAssignVertexCommand command)
{
    VertexCommands.push_back(shared_ptr<CreateAndAssignVertexCommand>(new CreateAndAssignVertexCommand(command)));
}

void EvalCommand::addCommand(EvalCommand command)
{
    SubEvalCommands.push_back(shared_ptr<EvalCommand>(new EvalCommand(command)));
}

void EvalCommand::addCommand(LoadCommand command)
{
    LoadCommands.push_back(shared_ptr<LoadCommand>(new LoadCommand(command)));
}

void EvalCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    for (std::vector<shared_ptr<CreateAndAssignVertexCommand>>::iterator it = VertexCommands.begin(); it != VertexCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }

    for (std::vector<shared_ptr<CreateAndAssignEdgeCommand>>::iterator it = EdgeCommands.begin(); it != EdgeCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }

    for (std::vector<shared_ptr<FindGraphCommand>>::iterator it = FindCommands.begin(); it != FindCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }
    for (std::vector<shared_ptr<OperationCommand>>::iterator it = OperationCommands.begin(); it != OperationCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }
    for (std::vector<shared_ptr<EvalCommand>>::iterator it = SubEvalCommands.begin(); it != SubEvalCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }
    for (std::vector<shared_ptr<LoadCommand>>::iterator it = LoadCommands.begin(); it != LoadCommands.end(); ++it)
    {
        (*it)->exec(context, params);
    }
}

CreateAndAssignVertexCommand::CreateAndAssignVertexCommand(std::string vertexName) : vertexName(vertexName)
{
}
void CreateAndAssignVertexCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    shared_ptr<Vertex> v = shared_ptr<Vertex>(new Vertex(vertexName));
    Graph graph = *context.find(params.temp_graphName)->second;
    graph.add_vertex(v);
}

CreateAndAssignEdgeCommand::CreateAndAssignEdgeCommand(std::string v1_name, std::string v2_name) : v1_name(v1_name), v2_name(v2_name)
{
}

void CreateAndAssignEdgeCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::map<std::string, shared_ptr<Graph>>::iterator it = context.find(params.temp_graphName);
    if (it == context.end())
    {
        throw Exception("couldnt find graph");
    }

    Graph graph = *it->second;
    shared_ptr<Vertex> v1 = graph.find_vertex(v1_name);
    shared_ptr<Vertex> v2 = graph.find_vertex(v2_name);
    if (v1 == nullptr || v2 == nullptr)
    {
        throw Exception("Couldn't find vertices.");
    }
    graph.add_edge(v1, v2);
}

PrintCommand::PrintCommand(EvalCommand evalCommand) : evalCommand(evalCommand)
{
}

void PrintCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    try
    {
        params.temp_graphName = "temp000toprint";
        shared_ptr<Graph> g = shared_ptr<Graph>(new Graph(params.temp_graphName));
        std::pair<std::string, shared_ptr<Graph>> p = std::make_pair(params.temp_graphName, g);
        context.insert(p);
        evalCommand.exec(context, params);
        g->print();
        context.erase(params.temp_graphName);
    }
    catch (gcalc::Exception *e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
    catch (gcalc::Exception &e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
}

FindGraphCommand::FindGraphCommand(std::string graphName, std::string attribute) : graphName(graphName), attribute(attribute)
{
}

void FindGraphCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::map<std::string, shared_ptr<Graph>>::iterator graph = context.find(graphName);
    if (graph == context.end())
    {
        throw Exception("Couldn't Find Graph Copy/Print. " + graphName);
    }
    std::map<std::string, shared_ptr<Graph>>::iterator temp_graph = context.find(params.temp_graphName);

    if (temp_graph != context.end())
    {
        *(temp_graph->second) = *(graph->second);
    }
}

WhoCommand::WhoCommand()
{
}

void WhoCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::map<std::string, shared_ptr<Graph>>::iterator it;
    for (it = context.begin(); it != context.end(); it++)
    {
        std::cout << it->first << std::endl;
    }
}

ResetCommand::ResetCommand()
{
}

void ResetCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    context.clear();
}

DeleteCommand::DeleteCommand(std::string graphName) : graphName(graphName)
{
}

void DeleteCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::map<std::string, shared_ptr<Graph>>::iterator graph = context.find(graphName);
    if (graph == context.end())
    {
        throw Exception("Couldn't Find Graph To Delete.");
    }
    context.erase(graphName);
}

OperationCommand::OperationCommand(EvalCommand ex1, EvalCommand ex2, std::string op) : op(op)
{
    exp1 = shared_ptr<EvalCommand>(new EvalCommand(ex1));
    exp2 = shared_ptr<EvalCommand>(new EvalCommand(ex2));
}

void OperationCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    IContextParams p1 = IContextParams();
    IContextParams p2 = IContextParams();

    p1.temp_graphName = "temp000" + std::to_string((rand() % 100000));
    p2.temp_graphName = "temp000" + std::to_string((rand() % 100000));

    shared_ptr<Graph> g1_temp = shared_ptr<Graph>(new Graph(p1.temp_graphName));
    std::pair<std::string, shared_ptr<Graph>> pair1 = std::make_pair(p1.temp_graphName, g1_temp);
    context.insert(pair1);

    shared_ptr<Graph> g2_temp = shared_ptr<Graph>(new Graph(p2.temp_graphName));
    std::pair<std::string, shared_ptr<Graph>> pair2 = std::make_pair(p2.temp_graphName, g2_temp);
    context.insert(pair2);

    exp1->exec(context, p1);
    exp2->exec(context, p2);

    std::map<std::string, shared_ptr<Graph>>::iterator temp_graph = context.find(params.temp_graphName);

    *(temp_graph->second) = *(g1_temp);

    if (op == "+")
    {
        *(temp_graph->second) = *(temp_graph->second) + *(g2_temp);
    }
    else if (op == "^")
    {
        *(temp_graph->second) = *(temp_graph->second) ^ *(g2_temp);
    }
    else if (op == "-")
    {
        *(temp_graph->second) = *(temp_graph->second) - *(g2_temp);
    }
    else if (op == "*")
    {
        *(temp_graph->second) = *(temp_graph->second) * (*g2_temp);
    }
    else if (op == "!")
    {
        *(temp_graph->second) = !(*(temp_graph->second));
    }

    context.erase(p1.temp_graphName);
    context.erase(p2.temp_graphName);
}

LoadCommand::LoadCommand(std::string filename) : filename(filename)
{
}

void LoadCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    std::ifstream infile(filename, std::ios_base::binary);
    if (infile.good())
    {
        std::map<std::string, shared_ptr<Graph>>::iterator temp_graph = context.find(params.temp_graphName);
        int num_vertices, num_edges;
        infile.read((char *)&num_vertices, sizeof(int));
        infile.read((char *)&num_edges, sizeof(int));

        while (num_vertices > 0)
        {
            int vertex_size;
            infile.read((char *)&vertex_size, sizeof(int));
            std::string vertex_name;
            char *temp = (char *)malloc((vertex_size + 1) * sizeof(char));
            infile.read(temp, vertex_size);
            temp[vertex_size] = '\0';
            vertex_name = temp;
            shared_ptr<Vertex> v = shared_ptr<Vertex>(new Vertex(vertex_name));
            (temp_graph)->second->add_vertex(v);
            free(temp);
            num_vertices--;
        }
        while (num_edges > 0)
        {
            int v1_size, v2_size;
            std::string v1_name, v2_name;

            infile.read((char *)&v1_size, sizeof(int));
            char *temp1 = (char *)malloc((v1_size + 1) * sizeof(char));

            infile.read(temp1, v1_size);
            infile.read((char *)&v2_size, sizeof(int));
            char *temp2 = (char *)malloc((v2_size + 1) * sizeof(char));
            infile.read(temp2, v2_size);

            temp1[v1_size] = '\0';
            temp2[v2_size] = '\0';
            v1_name = temp1;
            v2_name = temp2;

            shared_ptr<Vertex> v1 = shared_ptr<Vertex>(new Vertex(v1_name));
            shared_ptr<Vertex> v2 = shared_ptr<Vertex>(new Vertex(v2_name));
            (temp_graph)->second->add_edge(v1, v2);

            free(temp1);
            free(temp2);
            num_edges--;
        }
    }
    else
    {
        throw Exception("Couldn't Load From File.");
    }
}

SaveCommand::SaveCommand(std::string filename, EvalCommand evalCommand) : filename(filename), evalCommand(evalCommand)
{
}

void SaveCommand::exec(std::map<std::string, shared_ptr<Graph>> &context, IContextParams &params)
{
    try
    {
        params.temp_graphName = "temp000tosave";
        shared_ptr<Graph> g = shared_ptr<Graph>(new Graph(params.temp_graphName));
        std::pair<std::string, shared_ptr<Graph>> p = std::make_pair(params.temp_graphName, g);
        context.insert(p);
        evalCommand.exec(context, params);
        std::ofstream outfile(filename, std::ios_base::binary);
        if (outfile.good())
        {
            int num_vertices = g->vertices->size();
            int num_edges = g->edges->size();

            outfile.write((const char *)&num_vertices, sizeof(int));
            outfile.write((const char *)&num_edges, sizeof(int));

            std::set<shared_ptr<Vertex>>::iterator it;
            for (it = g->vertices->begin(); it != g->vertices->end(); it++)
            {
                int size = (*it)->get_name().size();
                outfile.write((const char *)&size, sizeof(int));
                outfile.write((*it)->get_name().c_str(), size);
            }

            std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it2;
            for (it2 = g->edges->begin(); it2 != g->edges->end(); it2++)
            {
                shared_ptr<Vertex> v1 = (*it2).first;
                int v1_size = v1->get_name().size();

                shared_ptr<Vertex> v2 = (*it2).second;
                int v2_size = v2->get_name().size();

                outfile.write((const char *)&v1_size, sizeof(int));
                outfile.write(v1->get_name().c_str(), v1_size);

                outfile.write((const char *)&v2_size, sizeof(int));
                outfile.write(v2->get_name().c_str(), v2_size);
            }
        }
        else
        {
            outfile.close();
            throw Exception("Couldn't Write to File");
        }
        outfile.close();
        context.erase(params.temp_graphName);
    }
    catch (gcalc::Exception *e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
    catch (gcalc::Exception &e)
    {
        context.erase(params.temp_graphName);
        throw e;
    }
}