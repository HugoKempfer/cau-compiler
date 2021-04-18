//
// Created by hugo on 4/17/21.
//

#ifndef LEXER_AUTOMATA_HPP
#define LEXER_AUTOMATA_HPP

#include <string>
#include <vector>

using DFA = const struct State *;

enum TokenType {
  BOOL,
  KEYWORD,
  ITERATIVE,
  CONDITIONAL,
  ARTITH_OP,
  ASSIGN,
  CMP_OP,
  SC,
  BLOCK,
  PAREN,
  ARRAY,
  COMMA,
  V_TYPE,
  ID,
  LITERAL,
  S_INT,
  S_CHAR,
  WHITESPACE,
  NONE
};
enum Alphabet { DIGIT, LETTER, POSITIVE_INT };

struct State;

typedef struct {
  TokenType type;
  std::string value;
} Token;

// Represent a transition to another state
typedef struct Transition {
  enum {
    ALPH,
    EXPR,
    DFA         // Tag for union (Algebraic data type)
  } value_type; // can either be an expression to match, alphabet or a reference
                // to another DFA
  union {
    enum Alphabet alphabet;
    const char *expression;
    const ::DFA dfa;
  } value;
  enum {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I // New state index
  } new_state;
} Transition;

struct State {
  bool is_accepting;
  std::vector<Transition> transitions;
};

std::vector<Token> get_tokens(std::string char_stream);

#endif // LEXER_AUTOMATA_HPP
