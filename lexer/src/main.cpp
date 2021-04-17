#include <iostream>
#include "../include/automata.hpp"
#include "../include/tokens.hpp"

typedef struct {
    const State *dfa;
    TokenType type;
} DFAListItem;

static const DFAListItem TokensDFA[] = {
        {BoolToken, TokenType::BOOL},
        {nullptr,   NONE}
};

size_t match_with_alphabet(Alphabet alphabet, std::string &str) {
    switch (alphabet) {
        case DIGIT:
            break;
        case LETTER:
            break;
        case NUMBERS:
            break;
        case POSITIVE_INT:
            break;
    };
    return 0;
}

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

// Check if the provided string matches the given DFA. Returns the number of matching characters
size_t match_dfa(std::string &str, const State *dfa) {
    size_t res;
    size_t total_shift = 0;
    auto current_state = &dfa[Transition::A];
    auto char_stream = std::string(str);

    do {
        res = 0;
        for (auto transition : current_state->transitions) {
            switch (transition.value_type) {
                case Transition::ALPH:
                    res = match_with_alphabet(transition.value.alphabet, str);
                    break;
                case Transition::EXPR:
                    res = match_with_expression(transition.value.expression, str);
                    break;
                case Transition::DFA:
                    res = match_dfa(str, transition.value.dfa);
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
    } while (res > 0);
    if (current_state->is_accepting) {
        return total_shift;
    } else {
        return 0;
    }
}

Token get_next_token(std::string &str, const DFAListItem *dfas) {
    auto current_dfa = dfas;
    while (current_dfa->type != NONE) {
        auto res = match_dfa(str, current_dfa->dfa);
        if (res > 0) {
            return {current_dfa->type, str.substr(0, res)};
        }
        ++current_dfa;
    }
    return {NONE, ""};
}

int main() {
    std::vector<Token> tokens;
    std::string char_stream("true  ");
    Token current_token;

    do {
        current_token = get_next_token(char_stream, TokensDFA);
        if (current_token.type != NONE) {
            tokens.push_back(current_token);
            try {
                char_stream = char_stream.substr(current_token.value.length(), char_stream.length());
            } catch (std::out_of_range &err) {
                break;
            }
        }
        std::cout << tokens.size() << std::endl;
    } while (current_token.type != NONE);
    return 0;
}
