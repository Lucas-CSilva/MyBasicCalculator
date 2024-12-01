#include <stdio.h>
#include <string.h>
#include <lexer.h>
#include <symtab.h>
#include <keywords.h>
#include <parser.h>

#define PLUS '+'
#define MINUS '-'
#define TIMES '*'
#define DIV '/'
#define L_PAREN '('
#define R_PAREN ')'

int look_ahead;
int stop_parser = 0;
double acc = 0;

int is_oplus(int c);
int is_otimes(int c);

#pragma region Public Functions 
void mybc(void)
{
    cmd();
    while (look_ahead == ';' || look_ahead == '\n' )
    {
        match(look_ahead);
        cmd();
    }
}

void cmd(void)
{
    switch (look_ahead)
    {
        case ';':
        case '\n':
        case EOF:
            return;

        case QUIT:
        case EXIT:
            exit(0);

        default:
            E();
            if (stop_parser)
            {
                stop_parser = 0;
                while ((look_ahead = getc(source)) != ';' && look_ahead != '\n' && look_ahead != EOF);
                return;
            }
            else
            {
                printf("result: %lg\n", acc);
                break;
            }

    }
}

void E(void)
{
    /*0*/
    int oplus = 0;
    int otimes = 0;
    int signal = 0;
    char varname[MAX_ID_LEN + 1];
    /*0*/
    
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
            if (!match(L_PAREN)) return;
            E();
            if (!match(R_PAREN)) return;
            break;
        
        case NUM:
            /*1*/acc = atof(lexeme);/*1*/
            if (!match(NUM)) return;
            break;

        default:
            /*5*/strcpy(varname, lexeme);/*5*/

            if (!match(ID)) return;

            if (look_ahead == ASGN)
            {
                if(!match(ASGN)) return;
                E();
                store(varname, acc);
            }
            else
            {
                /*4*/
                acc = recall(varname);
                /*4*/
            }
    }
// end _F:

    if (otimes)
    {
        switch (otimes)
        {
            case TIMES:
                /*1*/stack[stack_pointer] *= acc;/*1*/
                break;
            
            case DIV:
                /*1*/stack[stack_pointer] /= acc;/*1*/
                break;
        }

        /*1*/
        acc = pop();
        otimes = 0;
        /*1*/
    }

    if (is_otimes(look_ahead))
    {
        /*1*/
        otimes = look_ahead;
        push(acc); 
        /*1*/
        match(look_ahead);
        goto _F;
    }

// end _ T:
    if (signal)
    {
        /*1*/
        acc = -acc;
        signal = 0;
        /*1*/
    }

    if (oplus)
    {
        switch (oplus)
        {
            case PLUS:
                /*1*/
                stack[stack_pointer] += acc;
                /*1*/
                break;
            
            case MINUS:
                /*1*/
                stack[stack_pointer] -= acc;
                /*1*/
                break;
        }

        /*1*/
        acc = pop();
        /*1*/
        oplus = 0;
    }

    if (is_oplus(look_ahead))
    {
        /*1*/
        oplus = look_ahead;
        push(acc);
        /*1*/
        match(look_ahead);
        goto _T;
    }
}

int match(int expected)
{
    if (look_ahead == expected)
    {
        look_ahead = gettoken(source);
        return 1;
    }
    else
    {
        const char *expected_str = get_token_to_string(expected);
        const char *received_str = get_token_to_string(look_ahead);

        char expected_buf[2]; // Buffer para armazenar a string do número
        char received_buf[2]; // Buffer para armazenar a string do número

        if (expected_str == NULL)
        {
            sprintf(expected_buf, "%c", expected);
            expected_str = expected_buf;
        }

        if (received_str == NULL)
        {
            sprintf(received_buf, "%c", look_ahead);
            received_str = received_buf;
        }

        fprintf(stderr, "Token mismatch - expected: %s - received: %s\n", expected_str, received_str);
        stop_parser = 1;
        return 0;
        // exit(-1);
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