#ifndef UTILS_CPP
#define UTILS_CPP
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// std::vector<std::string> split(const std::string str, const std::string regex_str)
// {
//     std::regex regexz(regex_str);
//     std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
//                                   std::sregex_token_iterator());
//     return list;
// }

inline std::vector<std::string> split(std::string const& text, std::string const& separator)
{
    std::vector<std::string> result;
    std::string tmp = text;

    size_t first_pos = 0;
    size_t second_pos = tmp.find(separator);

    while (second_pos != std::string::npos)
    {
        if (first_pos != second_pos)
        {
            std::string word = tmp.substr(first_pos, second_pos - first_pos);
            result.push_back(word);
        }
        tmp = tmp.substr(second_pos + separator.length());
        second_pos = tmp.find(separator);
    }

    result.push_back(tmp);

    return result;
}



#endif