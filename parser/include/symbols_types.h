//
// Created by hugo on 6/4/21.
//

#ifndef PARSER_SYMBOLS_TYPES_H
#define PARSER_SYMBOLS_TYPES_H

#include <vector>

using std::vector;

typedef enum {

} Terminals;

typedef enum {

} NonTerminals;

/* ---=== SLR TABLE ===--- */

typedef struct {
    Terminals symbol;
    enum {
        SHIFT,
        REDUCE
    } type;
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

typedef struct {
    struct RHSEntry {
        enum {
            TERMINAL, NON_TERMINAL
        } type;
        union {
            Terminals terminal;
            NonTerminals nonTerminals
        } value;
    };
    NonTerminals non_terminal;
    vector<struct RHSEntry> rhs;
} ProductionEntry;

#endif //PARSER_SYMBOLS_TYPES_H
