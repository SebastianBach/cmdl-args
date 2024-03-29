#pragma once
#include "generator.h"
#include <array>

// compile time unit tests

template <auto N> constexpr auto to_array(const char (&a)[N])
{
    static_assert(N > 0);
    std::array<char, N - 1> out{};
    for (auto i = 0u; i < N - 1; ++i)
        out[i] = a[i];
    return out;
}

template <auto N, auto D>
constexpr auto check_token(const char (&a)[N], generator::token& token, const std::array<char, D>& data)
{
    const auto ref_length = N - 1;

    const auto diff = token.end - token.start + 1;
    if (diff != ref_length)
        return false;

    return std::equal(std::begin(a), std::end(a) - 1, std::begin(data) + token.start);
}

template <auto N, auto T>
constexpr auto test_scanner(const char (&input)[N], const char (&expected_token)[T], auto idx, auto exp)
{
    auto data = to_array(input);

    generator::token_array tokens;

    auto cnt = generator::scanner(data, tokens);

    if (cnt != exp)
        return false;

    if (!check_token(expected_token, tokens[idx], data))
        return false;

    return true;
}

#define TEST(ARG, MSG)                                                                                                 \
    static_assert(ARG, MSG);                                                                                           \
    if (!ARG)                                                                                                          \
        sucess = false;

constexpr auto run_tests()
{

    auto sucess = true;
    {
        const auto res = test_scanner("test:t:test argument", "test", 0, 3);
        TEST(res, "Test first token")
    }
    {
        const auto res = test_scanner("test:t:test argument", "t", 1, 3);
        TEST(res, "Test second token")
    }
    {
        const auto res = test_scanner("test:t:test argument", "test argument", 2, 3);
        TEST(res, "Test third token")
    }
    {
        const auto res = test_scanner("test:t:test argument:more:stuff", "test", 0, 3);
        TEST(res, "Test big input")
    }
    {
        const auto res = test_scanner("test:stuff", "test", 0, 2);
        TEST(res, "Test small input")
    }

    return sucess;
}