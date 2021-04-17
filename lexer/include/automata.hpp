//
// Created by hugo on 4/17/21.
//

#ifndef LEXER_AUTOMATA_HPP
#define LEXER_AUTOMATA_HPP

#include <vector>
#include <string>

using DFA = const struct State*;

enum TokenType { BOOL, NONE };
enum Alphabet { DIGIT, LETTER, NUMBERS, POSITIVE_INT };

struct State;

typedef struct {
    TokenType type;
    std::string value;
} Token;

typedef struct Transition {
  enum { ALPH, EXPR, DFA } value_type;
  union {
    enum Alphabet alphabet;
    const char *expression;
    const ::DFA dfa;
  } value;
  enum { A, B, C, D, E, F, G, H, I } new_state;
} Transition;

struct State {
  bool is_accepting;
  std::vector<Transition> transitions;
};

#endif // LEXER_AUTOMATA_HPP
