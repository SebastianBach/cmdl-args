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
const arguments parse(int argc, char* argv[]) {
    arguments result {};
    for (auto i = 1; i < argc; ++i) {
        auto* arg = argv[i];
        if (!result.help) {
            if (std::strcmp(arg, "--help") == 0) {
                result.help = true;
                continue;
            }
        }
        if (!result.i.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--i") == 0) {
                result.i = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.o.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--o") == 0) {
                result.o = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.header.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--header") == 0) {
                result.header = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.cpp.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--cpp") == 0) {
                result.cpp = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.pragma) {
            if (std::strcmp(arg, "--pragma") == 0) {
                result.pragma = true;
                continue;
            }
        }
        if (!result.space.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--space") == 0) {
                result.space = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.hyphen.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--hyphen") == 0) {
                result.hyphen = std::string {argv[i+1]};
                i = i + 1;
                continue;
            }
        }
        if (!result.tab.has_value()) {
            if (i < argc - 1 && std::strcmp(arg, "--tab") == 0) {
                try {
                    result.tab = std::stoi(std::string{argv[i+1]}); ++i;
                } catch (const std::exception&) {}
                i = i + 1;
                continue;
            }
        }
        if (!result.comments) {
            if (std::strcmp(arg, "--comments") == 0) {
                result.comments = true;
                continue;
            }
        }
        if (!result.date) {
            if (std::strcmp(arg, "--date") == 0) {
                result.date = true;
                continue;
            }
        }
        if (!result.print) {
            if (std::strcmp(arg, "--print") == 0) {
                result.print = true;
                continue;
            }
        }
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
