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
void mybc(void) // Define the function mybc with no parameters and no return value
{
    cmd(); // Call the function cmd
    while (look_ahead == ';' || look_ahead == '\n' ) // Loop while look_ahead is either ';' or a newline character
    {
        match(look_ahead); // Call the function match with look_ahead as the argument
        cmd(); // Call the function cmd again
    }
}

void cmd(void) // Define the function cmd with no parameters and no return value
{
    switch (look_ahead) // Start a switch statement based on the value of look_ahead
    {
        case ';': // If look_ahead is a semicolon
        case '\n': // If look_ahead is a newline character
        case EOF: // If look_ahead is the end of file
            return; // Return from the function

        case QUIT: // If look_ahead is the QUIT command
        case EXIT: // If look_ahead is the EXIT command
            exit(0); // Exit the program with status 0

        default: // For any other value of look_ahead
            E(); // Call the function E
            if (stop_parser) // If stop_parser is true
            {
                stop_parser = 0; // Reset stop_parser to false
                while ((look_ahead = getc(source)) != ';' && look_ahead != '\n' && look_ahead != EOF); // Read characters from source until a semicolon, newline, or EOF is found
                return; // Return from the function
            }
            else // If stop_parser is false
            {
                printf("result: %lg\n", acc); // Print the result stored in acc
                break; // Break out of the switch statement
            }

    }
}

void E(void) // Define the function E with no parameters and no return value
{
    /*0*/
    int oplus = 0; // Initialize oplus to 0
    int otimes = 0; // Initialize otimes to 0
    int signal = 0; // Initialize signal to 0
    char varname[MAX_ID_LEN + 1]; // Declare a character array varname with size MAX_ID_LEN + 1
    /*0*/
    
    if (is_oplus(look_ahead)) // If look_ahead is an addition operator
    {
       !(look_ahead == MINUS) || (signal = look_ahead); // If look_ahead is MINUS, set signal to look_ahead
       match(look_ahead); // Call match with look_ahead as the argument
    }
    
_T:

_F:
    switch (look_ahead) // Start a switch statement based on the value of look_ahead
    {
        case L_PAREN: // If look_ahead is a left parenthesis
            if (!match(L_PAREN)) return; // If match fails, return
            E(); // Call the function E
            if (!match(R_PAREN)) return; // If match fails, return
            break;
        
        case NUM: // If look_ahead is a number
            /*1*/acc = atof(lexeme);/*1*/ // Convert lexeme to a float and store in acc
            if (!match(NUM)) return; // If match fails, return
            break;

        default: // For any other value of look_ahead
            /*5*/strcpy(varname, lexeme);/*5*/ // Copy lexeme to varname

            if (!match(ID)) return; // If match fails, return

            if (look_ahead == ASGN) // If look_ahead is an assignment operator
            {
                if(!match(ASGN)) return; // If match fails, return
                E(); // Call the function E
                /*5*/
                store(varname, acc); // Store acc in varname
                /*5*/
            }
            else // If look_ahead is not an assignment operator
            {
                /*4*/
                acc = recall(varname); // Recall the value of varname and store in acc
                /*4*/
            }
    }
// end _F:

    if (otimes) // If otimes is not 0
    {
        switch (otimes) // Start a switch statement based on the value of otimes
        {
            case TIMES: // If otimes is TIMES
                /*1*/stack[stack_pointer] *= acc;/*1*/ // Multiply stack[stack_pointer] by acc
                break;
            
            case DIV: // If otimes is DIV
                /*1*/stack[stack_pointer] /= acc;/*1*/ // Divide stack[stack_pointer] by acc
                break;
        }

        /*1*/
        acc = pop(); // Pop the top value from the stack and store in acc
        otimes = 0; // Reset otimes to 0
        /*1*/
    }

    if (is_otimes(look_ahead)) // If look_ahead is a multiplication operator
    {
        /*1*/
        otimes = look_ahead; // Set otimes to look_ahead
        push(acc); // Push acc onto the stack
        /*1*/
        match(look_ahead); // Call match with look_ahead as the argument
        goto _F; // Go to label _F
    }

// end _T:
    if (signal) // If signal is not 0
    {
        /*1*/
        acc = -acc; // Negate acc
        signal = 0; // Reset signal to 0
        /*1*/
    }

    if (oplus) // If oplus is not 0
    {
        switch (oplus) // Start a switch statement based on the value of oplus
        {
            case PLUS: // If oplus is PLUS
                /*1*/
                stack[stack_pointer] += acc; // Add acc to stack[stack_pointer]
                /*1*/
                break;
            
            case MINUS: // If oplus is MINUS
                /*1*/
                stack[stack_pointer] -= acc; // Subtract acc from stack[stack_pointer]
                /*1*/
                break;
        }

        /*1*/
        acc = pop(); // Pop the top value from the stack and store in acc
        /*1*/
        oplus = 0; // Reset oplus to 0
    }

    if (is_oplus(look_ahead)) // If look_ahead is an addition operator
    {
        /*1*/
        oplus = look_ahead; // Set oplus to look_ahead
        push(acc); // Push acc onto the stack
        /*1*/
        match(look_ahead); // Call match with look_ahead as the argument
        goto _T; // Go to label _T
    }
}

/// @brief Matches the current token with the expected token and advances to the next token if they match.
/// @param expected The expected token to match.
int match(int expected)
{
    // If the current token matches the expected token
    if(look_ahead == expected)
    {
         // Get the next token from the source
        look_ahead = gettoken(source);
    }
    else
    {
        // Get the string representation of the expected token
        const char *expected_str = get_token_to_string(expected);
        // Get the string representation of the current token
        const char *lookahead_str = get_token_to_string(look_ahead);

        // Buffers to hold single character tokens if they are not recognized
        char expected_buf[2];
        char lookahead_buf[2];

        // If the expected token string is NULL, convert the expected token to a string
        if (expected_str == NULL)
        {
            sprintf(expected_buf, "%c", expected);
            expected_str = expected_buf;
        }

        // If the current token string is NULL, convert the current token to a string
        if (lookahead_str == NULL)
        {
            sprintf(lookahead_buf, "%c", look_ahead);
            lookahead_str = lookahead_buf;
        }

        // Print a syntax error message with the expected and received tokens and the line number
        fprintf(stderr, "\tSyntax error. expected: %s - recieved: %s\n", expected_str, lookahead_str);
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