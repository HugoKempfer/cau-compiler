#ifndef TOKENS_HPP
#define TOKENS_HPP

#include "../include/automata.hpp"

static const State BoolToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "true"}, Transition::B},
      {Transition::EXPR, {.expression = "false"}, Transition::B}}},
    {true, {}}};

static const State VTypeToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "int"}, Transition::B},
      {Transition::EXPR, {.expression = "char"}, Transition::B},
      {Transition::EXPR, {.expression = "boolean"}, Transition::B},
      {Transition::EXPR, {.expression = "String"}, Transition::B}}},
    {true, {}}};

static const State SInt[] = {
    {false,
     {{Transition::EXPR, {.expression = "-"}, Transition::B},
      {Transition::EXPR, {.expression = "0"}, Transition::C},
      {Transition::ALPH, {.alphabet = Alphabet::POSITIVE_INT}, Transition::D}}},
    {false,
     {{Transition::ALPH, {.alphabet = Alphabet::POSITIVE_INT}, Transition::D}}},
    {true, {}},
    {true, {{Transition::ALPH, {.alphabet = Alphabet::NUMBERS}, Transition::E}}},
    {true, {{Transition::ALPH, {.alphabet = Alphabet::NUMBERS}, Transition::E}}}
};

#endif /* ifndef TOKENS_HPP */
