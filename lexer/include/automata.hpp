//
// Created by hugo on 4/17/21.
//

#ifndef LEXER_AUTOMATA_HPP
#define LEXER_AUTOMATA_HPP

#include <vector>

#define ARR_SIZE(arr) sizeof(arr) / sizeof(*arr)

enum TokenType { BOOL, NONE };
enum Alphabet { DIGITS, LETTERS, NUMBERS, POSITIVE_INT };

struct State;

typedef struct Transition {
  enum { ALPH, EXPR, DFA } value_type;
  union {
    enum Alphabet alphabet;
    const char *expression;
    const struct State *dfa;
  } value;
  enum { A, B, C, D, E, F, G, H, I } new_state;
} Transition;

struct State {
  bool is_accepting;
  std::vector<Transition> transitions;
};

#endif // LEXER_AUTOMATA_HPP
