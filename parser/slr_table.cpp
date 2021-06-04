//
// Created by hugo on 6/4/21.
//

#include "include/slr_table.h"

static const ProductionEntry PRODUCTIONS[] = {
        {NT_CODE_PRIME, {{NON_TERMINAL, {.nonTerminals= NT_CODE}}}}
};
static const SLRTableEntry SLR_TABLE[] = {
        {{{T_VTYPE, SHIFT, 5}, {T_CLASS, SHIFT, 6}, {T_DOLLARS, REDUCE, 4}}, {{NT_CODE, 1}, {NT_V_DECL, 2}, {NT_F_DECL, 3}, {NT_C_DECL, 4}}},
        {{},                                                                 {}}
};