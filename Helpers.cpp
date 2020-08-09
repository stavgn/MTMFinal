#include "./Helpers.h"
#include <string>
#include <regex>
#include <cctype>
using namespace gcalc;
using namespace std;

bool gcalc::is_not_reserved_word(std::string word)
{
    std::string chars[8] = {"print", "delete", "save", "load", "who", "reset", "delete", "quit"};
    for (int i = 0; i < 8; i++)
    {

        if (std::regex_match(word, std::regex(chars[i])))
        {
            return false;
        }
    }
    return true;
}

bool gcalc::is_alpha(std::string word)
{
    for (unsigned int i = 0; i < word.size(); i++)
    {
        if (!isalpha(word[i]))
        {
            return false;
        }
    }
    return true;
}

bool gcalc::is_alphanumeric(std::string word)
{
    for (unsigned int i = 0; i < word.size(); i++)
    {
        if (!isalnum(word[i]))
        {
            return false;
        }
    }
    return true;
}

bool gcalc::areParanthesisBalanced(std::string expr)
{
    stack<char> s;
    char x;

    for (unsigned int i = 0; i < expr.length(); i++)
    {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
        {
            s.push(expr[i]);
            continue;
        }

        if (s.empty())
            return false;

        switch (expr[i])
        {
        case ')':

            x = s.top();
            s.pop();
            if (x == '{' || x == '[')
                return false;
            break;

        case '}':

            x = s.top();
            s.pop();
            if (x == '(' || x == '[')
                return false;
            break;

        case ']':
            x = s.top();
            s.pop();
            if (x == '(' || x == '{')
                return false;
            break;
        }
    }

    return (s.empty());
}

std::string gcalc::strip_to_parantheiss_only(std::string expr, char open, char close)
{
    std::string out = expr;
    int j = 0;
    for (unsigned int i = 0; i < expr.size(); i++)
    {
        if (expr[i] != open && expr[i] != close)
        {
            out.replace(i - j, 1, "");
            j++;
        }
    }
    return out;
}

std::string gcalc::char_to_string(char c)
{
    char temp[2];
    temp[0] = c;
    temp[1] = '\0';
    std::string s = temp;
    return s;
}

int gcalc::findClosingParen(std::string text, int openPos)
{
    int closePos = openPos;
    int counter = 1;
    while (counter > 0)
    {
        char c = text[++closePos];
        if (c == '(')
        {
            counter++;
        }
        else if (c == ')')
        {
            counter--;
        }
    }
    return closePos;
}

int gcalc::findClosingBracket(std::string text, int openPos)
{
    int closePos = openPos;
    int counter = 1;
    while (counter > 0)
    {
        char c = text[++closePos];
        if (c == '[')
        {
            counter++;
        }
        else if (c == ']')
        {
            counter--;
        }
    }
    return closePos;
}
