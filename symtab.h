#ifndef SYMTAB_H
#define SYMTAB_H

#include <string.h>

#define SYMB_TAB_SIZE 0x100 // 256
#define STACK_SIZE 1024

extern double stack[];
extern double vector_memory[];
extern double acc;
extern int symtab_next_entry;
extern int stack_pointer;

extern double pop(void);
extern void push(double value);
extern int symtab_lookup(char *var_name);
void store(char *var_name, double value);
double recall(char *var_name);

#endif