#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    ID = 1024,
    DEC,
    OCT,
    HEX,
} EToken;

#define MAX_ID_LEN 32

extern char lexeme[];

extern int lxr_get_token(FILE *p_source);

#endif