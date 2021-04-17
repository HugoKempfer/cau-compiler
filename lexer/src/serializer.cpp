//
// Created by hugo on 4/17/21.
//

#include <iostream>
#include "../include/serializer.hpp"

void print_tokens(std::vector<Token> const &tokens) {
    for (auto const &token : tokens) {
        if (token.type == WHITESPACE)
            continue;
        std::cout << "<" << TokenNames.at(token.type) << ", " << token.value << ">" << std::endl;
    }
}