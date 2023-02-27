// Generated with https://github.com/SebastianBach/cmdl-args 
// Created 2023-2-27 
#pragma once
#include <optional>
#include <string>
namespace args {
struct arguments {

    // Print help text
    // True if the flag was set, otherwise false.
    bool help;

    // Input File
    // Empty if the argument was not set.
    std::optional<std::string> i;

    // Output Folder
    // Empty if the argument was not set.
    std::optional<std::string> o;

    // Output Header File
    // Empty if the argument was not set.
    std::optional<std::string> header;

    // Output Source File
    // Empty if the argument was not set.
    std::optional<std::string> cpp;

    // Use pragma as include guard
    // True if the flag was set, otherwise false.
    bool pragma;

    // Namespace
    // Empty if the argument was not set.
    std::optional<std::string> space;

    // Characters preceding the arguments
    // Empty if the argument was not set.
    std::optional<std::string> hyphen;

    // Tab size (Whitespaces)
    // Empty if the argument was not set.
    std::optional<int> tab;

    // Enable comments
    // True if the flag was set, otherwise false.
    bool comments;

    // Include creation date
    // True if the flag was set, otherwise false.
    bool date;

    // Include print_help() function.
    // True if the flag was set, otherwise false.
    bool print;
};
const arguments parse(int argc, char* argv[]);

// Print help text to standard output.
void print_help();
}