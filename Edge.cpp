#include "./Edge.h"
#include "./Vertex.h"
#include <string>

using namespace gcalc;
using namespace std;

Edge::Edge(Vertex v1, Vertex v2) : v1(v1), v2(v2)
{
}

std::string Edge::get_name() const
{
    return v1.get_name() + " " + v2.get_name();
}

bool Edge::operator==(Edge e) const
{
    return get_name() == e.get_name();
}

bool Edge::operator<(Edge e) const
{
    return get_name() < e.get_name();
}