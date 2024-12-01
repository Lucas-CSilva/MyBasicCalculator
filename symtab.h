#ifndef SYMTAB_H
#define SYMTAB_H

#define SYMB_TAB_SIZE 256 // 256 entries in the symbol table
#define STACK_SIZE 1024   // 1024 entries in the stack

extern double stack[];
extern double vector_memory[];
extern int symtab_next_entry;
extern int stack_pointer;

/// @brief Pops the top value from the stack
/// @return The top value from the stack
extern double pop(void);

/// @brief Pushes a value onto the stack
/// @param value The value to push onto the stack
extern void push(double value);

/// @brief Looks up a variable in the symbol table
/// @param var_name The name of the variable to look up
/// @return The index of the variable in the symbol table
extern int symtab_lookup(const char *var_name);

/// @brief Stores a value in the symbol table
/// @param var_name The name of the variable
/// @param value The value to store
extern void store(const char *var_name, double value);

/// @brief Recalls a value from the symbol table
/// @param var_name The name of the variable
/// @return The value of the variable
extern double recall(const char *var_name);

#endif