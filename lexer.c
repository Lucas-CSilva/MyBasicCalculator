#include <ctype.h>
#include <stdio.h>
#include <keywords.h>
#include <lexer.h>

char lexeme[MAX_ID_LEN + 1];

void clear_lexeme(int index);
void skip_spaces(FILE *tape);
int isID(FILE *tape);
int isASGN(FILE *tape);
int isNUM(FILE *tape);

#pragma region Public Functions

/// @brief Gets the next token from the source file
/// @param source The source file to read from
/// @return The next token
int gettoken(FILE *source)
{
    int token = 0;

    skip_spaces(source);

    if (token = isASGN(source))
    {
        return token;
    }

    if (token = isID(source)) 
    {
        return token;
    }

    if (token = isNUM(source))
    {
        return token;
    } 
    
    return token = getc(source);
}

char* get_token_to_string(int token)
{
    switch (token)
    {
        case ID:
            return "ID";
        case NUM:
            return "NUM";
        case ASGN:
            return "ASGN";
        default:
            return NULL;
    }
}

#pragma endregion

#pragma region Private Functions

/// @brief Clears the lexeme at the given index
/// @param index The index to clear
void clear_lexeme(int index)
{
    lexeme[index] = 0;
}

/// @brief Skips spaces in the input tape
/// @param tape The input tape
void skip_spaces(FILE *tape)
{
    int head;

    while (isspace(head = getc(tape)))
    {

    }

    ungetc(head, tape);
}

/// @brief Ungets all read characters
/// @param tape The input tape
/// @param index The index to unget to
void unget_all_read_characters(FILE *tape, int index)
{
    for (int i = index; i > -1; i--)
    {
        ungetc(lexeme[i], tape);
        clear_lexeme(i);
    }
}

/// @brief checks if the character is zero
/// @param character 
/// @return 1 if the character is zero, 0 otherwise
int is_zero(int character)
{
    return character == '0';
}

/// @brief Checks if the character is a dot
/// @param character The character to check
/// @return 1 if the character is a dot, 0 otherwise
int is_dot(int character)
{
    return character == '.';
}

/// @brief Checks if the character is an exponent indicator
/// @param character The character to check
/// @return 1 if the character is an exponent indicator, 0 otherwise
int is_exp_indicator(int character)
{
    return character == 'e' || character == 'E';
}


/// @brief Checks if the next token in the tape is an assignment
/// @param tape The input tape
/// @return ASGN if the next token is an assignment, 0 otherwise
int isASGN(FILE *tape)
{
    lexeme[0] = getc(tape);

    if (lexeme[0] != ':') //if the token does not start with a colon then it is not an assignment
    {
         //put the read characters back in the tape
        ungetc(lexeme[0], tape);
        clear_lexeme(0);
        return 0;
    }

    lexeme[1] = getc(tape);

    if (lexeme[1] != '=') //if the next character is not an equal sign then it is not an assignment
    {
        ungetc(lexeme[1], tape);
        clear_lexeme(1);

        ungetc(lexeme[0], tape);
        clear_lexeme(0);

        return 0;
    }
    
    return ASGN;
}

/// @brief identifies if next token in the tape is an ID
/// @param tape 
/// @return ID if the next token read is an ID, 0 otherwise
int isID(FILE *tape)
{
    int i = 0;
    lexeme[i] = getc(tape);

    if (!isalpha(lexeme[i]))     //if the token does not start with a letter then it is not an ID
    {
        ungetc(lexeme[i], tape); //put the token back in the tape
        clear_lexeme(i);
        
        return 0;           
    }

    i++;
    while (isalnum(lexeme[i] = getc(tape))) i++; //while the next caracter is an alphanumeic, reads the tape

    ungetc(lexeme[i], tape); //put the token back in the tape
    clear_lexeme(i);
    
    int keyword = 0; //check if the token is a keyword
    if (keyword = is_keyword(lexeme)) //if the token is a keyword then return the keyword ID 
    {
        return keyword;
    } 
    
    return ID;
}

/// @brief Checks if the character is a valid start of a number
/// @param character 
/// @return 1 if the character is a valid start of a number, 0 otherwise
int is_valid_start_of_num(int character)
{
    return isdigit(character) || is_dot(character);
}

/// @brief Identifies if the next token in the tape is a number
/// using the following regular expression: 
/// (uint.[0−9]∗|′.′[0−9]+)([eE][′+′′−′]?[0−9]+)?|uint[eE][′+′′−′]?[0-9]+</para>
/// @param tape The input tape
/// @return NUM if the next token read is a number, 0 otherwise
int isNUM(FILE *tape)
{
    int i = 0;

    lexeme[i] = getc(tape);

    // a number can begin with a digit or a dot: 1 or .1
    if (!is_valid_start_of_num(lexeme[i])) // if the first char is not a digit or a dot then it is not a NUM
    {
        ungetc(lexeme[i], tape);
        clear_lexeme(i);
        return 0;
    }

    // if the first char is a dot then it must be followed by a digit: .1
    if (is_dot(lexeme[i]))
    {
        i++;
        if (!isdigit(lexeme[i] = getc(tape))) 
        {
            unget_all_read_characters(tape, i);
            return 0;
        }
        
    }

    // if the first char is a digit then it is a NUM
    if (isdigit(lexeme[i]))
    {
        i++;
        while (isdigit(lexeme[i] = getc(tape))) i++; //while the next caracter is a digit, reads the tape

        if (!is_dot(lexeme[i]) && !is_exp_indicator(lexeme[i])) // if the next char is not a dot or an exp indicator then it is a NUM
        {
            ungetc(lexeme[i], tape);
            clear_lexeme(i);
            return NUM;
        }
    }

    // if the read character is a dot then it is a NUM
    if (is_dot(lexeme[i]))
    {
        i++;
        if (!isdigit(lexeme[i] = getc(tape)) && !is_exp_indicator(lexeme[i]))// if the next char is not a digit or an exp indicator then the number sequence ended
        {
            ungetc(lexeme[i], tape);
            clear_lexeme(i);
            return NUM;
        }

        if (is_exp_indicator(lexeme[i])) goto _HANDLE_EXP;//verificar 1.e8

        i++;
        while (isdigit(lexeme[i] = getc(tape))) i++; // read the tape until the end of the digit sequence

        if (!is_exp_indicator(lexeme[i])) // if the next char is not an exp indicator then the number sequence ended
        {
            ungetc(lexeme[i], tape);
            clear_lexeme(i);
            return NUM;
        }
    }

// reads the exp indicator
_HANDLE_EXP:
        i++;
        lexeme[i] = getc(tape);
        if (!isdigit(lexeme[i]) && lexeme[i] != '+' && lexeme[i] != '-') // if the next char is not a digit or a sign then it is not a NUM
        {
            unget_all_read_characters(tape, i);
            return 0;
        }

        i++;
        while (isdigit(lexeme[i] = getc(tape))) i++; // read the tape until the end of the digit sequence
        
        ungetc(lexeme[i], tape);
        clear_lexeme(i);
        return NUM;
}
#pragma endregion