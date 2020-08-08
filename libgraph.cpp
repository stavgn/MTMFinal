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
