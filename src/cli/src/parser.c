#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

/* See parser.h */
char **parse(char *input)
{
    if(strcmp(input, "") == 0)
    {
        return NULL;
    }

    char **words;
    words = (char**)malloc(sizeof(char*)*TOKEN_LIST_SIZE);

    //Initializes all words to NULL
    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = NULL;
    }

    char *token = strtok(input, " ");

    for(int i = 0; i < TOKEN_LIST_SIZE; i++)
    {
        words[i] = token;
        token = strtok(NULL, " ");
    }

    if(token != NULL)
    {
        return NULL;
    }

    char *command = words[0];
    int i = 0;
    char ch;

    while(command[i])
    {
        ch = toupper(command[i]);
        command[i] = ch;
        i++;
    }

    return words;
}
