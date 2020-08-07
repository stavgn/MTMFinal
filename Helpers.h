
#ifndef GCALC_HELPERS_H
#define GCALC_HELPERS_H

#include <set>
#include <memory>
#include <string>

namespace gcalc
{
    bool is_not_reserved_word(std::string word);
    bool is_alpha(std::string word);
    bool is_alphanumeric(std::string word);
    std::string strip_to_parantheiss_only(std::string expr, char open, char close);
    bool areParanthesisBalanced(std::string expr);
    std::string char_to_string(char c);
    int findClosingParen(std::string text, int openPos);

} // namespace gcalc

#endif