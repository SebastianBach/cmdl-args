#include "generator.h"
#include "parser.h"
#include "tests.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

constexpr static auto s_version = "0.1.0";

using process_success = std::tuple<int, std::string>;

process_success process(const args::arguments& app_arguments)
{
    if (!(app_arguments.i.has_value() && app_arguments.header.has_value() && app_arguments.cpp.has_value() &&
          app_arguments.o.has_value()))
        return {-1, "Missing input or output file."};

    const auto            input         = app_arguments.i.value();
    std::filesystem::path output_folder = app_arguments.o.value();

    std::filesystem::path header_file_name = app_arguments.header.value();
    std::filesystem::path header_full_path = output_folder / header_file_name;
    std::filesystem::path cpp_file_name    = app_arguments.cpp.value();
    std::filesystem::path cpp_full_path    = output_folder / cpp_file_name;

    if (app_arguments.v)
    {
        std::cout << "\n";
        std::cout << "Input: " << input << "\n";
        std::cout << "Header: " << header_full_path << "\n";
        std::cout << "Source: " << cpp_full_path << "\n";
    }

    std::ifstream input_file{input};

    if (!input_file.is_open())
        return {1, "Failed to open input file."};

    generator::arguments args;

    std::string line;

    generator::token_array tokens;

    while (std::getline(input_file, line))
    {
        if (!line.empty())
        {
            const auto cnt = generator::scanner(line, tokens);
            if (cnt == 3)
            {
                std::string type;
                generator::token_to_string(tokens[1], line, type);

                static const std::map<std::string, generator::TYPE> map{{"f", generator::TYPE::FLAG},
                                                                        {"d", generator::TYPE::DOUBLE},
                                                                        {"s", generator::TYPE::STRING},
                                                                        {"i", generator::TYPE::INT}};

                const auto it = map.find(type);
                if (it != map.end())
                {
                    generator::arg arg;

                    generator::token_to_string(tokens[0], line, arg.name);
                    generator::token_to_string(tokens[2], line, arg.desc);
                    arg.type = it->second;

                    args.args.push_back(arg);
                }
            }
        }
    }

    input_file.close();

    std::ofstream header_file{header_full_path};

    if (!header_file.is_open())
        return {1, "Failed to open header file."};

    std::ofstream cpp_file{cpp_full_path};

    if (!cpp_file.is_open())
        return {1, "Failed to open cpp file."};

    const generator::options opt{
        .pragma   = app_arguments.pragma,
        .comments = app_arguments.comments,
        .date     = app_arguments.date,
        .print    = app_arguments.print,
        .values   = app_arguments.values,
        .space    = app_arguments.space.value_or("args"),
        .hyphen   = app_arguments.hyphen.value_or("--"),
        .tab      = std::string(app_arguments.tab.value_or(4), ' '),
        .header   = app_arguments.header.value(),
    };

    generator::make_result(args, header_file, cpp_file, opt);

    header_file.close();
    cpp_file.close();

    return {0, ""};
}

inline void print_error(const std::string& err)
{
    std::cout << "\033[31m";
    std::cout << err;
    std::cout << "\033[0m";
}

int main(int argc, char* argv[])
{
    // compile time unit tests
    run_tests();

    const auto& app_arguments = args::parse(argc, argv);

    if (app_arguments.help)
    {
        args::print_help();
        return 0;
    }
    else if (app_arguments.version)
    {
        std::cout << s_version << std::endl;
        return 0;
    }

    if (app_arguments.v)
        args::print_values(app_arguments);

    const auto [res, err] = process(app_arguments);

    if (res != 0)
        print_error(err);

    return res;
}
