#include <symtab.h>
#include <lexer.h>

double stack[STACK_SIZE];
double vector_memory[SYMB_TAB_SIZE];

char symtab[SYMB_TAB_SIZE][MAX_ID_LEN];

double acc = 0;
int symtab_next_entry = 0;
int stack_pointer = -1;


double pop(void)
{
    if (stack_pointer < 0)
    {
        fprintf(stderr, "can't pop an empty stackt"); 
        exit(-1);
    }

    return stack[stack_pointer--];
}

void push(double value)
{
    if (stack_pointer == STACK_SIZE - 1)
    {
        fprintf(stderr, "can't push to an empty stackt"); 
        exit(-1);
    }
    
    stack[++stack_pointer] = value;
}

/// @brief lookup in the symtab if varName has already been added
/// @param varName 
/// @return next position 
int symtab_lookup(char *var_name)
{
    int i;

    for (i = 0; i < symtab_next_entry; i++)
    {
        if (strcmp(var_name, symtab[i]) == 0) break;
    }

    if (i == symtab_next_entry)
    {
        strcpy(symtab[i], var_name);
    }

    return i;
}

void store(char *var_name, double value)
{
    int i = symtab_lookup(var_name);

    vector_memory[i] = value;
}


double recall(char *var_name)
{   
    int i = symtab_lookup(var_name);
    
    return vector_memory[i];
    // if varname exists return
    // if varname doesnt exists create var and return 0
}