#include "./Graph.h"
#include "./Vertex.h"
#include "./Exception.h"
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
    shared_ptr<Vertex> v_check = find_vertex(v->get_name());
    if (v_check == nullptr)
    {
        vertices->insert(v);
    }
    else
    {
        throw Exception("Cannot Duplicate Vertex " + v->get_name());
    }
}

void Graph::add_edge(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
{
    if (v1->get_name() == v2->get_name())
    {
        throw Exception("Cannot create a Self-Edge to" + v2->get_name());
    }
    if (find_vertex(v1->get_name()) == nullptr || find_vertex(v2->get_name()) == nullptr)
    {
        throw Exception("Cannot create an Edge. One Of The Vertices provided does belong to tis graph");
    }
    add_edge(std::make_pair(v1, v2));
}

void Graph::add_edge(std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>> edge)
{
    shared_ptr<Vertex> v1 = edge.first;
    shared_ptr<Vertex> v2 = edge.second;
    if (v1->get_name() == v2->get_name())
    {
        throw Exception("Cannot create a Self-Edge to" + v2->get_name());
    }
    if (find_vertex(v1->get_name()) == nullptr || find_vertex(v2->get_name()) == nullptr)
    {
        throw Exception("Cannot create an Edge. One Of The Vertices provided does belong to tis graph");
    }
    edges->insert(edge);
}

std::string Graph::get_name() const
{
    return name;
}

shared_ptr<Vertex> Graph::find_vertex(std::string vertexName)
{
    std::set<shared_ptr<Vertex>>::iterator it;
    for (it = (*vertices).begin(); it != (*vertices).end(); it++)
    {
        if ((*it)->get_name() == vertexName)
        {
            return *it;
        }
    }
    return nullptr;
}

bool Graph::is_edge_exists(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
{
    return is_edge_exists(std::make_pair(v1, v2));
}

bool Graph::is_edge_exists(std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>> edge)
{
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it;
    for (it = edges->begin(); it != edges->end(); it++)
    {
        if (it->first->get_name() == edge.first->get_name() && it->second->get_name() == edge.second->get_name())
        {
            return true;
        }
    }
    return false;
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

Graph Graph::operator+(Graph g)
{
    std::set<shared_ptr<Vertex>>::iterator it;
    for (it = g.vertices->begin(); it != g.vertices->end(); it++)
    {
        shared_ptr<Vertex> v = find_vertex((*it)->get_name());
        if (v == nullptr)
        {
            add_vertex(*it);
        }
    }
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it2;

    for (it2 = g.edges->begin(); it2 != g.edges->end(); it2++)
    {
        if (is_edge_exists(*it2) == false)
        {
            add_edge(*it2);
        }
    }
    return *this;
}

Graph Graph::operator^(Graph g)
{
    shared_ptr<std::set<shared_ptr<Vertex>>> verticesIntersection = shared_ptr<std::set<shared_ptr<Vertex>>>(new std::set<shared_ptr<Vertex>>);
    shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>> edgesIntersection = shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>>(new std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>);

    std::set<shared_ptr<Vertex>>::iterator it;
    for (it = g.vertices->begin(); it != g.vertices->end(); it++)
    {
        shared_ptr<Vertex> v = find_vertex((*it)->get_name());
        if (v != nullptr)
        {
            verticesIntersection->insert(*it);
        }
    }
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it2;

    for (it2 = g.edges->begin(); it2 != g.edges->end(); it2++)
    {
        if (is_edge_exists(*it2))
        {
            edgesIntersection->insert(*it2);
        }
    }
    vertices = verticesIntersection;
    edges = edgesIntersection;
    return *this;
}

Graph Graph::operator-(Graph g)
{
    shared_ptr<std::set<shared_ptr<Vertex>>> verticesSub = shared_ptr<std::set<shared_ptr<Vertex>>>(new std::set<shared_ptr<Vertex>>);
    shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>> edgesSub = shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>>(new std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>);

    std::set<shared_ptr<Vertex>>::iterator it;
    for (it = vertices->begin(); it != vertices->end(); it++)
    {
        shared_ptr<Vertex> v = g.find_vertex((*it)->get_name());
        if (v == nullptr)
        {
            verticesSub->insert(*it);
        }
    }
    vertices = verticesSub;
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it2;

    for (it2 = edges->begin(); it2 != edges->end(); it2++)
    {
        shared_ptr<Vertex> v1 = it2->first;
        shared_ptr<Vertex> v2 = it2->second;

        if (find_vertex((v1)->get_name()) != nullptr && find_vertex((v2)->get_name()) != nullptr)
        {
            edgesSub->insert(*it2);
        }
    }
    edges = edgesSub;
    return *this;
}

Graph Graph::operator*(Graph g)
{
    shared_ptr<std::set<shared_ptr<Vertex>>> verticesProduct = shared_ptr<std::set<shared_ptr<Vertex>>>(new std::set<shared_ptr<Vertex>>);
    shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>> edgesProdcut = shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>>(new std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>);

    std::set<shared_ptr<Vertex>>::iterator it;
    std::set<shared_ptr<Vertex>>::iterator it2;
    for (it = vertices->begin(); it != vertices->end(); it++)
    {
        for (it2 = g.vertices->begin(); it2 != g.vertices->end(); it2++)
        {
            std::string vname = "[" + (*it)->get_name() + ";" + (*it2)->get_name() + "]";
            shared_ptr<Vertex> v = shared_ptr<Vertex>(new Vertex(vname));
            verticesProduct->insert(v);
        }
    }
    vertices = verticesProduct;
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it3;
    std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>::iterator it4;

    for (it3 = edges->begin(); it3 != edges->end(); it3++)
    {
        for (it4 = g.edges->begin(); it4 != g.edges->end(); it4++)
        {
            shared_ptr<Vertex> v1 = (*it3).first;
            shared_ptr<Vertex> v2 = (*it4).first;

            shared_ptr<Vertex> v3 = (*it3).second;
            shared_ptr<Vertex> v4 = (*it4).second;

            shared_ptr<Vertex> vr = find_vertex("[" + v1->get_name() + ";" + v2->get_name() + "]");
            shared_ptr<Vertex> vl = find_vertex("[" + v3->get_name() + ";" + v4->get_name() + "]");

            if (vr != nullptr && vl != nullptr && *vr != *vl)
            {
                edgesProdcut->insert(std::make_pair(vr, vl));
            }
        }
    }
    edges = edgesProdcut;
    return *this;
}

Graph Graph::operator!()
{
    shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>> edgesComp = shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>>(new std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>);

    std::set<shared_ptr<Vertex>>::iterator it;
    std::set<shared_ptr<Vertex>>::iterator it2;
    for (it = vertices->begin(); it != vertices->end(); it++)
    {
        for (it2 = vertices->begin(); it2 != vertices->end(); it2++)
        {

            if (!is_edge_exists(*it, *it2) && *it != *it2)
            {
                edgesComp->insert(std::make_pair(*it, *it2));
            }
        }
    }
    edges = edgesComp;
    return *this;
}
