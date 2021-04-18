#include "../include/automata.hpp"
#include "../include/serializer.hpp"
#include "../include/tokens.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "A filename should be provided" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream source_file(argv[1]);
  std::string str((std::istreambuf_iterator<char>(source_file)),
                  std::istreambuf_iterator<char>());

  auto tokens = get_tokens(str);
  print_tokens(tokens);
  write_to_file(argv[1], tokens);
  return (!tokens.empty() && tokens.back().type == NONE) ? EXIT_FAILURE
                                                         : EXIT_SUCCESS;
}
