#include <iostream>
#include "include/slr_table.h"

void damn();

bool parse_tokens(vector<Terminals> tokens);

int main() {
    vector<Terminals> tokens = {T_VTYPE, T_ID, T_L_PAREN, T_R_PAREN, T_L_BRACE, T_RETURN, T_LITERAL, T_SEMI, T_R_BRACE, T_DOLLARS};
    if (parse_tokens(tokens)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "KO" << std::endl;
    }
    return 0;
}
