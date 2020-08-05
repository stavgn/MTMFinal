
#ifndef GCALC_VERTEX_H
#define GCALC_VERTEX_H

#include <set>
#include <memory>
#include <string>

namespace gcalc
{
    class Vertex
    {
        std::string name;

    public:
        Vertex(std::string);
        ~Vertex() = default;
        std::string get_name() const;
        bool operator==(Vertex v) const;
        bool operator!=(Vertex v) const;
        bool operator<(const Vertex &v) const;
    };

} // namespace gcalc

#endif