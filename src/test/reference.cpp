// Generated with https://github.com/SebastianBach/cmdl-args 
#include <iostream>
#include <cstring>
#include <optional>
#include <string>
#include "parser.h"
namespace cmdl_args {
static arguments s_args;
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
inline auto check_double(std::optional<double>&double_arg, int&i, int argc, char* argv[], const char* arg) {
  if (double_arg.has_value()) return false;
  if (i < argc - 1 && std::strcmp(arg, argv[i]) == 0) {
    try { double_arg = std::stod(std::string{argv[i + 1]});} catch (const std::exception&) {}  
    ++i;
    return true;
  }
  return false;
}
const arguments& parse(int argc, char* argv[]) {
  for (auto i = 1; i < argc; ++i) {
    if (check_flag(s_args.test, argv[i], "--test"))
      continue;

    if (check_string(s_args.i, i, argc, argv, "--i"))
      continue;

    if (check_string(s_args.o, i, argc, argv, "--o"))
      continue;

    if (check_int(s_args.cnt, i, argc, argv, "--cnt"))
      continue;

    if (check_double(s_args.r, i, argc, argv, "--r"))
      continue;

  }
  return s_args;
}
void print_help() {
  std::cout << "Options:" << "\n";
  std::cout << "--test          = Test Flag" << "\n";
  std::cout << "--i    <string> = Test Input" << "\n";
  std::cout << "--o    <string> = Test Output" << "\n";
  std::cout << "--cnt  <int>    = Count" << "\n";
  std::cout << "--r    <double> = Ratio" << "\n";
}
void print_values(const arguments&args) {
  std::cout << std::boolalpha;
  std::cout << "--test = " << args.test << "\n";
  std::cout << "--i    ";
  if (args.i.has_value()) { std::cout<< "= " << args.i.value() << "\n"; }
  else { std::cout<< "not set" << "\n"; }
  std::cout << "--o    ";
  if (args.o.has_value()) { std::cout<< "= " << args.o.value() << "\n"; }
  else { std::cout<< "not set" << "\n"; }
  std::cout << "--cnt  ";
  if (args.cnt.has_value()) { std::cout<< "= " << args.cnt.value() << "\n"; }
  else { std::cout<< "not set" << "\n"; }
  std::cout << "--r    ";
  if (args.r.has_value()) { std::cout<< "= " << args.r.value() << "\n"; }
  else { std::cout<< "not set" << "\n"; }
}
}
