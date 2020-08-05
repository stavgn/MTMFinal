#include "./Calculator.h"

using namespace gcalc;

int main()
{
    // Graph G1 = Graph("G1");
    // Vertex V1 = Vertex("V1");
    // Vertex V2 = Vertex("V2");
    // G1.add_vertex(V2);
    // G1.add_vertex(V1);

    Calculator calc = Calculator();
    calc.interactive();

    return 0;
}