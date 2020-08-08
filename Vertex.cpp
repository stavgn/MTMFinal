#include "./Vertex.h"
#include "./Exception.h"
#include "./Helpers.h"
#include <string>

using namespace gcalc;
using namespace std;

Vertex::Vertex(std::string vertexName) : name(vertexName)
{
    if (is_not_reserved_word(name) && !is_name_valid(name))
    {
        throw Exception("Vertex name is not valid: " + name);
    }
}

std::string Vertex::get_name() const
{
    return name;
}

bool Vertex::operator==(Vertex v) const
{
    return name == v.get_name();
}

bool Vertex::operator!=(Vertex v) const
{
    return name != v.get_name();
}

bool Vertex::operator<(const Vertex &v) const
{
    return name < v.get_name();
}

bool Vertex::is_name_valid(std::string name)
{
    for (unsigned int i = 0; i < name.size(); i++)
    {
        if (!isalnum(name[i]) && name[i] != '[' && name[i] != ']' && name[i] != ';')
        {
            return false;
        }
    }
    std::string stripped = strip_to_parantheiss_only(name, '[', ']');
    if (!areParanthesisBalanced(stripped))
    {
        return false;
    }

    if (name.find(";") != string::npos)
    {
        if (stripped == "")
        {
            return false;
        }

        return (name.find_first_of(';') >= name.find_first_of('[')) && (name.find_last_of(';') <= name.find_last_of(']'));
    }

    return true;
}
