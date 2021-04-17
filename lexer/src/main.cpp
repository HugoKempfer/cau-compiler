#include <iostream>
#include "../include/automata.hpp"

typedef struct {
    const State *dfa;
	TokenType type;
    size_t nb_state;
} DFAListItem;

static const State BoolToken[] = {
        {false, {{Transition::EXPR, {.expression="true"}, 1}, {Transition::EXPR, {.expression="false"}, 1} }},
        {true, {}}
};


static const DFAListItem Tokens[] = {
	{BoolToken, TokenType::BOOL, ARR_SIZE(BoolToken)},
	{NULL, NONE, 0}
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
