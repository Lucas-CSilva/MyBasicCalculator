#include <ctype.h>
#include <stdio.h>
#include <lexer.h>

char lexeme[MAX_ID_LEN + 1];

void clear_lexeme(int index);
void skip_spaces(FILE *p_tape);
int is_ID(FILE *p_tape);
int is_ASGN(FILE *p_tape);
// int is_DEC(FILE *p_tape);
int is_OCT(FILE *p_tape);
int is_HEX(FILE *p_tape);
int is_NUM(FILE *p_tape);

#pragma region Public Functions
int lxr_get_token(FILE *p_source)
{
    int token = 0;

    skip_spaces(p_source);

    if (token = is_ASGN(p_source)) return token;
    if (token = is_ID(p_source)) return token;
    if (token = is_HEX(p_source)) return token;
    if (token = is_OCT(p_source)) return token;
    if (token = is_NUM(p_source)) return token;

    return token = getc(p_source);
}
#pragma endregion

#pragma region Private Functions

void clear_lexeme(int index)
{
    lexeme[index] = 0;
}

void skip_spaces(FILE *p_tape)
{
    int head;

    while (isspace(head = getc(p_tape)));

    ungetc(head, p_tape);
}

void unget_all_read_characters(FILE *p_tape, int index)
{
    for (int i = index; i > -1; i--)
    {
        ungetc(lexeme[i], p_tape);
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


/// @brief checks if the character is an octal number
/// @param character
/// @return 1 if the character is an octal number, 0 otherwise
int is_oct(int character)
{
    return character >= '0' && character <= '7';
}

/// @brief checks if the character is a hex indicator
/// @param character 
/// @return 1 if the character is a hex indicator, 0 otherwise
int is_hex_indicator(int character)
{
    return character == 'x' || character == 'X';
}

int is_dot(int character)
{
    return character == '.';
}

int is_exp_indicator(int character)
{
    return character == 'e' || character == 'E';
}

int is_exp(int character)
{
    return character == '+' || character == '-' || isdigit(character);
}

int is_invalid_NUM_character(int character)
{
    return !isdigit(character) 
        && !is_dot(character) 
        && !is_exp_indicator(character)
        && !isspace(character);
}

int is_ASGN(FILE *p_tape)
{
    int i = 0;
    lexeme[i] = getc(p_tape);

    if (lexeme[i] != ':')
    {
        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);
        return 0;
    }

    i++;
    lexeme[i] = getc(p_tape);

    if (lexeme[i] != '=')
    {
        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);

        i--;

        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);
        return 0;
    }
    
    return ASGN;
}

/// @brief identifies if next token in the tape is an ID
/// @param tape 
/// @return ID if the next token read is an ID, 0 otherwise
int is_ID(FILE *p_tape)
{
    int i = 0;
    lexeme[i] = getc(p_tape);

    if (!isalpha(lexeme[i]))     //if the token does not start with a letter then it is not an ID
    {
        ungetc(lexeme[i], p_tape); //put the token back in the tape
        clear_lexeme(i);
        return 0;           
    }

    i++;
    while (isalnum(lexeme[i] = getc(p_tape))) i++; //while the next caracter is an alphanumeic, reads the tape

    ungetc(lexeme[i], p_tape); //put the character that is not an alphanumeric back into the tape
    clear_lexeme(i);
    
    return ID;
}

/// @brief indentifies if the next token in the tape is a DEC
/// @param p_tape 
/// @return DEC if the next token read is a DEC, 0 otherwise
/*int is_DEC(FILE *p_tape)
{
    int i = 0;
    lexeme[i] = getc(p_tape);

    if (!isdigit(lexeme[i])) //if the token does not start with a digit then it is not a DEC
    {
        ungetc(lexeme[i], p_tape); //put the token back in the tape
        clear_lexeme(i);
        return 0;
    }

    if (is_zero(lexeme[i])) //if the token is zero then it is a DEC
    {
        return DEC;
    }

    i++;
    while (isdigit(lexeme[i] = getc(p_tape))) i++; //while the next caracter is a digit, reads the tape
    
    ungetc(lexeme[i], p_tape); //put the character that is not a digit back into the tape

    clear_lexeme(i);

    printf("\t is DEC\n");

    return DEC; 
}*/



