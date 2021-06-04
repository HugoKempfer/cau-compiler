//
// Created by hugo on 6/4/21.
//

#include "include/slr_table.h"
#include <unordered_map>


static const std::unordered_map<NonTerminals, vector<ProductionEntry>> PRODUCTIONS =
        {{
                 NT_CODE_PRIME, {{{NonTerminals, NT_CODE}}}
         },
         {       NT_CODE,       {
                                 {{NON_TERMINAL, NT_V_DECL}, {NON_TERMINAL, NT_CODE}}, {{NON_TERMINAL, NT_F_DECL}, {NON_TERMINAL, NT_CODE}}, {{NON_TERMINAL, NT_C_DECL}, {NON_TERMINAL, NT_CODE}}, {}
                                }}
        };

static const SLRTableEntry SLR_TABLE[] = {
        {{{T_VTYPE, SHIFT, 5}, {T_CLASS, SHIFT, 6}, {T_DOLLARS, REDUCE, 4}}, {{NT_CODE, 1}, {NT_V_DECL, 2}, {NT_F_DECL, 3}, {NT_C_DECL, 4}}},
        {{},                                                                 {}}
};