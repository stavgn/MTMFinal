
#ifndef GCALC_EDGE_H
#define GCALC_EDGE_H

#include <set>
#include <memory>
#include <string>
#include "./Vertex.h"

namespace gcalc
{
    class Edge
    {
        Vertex v1;
        Vertex v2;

    public:
        Edge(Vertex v1, Vertex v2);
        ~Edge() = default;
        std::string get_name() const;
        bool operator==(Edge e) const;
        bool operator<(Edge v) const;
    };

} // namespace gcalc

#endif