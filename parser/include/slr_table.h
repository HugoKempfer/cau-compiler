//
// Created by hugo on 6/4/21.
//

#ifndef PARSER_SLR_TABLE_H
#define PARSER_SLR_TABLE_H

#include <vector>

using std::vector;

typedef enum {
    T_VTYPE,
    T_ID,
    T_SEMI,
    T_ASSIGN,
    T_LITERAL,
    T_CHARACTER,
    T_BOOLSTR,
    T_ADDSUB,
    T_MULTDIV,
    T_L_PAREN,
    T_R_PAREN,
    T_NUM,
    T_L_BRACE,
    T_R_BRACE,
    T_COMMA,
    T_IF,
    T_WHILE,
    T_COMP,
    T_ELSE,
    T_RETURN,
    T_CLASS,
    T_DOLLARS
} Terminals;

typedef enum {
    NT_CODE_PRIME,
    NT_CODE,
    NT_V_DECL,
    NT_ASSIGN,
    NT_RHS,
    NT_EXPR,
    NT_F_DECL,
    NT_ARG,
    NT_MOREARGS,
    NT_BLOCK,
    NT_STMT,
    NT_COND,
    NT_ELSE,
    NT_RETURN,
    NT_C_DECL,
    NT_O_DECL
} NonTerminals;

/* ---=== SLR TABLE ===--- */

typedef enum {
    SHIFT,
    REDUCE
} ActionType;

typedef struct {
    Terminals symbol;
    ActionType type;
    int value;
} ActionEntry;

typedef struct {
    NonTerminals symbol;
    int dest;
} GotoEntry;

typedef struct {
    vector<ActionEntry> actions;
    vector<GotoEntry> gotos;
} SLRTableEntry;

typedef enum {
    TERM, NTERM
} RHSType;

struct RHSEntry { // Maybe rename
    RHSType type;
    int value;

    bool operator==(const RHSEntry &other) const {
        return this->type == other.type && this->value == other.value;
    }

    bool operator!=(const RHSEntry &other) const {
        return this->type != other.type && this->value != other.value;
    }
};

using ProductionEntry = vector<struct RHSEntry>;

#endif //PARSER_SLR_TABLE_H
