#pragma once
#include <array>
#include <string>
#include <vector>

namespace generator
{
// command line argument type
enum class TYPE
{
    FLAG,
    INT,
    DOUBLE,
    STRING
};

// token as start and end index of the scanned line
struct token
{
    constexpr token()
    {
        reset();
    }

    unsigned int start;
    unsigned int end;

    constexpr void reset()
    {
        start = 0;
        end   = 0;
    }
};

using token_array = std::array<token, 3>;

// writes the found token to the given std::string
inline auto token_to_string(const token& t, const std::string& line, std::string& dst)
{
    dst = line.substr(t.start, t.end - t.start + 1);
};

// scans the given line for tokens
template <typename DATA> constexpr auto scanner(const DATA& line, token_array& tokens)
{
    // clear tokens
    for (auto& t : tokens)
        t.reset();

    tokens[0].start = 0;
    auto ti         = 0u;
    auto i          = 0u;

    const auto cnt = line.size();

    auto t_cnt = 0;

    for (const auto& c : line)
    {
        if (c == ':')
        {
            tokens[ti].end = i - 1;
            ++t_cnt;

            ++ti;

            if (ti >= tokens.size())
                return t_cnt;

            tokens[ti].start = i + 1;
        }
        else if (i == cnt - 1)
        {
            auto& t = tokens[ti];

            t.end = i;
            ++t_cnt;
        }

        ++i;
    }

    return t_cnt;
}

// command line argument description
struct arg
{
    std::string name;
    std::string desc;
    TYPE        type;
};

// list of command line arguments descriptions
struct arguments
{
    std::vector<arg> args;
};

// code generation options
struct options
{
    bool pragma;
    bool comments;
    bool date;
    bool print;
    bool values;

    std::string space;
    std::string hyphen;
    std::string tab;
    std::string header;
};

void make_result(const arguments& args, std::ofstream& header_file, std::ofstream& cpp_file, const options& opt);

} // namespace generator
