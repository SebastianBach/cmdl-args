#include "generator.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

namespace generator
{
void make_result(const arguments& args, const std::filesystem::path& header, const std::filesystem::path& cpp,
                 const options& opt)
{
    const auto tab   = opt.tab;
    const auto tab_2 = tab + tab;
    const auto tab_3 = tab + tab + tab;
    const auto tab_4 = tab + tab + tab + tab;
    const auto tab_5 = tab + tab + tab + tab + tab;

    const auto info = "// Generated with https://github.com/SebastianBach/cmdl-args \n";

    std::string date;
    if (opt.date)
    {
        auto now = std::chrono::system_clock::now();

        auto       time = std::chrono::system_clock::to_time_t(now);
        const auto tm   = *std::localtime(&time);

        date = std::format("// Created {}-{}-{} \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    }

    // header file

    std::ofstream header_file{header};

    header_file << info;
    if (opt.date)
        header_file << date;

    header_file << "#pragma once"
                << "\n";
    header_file << "#include <optional>"
                << "\n";
    header_file << "#include <string>"
                << "\n";
    header_file << "namespace args {"
                << "\n";

    header_file << "struct arguments {"
                << "\n";

    for (const auto& arg : args.args)
    {
        header_file << "\n";

        if (opt.comments)
            header_file << tab << "// " << arg.desc << "\n";

        if (arg.type == TYPE::FLAG)
        {
            if (opt.comments)
                header_file << tab << "// True if the flag was set, otherwise false.\n";

            header_file << tab << "bool " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::STRING)
        {
            if (opt.comments)
                header_file << tab << "// Empty if the argument was not set.\n";
            header_file << tab << "std::optional<std::string> " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::INT)
        {
            if (opt.comments)
                header_file << tab << "// Empty if the argument was not set.\n";
            header_file << tab << "std::optional<int> " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::DOUBLE)
        {
            if (opt.comments)
                header_file << tab << "// Empty if the argument was not set.\n";
            header_file << tab << "std::optional<double> " << arg.name << ";\n";
        }
    }

    header_file << "};"
                << "\n";

    header_file << "const arguments parse(int argc, char* argv[]);"
                << "\n";

    if (opt.print)
    {
        if (opt.comments)
            header_file << "\n// Print help text to standard output."
                        << "\n";

        header_file << "void print_help();"
                    << "\n";
    }

    header_file << "}";

    header_file.close();

    // source file

    std::ofstream cpp_file{cpp};

    cpp_file << info;

    if (opt.date)
        cpp_file << date;

    cpp_file << "#include \"" << opt.header
             << "\""
                "\n";
    cpp_file << "#include <iostream> \n";
    cpp_file << "#include <cstring> \n";
    cpp_file << "#include <optional> \n";
    cpp_file << "#include <string> \n";
    cpp_file << "#include <ranges> \n";
    cpp_file << "#include <array> \n";
    cpp_file << "namespace args {"
             << "\n";

    cpp_file << "inline auto check_flag(bool&flag, char* current_arg,  const char* arg) {"
             << "\n";
    cpp_file << tab << "if (flag) return false;"
             << "\n";
    cpp_file << tab << "flag = std::strcmp(current_arg, arg) == 0;"
             << "\n";
    cpp_file << tab << "return flag;"
             << "\n";
    cpp_file << "}\n";

    cpp_file << "inline auto check_string(std::optional<std::string>&string_arg, int&i,char* current_arg, int argc, "
                "char* argv[], const "
                "char* arg) {"
             << "\n";
    cpp_file << tab << "if (string_arg.has_value()) return false;"
             << "\n";
    cpp_file << tab << "if (i < argc - 1 && std::strcmp(arg, current_arg) == 0) {"
             << "\n";
    cpp_file << tab_2 << "string_arg = std::string {argv[i+1]};"
             << "\n";
    cpp_file << tab_2 << "i = i + 1;"
             << "\n";
    cpp_file << tab_2 << "return true;"
             << "\n";
    cpp_file << tab << "}\n";
    cpp_file << tab << "return false;\n";
    cpp_file << "}\n";

    cpp_file << "const arguments parse(int argc, char* argv[]) {"
             << "\n";
    cpp_file << tab << "arguments result {};"
             << "\n";

    cpp_file << tab << "for (auto i = 1; i < argc; ++i) {"
             << "\n";

    cpp_file << tab_2 << "auto* arg = argv[i];"
             << "\n";

    std::string else_if = "if";

    for (const auto& arg : args.args)
    {
        if (arg.type == TYPE::FLAG)
        {

            cpp_file << tab_2 << "if (check_flag(result." << arg.name << ", arg, \"" << opt.hyphen << arg.name << "\"))"
                     << "\n";

            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
        else if (arg.type == TYPE::STRING)
        {
            cpp_file << tab_2 << "if (check_string(result." << arg.name << ", i, arg, argc, argv, \"" << opt.hyphen
                     << arg.name << "\"))"
                     << "\n";
            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
        else if (arg.type == TYPE::INT)
        {
            cpp_file << tab_2 << else_if << " (!result." << arg.name << ".has_value()) {"
                     << "\n";

            cpp_file << tab_3 << "if (i < argc - 1 && std::strcmp(arg, \"" << opt.hyphen << arg.name << "\") == 0) {"
                     << "\n";

            cpp_file << tab_4 << "try {"
                     << "\n";
            cpp_file << tab_5 << "result." << arg.name << " = std::stoi(std::string{argv[i+1]}); ++i;"
                     << "\n";
            cpp_file << tab_4 << "} catch (const std::exception&) {}"
                     << "\n";
            cpp_file << tab_4 << "i = i + 1;"
                     << "\n";
            cpp_file << tab_4 << "continue;"
                     << "\n";
            cpp_file << tab_3 << "}"
                     << "\n";
            cpp_file << tab_2 << "}"
                     << "\n";
        }
        else if (arg.type == TYPE::DOUBLE)
        {
            cpp_file << tab_2 << else_if << " (!result." << arg.name << ".has_value()) {"
                     << "\n";

            cpp_file << tab_3 << "if (i < argc - 1 && std::strcmp(arg, \"" << opt.hyphen << arg.name << "\") == 0) {"
                     << "\n";
            cpp_file << tab_4 << "try {"
                     << "\n";
            cpp_file << tab_5 << "result." << arg.name << " = std::stod(std::string{argv[i+1]}); ++i;"
                     << "\n";
            cpp_file << tab_4 << "} catch (const std::exception&) {}"
                     << "\n";
            cpp_file << tab_4 << "i = i + 1;"
                     << "\n";
            cpp_file << tab_4 << "continue;"
                     << "\n";
            cpp_file << tab_3 << "}"
                     << "\n";
            cpp_file << tab_2 << "}"
                     << "\n";
        }
    }

    cpp_file << tab << "}"
             << "\n";
    cpp_file << tab << "return result;"
             << "\n";
    cpp_file << "}\n";

    if (opt.print)
    {
        cpp_file << "void print_help() {"
                 << "\n";

        size_t max_length = 0;

        for (const auto& arg : args.args)
            if (auto length = arg.name.length(); length > max_length)
                max_length = length;

        cpp_file << tab << "std::cout << \"Options:\" << \"\\n\";\n";

        for (const auto& arg : args.args)
        {
            auto tmp_string = arg.name;
            if (auto diff = max_length - tmp_string.length(); diff > 0)
                tmp_string.append(diff, ' ');

            static const std::map<TYPE, std::string> map_type_desc = {{TYPE::DOUBLE, "<double>"},
                                                                      {TYPE::INT, "<int>   "},
                                                                      {TYPE::STRING, "<string>"},
                                                                      {TYPE::FLAG, "        "}};

            cpp_file << tab << "std::cout << \"" << opt.hyphen << tmp_string << " " << map_type_desc.at(arg.type)
                     << " = " << arg.desc << "\" << \"\\n\";\n";
        }

        cpp_file << "}"
                 << "\n";
    }

    cpp_file << "}\n";

    cpp_file.close();
}

} // namespace generator
