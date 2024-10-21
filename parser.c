#include <stdio.h>
#include <lexer.h>
#include <parser.h>

#define PLUS '+'
#define MINUS '-'
#define TIMES '*'
#define DIV '/'
#define L_PAREN '('
#define R_PAREN ')'

int look_ahead;

int is_oplus(int c);
int is_otimes(int c);

#pragma region Public Functions 

void psr_E(void)
{
    int oplus = 0;
    int otimes = 0;
    int signal = 0;
    
    if (is_oplus(look_ahead))
    {
       !(look_ahead == MINUS) || (signal = look_ahead);
       psr_match(look_ahead);
    }
    
_T:
    otimes = 0;
_F:
    switch (look_ahead)
    {
        case L_PAREN:
            psr_match(L_PAREN);
            psr_E();
            psr_match(R_PAREN);
            break;
        
        case DEC:
            printf("\t%s\n", lexeme);
            psr_match(DEC);
            break;

        case OCT:
            printf("\t%s\n", lexeme);
            psr_match(OCT);
            break;

        case HEX:
            printf("\t%s\n", lexeme);
            psr_match(HEX);
            break;

        default:
            printf("\t%s\n", lexeme);
            psr_match(ID);
    }

    if (otimes)
    {
        printf("\t%c\n", otimes);
        otimes = 0;
    }

    if (is_otimes(look_ahead))
    {
        otimes = look_ahead;
        psr_match(look_ahead);
        goto _F;
    }

    if (signal)
    {
        printf("\tneg\n");
        signal = 0;
    }

    if (oplus)
    {
        printf("\t%c\n", oplus);
        oplus = 0;
    }

    if (is_oplus(look_ahead))
    {
        oplus = look_ahead;
        psr_match(look_ahead);
        goto _T;
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

#pragma endregion

#pragma region Private Functions

int is_oplus(int c)
{
    return c == PLUS || c == MINUS;
}

int is_otimes(int c)
{
    return c == TIMES || c == DIV;
}

#pragma endregion