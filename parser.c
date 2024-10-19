#include <stdio.h>
#include <lexer.h>
#include <parser.h>

int look_ahead;

void psr_E(void)
{
    if (look_ahead == '+' || look_ahead == '-')
    {
       psr_match(look_ahead);
    }
    
    psr_T();
    psr_R();
}


void psr_T(void)
{
    psr_F();
    psr_Q();
}


void psr_F(void)
{
    switch (look_ahead)
    {
        case '(':
            psr_match('(');
            psr_E();
            psr_match(')');
            break;
        
        case DEC:
            psr_match(DEC);
            break;

        case OCT:
            psr_match(OCT);
            break;

        case HEX:
            psr_match(HEX);
            break;

        default:
            psr_match(ID);
    }
}

psr_R(void)
{
    switch (look_ahead)
    {
        case '+':
            psr_match('+');
            psr_T();
            psr_R();
            break;

        case '-':
            psr_match('-');
            psr_T();
            psr_R();
            break;
    }
}


void psr_Q(void)
{
    switch (look_ahead)
    {
        case '*':
            psr_match('*');
            psr_F();
            psr_Q();
            break;

        case '/':
            psr_match('/');
            psr_F();
            psr_Q();
            break;
    }
}

void psr_match(int expected)
{
    if (look_ahead == expected)
    {
        look_ahead = lxr_get_token(pSource);
    }
    else
    {
        fprintf(stderr, "Syntax error\n");
        exit(-1);
    }
}