// Generated with https://github.com/SebastianBach/cmdl-args 
// Created 2023-2-27 
#include "parser.h"
#include <iostream> 
#include <cstring> 
#include <optional> 
#include <string> 
#include <ranges> 
#include <array> 
namespace args {
inline auto check_flag(bool&flag, char* current_arg,  const char* arg) {
    if (flag) return false;
    flag = std::strcmp(current_arg, arg) == 0;
    return flag;
}
inline auto check_string(std::optional<std::string>&string_arg, int&i,char* current_arg, int argc, char* argv[], const char* arg) {
    if (string_arg.has_value()) return false;
    if (i < argc - 1 && std::strcmp(arg, current_arg) == 0) {
        string_arg = std::string {argv[i+1]};
        i = i + 1;
        return true;
    }
    return false;
}
const arguments parse(int argc, char* argv[]) {
    arguments result {};
    for (auto i = 1; i < argc; ++i) {
        auto* arg = argv[i];
        if (check_flag(result.help, arg, "--help"))
            continue;

        if (check_string(result.i, i, arg, argc, argv, "--i"))
            continue;

        if (check_string(result.o, i, arg, argc, argv, "--o"))
            continue;

        if (check_string(result.header, i, arg, argc, argv, "--header"))
            continue;

        if (check_string(result.cpp, i, arg, argc, argv, "--cpp"))
            continue;

        if (check_flag(result.pragma, arg, "--pragma"))
            continue;

        if (check_string(result.space, i, arg, argc, argv, "--space"))
            continue;

        if (check_string(result.hyphen, i, arg, argc, argv, "--hyphen"))
            continue;

        if (!result.tab.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--tab") == 0) {
                try {
                    result.tab = std::stoi(std::string{argv[i+1]}); ++i;
                } catch (const std::exception&) {}
                i = i + 1;
                continue;
            }
        }
        if (check_flag(result.comments, arg, "--comments"))
            continue;

        if (check_flag(result.date, arg, "--date"))
            continue;

        if (check_flag(result.print, arg, "--print"))
            continue;

    }
    return result;
}
void print_help() {
    std::cout << "Options:" << "\n";
    std::cout << "--help              = Print help text" << "\n";
    std::cout << "--i        <string> = Input File" << "\n";
    std::cout << "--o        <string> = Output Folder" << "\n";
    std::cout << "--header   <string> = Output Header File" << "\n";
    std::cout << "--cpp      <string> = Output Source File" << "\n";
    std::cout << "--pragma            = Use pragma as include guard" << "\n";
    std::cout << "--space    <string> = Namespace" << "\n";
    std::cout << "--hyphen   <string> = Characters preceding the arguments" << "\n";
    std::cout << "--tab      <int>    = Tab size (Whitespaces)" << "\n";
    std::cout << "--comments          = Enable comments" << "\n";
    std::cout << "--date              = Include creation date" << "\n";
    std::cout << "--print             = Include print_help() function." << "\n";
}
}
