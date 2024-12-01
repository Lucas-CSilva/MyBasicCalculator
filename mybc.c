#include <stdio.h>
#include <parser.h>
#include <lexer.h>

FILE *source;

int main() 
{
    source = stdin;

    look_ahead = gettoken(source);

    mybc();

    return 0;
}

