#include <stdio.h>
#include <stdlib.h>

extern void psr_match(int expected);
extern FILE *pSource;
extern int look_ahead;

void psr_E(void);
void psr_T(void);
void psr_F(void);
void psr_R(void);
void psr_Q(void);