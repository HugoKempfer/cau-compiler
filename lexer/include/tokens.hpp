#ifndef TOKENS_HPP
#define TOKENS_HPP

#include "../include/automata.hpp"

static const State WhiteSpaceToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "\n"}, Transition::B},
      {Transition::EXPR, {.expression = " "}, Transition::B},
      {Transition::EXPR, {.expression = "\t"}, Transition::B}}},
    {true, {}}};

static const State NumbersToken[] = {
    {false, {{Transition::ALPH, {.alphabet = Alphabet::DIGIT}, Transition::B}}},
    {true, {{Transition::ALPH, {.alphabet = Alphabet::DIGIT}, Transition::B}}}};

static const State VTypeToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "int"}, Transition::B},
      {Transition::EXPR, {.expression = "char"}, Transition::B},
      {Transition::EXPR, {.expression = "boolean"}, Transition::B},
      {Transition::EXPR, {.expression = "String"}, Transition::B}}},
    {true, {}}};

static const State SIntToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "-"}, Transition::B},
      {Transition::EXPR, {.expression = "0"}, Transition::C},
      {Transition::ALPH, {.alphabet = Alphabet::POSITIVE_INT}, Transition::D}}},
    {false,
     {{Transition::ALPH, {.alphabet = Alphabet::POSITIVE_INT}, Transition::D}}},
    {true, {}},
    {true, {{Transition::DFA, {.dfa = NumbersToken}, Transition::E}}},
    {true, {{Transition::DFA, {.dfa = NumbersToken}, Transition::E}}}};

static const State SCharToken[] = {
    {false, {{Transition::EXPR, {.expression = "'"}, Transition::B}}},
    {false, {{Transition::EXPR, {.expression = "."}, Transition::C}}},
    {false, {{Transition::EXPR, {.expression = "'"}, Transition::D}}},
    {true, {}}};

static const State BoolToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "true"}, Transition::B},
      {Transition::EXPR, {.expression = "false"}, Transition::B}}},
    {true, {}}};

static const State LiteralToken[] = {
    {false, {{Transition::EXPR, {.expression = "\""}, Transition::B}}},
    {false,
     {{Transition::EXPR, {.expression = "\""}, Transition::C},
      {Transition::ALPH, {.alphabet = Alphabet::DIGIT}, Transition::B},
      {Transition::ALPH, {.alphabet = Alphabet::LETTER}, Transition::B},
      {Transition::ALPH, {.dfa = WhiteSpaceToken}, Transition::B}}},
    {true, {}}};

static const State IDToken[] = {
    {false,
     {{Transition::ALPH, {.alphabet = Alphabet::LETTER}, Transition::B},
      {Transition::EXPR, {.expression = "_"}, Transition::B}}},
    {true,
     {{Transition::ALPH, {.alphabet = Alphabet::LETTER}, Transition::B},
      {Transition::DFA, {.dfa = NumbersToken}, Transition::B},
      {Transition::EXPR, {.expression = "_"}, Transition::B}}}};

static const State ConditionalToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "if"}, Transition::B},
      {Transition::EXPR, {.expression = "else"}, Transition::B}}},
    {true, {}}};

static const State IterativeToken[] = {
    {false, {{Transition::EXPR, {.expression = "while"}, Transition::B}}},
    {true, {}}};

static const State KeywordsToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "class"}, Transition::B},
      {Transition::EXPR, {.expression = "return"}, Transition::B}}},
    {true, {}}};

static const State ArithOpToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "+"}, Transition::B},
      {Transition::EXPR, {.expression = "-"}, Transition::B},
      {Transition::EXPR, {.expression = "*"}, Transition::B},
      {Transition::EXPR, {.expression = "/"}, Transition::B}}},
    {true, {}}};

static const State AssignToken[] = {
    {false, {{Transition::EXPR, {.expression = "="}, Transition::B}}},
    {true, {}}};

static const State CmpOpToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "!"}, Transition::B},
      {Transition::EXPR, {.expression = "<"}, Transition::C},
      {Transition::EXPR, {.expression = ">"}, Transition::E},
      {Transition::EXPR, {.expression = "="}, Transition::D}}},
    {false, {{Transition::EXPR, {.expression = "="}, Transition::F}}},
    {true, {{Transition::EXPR, {.expression = "="}, Transition::G}}},
    {false, {{Transition::EXPR, {.expression = "="}, Transition::H}}},
    {true, {{Transition::EXPR, {.expression = "="}, Transition::I}}},
    {true, {}}};

static const State SCToken[] = {
    {false, {{Transition::EXPR, {.expression = ";"}, Transition::B}}},
    {true, {}}};

static const State BlockToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "{"}, Transition::B},
      {Transition::EXPR, {.expression = "}"}, Transition::B}}},
    {true, {}}};

static const State ParenToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "("}, Transition::B},
      {Transition::EXPR, {.expression = ")"}, Transition::B}}},
    {true, {}}};

static const State ArrayToken[] = {
    {false,
     {{Transition::EXPR, {.expression = "["}, Transition::B},
      {Transition::EXPR, {.expression = "]"}, Transition::B}}},
    {true, {}}};

static const State CommaToken[] = {
    {false, {{Transition::EXPR, {.expression = ","}, Transition::B}}},
    {true, {}}};

#endif /* ifndef TOKENS_HPP */
