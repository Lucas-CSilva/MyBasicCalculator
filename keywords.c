#include <string.h>
#include <keywords.h>

char* keywords[] = {
    "quit",
    "exit",
};

int is_keyword(const char *word)
{  
    for (int i = QUIT; i <= EXIT ; i++)
    {
        if (strcmp(word, keywords[i - QUIT]) == 0)
        {
            return i;
        }
    }

    return 0;
}