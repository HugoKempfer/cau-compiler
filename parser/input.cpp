//
// Created by hugo on 6/5/21.
//

#include <string>
#include <iostream>
#include <unordered_map>
#include "include/slr_table.h"

static const std::unordered_map<std::string, Terminals> tokens_type = {
        {"BOOL", T_BOOLSTR},
        {"ITERATIVE", T_WHILE},
        {"ASSIGN", T_ASSIGN},
        {"CMP_OP", T_COMP},
        {"SC", T_SEMI},
        //{"ARRAY",},
        {"COMMA", T_COMMA},
        {"V_TYPE", T_VTYPE},
        {"ID", T_ID},
        {"LITERAL", T_LITERAL},
        {"S_INT", T_NUM},
        {"S_CHAR", T_CHARACTER}
        //{"WHITESPACE",
};

Terminals match_token(std::string &type, std::string &value) {
    if (tokens_type.contains(type)) {
        return tokens_type.at(type);
    }
    if (type == "ARTITH_OP") {
        if (value == "+" || value == "-") {
            return T_ADDSUB;
        }
        else if (value == "*" || value == "/") {
            return T_MULTDIV;
        }
    }
    if (type == "PAREN") {
        if (value == "(")
            return T_L_PAREN;
        if (value == ")")
            return T_R_PAREN;
    }
    if (type == "BLOCK") {
        if (value == "{")
            return T_L_BRACE;
        if (value == "}")
            return T_R_BRACE;
    }
    if (type == "CONDITIONAL") {
        if (value == "if")
            return T_IF;
        if (value == "else")
            return T_ELSE;
    }
    if (type == "KEYWORD") {
        if (value == "class")
            return T_CLASS;
        if (value == "return")
            return T_RETURN;
    }
    std::cout << "WOW LA CHANKLA" << std::endl;
}

vector<Terminals> get_tokens_from_input() {
    vector<Terminals> tokens;

    for (std::string line; std::getline(std::cin, line);) {
        auto comma_pos = line.find_first_of(',');
        auto type = line.substr(1, comma_pos - 1);
        auto value = line.substr(comma_pos + 2, (line.find_last_of('>')) - (comma_pos + 2));
        tokens.push_back(match_token(type, value));
    }
    tokens.push_back(T_DOLLARS);
    return tokens;
}
