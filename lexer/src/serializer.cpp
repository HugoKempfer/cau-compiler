//
// Created by hugo on 4/17/21.
//

#include <iostream>
#include <fstream>
#include "../include/serializer.hpp"

void print_tokens(std::vector<Token> const &tokens) {
    if (!tokens.empty() && tokens.back().type == NONE) {
        size_t line_nb = 0;

        for (auto &token : tokens) {
            if (token.type == NONE) {
                break;
            } else if (token.type == WHITESPACE && token.value == "\n") {
                ++line_nb;
            }
        }
        std::cerr << "Error line " << line_nb << ":" << std::endl << std::endl;
        auto error = tokens.back().value;
        auto error_end_index = error.find_first_of('\n');
        std::cerr << "[ " << error.substr(0, error_end_index ? error_end_index : error.length()) << " ]" << std::endl;
        std::cerr << "  ^ lexical error" << std::endl;
        return;
    }
    for (auto const &token : tokens) {
        if (token.type == WHITESPACE || token.type == NONE)
            continue;
        std::cout << "<" << TokenNames.at(token.type) << ", " << token.value << ">" << std::endl;
    }
}

void write_error_report(std::ofstream &file, const std::vector<Token> &tokens) {
    size_t line_nb = 0;

    for (auto &token : tokens) {
        if (token.type == NONE) {
            break;
        } else if (token.type == WHITESPACE && token.value == "\n") {
            ++line_nb;
        }
    }
    file << "Error line " << line_nb << ":" << std::endl << std::endl;
    auto error = tokens.back().value;
    auto error_end_index = error.find_first_of('\n');
    file << "[ " << error.substr(0, error_end_index ? error_end_index : error.length()) << " ]" << std::endl;
    file << "  ^ lexical error" << std::endl;
}

void write_to_file(std::string const &source_file_name, const std::vector<Token> &tokens) {
    std::ofstream outfile(source_file_name + "_output.txt");

    if (!tokens.empty() && tokens.back().type == NONE) {
        write_error_report(outfile, tokens);
        return;
    }
    for (auto const &token : tokens) {
        if (token.type == WHITESPACE)
            continue;
        outfile << "<" << TokenNames.at(token.type) << ", " << token.value << ">" << std::endl;
    }
}
