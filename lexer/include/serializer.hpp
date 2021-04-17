//
// Created by hugo on 4/17/21.
//

#include <unordered_map>
#include "automata.hpp"

#ifndef LEXER_SERIALIZER_HPP
#define LEXER_SERIALIZER_HPP

void print_tokens(std::vector<Token> const &);
void write_to_file(std::string const &, const std::vector<Token> &);

static const std::unordered_map<TokenType, std::string> TokenNames = {
	{BOOL, "BOOL"},
	{KEYWORD, "KEYWORD"},
	{ITERATIVE, "ITERATIVE"},
	{CONDITIONAL, "CONDITIONAL"},
	{ARTITH_OP, "ARTITH_OP"},
	{ASSIGN, "ASSIGN"},
	{CMP_OP, "CMP_OP"},
	{SC, "SC"},
	{BLOCK, "BLOCK"},
	{PAREN, "PAREN"},
	{ARRAY, "ARRAY"},
	{COMMA, "COMMA"},
	{V_TYPE, "V_TYPE"},
	{ID, "ID"},
	{LITERAL, "LITERAL"},
	{S_INT, "S_INT"},
	{S_CHAR, "S_CHAR"},
	{WHITESPACE, "WHITESPACE"}
};


#endif //LEXER_SERIALIZER_HPP
