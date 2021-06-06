#include <iostream>
#include "include/slr_table.h"

bool parse_tokens(vector<Terminals> tokens);
vector<Terminals> get_tokens_from_input(char *);

int main(int ac, char **av) {
    if (ac < 2) {
        std::cerr << "A filename should be provided" << std::endl;
        return EXIT_FAILURE;
    }
    auto tokens = get_tokens_from_input(av[1]);
    if (parse_tokens(tokens)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "KO" << std::endl;
    }
    return 0;
}
