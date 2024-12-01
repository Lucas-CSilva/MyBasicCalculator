#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

extern FILE *source;
extern int look_ahead;

extern void E(void);
extern int match(int expected);
extern void cmd(void);
extern void mybc(void);

extern double acc;

#endif