/// @brief identifies if the next token in the tape is an OCT
/// @param p_tape 
/// @return OCT if the token read is an OCT, 0 otherwise
int is_OCT(FILE *p_tape)
{
    int prefix = 0;
    
    lexeme[prefix] = getc(p_tape);

    if (!is_zero(lexeme[prefix]))       //if the token does not start with the prefix zero then it is not an OCT
    {
        ungetc(lexeme[prefix], p_tape); //put the character read back in the tape
        clear_lexeme(prefix);
        return 0;
    }

    
    int i = 1;
    lexeme[i] = getc(p_tape);
    
    if (!is_oct(lexeme[i]))          //if the next character read it's not an octal number then it is not an OCT
    {
        ungetc(lexeme[i], p_tape);   //put the character read back in the tape
        ungetc(lexeme[prefix], p_tape); //put the prefix back in the tape

        clear_lexeme(i);
        clear_lexeme(prefix);
        return 0;
    }

    i++;
    while (isdigit(lexeme[i] = getc(p_tape)) && is_oct(lexeme[i])) i++;    //while the next caracter is an octal number, reads the tape
    ungetc(lexeme[i], p_tape);                                                   //put the character that is not an octal number back into the tape
    clear_lexeme(i);

    return OCT;
}



/// @brief identifies if the next token in the tape is a HEX
/// @param p_tape
/// @return HEX if the token read is a HEX, 0 otherwise
int is_HEX(FILE *p_tape)
{
    int prefixZero = 0;
    lexeme[prefixZero] = getc(p_tape);

    if (!is_zero(lexeme[prefixZero])) //if the token does not start with the prefix zero then it is not a HEX
    {
        ungetc(lexeme[prefixZero], p_tape); //put the character read back in the tape
        clear_lexeme(prefixZero);
        return 0;
    }

    int prefixHexIndicator = 1;
    lexeme[prefixHexIndicator] = getc(p_tape);

    if (!is_hex_indicator(lexeme[prefixHexIndicator]))
    {
        ungetc(lexeme[prefixHexIndicator], p_tape); //put the character read back in the tape
        ungetc(lexeme[prefixZero], p_tape);         //put the prefix back in the tape

        clear_lexeme(prefixHexIndicator);
        clear_lexeme(prefixZero);
        return 0;
    }

    int i = 2;
    lexeme[i] = getc(p_tape);

    if (!isxdigit(lexeme[i])) //if the next character is not a hexadecimal digit then it is not a HEX
    {
        ungetc(lexeme[i], p_tape); //put the character read back in the tape
        ungetc(lexeme[prefixHexIndicator], p_tape); //put the prefix back in the tape
        ungetc(lexeme[prefixZero], p_tape); //put the prefix back in the tape

        clear_lexeme(i);
        clear_lexeme(prefixHexIndicator);
        clear_lexeme(prefixZero);
        return 0;
    }

    i++;
    while (isxdigit(lexeme[i] = getc(p_tape))) i++; //while the next caracter is a hexadecimal digit, reads the tape
    
    ungetc(lexeme[i], p_tape); //put the character that is not a hexadecimal digit back into the tape
    clear_lexeme(i);

    return HEX;
}


int is_NUM(FILE *p_tape)
{
    int i = 0;

    lexeme[i] = getc(p_tape);
    if (!isdigit(lexeme[i]) && !is_dot(lexeme[i])) // if the first char is not a digit or a dot then it is not a NUM
    {
        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);
        return 0;
    }

    if (isdigit(lexeme[i]))
    {
        i++;
        while (isdigit(lexeme[i] = getc(p_tape))) i++; //while the next caracter is a digit, reads the tape

        if (is_invalid_NUM_character(lexeme[i]))
        {
            unget_all_read_characters(p_tape, i);
            return 0;
        }

        if (isspace(lexeme[i]))
        {
            ungetc(lexeme[i], p_tape);
            clear_lexeme(i);
            return NUM;
        }
    }

    i++;
    //o ultimo caracter lido foi um '.', le ate encontrar um char diferente de digito
    while (isdigit(lexeme[i] = getc(p_tape))) i++;

    if (isalpha(lexeme[i]) && !is_exp_indicator(lexeme[i])) // verifica se o ultimo caracter lido e invalido
    {
        unget_all_read_characters(p_tape, i);
        return 0;
    }
    else if (is_exp_indicator(lexeme[i])) // o char lido eh um identificador de exponencial e ou E
    {
        i++;
        if (!is_exp(lexeme[i] = getc(p_tape))) // verifica se o proximo char eh um sinal ou um digito, caso nao seja, o numero eh invalido
        {
            unget_all_read_characters(p_tape, i);
            return 0;
        }

        if (lexeme[i] == '+' || lexeme[i] == '-') // caso o proximo char seja um sinal, le o proximo char, caso nao seja um digito, o numero eh invalido
        {
            i++;
            if (!isdigit(lexeme[i] = getc(p_tape))) // 0.1e+a
            {
                unget_all_read_characters(p_tape, i);
                return 0;
            }
        }

        i++;
        while (isdigit(lexeme[i] = getc(p_tape))) i++; // le ate encontrar um char diferente de digito
        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);
        return NUM;
    }
    else // o char lido nao faz parte do numero
    {
        ungetc(lexeme[i], p_tape);
        clear_lexeme(i);
        return NUM;
    }
}
#pragma endregion