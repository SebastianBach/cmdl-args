// Generated with https://github.com/SebastianBach/cmdl-args 
// Created Mar 16, 2023 
#pragma once
#include <optional>
#include <string>
namespace args {
struct arguments {
    arguments(const arguments&) = delete;
    arguments() = default;

    // Print help text.
    // True if the flag was set, otherwise false.
    bool help;

    // Print version.
    // True if the flag was set, otherwise false.
    bool version;

    // Input File.
    // Empty if the argument was not set.
    std::optional<std::string> i;

    // Output Folder.
    // Empty if the argument was not set.
    std::optional<std::string> o;

    // Output Header File.
    // Empty if the argument was not set.
    std::optional<std::string> header;

    // Output Source File.
    // Empty if the argument was not set.
    std::optional<std::string> cpp;

    // Use pragma as include guard.
    // True if the flag was set, otherwise false.
    bool pragma;

    // Namespace.
    // Empty if the argument was not set.
    std::optional<std::string> space;

    // Characters preceding the arguments.
    // Empty if the argument was not set.
    std::optional<std::string> hyphen;

    // Tab size.
    // Empty if the argument was not set.
    std::optional<int> tab;

    // Enable comments.
    // True if the flag was set, otherwise false.
    bool comments;

    // Include creation date.
    // True if the flag was set, otherwise false.
    bool date;

    // Include print_help() function.
    // True if the flag was set, otherwise false.
    bool print;

    // Include print_values() function.
    // True if the flag was set, otherwise false.
    bool values;

    // Verbose Output.
    // True if the flag was set, otherwise false.
    bool v;
};
const arguments& parse(int argc, char* argv[]);
// Print help text to standard output.
void print_help();
// Print arguments to standard output.
void print_values(const arguments&);
}
