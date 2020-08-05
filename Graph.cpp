#include "./Graph.h"
#include "./Vertex.h"
#include <iostream>

using namespace gcalc;
using namespace std;
using std::shared_ptr;

Graph::Graph(std::string name) : name(name)
{
    vertices = shared_ptr<std::set<shared_ptr<Vertex>>>(new std::set<shared_ptr<Vertex>>);
    edges = shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>>(new std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>);
}

Graph::Graph(const Graph &g)
{
    if (name == "")
    {
        name = g.name;
    }
    vertices = g.vertices;
    edges = g.edges;
}

Graph Graph::operator=(Graph g)
{
    if (this == &g)
    {
        return *this;
    }
    if (name == "")
    {
        name = g.name;
    }
    vertices = g.vertices;
    edges = g.edges;
    return *this;
}

void Graph::add_vertex(shared_ptr<Vertex> v)
{

    vertices->insert(v);
}

void Graph::add_edge(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
{
    edges->insert(std::make_pair(v1, v2));
}

std::string Graph::get_name() const
{
    return name;
}

shared_ptr<Vertex> Graph::find_vertex(std::string vertexName)
{
    std::set<shared_ptr<Vertex>>::iterator it;
    int s = (*vertices).size();
    std::cout << s;
    for (it = (*vertices).begin(); it != (*vertices).end(); it++)
    {
        if ((*it)->get_name() == vertexName)
        {
            return *it;
        }
    }
    return nullptr;
}

void Graph::print()
{
    std::set<shared_ptr<Vertex>>::iterator it;
    for (it = vertices->begin(); it != vertices->end(); it++)
    {
        std::cout << (*it)->get_name() << std::endl;
    }
    std::cout << "$" << std::endl;
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it2;

    for (it2 = edges->begin(); it2 != edges->end(); it2++)
    {
        std::cout << it2->first->get_name() << " " << it2->second->get_name() << std::endl;
    }
}
