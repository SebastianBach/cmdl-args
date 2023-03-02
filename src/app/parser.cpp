// Generated with https://github.com/SebastianBach/cmdl-args 
// Created Mar 02, 2023 
#include <iostream>
#include <cstring>
#include <optional>
#include <string>
#include "parser.h"
namespace args {
inline auto check_flag(bool&flag, char* current_arg,  const char* arg) {
    if (flag) return false;
    flag = std::strcmp(current_arg, arg) == 0;
    return flag;
}
inline auto check_string(std::optional<std::string>&string_arg, int&i, int argc, char* argv[], const char* arg) {
    if (string_arg.has_value()) return false;
    if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {
        string_arg = std::string {argv[i+1]};
        i = i + 1;
        return true;
    }
    return false;
}
inline auto check_int(std::optional<int>&int_arg, int&i, int argc, char* argv[], const char* arg) {
    if (int_arg.has_value()) return false;
    if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {
        try { int_arg = std::stoi(std::string{argv[i + 1]});} catch (const std::exception&) {}  
        ++i;
        return true;
    }
    return false;
}
const arguments parse(int argc, char* argv[]) {
    arguments result {};
    for (auto i = 1; i < argc; ++i) {
        if (check_flag(result.help, argv[i], "--help"))
            continue;

        if (check_string(result.i, i, argc, argv, "--i"))
            continue;

        if (check_string(result.o, i, argc, argv, "--o"))
            continue;

        if (check_string(result.header, i, argc, argv, "--header"))
            continue;

        if (check_string(result.cpp, i, argc, argv, "--cpp"))
            continue;

        if (check_flag(result.pragma, argv[i], "--pragma"))
            continue;

        if (check_string(result.space, i, argc, argv, "--space"))
            continue;

        if (check_string(result.hyphen, i, argc, argv, "--hyphen"))
            continue;

        if (check_int(result.tab, i, argc, argv, "--tab"))
            continue;

        if (check_flag(result.comments, argv[i], "--comments"))
            continue;

        if (check_flag(result.date, argv[i], "--date"))
            continue;

        if (check_flag(result.print, argv[i], "--print"))
            continue;

        if (check_flag(result.values, argv[i], "--values"))
            continue;

        if (check_flag(result.v, argv[i], "--v"))
            continue;

    }
    return result;
}
void print_help() {
    std::cout << "Options:" << "\n";
    std::cout << "--help              = Print help text." << "\n";
    std::cout << "--i        <string> = Input File." << "\n";
    std::cout << "--o        <string> = Output Folder." << "\n";
    std::cout << "--header   <string> = Output Header File." << "\n";
    std::cout << "--cpp      <string> = Output Source File." << "\n";
    std::cout << "--pragma            = Use pragma as include guard." << "\n";
    std::cout << "--space    <string> = Namespace." << "\n";
    std::cout << "--hyphen   <string> = Characters preceding the arguments." << "\n";
    std::cout << "--tab      <int>    = Tab size." << "\n";
    std::cout << "--comments          = Enable comments." << "\n";
    std::cout << "--date              = Include creation date." << "\n";
    std::cout << "--print             = Include print_help() function." << "\n";
    std::cout << "--values            = Include print_values() function." << "\n";
    std::cout << "--v                 = Verbose Output." << "\n";
}
void print_values(const arguments&args) {
    std::cout << std::boolalpha;
    std::cout << "--help     = " << args.help << "\n";
    std::cout << "--i        ";
    if (args.i.has_value()) { std::cout<< "= " << args.i.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--o        ";
    if (args.o.has_value()) { std::cout<< "= " << args.o.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--header   ";
    if (args.header.has_value()) { std::cout<< "= " << args.header.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--cpp      ";
    if (args.cpp.has_value()) { std::cout<< "= " << args.cpp.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--pragma   = " << args.pragma << "\n";
    std::cout << "--space    ";
    if (args.space.has_value()) { std::cout<< "= " << args.space.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--hyphen   ";
    if (args.hyphen.has_value()) { std::cout<< "= " << args.hyphen.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--tab      ";
    if (args.tab.has_value()) { std::cout<< "= " << args.tab.value() << "\n"; }
    else { std::cout<< "not set" << "\n"; }
    std::cout << "--comments = " << args.comments << "\n";
    std::cout << "--date     = " << args.date << "\n";
    std::cout << "--print    = " << args.print << "\n";
    std::cout << "--values   = " << args.values << "\n";
    std::cout << "--v        = " << args.v << "\n";
}
}
