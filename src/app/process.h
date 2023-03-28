#pragma once
#include "parser.h"
#include <tuple>

enum class RETURN_VALUE
{
    SUCCESS             = 0,
    MISSING_ARGS        = 3,
    FAILURE_INTPUT_FILE = 1,
    FAILURE_OUTPUT_FILE = 2
};

using process_success = std::tuple<RETURN_VALUE, std::string>;

process_success process(const args::arguments& app_arguments);
