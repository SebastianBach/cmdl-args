// Generated with https://github.com/SebastianBach/cmdl-args 
#pragma once
#include <optional>
#include <string>
namespace cmdl_args {
struct arguments {
  arguments(const arguments&) = delete;
  arguments() = default;

  // Test Flag
  // True if the flag was set, otherwise false.
  bool test;

  // Test Input
  // Empty if the argument was not set.
  std::optional<std::string> i;

  // Test Output
  // Empty if the argument was not set.
  std::optional<std::string> o;

  // Count
  // Empty if the argument was not set.
  std::optional<int> cnt;

  // Ratio
  // Empty if the argument was not set.
  std::optional<double> r;
};
const arguments& parse(int argc, char* argv[]);
// Print help text to standard output.
void print_help();
// Print arguments to standard output.
void print_values(const arguments&);
}
