//
// Created by hugo on 6/4/21.
//

#include "include/slr_table.h"
#include <ranges>
#include <unordered_map>
#include <stack>
#include <optional>
#include <iostream>

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
                {{{T_VTYPE,   SHIFT,     5},              {T_CLASS,   SHIFT,  6},            {T_DOLLARS,   REDUCE, NT_CODE,   3}},                                                                                                                                                                              {{NT_CODE,     1},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_DOLLARS, ACCEPTING, -1}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   SHIFT,     5},              {T_CLASS,   SHIFT,  6},            {T_DOLLARS,   REDUCE, NT_CODE,   3}},                                                                                                                                                                              {{NT_CODE,     7},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_VTYPE,   SHIFT,     5},              {T_CLASS,   SHIFT,  6},            {T_DOLLARS,   REDUCE, NT_CODE,   3}},                                                                                                                                                                              {{NT_CODE,     8},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_VTYPE,   SHIFT,     5},              {T_CLASS,   SHIFT,  6},            {T_DOLLARS,   REDUCE, NT_CODE,   3}},                                                                                                                                                                              {{NT_CODE,     9},  {NT_V_DECL, 2},  {NT_F_DECL, 3},  {NT_C_DECL, 4}}},
                {{{T_ID,      SHIFT,     10}},                                                                                                                                                                                                                                                                  {{NT_ASSIGN,   11}}},
                {{{T_ID,      SHIFT,     12}},                                                                                                                                                                                                                                                                  {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE,     0}},                                                                                                                                                                                                                                                      {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE,     1}},                                                                                                                                                                                                                                                      {}},
                {{{T_DOLLARS, REDUCE,    NT_CODE,     2}},                                                                                                                                                                                                                                                      {}},
                {{{T_SEMI,    SHIFT,     13},             {T_ASSIGN,  SHIFT,  15},           {T_L_PAREN,   SHIFT,  14}},                                                                                                                                                                                        {}},
                {{{T_SEMI,    SHIFT,     16}},                                                                                                                                                                                                                                                                  {}},
                {{{T_L_BRACE, SHIFT,     17}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   REDUCE,    NT_V_DECL,   0}, {T_ID,      REDUCE, NT_V_DECL, 0}, {T_R_BRACE,   REDUCE, NT_V_DECL, 0}, {T_IF,      REDUCE, NT_V_DECL, 0}, {T_WHILE,   REDUCE, NT_V_DECL, 0}, {T_RETURN, REDUCE, NT_V_DECL, 0}, {T_CLASS,  REDUCE, NT_V_DECL, 0}, {T_DOLLARS, REDUCE, NT_V_DECL, 0}}, {}},
                {{{T_VTYPE,   SHIFT,     19},             {T_R_PAREN, REDUCE, NT_ARG,    1}},                                                                                                                                                                                                                   {{NT_ARG,      18}}},
                {{{T_ID,      SHIFT,     26},             {T_LITERAL, SHIFT,  22},           {T_CHARACTER, SHIFT,  23},           {T_BOOLSTR, SHIFT,  24},           {T_L_PAREN, SHIFT,  25},           {T_NUM,    SHIFT,  27}},                                                                                {{NT_EXPR,     20}, {NT_F_DECL, 21}}},
                {{{T_VTYPE,   REDUCE,    NT_V_DECL,   1}, {T_ID,      REDUCE, NT_V_DECL, 1}, {T_R_BRACE,   REDUCE, NT_V_DECL, 1}, {T_IF,      REDUCE, NT_V_DECL, 1}, {T_WHILE,   REDUCE, NT_V_DECL, 1}, {T_RETURN, REDUCE, NT_V_DECL, 1}, {T_CLASS,  REDUCE, NT_V_DECL, 1}, {T_DOLLARS, REDUCE, NT_V_DECL, 1}}, {}},
                {{{T_VTYPE,   SHIFT,     5},              {T_R_BRACE, REDUCE, NT_O_DECL, 2}},                                                                                                                                                                                                                   {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 28}}},
                {{{T_R_PAREN, SHIFT,     31}},                                                                                                                                                                                                                                                                  {}},
                {{{T_ID,      SHIFT,     32}},                                                                                                                                                                                                                                                                  {}},
                {{{T_SEMI,    REDUCE,    NT_ASSIGN,   0}},                                                                                                                                                                                                                                                      {}},
                {{{T_SEMI,    REDUCE,    NT_RHS,      0}, {T_ADDSUB,  SHIFT,  33},           {T_MULTDIV,   SHIFT,  34}},                                                                                                                                                                                        {}},
                {{{T_SEMI,    REDUCE,    NT_RHS,      1}},                                                                                                                                                                                                                                                      {}},
                {{{T_SEMI,    REDUCE,    NT_RHS,      2}},                                                                                                                                                                                                                                                      {}},
                {{{T_SEMI,    REDUCE,    NT_RHS,      3}},                                                                                                                                                                                                                                                      {}},
                {{{T_ID,      SHIFT,     26},             {T_L_PAREN, SHIFT,  25},           {T_NUM,       SHIFT,  27}},                                                                                                                                                                                        {{NT_EXPR,     35}}},
                {{{T_SEMI,    REDUCE,    NT_EXPR,     3}, {T_ADDSUB,  REDUCE, NT_EXPR,   3}, {T_MULTDIV,   REDUCE, NT_EXPR,   3}, {T_L_PAREN, REDUCE, NT_EXPR,   3}},                                                                                                                                           {}},
                {{{T_SEMI,    REDUCE,    NT_EXPR,     4}, {T_ADDSUB,  REDUCE, NT_EXPR,   4}, {T_MULTDIV,   REDUCE, NT_EXPR,   4}, {T_L_PAREN, REDUCE, NT_EXPR,   4}},                                                                                                                                           {}},
                {{{T_R_BRACE, SHIFT,     36}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   SHIFT,     5},              {T_R_BRACE, REDUCE, NT_O_DECL, 2}},                                                                                                                                                                                                                   {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 37}}},
                {{{T_VTYPE,   SHIFT,     5},              {T_R_BRACE, REDUCE, NT_O_DECL, 2}},                                                                                                                                                                                                                   {{NT_V_DECL,   29}, {NT_F_DECL, 30}, {NT_O_DECL, 38}}},
                {{{T_L_BRACE, SHIFT,     39}},                                                                                                                                                                                                                                                                  {}},
                {{{T_R_PAREN, REDUCE,    NT_MOREARGS, 1}, {T_COMMA,   SHIFT,  41}},                                                                                                                                                                                                                             {{NT_MOREARGS, 40}}},
                {{{T_ID,      SHIFT,     26},             {T_L_PAREN, SHIFT,  25},           {T_NUM,       SHIFT,  27}},                                                                                                                                                                                        {{NT_EXPR,     42}}},
                {{{T_ID,      SHIFT,     26},             {T_L_PAREN, SHIFT,  25},           {T_NUM,       SHIFT,  27}},                                                                                                                                                                                        {{NT_EXPR,     43}}},
                {{{T_ADDSUB,  SHIFT,     33},             {T_MULTDIV, SHIFT,  34},           {T_R_PAREN,   SHIFT,  44}},                                                                                                                                                                                        {}},
                {{{T_VTYPE,   REDUCE,    NT_C_DECL,   0}, {T_CLASS,   REDUCE, NT_C_DECL, 0}, {T_DOLLARS,   REDUCE, NT_C_DECL, 0}},                                                                                                                                                                              {}},
                {{{T_R_BRACE, REDUCE,    NT_O_DECL,   0}},                                                                                                                                                                                                                                                      {}},
                {{{T_R_BRACE, REDUCE,    NT_O_DECL,   1}},                                                                                                                                                                                                                                                      {}},
                {{{T_VTYPE,   SHIFT,     51},             {T_ID,      SHIFT,  52},           {T_R_BRACE,   REDUCE, NT_BLOCK,  1}, {T_IF,      SHIFT,  49},           {T_WHILE,   SHIFT,  50},           {T_RETURN, REDUCE, NT_BLOCK,  1}},                                                                      {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  45}, {NT_STMT,   46}}},
                {{{T_R_PAREN, REDUCE,    NT_ARG,      0}},                                                                                                                                                                                                                                                      {}},
                {{{T_VTYPE,   SHIFT,     53}},                                                                                                                                                                                                                                                                  {}},
                {{{T_SEMI,    REDUCE,    NT_EXPR,     0}, {T_ADDSUB,  REDUCE, NT_EXPR,   0}, {T_MULTDIV,   REDUCE, NT_EXPR,   0}, {T_R_PAREN, REDUCE, NT_EXPR,   0}}}, // AMBIGIOUS
                {{{T_SEMI,    REDUCE,    NT_EXPR,     1}, {T_ADDSUB,  REDUCE, NT_EXPR,   1}, {T_MULTDIV,   REDUCE, NT_EXPR,   1}, {T_R_PAREN, REDUCE, NT_EXPR,   1}}}, // AMBIGIOUS
                {{{T_SEMI,    REDUCE,    NT_EXPR,     2}, {T_ADDSUB,  REDUCE, NT_EXPR,   2}, {T_MULTDIV,   REDUCE, NT_EXPR,   2}, {T_R_PAREN, REDUCE, NT_EXPR,   2}}},
                {{{T_RETURN,  SHIFT,     55}},                                                                                                                                                                                                                                                                  {{NT_RETURN,   54}}},
                {{{T_VTYPE,   SHIFT,     51},             {T_ID,      SHIFT,  52},           {T_R_BRACE,   REDUCE, NT_BLOCK,  1}, {T_IF,      SHIFT,  49},           {T_WHILE,   SHIFT,  50},           {T_RETURN, REDUCE, NT_BLOCK,  1}},                                                                      {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  56}, {NT_STMT,   46}}},
                {{{T_VTYPE,   REDUCE,    NT_STMT,     0}, {T_ID,      REDUCE, NT_STMT,   0}, {T_R_BRACE,   REDUCE, NT_STMT,   0}, {T_IF,      REDUCE, NT_STMT,   0}, {T_WHILE,   REDUCE, NT_STMT,   0}, {T_RETURN, REDUCE, NT_STMT,   0}},                                                                      {}},
                {{{T_SEMI,    SHIFT,     57}},                                                                                                                                                                                                                                                                  {}},
                {{{T_L_PAREN, SHIFT,     58}},                                                                                                                                                                                                                                                                  {}},
                {{{T_L_PAREN, SHIFT,     58}},                                                                                                                                                                                                                                                                  {}},
                {{{T_ID,      SHIFT,     60}},                                                                                                                                                                                                                                                                  {{NT_ASSIGN,   11}}},
                {{{T_ASSIGN,  SHIFT,     15}},                                                                                                                                                                                                                                                                  {}},
                {{{T_ID,      SHIFT,     61}},                                                                                                                                                                                                                                                                  {}},
                {{{T_R_BRACE, SHIFT,     62}},                                                                                                                                                                                                                                                                  {}},
                {{{T_ID,      SHIFT,     26},             {T_LITERAL, SHIFT,  22},           {T_CHARACTER, SHIFT,  23},           {T_BOOLSTR, SHIFT,  24},           {T_L_PAREN, SHIFT,  25},           {T_NUM,    SHIFT,  27}},                                                                                {{NT_RHS,      63}, {NT_EXPR,   21}}},
                {{{T_R_BRACE, REDUCE,    NT_BLOCK,    0}, {T_RETURN,  REDUCE, NT_BLOCK,  0}},                                                                                                                                                                                                                   {}},
                {{{T_VTYPE,   REDUCE,    NT_STMT,     1}, {T_ID,      REDUCE, NT_STMT,   1}, {T_R_BRACE,   REDUCE, NT_STMT,   1}, {T_IF,      REDUCE, NT_STMT,   1}, {T_WHILE,   REDUCE, NT_STMT,   1}, {T_RETURN, REDUCE, NT_STMT,   1}},                                                                      {}},
                {{{T_BOOLSTR, SHIFT,     65}},                                                                                                                                                                                                                                                                  {{NT_COND,     64}}},
                {{{T_BOOLSTR, SHIFT,     65}},                                                                                                                                                                                                                                                                  {{NT_COND,     66}}},
                {{{T_SEMI,    SHIFT,     13},             {T_ASSIGN,  SHIFT,  15}},                                                                                                                                                                                                                             {}},
                {{{T_R_PAREN, REDUCE,    NT_MOREARGS, 1}, {T_COMMA,   SHIFT,  41}},                                                                                                                                                                                                                             {{NT_MOREARGS, 67}}},
                {{{T_VTYPE,   REDUCE,    NT_F_DECL,   0}, {T_R_BRACE, REDUCE, NT_F_DECL, 0}, {T_CLASS,     REDUCE, NT_F_DECL, 0}, {T_DOLLARS, REDUCE, NT_F_DECL, 0}},                                                                                                                                           {}},
                {{{T_SEMI,    SHIFT,     68}},                                                                                                                                                                                                                                                                  {}},
                {{{T_R_PAREN, SHIFT,     69},             {T_COMP,    SHIFT,  70}},                                                                                                                                                                                                                             {}},
                {{{T_R_PAREN, REDUCE,    NT_COND,     1}, {T_COMP,    REDUCE, NT_COND,   1}},                                                                                                                                                                                                                   {}},
                {{{T_R_PAREN, SHIFT,     71},             {T_COMP,    SHIFT,  70}},                                                                                                                                                                                                                             {}},
                {{{T_R_PAREN, REDUCE,    NT_MOREARGS, 0}},                                                                                                                                                                                                                                                      {}},
                {{{T_R_BRACE, REDUCE,    NT_RETURN,   0}},                                                                                                                                                                                                                                                      {}},
                {{{T_L_BRACE, SHIFT,     72}},                                                                                                                                                                                                                                                                  {}},
                {{{T_BOOLSTR, SHIFT,     65}},                                                                                                                                                                                                                                                                  {{NT_COND,     73}}},
                {{{T_L_BRACE, SHIFT,     74}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   SHIFT,     51},             {T_ID,      SHIFT,  52},           {T_R_BRACE,   REDUCE, NT_BLOCK,  1}, {T_IF,      SHIFT,  49},           {T_WHILE,   SHIFT,  50},           {T_RETURN, REDUCE, NT_BLOCK,  1}},                                                                      {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  75}, {NT_STMT,   46}}},
                {{{T_R_PAREN, REDUCE,    NT_COND,     0}, {T_COMP,    SHIFT,  70}},                                                                                                                                                                                                                             {}},
                {{{T_VTYPE,   SHIFT,     51},             {T_ID,      SHIFT,  52},           {T_R_BRACE,   REDUCE, NT_BLOCK,  1}, {T_IF,      SHIFT,  49},           {T_WHILE,   SHIFT,  50},           {T_RETURN, REDUCE, NT_BLOCK,  1}},                                                                      {{NT_V_DECL,   47}, {NT_ASSIGN, 48}, {NT_BLOCK,  76}, {NT_STMT,   46}}},
                {{{T_R_BRACE, SHIFT,     77}},                                                                                                                                                                                                                                                                  {}},
                {{{T_R_BRACE, SHIFT,     78}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   REDUCE,    NT_ELSE,     1}, {T_ID,      REDUCE, NT_ELSE,   1}, {T_R_BRACE,   REDUCE, NT_ELSE,   1}, {T_IF,      REDUCE, NT_ELSE,   1}, {T_WHILE,   REDUCE, NT_ELSE,   1}, {T_ELSE,   SHIFT,  80},           {T_RETURN, REDUCE, NT_ELSE,   1}},                                    {{NT_ELSE,     79}}},
                {{{T_VTYPE,   REDUCE,    NT_STMT,     3}, {T_ID,      REDUCE, NT_STMT,   3}, {T_R_BRACE,   REDUCE, NT_STMT,   3}, {T_IF,      REDUCE, NT_STMT,   3}, {T_WHILE,   REDUCE, NT_STMT,   3}, {T_RETURN, REDUCE, NT_STMT,   3}},                                                                      {}},
                {{{T_VTYPE,   REDUCE,    NT_STMT,     2}, {T_ID,      REDUCE, NT_STMT,   2}, {T_R_BRACE,   REDUCE, NT_STMT,   2}, {T_IF,      REDUCE, NT_STMT,   2}, {T_WHILE,   REDUCE, NT_STMT,   2}, {T_RETURN, REDUCE, NT_STMT,   2}},                                                                      {}},
                {{{T_L_BRACE, SHIFT,     81}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   SHIFT,     51},             {T_ID,      SHIFT,  52},           {T_R_BRACE,   REDUCE, NT_BLOCK,  1}, {T_IF,      SHIFT,  49},           {T_WHILE,   SHIFT,  50},           {T_RETURN, REDUCE, NT_BLOCK,  1}},                                                                      {{NT_V_DECL,   47}, {NT_ASSIGN, 48}}},
                {{{T_R_BRACE, SHIFT,     83}},                                                                                                                                                                                                                                                                  {}},
                {{{T_VTYPE,   REDUCE,    NT_ELSE,     0}, {T_ID,      REDUCE, NT_ELSE,   0}, {T_R_BRACE,   REDUCE, NT_ELSE,   0}, {T_IF,      REDUCE, NT_ELSE,   0}, {T_WHILE,   REDUCE, NT_ELSE,   0}, {T_RETURN, REDUCE, NT_ELSE,   0}},                                                                      {}}
        };


