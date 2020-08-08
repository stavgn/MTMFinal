
#ifndef GCALC_LIBGRAPH_H
#define GCALC_LIBGRAPH_H

#include "./Graph.h"
#include "./Vertex.h"

gcalc::Graph *create();
void destroy(gcalc::Graph *g);
gcalc::Graph *addVertex(gcalc::Graph *g, char *v);
gcalc::Graph *addEdge(gcalc::Graph *g, char *v1, char *v2);
void disp(gcalc::Graph *g);
gcalc::Graph *graphUnion(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out);
gcalc::Graph *graphIntersection(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out);
gcalc::Graph *graphDifference(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out);
gcalc::Graph *graphProduct(gcalc::Graph *graph_in1, gcalc::Graph *graph_in2, gcalc::Graph *graph_out);
gcalc::Graph *graphComplement(gcalc::Graph *graph_in, gcalc::Graph *graph_out);

#endif
