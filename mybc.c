#include <stdio.h>
#include <parser.h>
#include <lexer.h>

FILE *pSource;

int main() 
{
    pSource = stdin;

    look_ahead = lxr_get_token(pSource);
    
    psr_E();

    return 0;
}

