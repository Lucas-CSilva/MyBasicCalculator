#include <stdio.h>

typedef enum {
    ID = 1024,
    DEC,
    OCT,
    HEX,
} EToken;

extern int lineNum;

extern int lxr_get_token(FILE *p_source);