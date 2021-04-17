#include <iostream>
#include <fstream>
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
            return (str[0] >= '0' && str[0] <= '9') ? 1 : 0;
        case LETTER:
            return isalpha(str[0]) ? 1 : 0;
        case POSITIVE_INT:
            return (str[0] >= '1' && str[0] <= '9') ? 1 : 0;
    }
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

std::vector<Token> get_tokens(std::string char_stream)
{
    std::vector<Token> tokens;
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
    } while (current_token.type != NONE);
    return tokens;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "A filename should be provided" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream source_file(argv[1]);
    std::string str((std::istreambuf_iterator<char>(source_file)),
                    std::istreambuf_iterator<char>());

    return 0;
}
