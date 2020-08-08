#include "./libgraph.h"
#include "./Graph.h"
#include "./Vertex.h"

using namespace gcalc;

Graph create()
{
    return Graph();
}

// void destroy(gcalc::Graph *g)
// {
//     delete g;
// }

// gcalc::Graph *addVertex(gcalc::Graph *g, std::string v)
// {
//     gcalc::Vertex ver(v);
//     g->add_vertex(ver);
//     return g;
// }

// gcalc::Graph *addEdge(gcalc::Graph *g, std::string v1, std::string v2)
// {
//     gcalc::Vertex ver1(v1);
//     gcalc::Vertex ver2(v2);
//     g->add_edge(ver1, ver2);
//     return g;
// }

// void disp(gcalc::Graph *g)
// {
//     g->print();
// }

// gcalc::Graph *graphUnion(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
// {
//     *graph_out = *graph_in1 + *graph_in2;
//     return graph_out;
// }

// gcalc::Graph *graphIntersection(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
// {
//     *graph_out = *graph_in1 ^ *graph_in2;
//     return graph_out;
// }

// gcalc::Graph *graphDifference(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
// {
//     *graph_out = *graph_in1 - *graph_in2;
//     return graph_out;
// }

// gcalc::Graph *graphProduct(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out)
// {
//     *graph_out = *graph_in1 * *graph_in2;
//     return graph_out;
// }

// gcalc::Graph *graphComplement(gcalc::Graph *graph_in, gcalc::Graph *graph_out)
// {
//     *graph_out = !(*graph_in);
//     return graph_out;
// }

int foo(int x)
{
    return x;
}
