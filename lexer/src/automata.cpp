#include "../include/automata.hpp"
#include "../include/tokens.hpp"
#include <stdexcept>

typedef struct {
  const State *dfa;
  TokenType type;
} DFAListItem;

// Token matching table, the order define the lexing precedence
static const DFAListItem TokensDFA[] = {{KeywordsToken, KEYWORD},
                                        {VTypeToken, V_TYPE},
                                        {IterativeToken, ITERATIVE},
                                        {ConditionalToken, CONDITIONAL},
                                        {SIntToken, S_INT},
                                        {BoolToken, BOOL},
                                        {ArithOpToken, ARTITH_OP},
                                        {IDToken, ID},
                                        {LiteralToken, LITERAL},
                                        {CmpOpToken, CMP_OP},
                                        {BlockToken, BLOCK},
                                        {ParenToken, PAREN},
                                        {SCToken, SC},
                                        {ArrayToken, ARRAY},
                                        {AssignToken, ASSIGN},
                                        {CommaToken, COMMA},
                                        {SCharToken, S_CHAR},
                                        {WhiteSpaceToken, WHITESPACE},
                                        {nullptr, NONE}};

// Check if a char is part of a charset (alphabet)
size_t match_with_alphabet(Alphabet alphabet, std::string &str) {
  switch (alphabet) {
  case DIGIT:
    return (str[0] >= '0' && str[0] <= '9') ? 1 : 0;
  case LETTER:
    return isalpha(str[0]) ? 1 : 0;
  case POSITIVE_INT:
    return (str[0] >= '1' && str[0] <= '9') ? 1 : 0;
  }
  return 0;
}

// Check if the given expression is part of the charstream
size_t match_with_expression(const std::string &expr, std::string &str) {
  try {
    if (str.substr(0, expr.length()) == expr) {
      return expr.length();
    }
  } catch (std::out_of_range &err) {
    return 0;
  }
  return 0;
}

// Check if the provided string matches the given DFA. Returns the number of
// matching characters
size_t match_dfa(std::string &str, const State *dfa) {
  size_t res;
  size_t total_shift = 0;
  auto current_state =
      &dfa[Transition::A];             // Set current state to entry A state
  auto char_stream = std::string(str); // Local deep copy of charstream

  do {
    res = 0;
    // Try each transition until one is valid
    for (auto transition : current_state->transitions) {
      switch (transition.value_type) {
      case Transition::ALPH:
        res = match_with_alphabet(transition.value.alphabet, char_stream);
        break;
      case Transition::EXPR:
        res = match_with_expression(transition.value.expression, char_stream);
        break;
      case Transition::DFA:
        res = match_dfa(char_stream, transition.value.dfa);
        break;
      }
      if (res > 0) {
        current_state = &dfa[transition.new_state];
        break;
      }
    }
    total_shift += res;
    try {
      char_stream = char_stream.substr(res, char_stream.length());
    } catch (std::out_of_range &err) {
      break;
    }
  } while (res > 0); // Keep trying to reach new state until stuck
  if (current_state->is_accepting) {
    return total_shift;
  } else {
    return 0; // 0 char are matched for this token DFA
  }
}

// Find next matching token in charstream
Token get_next_token(std::string &str, const DFAListItem *dfas,
                     TokenType previous_token_type) {
  for (auto current_dfa = dfas; current_dfa->type != NONE; ++current_dfa) {
    auto res = match_dfa(str, current_dfa->dfa);
    if (res > 0) {
      Token token = {current_dfa->type, str.substr(0, res)};
      if (token.type == S_INT && token.value[0] == '-' &&
          previous_token_type == S_INT) {
        continue;
      }
      return token;
    }
  }
  return {NONE, str};
}

std::vector<Token> get_tokens(std::string char_stream) {
  std::vector<Token> tokens;
  Token current_token = {NONE, ""};

  do {
    if (char_stream.empty()) {
      break;
    }
    current_token = get_next_token(char_stream, TokensDFA, current_token.type);
    if (current_token.type != NONE) {
      try {
        char_stream = char_stream.substr(current_token.value.length(),
                                         char_stream.length());
      } catch (std::out_of_range &err) {
        break;
      }
    }
    tokens.push_back(current_token);
  } while (current_token.type != NONE);
  return tokens;
}
