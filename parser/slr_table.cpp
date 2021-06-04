//
// Created by hugo on 6/4/21.
//

#include "include/slr_table.h"
#include <unordered_map>

static const std::unordered_map<NonTerminals, vector<ProductionEntry>> PRODUCTIONS =
    {{NT_CODE_PRIME, {{{NTERM, NT_CODE}}}},
     {NT_CODE, {{{NTERM, NT_V_DECL}, {NTERM, NT_CODE}}, {{NTERM, NT_F_DECL}, {NTERM, NT_CODE}}, {{NTERM, NT_C_DECL}, {NTERM, NT_CODE}}, {}}},
     {NT_V_DECL, {{{TERM, T_VTYPE}, {TERM, T_ID}, {TERM, T_SEMI}}, {{TERM, T_VTYPE}, {NTERM, NT_ASSIGN}, {TERM, T_SEMI}}}},
     {NT_ASSIGN, {{{TERM, T_ID}, {TERM, T_ASSIGN}, {NTERM, NT_RHS}}}},
     {NT_RHS, {{{NTERM, NT_EXPR}}, {{TERM, T_LITERAL}}, {{TERM, T_CHARACTER}}, {{TERM, T_BOOLSTR}}}},
     {NT_EXPR, {{{NTERM, NT_EXPR}, {TERM, T_ADDSUB}, {NTERM, NT_EXPR}}, {{NTERM, NT_EXPR}, {TERM, T_MULTDIV}, {NTERM, NT_EXPR}}, {{TERM, T_L_PAREN}, {NTERM, NT_EXPR}, {TERM, T_R_PAREN}}, {{TERM, T_ID}}, {{TERM, T_NUM}}}},
     {NT_F_DECL, {{{TERM, T_VTYPE}, {TERM, T_ID}, {TERM, T_L_PAREN}, {NTERM, NT_ARG}, {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {NTERM, NT_RETURN}, {TERM, T_R_BRACE}}}},
     {NT_ARG, {{{TERM, T_VTYPE}, {TERM, T_ID}, {NTERM, NT_MOREARGS}}, {}}},
     {NT_MOREARGS, {{{TERM, T_COMMA}, {TERM, T_VTYPE}, {TERM, T_ID}, {NTERM, NT_MOREARGS}}, {}}},
     {NT_BLOCK, {{{NTERM, NT_STMT}, {NTERM, NT_BLOCK}}, {}}},
     {NT_STMT, {{{NTERM, NT_V_DECL}}, {{NTERM, T_ASSIGN}, {TERM, T_SEMI}}, {{TERM, T_IF}, {TERM, T_L_PAREN}, {NTERM, NT_COND}, {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {TERM, T_R_BRACE}, {NTERM, NT_ELSE}}, {{TERM, T_WHILE}, {TERM, T_L_PAREN}, {NTERM, NT_COND}, {TERM, T_R_PAREN}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {TERM, T_R_BRACE}}}},
     {NT_COND, {{{NTERM, NT_COND}, {TERM, T_COMP}, {NTERM, NT_COND}}, {{TERM, T_BOOLSTR}}}},
     {NT_ELSE, {{{TERM, T_ELSE}, {TERM, T_L_BRACE}, {NTERM, NT_BLOCK}, {TERM, T_R_BRACE}}, {}}},
     {NT_RETURN, {{{TERM, T_RETURN}, {NTERM, NT_RHS}, {TERM, T_SEMI}}}},
     {NT_C_DECL, {{{TERM, T_CLASS}, {TERM, T_ID}, {TERM, T_L_BRACE}, {NTERM, NT_O_DECL}, {TERM, T_R_BRACE}}}},
     {NT_O_DECL, {{{NTERM, NT_V_DECL}, {NTERM, NT_O_DECL}}, {{NTERM, NT_F_DECL}, {NTERM, NT_O_DECL}}, {}}}
    };

static const SLRTableEntry SLR_TABLE[] = {
    {{{T_VTYPE, SHIFT, 5}, {T_CLASS, SHIFT, 6}, {T_DOLLARS, REDUCE, 4}}, {{NT_CODE, 1}, {NT_V_DECL, 2}, {NT_F_DECL, 3}, {NT_C_DECL, 4}}},
    {{}, {}}};