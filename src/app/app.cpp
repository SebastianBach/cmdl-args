#include "generator.h"
#include "parser.h"
#include <filesystem>
#include <fstream>
#include <iostream>

constexpr static auto s_version = "0.1.0";

std::tuple<int, std::string> process(const args::arguments& app_arguments)
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
    while (std::getline(input_file, line))
    {
        if (!line.empty())
        {
            // TODO: may be garbage line; may fail!
            generator::arg arg;
            arg.parse(line);

            args.args.push_back(arg);
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

void print_error(const std::string& err)
{
    std::cout << "\033[31m";
    std::cout << err;
    std::cout << "\033[0m";
}

int main(int argc, char* argv[])
{
    const auto& app_arguments = args::parse(argc, argv);

    if (app_arguments.help)
    {
        args::print_help();
        return 0;
    }

    if (app_arguments.version)
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
