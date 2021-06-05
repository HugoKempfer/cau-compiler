//
// Created by hugo on 6/4/21.
//

#include "include/slr_table.h"
#include <ranges>
#include <unordered_map>
#include <stack>
#include <optional>
#include <deque>

using TokenIt = vector<RHSEntry>::iterator;

static const std::unordered_map<NonTerminals, vector<ProductionEntry>> PRODUCTIONS =
        {{NT_CODE_PRIME, {{{NTERM, NT_CODE}}}},
         {NT_CODE,       {{{NTERM, NT_V_DECL}, {NTERM, NT_CODE}},                                             {{NTERM, NT_F_DECL}, {NTERM, NT_CODE}},                     {{NTERM, NT_C_DECL}, {NTERM, NT_CODE}},                                                                                                                   {}}},
         {NT_V_DECL,     {{{TERM,  T_VTYPE},   {TERM,  T_ID},      {TERM,  T_SEMI}},                          {{TERM,  T_VTYPE},   {NTERM, NT_ASSIGN}, {TERM,  T_SEMI}}}},
         {NT_ASSIGN,     {{{TERM,  T_ID},      {TERM,  T_ASSIGN},  {NTERM, NT_RHS}}}},
         {NT_RHS,        {{{NTERM, NT_EXPR}},                                                                 {{TERM,  T_LITERAL}},                                       {{TERM,  T_CHARACTER}},                                                                                                                                   {{TERM, T_BOOLSTR}}}},
         {NT_EXPR,       {{{NTERM, NT_EXPR},   {TERM,  T_ADDSUB},  {NTERM, NT_EXPR}},                         {{NTERM, NT_EXPR},   {TERM,  T_MULTDIV}, {NTERM, NT_EXPR}}, {{TERM,  T_L_PAREN}, {NTERM, NT_EXPR},   {TERM,  T_R_PAREN}},                                                                                             {{TERM, T_ID}}, {{TERM, T_NUM}}}},
         {NT_F_DECL,     {{{TERM,  T_VTYPE},   {TERM,  T_ID},      {TERM,  T_L_PAREN}, {NTERM, NT_ARG},    {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {NTERM, NT_RETURN}, {TERM, T_R_BRACE}}}},
         {NT_ARG,        {{{TERM,  T_VTYPE},   {TERM,  T_ID},      {NTERM, NT_MOREARGS}},                     {}}},
         {NT_MOREARGS,   {{{TERM,  T_COMMA},   {TERM,  T_VTYPE},   {TERM,  T_ID},      {NTERM, NT_MOREARGS}}, {}}},
         {NT_BLOCK,      {{{NTERM, NT_STMT},   {NTERM, NT_BLOCK}},                                            {}}},
         {NT_STMT,       {{{NTERM, NT_V_DECL}},                                                               {{NTERM, T_ASSIGN},  {TERM,  T_SEMI}},                      {{TERM,  T_IF},      {TERM,  T_L_PAREN}, {NTERM, NT_COND}, {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {TERM, T_R_BRACE}, {NTERM, NT_ELSE}}, {{TERM, T_WHILE}, {TERM, T_L_PAREN}, {NTERM, NT_COND}, {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {TERM, T_R_BRACE}}}},
         {NT_COND,       {{{NTERM, NT_COND},   {TERM,  T_COMP},    {NTERM, NT_COND}},                         {{TERM,  T_BOOLSTR}}}},
         {NT_ELSE,       {{{TERM,  T_ELSE},    {TERM,  T_L_BRACE}, {NTERM, NT_BLOCK},  {TERM,  T_R_BRACE}},   {}}},
         {NT_RETURN,     {{{TERM,  T_RETURN},  {NTERM, NT_RHS},    {TERM,  T_SEMI}}}},
         {NT_C_DECL,     {{{TERM,  T_CLASS},   {TERM,  T_ID},      {TERM,  T_L_BRACE}, {NTERM, NT_O_DECL}, {TERM, T_R_BRACE}}}},
         {NT_O_DECL,     {{{NTERM, NT_V_DECL}, {NTERM, NT_O_DECL}},                                           {{NTERM, NT_F_DECL}, {NTERM, NT_O_DECL}},                   {}}}};

static const SLRTableEntry SLR_TABLE[] =
        {
                {{{T_VTYPE,   SHIFT,     5},           {T_CLASS,   SHIFT,  6},         {T_DOLLARS,   REDUCE, NT_CODE}},                                                                                                                                                                {{NT_CODE,     1},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_DOLLARS, ACCEPTING, -1}},                                                                                                                                                                                                                                         {}},
                {{{T_VTYPE,   SHIFT,     5},           {T_CLASS,   SHIFT,  6},         {T_DOLLARS,   REDUCE, NT_CODE}},                                                                                                                                                                {{NT_CODE,     7},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_VTYPE,   SHIFT,     5},           {T_CLASS,   SHIFT,  6},         {T_DOLLARS,   REDUCE, NT_CODE}},                                                                                                                                                                {{NT_CODE,     8},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_VTYPE,   SHIFT,     5},           {T_CLASS,   SHIFT,  6},         {T_DOLLARS,   REDUCE, NT_CODE}},                                                                                                                                                                {{NT_CODE,     9},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_ID,      SHIFT,     10}},                                                                                                                                                                                                                                         {{NT_ASSIGN,   11}}},
                {{{T_ID,      SHIFT,     12}},                                                                                                                                                                                                                                         {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE}},                                                                                                                                                                                                                                    {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE}},                                                                                                                                                                                                                                    {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE}},                                                                                                                                                                                                                                    {}},
                {{{T_SEMI,    SHIFT,     13},          {T_ASSIGN,  SHIFT,  15},        {T_L_PAREN,   SHIFT,  14}},                                                                                                                                                                     {}},
                {{{T_SEMI,    SHIFT,     16}},                                                                                                                                                                                                                                         {}},
                {{{T_L_BRACE, SHIFT,     17}},                                                                                                                                                                                                                                         {}},
                {{{T_VTYPE,   REDUCE,    NT_V_DECL},   {T_ID,      REDUCE, NT_V_DECL}, {T_R_BRACE,   REDUCE, NT_V_DECL}, {T_IF,      REDUCE, NT_V_DECL}, {T_WHILE,   REDUCE, NT_V_DECL}, {T_RETURN, REDUCE, NT_V_DECL}, {T_CLASS, REDUCE, NT_V_DECL}, {T_DOLLARS, REDUCE, NT_V_DECL}}, {}},
                {{{T_VTYPE,   SHIFT,     19},          {T_R_PAREN, REDUCE, NT_ARG}},                                                                                                                                                                                                   {{NT_ARG,      18}}},
                {{{T_ID,      SHIFT,     26},          {T_LITERAL, SHIFT,  22},        {T_CHARACTER, SHIFT,  23},        {T_BOOLSTR, SHIFT,  24},        {T_L_PAREN, SHIFT,  25},        {T_NUM,    SHIFT,  27}},                                                                      {{NT_EXPR,     20}, {NT_F_DECL, 21}}},
                {{{T_VTYPE,   REDUCE,    NT_V_DECL},   {T_ID,      REDUCE, NT_V_DECL}, {T_R_BRACE,   REDUCE, NT_V_DECL}, {T_IF,      REDUCE, NT_V_DECL}, {T_WHILE,   REDUCE, NT_V_DECL}, {T_RETURN, REDUCE, NT_V_DECL}, {T_CLASS, REDUCE, NT_V_DECL}, {T_DOLLARS, REDUCE, NT_V_DECL}}, {}},
                {{{T_VTYPE,   SHIFT,     5},           {T_R_BRACE, REDUCE, NT_O_DECL}},                                                                                                                                                                                                {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 28}}},
                {{{T_R_PAREN, SHIFT,     31}},                                                                                                                                                                                                                                         {}},
                {{{T_ID,      SHIFT,     32}},                                                                                                                                                                                                                                         {}},
                {{{T_SEMI,    REDUCE,    NT_ASSIGN}},                                                                                                                                                                                                                                  {}},
                {{{T_SEMI,    REDUCE,    NT_RHS},      {T_ADDSUB,  SHIFT,  33},        {T_MULTDIV,   SHIFT,  34}},                                                                                                                                                                     {}},
                {{{T_SEMI,    REDUCE,    NT_RHS}},                                                                                                                                                                                                                                     {}},
                {{{T_SEMI,    REDUCE,    NT_RHS}},                                                                                                                                                                                                                                     {}},
                {{{T_SEMI,    REDUCE,    NT_RHS}},                                                                                                                                                                                                                                     {}},
                {{{T_ID,      SHIFT,     26},          {T_L_PAREN, SHIFT,  25},        {T_NUM,       SHIFT,  27}},                                                                                                                                                                     {{NT_EXPR,     35}}},
                {{{T_SEMI,    REDUCE,    NT_EXPR},     {T_ADDSUB,  REDUCE, NT_EXPR},   {T_MULTDIV,   REDUCE, NT_EXPR},   {T_L_PAREN, REDUCE, NT_EXPR}},                                                                                                                                {}},
                {{{T_SEMI,    REDUCE,    NT_EXPR},     {T_ADDSUB,  REDUCE, NT_EXPR},   {T_MULTDIV,   REDUCE, NT_EXPR},   {T_L_PAREN, REDUCE, NT_EXPR}},                                                                                                                                {}},
                {{{T_R_BRACE, SHIFT,     36}},                                                                                                                                                                                                                                         {}},
                {{{T_VTYPE,   SHIFT,     5},           {T_R_BRACE, REDUCE, NT_O_DECL}},                                                                                                                                                                                                {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 37}}},
                {{{T_VTYPE,   SHIFT,     5},           {T_R_BRACE, REDUCE, NT_O_DECL}},                                                                                                                                                                                                {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 38}}},
                {{{T_L_BRACE, SHIFT,     39}},                                                                                                                                                                                                                                         {}},
                {{{T_R_PAREN, REDUCE,    NT_MOREARGS}, {T_COMMA,   SHIFT,  41}},                                                                                                                                                                                                       {{NT_MOREARGS, 40}}},
                {{{T_ID,      SHIFT,     26},          {T_L_PAREN, SHIFT,  25},        {T_NUM,       SHIFT,  27}},                                                                                                                                                                     {{NT_EXPR,     42}}},
                {{{T_ID,      SHIFT,     26},          {T_L_PAREN, SHIFT,  25},        {T_NUM,       SHIFT,  27}},                                                                                                                                                                     {{NT_EXPR,     43}}},
                {{{T_ADDSUB,  SHIFT,     33},          {T_MULTDIV, SHIFT,  34},        {T_R_PAREN,   SHIFT,  44}},                                                                                                                                                                     {}},
                {{{T_VTYPE,   REDUCE,    NT_C_DECL},   {T_CLASS,   REDUCE, NT_C_DECL}, {T_DOLLARS,   REDUCE, NT_C_DECL}},                                                                                                                                                              {}},
                {{{T_R_BRACE, REDUCE,    NT_O_DECL}},                                                                                                                                                                                                                                  {}},
                {{{T_R_BRACE, REDUCE,    NT_O_DECL}},                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   SHIFT,     51},          {T_ID,      SHIFT,  52},        {T_R_BRACE,   REDUCE, NT_BLOCK},  {T_IF,      SHIFT,  49},        {T_WHILE,   SHIFT,  50},        {T_RETURN, REDUCE, NT_BLOCK}},                                                                {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  45}, {NT_STMT,   46}}},
                {{{T_R_PAREN, REDUCE,    NT_ARG}},                                                                                                                                                                                                                                     {}},
                {{{T_VTYPE,   SHIFT,     53}},                                                                                                                                                                                                                                         {}},
                {{{T_SEMI,    REDUCE,    NT_EXPR},     {T_ADDSUB,  REDUCE, NT_EXPR},   {T_MULTDIV,   REDUCE, NT_EXPR},   {T_R_PAREN, REDUCE, NT_EXPR}}}, // AMBIGIOUS
                {{{T_SEMI,    REDUCE,    NT_EXPR},     {T_ADDSUB,  REDUCE, NT_EXPR},   {T_MULTDIV,   REDUCE, NT_EXPR},   {T_R_PAREN, REDUCE, NT_EXPR}}}, // AMBIGIOUS
                {{{T_SEMI,    REDUCE,    NT_EXPR},     {T_ADDSUB,  REDUCE, NT_EXPR},   {T_MULTDIV,   REDUCE, NT_EXPR},   {T_R_PAREN, REDUCE, NT_EXPR}}},
                {{{T_RETURN,  SHIFT,     55}},                                                                                                                                                                                                                                         {{NT_RETURN,   54}}},
                {{{T_VTYPE,   SHIFT,     51},          {T_ID,      SHIFT,  52},        {T_R_BRACE,   REDUCE, NT_BLOCK},  {T_IF,      SHIFT,  49},        {T_WHILE,   SHIFT,  50},        {T_RETURN, REDUCE, NT_BLOCK}},                                                                {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  56}, {NT_STMT,   46}}},
                {{{T_VTYPE,   REDUCE,    NT_STMT},     {T_ID,      REDUCE, NT_STMT},   {T_R_BRACE,   REDUCE, NT_STMT},   {T_IF,      REDUCE, NT_STMT},   {T_WHILE,   REDUCE, NT_STMT},   {T_RETURN, REDUCE, NT_STMT}},                                                                 {}},
                {{{T_SEMI,    SHIFT,     57}},                                                                                                                                                                                                                                         {}},
                {{{T_L_PAREN, SHIFT,     58}},                                                                                                                                                                                                                                         {}},
                {{{T_L_PAREN, SHIFT,     58}},                                                                                                                                                                                                                                         {}},
                {{{T_ID,      SHIFT,     60}},                                                                                                                                                                                                                                         {{NT_ASSIGN,   11}}},
                {{{T_ASSIGN,  SHIFT,     15}},                                                                                                                                                                                                                                         {}},
                {{{T_ID,      SHIFT,     61}},                                                                                                                                                                                                                                         {}},
                {{{T_R_BRACE, SHIFT,     62}},                                                                                                                                                                                                                                         {}},
                {{{T_ID,      SHIFT,     26},          {T_LITERAL, SHIFT,  22},        {T_CHARACTER, SHIFT,  23},        {T_BOOLSTR, SHIFT,  24},        {T_L_PAREN, SHIFT,  25},        {T_NUM,    SHIFT,  27}},                                                                      {{NT_RHS,      63}, {NT_EXPR,   21}}},
                {{{T_R_BRACE, REDUCE,    NT_BLOCK},    {T_RETURN,  REDUCE, NT_BLOCK}},                                                                                                                                                                                                 {}},
                {{{T_VTYPE,   REDUCE,    NT_STMT},     {T_ID,      REDUCE, NT_STMT},   {T_R_BRACE,   REDUCE, NT_STMT},   {T_IF,      REDUCE, NT_STMT},   {T_WHILE,   REDUCE, NT_STMT},   {T_RETURN, REDUCE, NT_STMT}},                                                                 {}},
                {{{T_BOOLSTR, SHIFT,     65}},                                                                                                                                                                                                                                         {{NT_COND,     64}}},
                {{{T_BOOLSTR, SHIFT,     65}},                                                                                                                                                                                                                                         {{NT_COND,     66}}},
                {{{T_SEMI,    SHIFT,     13},          {T_ASSIGN,  SHIFT,  15}},                                                                                                                                                                                                       {}},
                {{{T_R_PAREN, REDUCE,    NT_MOREARGS}, {T_COMMA,   SHIFT,  41}},                                                                                                                                                                                                       {{NT_MOREARGS, 67}}},
                {{{T_VTYPE,   REDUCE,    NT_F_DECL},   {T_R_BRACE, REDUCE, NT_F_DECL}, {T_CLASS,     REDUCE, NT_F_DECL}, {T_DOLLARS, REDUCE, NT_F_DECL}},                                                                                                                              {}},
                {{{T_SEMI,    SHIFT,     68}},                                                                                                                                                                                                                                         {}},
                {{{T_R_PAREN, SHIFT,     69},          {T_COMP,    SHIFT,  70}},                                                                                                                                                                                                       {}},
                {{{T_R_PAREN, REDUCE, NT_COND}, {T_COMP, REDUCE, NT_COND}}, {}},
                {{{T_R_PAREN, SHIFT, 71}, {T_COMP, SHIFT, 70}}, {}},
                {{{T_L_PAREN, REDUCE, NT_MOREARGS}}, {}},
                {{{T_R_BRACE, REDUCE, NT_RETURN}}, {}},
                {{{T_L_BRACE, SHIFT, 72}}, {}},
                {{{T_BOOLSTR, SHIFT, 65}}, {NT_COND, 73}},
                {{{T_L_BRACE, SHIFT, 74}}, {}},
                {{{T_VTYPE, SHIFT, 51}, {T_ID, SHIFT, 52}, {T_R_BRACE, REDUCE, NT_BLOCK}, {T_IF, SHIFT, 49}, {T_WHILE, SHIFT, 50}, {T_RETURN, REDUCE, NT_BLOCK}}, {{NT_V_DECL, 47}, {NT_ASSIGN, 48}, {NT_BLOCK, 75}, {NT_STMT, 46}}},
                {{{T_R_PAREN, REDUCE, NT_COND}, {T_COMP, SHIFT, 70}}, {}},
                {{{T_VTYPE, SHIFT, 51}, {T_ID, SHIFT, 52}, {T_R_BRACE, REDUCE, NT_BLOCK}, {T_IF, SHIFT, 49}, {T_WHILE, SHIFT, 50}, {T_RETURN, REDUCE, NT_BLOCK}}, {{NT_V_DECL, 47}, {NT_ASSIGN, 48}, {NT_BLOCK, 76}, {NT_STMT, 46}}},
                {{{T_R_BRACE, SHIFT, 77}}, {}},
                {{{T_R_BRACE, SHIFT, 78}}, {}},
                {{{T_VTYPE, REDUCE, NT_ELSE}, {T_ID, REDUCE, NT_ELSE}, {T_R_BRACE, REDUCE, NT_ELSE}, {T_IF, REDUCE, NT_ELSE}, {T_WHILE, REDUCE, NT_ELSE}, {T_ELSE, SHIFT, 80}, {T_RETURN, REDUCE, NT_ELSE}}, {{NT_ELSE, 79}}},
                {{{T_VTYPE, REDUCE, NT_STMT}, {T_ID, REDUCE, NT_STMT}, {T_R_BRACE, REDUCE, NT_STMT}, {T_IF, REDUCE, NT_STMT}, {T_WHILE, REDUCE, NT_STMT}, {T_RETURN, REDUCE, NT_STMT}}, {}},
                {{{T_VTYPE, REDUCE, NT_STMT}, {T_ID, REDUCE, NT_STMT}, {T_R_BRACE, REDUCE, NT_STMT}, {T_IF, REDUCE, NT_STMT}, {T_WHILE, REDUCE, NT_STMT}, {T_RETURN, REDUCE, NT_STMT}}, {}},
                {{{T_L_BRACE, SHIFT, 81}}, {}},
                {{{T_VTYPE, SHIFT, 51}, {T_ID, SHIFT, 52}, {T_R_BRACE, REDUCE, NT_BLOCK}, {T_IF, SHIFT, 49}, {T_WHILE, SHIFT, 50}, {T_RETURN, REDUCE, NT_BLOCK}}, {{NT_V_DECL, 47}, {NT_ASSIGN, 48}}},
                {{{T_R_BRACE, SHIFT, 83}}, {}},
                {{{T_VTYPE, REDUCE, NT_ELSE}, {T_ID, REDUCE, NT_ELSE}, {T_R_BRACE, REDUCE, NT_ELSE}, {T_IF, REDUCE, NT_ELSE}, {T_WHILE, REDUCE, NT_ELSE}, {T_RETURN, REDUCE, NT_ELSE}}, {}}
        }

