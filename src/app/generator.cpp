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

#if defined(__cpp_lib_format)
#include <format>
#endif

namespace generator
{

inline const char* pragma_once()
{
    return "#pragma once\n";
}
#if defined(__cpp_lib_format)
inline std::string include_local(const std::string& file)
{
    return std::format("#include \"{}\"\n", file);
}

inline std::string include_stl(const std::string& lib)
{
    return std::format("#include <{}>\n", lib);
}

inline std::string start_namespace(const std::string& name)
{
    return std::format("namespace {} {{\n", name);
}

inline std::string comment(const char* text)
{
    return std::format("// {}\n", text);
}
inline std::string format_year(auto month, auto day, auto year)
{
    std::format("// Created {} {}, {} \n", month, day, year);
}

#else
inline std::string include_local(const std::string& file)
{
    return std::string{"#include \""} + file + std::string{"\"\n"};
}

inline std::string include_stl(const std::string& lib)
{
    return std::string{"#include <\">"} + lib + std::string{">\n"};
}

inline std::string start_namespace(const std::string& name)
{
    return std::string{"namespace "} + name + std::string{" {\n"};
}

inline std::string comment(const char* text)
{
    return std::string{"// "} + text + std::string{"\n"};
}
inline std::string format_year(auto month, auto day, auto year)
{
    return std::string{"// Created "};
}
#endif

inline const char* close()
{
    return "}\n";
}

inline std::string info()
{
    return "// Generated with https://github.com/SebastianBach/cmdl-args \n";
}

void generate_header(const arguments& args, const options& opt, std::ofstream& header_file, const std::string& date)
{
    const auto tab = opt.tab;

    // header file

    header_file << info();
    if (opt.date)
        header_file << date;

    if (opt.pragma)
    {
        header_file << pragma_once();
    }
    else
    {
        header_file << "#ifndef _PARSER_H__\n";
        header_file << "#define _PARSER_H__\n";
    }

    header_file << include_stl("optional");
    header_file << include_stl("string");

    header_file << start_namespace(opt.space);

    header_file << "struct arguments {"
                << "\n";

    header_file << tab << "arguments(const arguments&) = delete;\n";
    header_file << tab << "arguments() = default;\n";

    for (const auto& arg : args.args)
    {
        header_file << "\n";

        if (opt.comments)
            header_file << tab << comment(arg.desc.c_str());

        if (arg.type == TYPE::FLAG)
        {
            if (opt.comments)
                header_file << tab << comment("True if the flag was set, otherwise false.");

            header_file << tab << "bool " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::STRING)
        {
            if (opt.comments)
                header_file << tab << comment("Empty if the argument was not set.");
            header_file << tab << "std::optional<std::string> " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::INT)
        {
            if (opt.comments)
                header_file << tab << comment("Empty if the argument was not set.");
            header_file << tab << "std::optional<int> " << arg.name << ";\n";
        }
        else if (arg.type == TYPE::DOUBLE)
        {
            if (opt.comments)
                header_file << tab << comment("Empty if the argument was not set.");
            header_file << tab << "std::optional<double> " << arg.name << ";\n";
        }
    }

    header_file << "};\n";

    header_file << "const arguments& parse(int argc, char* argv[]);"
                << "\n";

    if (opt.print)
    {
        if (opt.comments)
            header_file << comment("Print help text to standard output.");

        header_file << "void print_help();"
                    << "\n";
    }
    if (opt.values)
    {
        if (opt.comments)
            header_file << comment("Print arguments to standard output.");

        header_file << "void print_values(const arguments&);"
                    << "\n";
    }

    header_file << close();

    if (!opt.pragma)
    {
        header_file << "#endif\n";
    }
}

void generate_cpp(const arguments& args, const options& opt, std::ofstream& cpp_file, const std::string& date)
{
    const auto tab   = opt.tab;
    const auto tab_2 = tab + tab;
    const auto tab_3 = tab + tab + tab;
    const auto tab_4 = tab + tab + tab + tab;
    const auto tab_5 = tab + tab + tab + tab + tab;

    bool has_flags   = false;
    bool has_strings = false;
    bool has_ints    = false;
    bool has_doubles = false;

    for (const auto& arg : args.args)
    {
        if (arg.type == TYPE::FLAG)
        {
            has_flags = true;
        }
        else if (arg.type == TYPE::STRING)
        {
            has_strings = true;
        }
        else if (arg.type == TYPE::INT)
        {
            has_ints = true;
        }
        else if (arg.type == TYPE::DOUBLE)
        {
            has_doubles = true;
        }
    }

    cpp_file << info();

    if (opt.date)
        cpp_file << date;

    cpp_file << include_stl("iostream");
    cpp_file << include_stl("cstring");
    cpp_file << include_stl("optional");
    cpp_file << include_stl("string");
    cpp_file << include_local(opt.header);

    cpp_file << start_namespace(opt.space);

    cpp_file << "static arguments s_args;\n";

    if (has_flags)
    {
        cpp_file << "inline auto check_flag(bool&flag, char* current_arg,  const char* arg) {"
                 << "\n";
        cpp_file << tab << "if (flag) return false;"
                 << "\n";
        cpp_file << tab << "flag = std::strcmp(current_arg, arg) == 0;"
                 << "\n";
        cpp_file << tab << "return flag;"
                 << "\n";
        cpp_file << close();
    }

    if (has_strings)
    {
        cpp_file << "inline auto check_string(std::optional<std::string>&string_arg, int&i, int argc, "
                    "char* argv[], const "
                    "char* arg) {"
                 << "\n";
        cpp_file << tab << "if (string_arg.has_value()) return false;"
                 << "\n";
        cpp_file << tab << "if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {"
                 << "\n";
        cpp_file << tab_2 << "string_arg = std::string {argv[i+1]};"
                 << "\n";
        cpp_file << tab_2 << "i = i + 1;"
                 << "\n";
        cpp_file << tab_2 << "return true;"
                 << "\n";
        cpp_file << tab << "}\n";
        cpp_file << tab << "return false;\n";
        cpp_file << close();
    }

    if (has_ints)
    {
        cpp_file
            << "inline auto check_int(std::optional<int>&int_arg, int&i, int argc, char* argv[], const char* arg) {"
            << "\n";
        cpp_file << tab << "if (int_arg.has_value()) return false;"
                 << "\n";

        cpp_file << tab << "if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {"
                 << "\n";

        cpp_file << tab_2 << "try { int_arg = std::stoi(std::string{argv[i + 1]});} catch (const std::exception&) {}  "
                 << "\n";

        cpp_file << tab_2 << "++i;"
                 << "\n";
        cpp_file << tab_2 << "return true;"
                 << "\n";
        cpp_file << tab << "}\n";
        cpp_file << tab << "return false;\n";

        cpp_file << close();
    }

    if (has_doubles)
    {
        cpp_file << "inline auto check_double(std::optional<double>&double_arg, int&i, int argc, char* argv[], const "
                    "char* arg) {"
                 << "\n";
        cpp_file << tab << "if (double_arg.has_value()) return false;"
                 << "\n";

        cpp_file << tab << "if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {"
                 << "\n";

        cpp_file << tab_2
                 << "try { double_arg = std::stod(std::string{argv[i + 1]});} catch (const std::exception&) {}  "
                 << "\n";

        cpp_file << tab_2 << "++i;"
                 << "\n";
        cpp_file << tab_2 << "return true;"
                 << "\n";
        cpp_file << tab << "}\n";
        cpp_file << tab << "return false;\n";

        cpp_file << close();
    }

    cpp_file << "const arguments& parse(int argc, char* argv[]) {"
             << "\n";
    cpp_file << tab << "for (auto i = 1; i < argc; ++i) {"
             << "\n";

    for (const auto& arg : args.args)
    {
        if (arg.type == TYPE::FLAG)
        {
            cpp_file << tab_2 << "if (check_flag(s_args." << arg.name << ", argv[i], \"" << opt.hyphen << arg.name
                     << "\"))"
                     << "\n";

            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
        else if (arg.type == TYPE::STRING)
        {
            cpp_file << tab_2 << "if (check_string(s_args." << arg.name << ", i, argc, argv, \"" << opt.hyphen
                     << arg.name << "\"))"
                     << "\n";
            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
        else if (arg.type == TYPE::INT)
        {
            cpp_file << tab_2 << "if (check_int(s_args." << arg.name << ", i, argc, argv, \"" << opt.hyphen << arg.name
                     << "\"))"
                     << "\n";
            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
        else if (arg.type == TYPE::DOUBLE)
        {
            cpp_file << tab_2 << "if (check_double(s_args." << arg.name << ", i, argc, argv, \"" << opt.hyphen
                     << arg.name << "\"))"
                     << "\n";
            cpp_file << tab_3 << "continue;"
                     << "\n"
                     << "\n";
        }
    }

    cpp_file << tab << "}"
             << "\n";
    cpp_file << tab << "return s_args;"
             << "\n";
    cpp_file << close();

    size_t max_length = 0;
    for (const auto& arg : args.args)
        if (auto length = arg.name.length(); length > max_length)
            max_length = length;

    if (opt.print)
    {
        cpp_file << "void print_help() {"
                 << "\n";

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

        cpp_file << close();
    }

    if (opt.values)
    {
        cpp_file << "void print_values(const arguments&args) {"
                 << "\n";

        cpp_file << tab << "std::cout << std::boolalpha;"
                 << "\n";

        for (const auto& arg : args.args)
        {
            auto tmp_string = arg.name;
            if (auto diff = max_length - tmp_string.length(); diff > 0)
                tmp_string.append(diff, ' ');

            if (arg.type == TYPE::FLAG)
            {
                cpp_file << tab << "std::cout << \"" << opt.hyphen << tmp_string << " = \" << args." << arg.name
                         << " << \"\\n\";"
                         << "\n";
            }
            else
            {
                cpp_file << tab << "std::cout << \"" << opt.hyphen << tmp_string << " \";"
                         << "\n";

                cpp_file << tab << "if (args." << arg.name << ".has_value()) { std::cout<< \"= \" << args." << arg.name
                         << ".value() << \"\\n\"; }"
                         << "\n";
                cpp_file << tab << "else { std::cout<< \"not set\" << \"\\n\"; }"
                         << "\n";
            }
        }
        cpp_file << close();
    }

    cpp_file << close();
}

void make_result(const arguments& args, std::ofstream& header_file, std::ofstream& cpp_file, const options& opt)
{
    std::string date{"unknown"};

    if (opt.date)
    {
#if defined(__cpp_lib_chrono) && __cpp_lib_chrono >= 201907
        const auto now       = std::chrono::system_clock::now();
        const auto local_now = std::chrono::zoned_time(std::chrono::current_zone(), now);
        const auto ymd = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(local_now.get_local_time())};

        date = format_year(ymd.month(), ymd.day(), ymd.year());
#endif
    }

    generate_header(args, opt, header_file, date);
    generate_cpp(args, opt, cpp_file, date);

    // source file
}

} // namespace generator
