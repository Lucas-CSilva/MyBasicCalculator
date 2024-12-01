#include <stdlib.h>
#include <string.h>
#include <lexer.h>
#include <symtab.h>

double stack[STACK_SIZE];
double vector_memory[SYMB_TAB_SIZE];
char symtab[SYMB_TAB_SIZE][MAX_ID_LEN];

int symtab_next_entry = 0;
int stack_pointer = -1;

/// @brief Pops the top value from the stack
/// @return The top value from the stack
double pop(void)
{
    if (stack_pointer < 0)
    {
        fprintf(stderr, "Error: can't pop from an empty stack.\n"); 
        exit(-1);
    }

    return stack[stack_pointer--];
}

/// @brief Pushes a value onto the stack
/// @param value The value to push onto the stack
void push(double value)
{
    if (stack_pointer == STACK_SIZE - 1)
    {
        fprintf(stderr, "Error: can't push to a full stack.\n"); 
        exit(-1);
    }
    
    stack[++stack_pointer] = value;
}

/// @brief Looks up a variable in the symbol table
/// @param var_name The name of the variable to look up
/// @return The index of the variable in the symbol table
int symtab_lookup(const char *var_name)
{
    for (int i = 0; i < symtab_next_entry; i++)
    {
        if (strcmp(var_name, symtab[i]) == 0)
        {
            return i;
        }
    }

    if (symtab_next_entry < SYMB_TAB_SIZE)
    {
        strcpy(symtab[symtab_next_entry], var_name);
        return symtab_next_entry++;
    }
    else
    {
        fprintf(stderr, "Error: symbol table is full.\n");
        exit(-1);
    }
}

/// @brief Stores a value in the symbol table
/// @param var_name The name of the variable
/// @param value The value to store
void store(const char *var_name, double value)
{
    int index = symtab_lookup(var_name);
    vector_memory[index] = value;
}

/// @brief Recalls a value from the symbol table
/// @param var_name The name of the variable
/// @return The value of the variable
double recall(const char *var_name)
{
    int index = symtab_lookup(var_name);
    return vector_memory[index];
}