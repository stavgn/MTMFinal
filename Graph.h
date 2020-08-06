
#ifndef GCALC_GRAPH_H
#define GCALC_GRAPH_H

#include <set>
#include <memory>
#include <string>
#include "./Vertex.h"

using std::shared_ptr;

namespace gcalc
{
    class Graph
    {
        std::string name;
        shared_ptr<std::set<shared_ptr<Vertex>>> vertices;
        shared_ptr<std::set<std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>>>> edges;

    public:
        Graph(std::string graphName);
        ~Graph() = default;
        Graph(const Graph &g);
        Graph operator=(Graph g);
        Graph operator+(Graph g);
        Graph operator^(Graph g);
        Graph operator-(Graph g);
        Graph operator*(Graph g);
        Graph operator!();
        void add_vertex(shared_ptr<Vertex> v);
        void add_edge(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
        void add_edge(std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>> edge);
        shared_ptr<Vertex> find_vertex(std::string vertexName);
        std::string get_name() const;
        bool is_edge_exists(std::pair<shared_ptr<Vertex>, shared_ptr<Vertex>> edge);
        bool is_edge_exists(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
        void print();
    };

} // namespace gcalc

#endif