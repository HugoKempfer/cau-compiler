#include <iostream>
#include "../include/automata.hpp"
#include "../include/tokens.hpp"

typedef struct {
    const State *dfa;
    TokenType type;
    size_t nb_state;
} DFAListItem;

static const DFAListItem Tokens[] = {
    {BoolToken, TokenType::BOOL, ARR_SIZE(BoolToken)},
    {NULL, NONE, 0}
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
