#pragma once

#include <stdio.h>

typedef enum _keyword_
{
    QUIT = 0X1000,
    EXIT,
}EKeyword;

extern char* keywords[];

extern int is_keyword(const char *word);