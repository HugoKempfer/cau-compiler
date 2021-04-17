//
// Created by hugo on 4/17/21.
//

#ifndef LEXER_AUTOMATA_HPP
#define LEXER_AUTOMATA_HPP

#include <vector>

#define ARR_SIZE(arr)   sizeof(arr) / sizeof(*arr)

enum TokenType {BOOL, NONE};
enum Alphabet { DIGITS, LETTERS, NUMBERS };

struct State;

typedef struct Transition {
    enum {ALPH, EXPR, DFA} value_type;
    union {
        enum Alphabet alphabet;
        const char *expression;
        const struct State *dfa;
    } value;
    int new_state_index;
} Transition;

struct State {
    bool is_accepting;
    std::vector<Transition> transitions;
};

#endif //LEXER_AUTOMATA_HPP
