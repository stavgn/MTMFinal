#include "./libgraph.h"
#include "./Graph.h"
#include "./Vertex.h"
#include "Exception.h"
#include <iostream>

gcalc::Graph *create()
{
    try
    {
        return new gcalc::Graph("graph");
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

void destroy(gcalc::Graph *g)
{
    if (g == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return;
    }
    try
    {
        delete g;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

gcalc::Graph *addVertex(gcalc::Graph *g, char *v)
{
    if (g == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        gcalc::Vertex ver(v);
        g->add_vertex(ver);
        return g;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

gcalc::Graph *addEdge(gcalc::Graph *g, char *v1, char *v2)
{
    if (g == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        gcalc::Vertex ver1(v1);
        gcalc::Vertex ver2(v2);
        g->add_edge(ver1, ver2);
        return g;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

void disp(gcalc::Graph *g)
{
    if (g == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return;
    }
    try
    {
        g->print();
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

gcalc::Graph *graphUnion(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
{
    if (graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 + *graph_in2;
        return graph_out;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

gcalc::Graph *graphIntersection(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
{
    if (graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 ^ *graph_in2;
        return graph_out;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

gcalc::Graph *graphDifference(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
{
    if (graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 - *graph_in2;
        return graph_out;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

gcalc::Graph *graphProduct(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
{
    if (graph_in1 == nullptr || graph_in2 == nullptr || graph_out == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 * *graph_in2;
        return graph_out;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}

gcalc::Graph *graphComplement(gcalc::Graph *graph_in, gcalc::Graph *graph_out)
{
    if (graph_in == nullptr || graph_out == nullptr)
    {
        std::cout << "Error: argument is nullptr" << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = !(*graph_in);
        return graph_out;
    }
    catch (gcalc::Exception *e)
    {
        std::cout << "Error: " << e->what() << std::endl;
    }
    catch (gcalc::Exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return nullptr;
}
