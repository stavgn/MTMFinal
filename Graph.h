
#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <set>
#include <memory>
#include <string>
#include "./Vertex.h"
#include "./Edge.h"

namespace gcalc
{
    class Graph
    {
        std::string name;
        std::set<Vertex> vertices;
        std::set<Edge> edges;

    public:
        Graph(std::string name);
        ~Graph() = default;
        void add_vertex(Vertex v);
        void add_edge(Edge e);
        std::string get_name() const;
    };

} // namespace gcalc

#endif