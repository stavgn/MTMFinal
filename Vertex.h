
#ifndef GCALC_VERTEX_H
#define GCALC_VERTEX_H

#include <set>
#include <memory>

namespace gcalc
{
    class Vertex
    {
        std::string name;

    public:
        Vertex(std::string vertexName);
        ~Vertex() = default;
        Vertex(Vertex &v) = default;
        std::string get_name() const;
        bool operator==(Vertex v) const;
        bool operator!=(Vertex v) const;
        bool operator<(const Vertex &v) const;

    private:
        bool is_name_valid(std::string name);
    };

} // namespace gcalc

#endif