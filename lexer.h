#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_ID_LEN 32

typedef enum {
    ID = 1024,
    NUM,
    ASGN,
} EToken;

extern char lexeme[];

/// @brief Gets the next token from the source file
/// @param p_source The source file to read from
/// @return The next token
extern int gettoken(FILE *source);

#endif