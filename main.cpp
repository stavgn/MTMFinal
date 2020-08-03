#include "./Graph.h"

using namespace gcalc;

int main()
{
    Graph G1 = Graph("G1");
    Vertex V1 = Vertex("V1");
    Vertex V2 = Vertex("V2");
    Edge E1 = Edge(V1, V2);
    G1.add_vertex(V1);
    G1.add_vertex(V2);
    G1.add_edge(E1);

    return 0;
}