bool is_production_reducible(const Expression &expr, const NonTerminals production_symbol) {
    auto productions = PRODUCTIONS.at(production_symbol);

    if (expr._lhs.back() == RHSEntry({NTERM, production_symbol})) {
        return true;
    }
    for (auto &production : productions) {
        if (production.empty() && expr._lhs.back() == production_symbol) {
            return true;
        } else if (expr.is_reducible_by_production({NTERM, production_symbol}, production)) {
            return true;
        }
    }
    return false;
}

std::optional<GotoEntry> try_match_goto(const Expression &expr, const vector<GotoEntry> &gotos) {
    for (auto goto_entry : gotos) {
        if (is_production_reducible(expr, goto_entry.symbol)) {
            return goto_entry;
        }
    }
    return std::nullopt;
}

std::optional<ActionEntry> try_match_action(Expression &expr, const vector<ActionEntry> &actions) {
    for (auto action : actions) {
        if (action.symbol == expr.next_symbol()) {
            return action;
        }
    }
    return std::nullopt;
}

bool apply_action(Expression &expr, ActionEntry &action, std::stack<int> &states) {
    switch (action.type) {
        case SHIFT:
            expr.shift(1);
            states.push(action.value);
            break;
        case REDUCE: {
            auto symbol = static_cast<NonTerminals>(action.value);
            auto &production = PRODUCTIONS.at(symbol);
            //Skip already reduced epsilon productions
            if (production[action.index].empty() && !expr.is_reducible_by_production({NTERM, symbol}, production[action.index])) {
                return false;
            }
            expr.reduce(symbol, production[action.index]);
            for (auto it = production[action.index].size(); it != 0; --it) {
                states.pop();
            }
        }
            break;
        case ACCEPTING:
            break;
    }
    return true;
}

bool parse_tokens(vector<Terminals> tokens) {
    std::stack<int> state_stack;
    Expression expr(tokens);

    state_stack.push(0); // set start state to 0
    while (true) {
        std::cout << "Current state => " << state_stack.top() << std::endl;
        auto action = try_match_action(expr, SLR_TABLE[state_stack.top()].actions);
        if (action.has_value()) {
            if (action->type == ACCEPTING) {
                return true;
            }
            if (apply_action(expr, *action, state_stack)) {
                continue;
            }
        }
        auto goto_entry = try_match_goto(expr, SLR_TABLE[state_stack.top()].gotos);
        if (goto_entry.has_value()) {
            state_stack.push(goto_entry->dest);
            continue;
        }
        return false;
    }
}