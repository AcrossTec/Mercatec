#pragma once

//
// Foreach Macro in C:
//  https://dev.to/sgf4/foreach-macro-in-c-48ic
//
// Recursive Macros in C/C++:
//  http://www.individual.utoronto.ca/dfr/hmmmm/2020/07/26/1.html
//
// Recursive macros with C++20 __VA_OPT__:
//  https://www.scs.stanford.edu/~dm/blog/va-opt.html
//
// C/C++ Preprocessor Metaprogramming - Recursion:
//  http://saadahmad.ca/cc-preprocessor-metaprogramming-recursion/
//
// Replacing text macros:
//  https://en.cppreference.com/w/cpp/preprocessor/replace
//
// Announcing full support for a C/C++ conformant preprocessor in MSVC:
//  https://devblogs.microsoft.com/cppblog/announcing-full-support-for-a-c-c-conformant-preprocessor-in-msvc/
//
// clang-format off
//

#define MERCATEC_PARENS ()

#define MERCATEC_EXPAND(...)  MERCATEC_EXPAND4(MERCATEC_EXPAND4(MERCATEC_EXPAND4(MERCATEC_EXPAND4(__VA_ARGS__))))
#define MERCATEC_EXPAND4(...) MERCATEC_EXPAND3(MERCATEC_EXPAND3(MERCATEC_EXPAND3(MERCATEC_EXPAND3(__VA_ARGS__))))
#define MERCATEC_EXPAND3(...) MERCATEC_EXPAND2(MERCATEC_EXPAND2(MERCATEC_EXPAND2(MERCATEC_EXPAND2(__VA_ARGS__))))
#define MERCATEC_EXPAND2(...) MERCATEC_EXPAND1(MERCATEC_EXPAND1(MERCATEC_EXPAND1(MERCATEC_EXPAND1(__VA_ARGS__))))
#define MERCATEC_EXPAND1(...) __VA_ARGS__

#define MERCATEC_FOR_EACH(MACRO, ...)                                         \
  __VA_OPT__(MERCATEC_EXPAND(MERCATEC_FOR_EACH_HELPER(MACRO, __VA_ARGS__)))

#define MERCATEC_FOR_EACH_HELPER(MACRO, ARG1, ...)                            \
  MACRO(ARG1)                                                                 \
  __VA_OPT__(MERCATEC_FOR_EACH_AGAIN MERCATEC_PARENS (MACRO, __VA_ARGS__))

#define MERCATEC_FOR_EACH_AGAIN() MERCATEC_FOR_EACH_HELPER

#define MERCATEC_COMMA(EXPRESSION) EXPRESSION,

//
// clang-format on
//
