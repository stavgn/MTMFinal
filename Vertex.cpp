#include "./Vertex.h"
using namespace gcalc;
using namespace std;

Vertex::Vertex(std::string name) : name(name)
{
}

std::string Vertex::get_name() const
{
    return name;
}

bool Vertex::operator==(Vertex v) const
{
    return name == v.get_name();
}

bool Vertex::operator<(Vertex v) const
{
    return name < v.get_name();
}
