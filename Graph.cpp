#include "./Graph.h"
using namespace gcalc;
using namespace std;

Graph::Graph(std::string name) : name(name)
{
    //TODO: Validate Graph Name
}

void Graph::add_vertex(Vertex v)
{
    vertices.insert(v);
}

void Graph::add_edge(Edge e)
{
    edges.insert(e);
}

std::string Graph::get_name() const
{
    return name;
}