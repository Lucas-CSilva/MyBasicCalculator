#include <stdio.h>
#include <string.h>
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
    char varname[MAX_ID_LEN + 1];
    
    if (is_oplus(look_ahead))
    {
       !(look_ahead == MINUS) || (signal = look_ahead);
       match(look_ahead);
    }
    
_T:

_F:
    switch (look_ahead)
    {
        case L_PAREN:
            match(L_PAREN);
            psr_E();
            match(R_PAREN);
            break;
        
        case NUM:
            /*1*/printf("\tmov %s, acc\n", lexeme);/*1*/
            match(NUM);
            break;

        // case DEC:
        //     printf("\t%s\n", lexeme);
        //     match(DEC);
        //     break;

        case OCT:
            printf("\t%s\n", lexeme);
            match(OCT);
            break;

        case HEX:
            printf("\t%s\n", lexeme);
            match(HEX);
            break;

        default:
            /*5*/strcpy(varname, lexeme);/*5*/
            match(ID);
            if (look_ahead == ASGN)
            {
                match(ASGN);
                psr_E();
                printf("\tstore(%s, acc)\n", varname); // -> funcao store
            }
            else
            {
                // R-value variavel de consulta
                /*4*/
                printf("\tacc = recall(%s)\n", varname);
                /*4*/
            }
    }
// end _F:

    if (otimes)
    {
        switch (otimes)
        {
            case TIMES:
                printf("\ttimes stack sp, acc\n"/*, otimes*/);
                break;
            
            case DIV:
                printf("\tdivision stack sp, acc\n"/*, otimes*/);
                break;
        }

        otimes = 0;
    }

    if (is_otimes(look_ahead))
    {
        otimes = look_ahead;
        match(look_ahead);
        goto _F;
    }

// end _ T:
    if (signal)
    {
        printf("\tneg acc\n");
        signal = 0;
    }

    if (oplus)
    {
        switch (oplus)
        {
            case PLUS:
                printf("\tadd acc, stack[sp]\n"/*, oplus*/);
                break;
            
            case MINUS:
                printf("\tsub acc, stack[sp]\n"  /*, oplus*/);
                break;
        }

        oplus = 0;
        printf("\tpop acc\n");
    }

    if (is_oplus(look_ahead))
    {
        /*1*/
        oplus = look_ahead;
        printf("\tpush acc\n");
        /*1*/
        match(look_ahead);
        goto _T;
    }
}

void match(int expected)
{
    if (look_ahead == expected)
    {
        look_ahead = lxr_get_token(pSource);
    }
    else
    {
        fprintf(stderr, "Token missmatch.\n");
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