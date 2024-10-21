#include <ctype.h>
#include <stdio.h>
#include <lexer.h>

char lexeme[MAX_ID_LEN + 1];

int lineNum = 1;

void skip_spaces(FILE *p_tape);
int is_ID(FILE *p_tape);
int is_DEC(FILE *p_tape);
int is_OCT(FILE *p_tape);
int is_HEX(FILE *p_tape);

#pragma region Public Functions
int lxr_get_token(FILE *p_source)
{
    int token = 0;

    if (token = is_ID(p_source)) return token;
    if (token = is_HEX(p_source)) return token;
    if (token = is_OCT(p_source)) return token;
    if (token = is_DEC(p_source)) return token;

    return token = getc(p_source);
}
#pragma endregion

#pragma region Private Functions

void skip_spaces(FILE *p_tape)
{
    int head;

    while (isspace(head = getc(p_tape)))
    {
        if (head == '\n')
        {
            lineNum++;
        }
    }

    ungetc(head, p_tape);
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

/// @brief identifies if next token in the tape is an ID
/// @param tape 
/// @return ID if the next token read is an ID, 0 otherwise
int is_ID(FILE *p_tape)
{
    int head = getc(p_tape);

    if (!isalpha(head))     //if the token does not start with a letter then it is not an ID
    {
        ungetc(head, p_tape); //put the token back in the tape
        return 0;           
    }

    while (isalnum(head = getc(p_tape))); //while the next caracter is an alphanumeic, reads the tape

    ungetc(head, p_tape); //put the character that is not an alphanumeric back into the tape
    
    printf("\t is ID\n");
    
    return ID;
}

/// @brief indentifies if the next token in the tape is a DEC
/// @param p_tape 
/// @return DEC if the next token read is a DEC, 0 otherwise
int is_DEC(FILE *p_tape)
{
    int head = getc(p_tape);

    if (!isdigit(head)) //if the token does not start with a digit then it is not a DEC
    {
        ungetc(head, p_tape); //put the token back in the tape
        return 0;
    }

    if (is_zero(head)) //if the token is zero then it is a DEC
    {
        printf("\t is DEC\n");
        return DEC;
    }

    while (isdigit(head = getc(p_tape))); //while the next caracter is a digit, reads the tape
    
    ungetc(head, p_tape); //put the character that is not a digit back into the tape

    printf("\t is DEC\n");

    return DEC; 
}



/// @brief identifies if the next token in the tape is an OCT
/// @param p_tape 
/// @return OCT if the token read is an OCT, 0 otherwise
int is_OCT(FILE *p_tape)
{
    int prefix = getc(p_tape);

    if (!is_zero(prefix))       //if the token does not start with the prefix zero then it is not an OCT
    {
        ungetc(prefix, p_tape); //put the character read back in the tape
        return 0;
    }

    int head = getc(p_tape);
    
    if (!is_oct(head))          //if the next character read it's not an octal number then it is not an OCT
    {
        ungetc(head, p_tape);   //put the character read back in the tape
        ungetc(prefix, p_tape); //put the prefix back in the tape
        return 0;
    }


    while (isdigit(head = getc(p_tape)) && is_oct(head = getc(p_tape)));    //while the next caracter is an octal number, reads the tape
    ungetc(head, p_tape);                                                   //put the character that is not an octal number back into the tape
    printf("\t is OCT\n");
    return OCT;
}



/// @brief identifies if the next token in the tape is a HEX
/// @param p_tape
/// @return HEX if the token read is a HEX, 0 otherwise
int is_HEX(FILE *p_tape)
{
    int prefixZero = getc(p_tape);

    if (!is_zero(prefixZero)) //if the token does not start with the prefix zero then it is not a HEX
    {
        ungetc(prefixZero, p_tape); //put the character read back in the tape
        return 0;
    }

    int prefixHexIndicator = getc(p_tape);

    if (!is_hex_indicator(prefixHexIndicator))
    {
        ungetc(prefixHexIndicator, p_tape); //put the character read back in the tape
        ungetc(prefixZero, p_tape);         //put the prefix back in the tape
        return 0;
    }

    int head = getc(p_tape);

    if (!isxdigit(head)) //if the next character is not a hexadecimal digit then it is not a HEX
    {
        ungetc(head, p_tape); //put the character read back in the tape
        ungetc(prefixHexIndicator, p_tape); //put the prefix back in the tape
        ungetc(prefixZero, p_tape); //put the prefix back in the tape
        return 0;
    }

    while (isxdigit(head = getc(p_tape))); //while the next caracter is a hexadecimal digit, reads the tape
    ungetc(head, p_tape); //put the character that is not a hexadecimal digit back into the tape
    printf("\t is HEX\n");
    return HEX;
}
#pragma endregion