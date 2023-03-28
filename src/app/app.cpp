#include "parser.h"
#include "process.h"
#include "tests.h"
#include <iostream>


static auto version()
{
    return TOOL_VERSION;
}

inline void print_error(const std::string& err)
{
    std::cout << "\033[31m";
    std::cout << err;
    std::cout << "\033[0m";
}

int main(int argc, char* argv[])
{
    // compile time unit tests
    static_assert(run_tests(), "compile time unit tests");

    const auto& app_arguments = args::parse(argc, argv);

    if (app_arguments.help)
    {
        args::print_help();
        return 0;
    }
    else if (app_arguments.version)
    {
        std::cout << version() << std::endl;
        return 0;
    }

    if (app_arguments.v)
    {
        std::cout << "version: " << version() << "\n\n" << std::endl;
        args::print_values(app_arguments);
    }

    const auto [res, err] = process(app_arguments);

    if (res != RETURN_VALUE::SUCCESS)
        print_error(err);

    return static_cast<int>(res);
}