bool evaluate_production(const vector<RHSEntry> &tokens, const TokenIt &cursor, const ProductionEntry &production) {
    auto lhs = cursor;
    for (auto symbol = production.rbegin(); symbol != production.rend(); ++symbol) {
        if (lhs == tokens.begin()) {
            return false;
        }
        --lhs;
        if (*lhs != *symbol) {
            return false;
        }
    }
    return true;
}

bool is_production_reducible(const vector<RHSEntry> &tokens, const TokenIt &cursor, const NonTerminals production_symbol) {
    auto productions = PRODUCTIONS.at(production_symbol);

    for (auto &production : productions) {
        if (evaluate_production(tokens, cursor, production)) {
            return true;
        }
    }
    return false;
}

std::optional<GotoEntry> try_match_goto(const vector<RHSEntry> &tokens, const TokenIt &cursor, const vector<GotoEntry> &gotos) {
    for (auto goto_entry : gotos) {
        if (is_production_reducible(tokens, cursor, goto_entry.symbol)) {
            return goto_entry;
        }
    }
    return std::nullopt;
}

std::optional<ActionEntry> try_match_action(const vector<RHSEntry> &tokens, const TokenIt &cursor, const vector<ActionEntry> &actions) {
    for (auto action : actions) {
        if (action.symbol == cursor->value) {
            return action;
        }
    }
    return std::nullopt;
}

void apply_action(vector<RHSEntry> &tokens, TokenIt &cursor, ActionEntry &action, std::stack<int> &states) {
    switch (action.type) {
        case SHIFT:
            ++cursor;
            states.push(action.value);
            break;
        case REDUCE:
            tokens.
            break;
        case ACCEPTING:
            return;
    }
}

void apply_goto(vector<RHSEntry> &tokens, TokenIt &cursor, GotoEntry &goto_entry) {

}

bool parse_tokens(vector<RHSEntry> tokens) { //gona refactor tokens and lhs handling
    std::stack<int> state_stack;
    TokenIt cursor;

    state_stack.push(0); // set start state to 0
    while (cursor != tokens.end()) {
        auto action = try_match_action(tokens, cursor, SLR_TABLE[state_stack.top()].actions);
        if (action.has_value()) {
            if (action->type == ACCEPTING) {
                return true;
            }
            apply_action(tokens, cursor, *action, state_stack);
            continue;
        }
        auto goto_entry = try_match_goto(tokens, cursor, SLR_TABLE[state_stack.top()].gotos);
        if (goto_entry.has_value()) {
            apply_goto(tokens, cursor, *goto_entry);
            continue;
        }
        //Nothing else to do
    }
    return false;
}
