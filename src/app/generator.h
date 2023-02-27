#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace generator
{
enum class TYPE
{
    FLAG,
    INT,
    DOUBLE,
    STRING
};

struct arg
{
    void parse(const std::string& input)
    {
        std::string substring;
        int         phase = 0;

        for (auto i = 0u; i < input.length(); ++i)
        {

            if (i == input.length() - 1)
            {
                substring.append(1, input[i]);
                desc = substring;
                break;
            }

            if (input[i] == ':')
            {

                switch (phase)
                {
                case (0):
                {
                    name = substring;
                    break;
                }
                case (1):
                {
                    if (substring == "f")
                    {
                        type = TYPE::FLAG;
                    }
                    else if (substring == "s")
                    {
                        type = TYPE::STRING;
                    }
                    else if (substring == "i")
                    {
                        type = TYPE::INT;
                    }
                    else if (substring == "d")
                    {
                        type = TYPE::DOUBLE;
                    }
                    break;
                }
                default:
                    break;
                }

                phase++;
                substring.clear();
            }
            else
            {
                substring.append(1, input[i]);
            }
        }
    }

    std::string name;
    std::string desc;

    TYPE type;
};

struct arguments
{
    std::vector<arg> args;
};

struct options
{
    bool        pragma;
    bool        comments;
    bool        date;
    bool        print;
    std::string space;
    std::string hyphen;
    std::string tab;
    std::string header;
};

void make_result(const arguments& args, const std::filesystem::path& header,
                 const std::filesystem::path& cpp, const options& opt);

} // namespace generator
