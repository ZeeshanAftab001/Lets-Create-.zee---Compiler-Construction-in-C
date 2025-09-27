#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include "linkedlist.h"

#define MAX 100

const char *keyword_pattern = "^(if|else|while|for|int|float|return)$";
const char *identifier_pattern = "^[a-zA-Z_][a-zA-Z0-9_]*$";
const char *number_pattern = "^[0-9]+$";
const char *operator_pattern = "^(\\+|-|\\*|/|==|=|<|>)$";
const char *punct_pattern = "^(;|,|\\(|\\)|\\{|\\})$";

int match(const char *pattern, char *word)
{
    regex_t regex;
    int result;
    if (regcomp(&regex, pattern, REG_EXTENDED))
        return 0; // if fails
    result = (regexec(&regex, word, 0, NULL, 0) == 0);
    regfree(&regex);
    return result;
}

int main()
{

    FILE *file = fopen("file.zee", "r");

    if (!file)
    {
        printf("file not opened.");
        return 0;
    }

    char buffer[MAX];
    int ch;
    int i = 0;
    Node *head = NULL;

    while ((ch = fgetc(file)) != EOF)
    {

        if (isalnum(ch))
        {
            if (i < sizeof(buffer) - 1)
            {
                buffer[i++] = ch;
            }
        }
        else
        {
            if (i > 0)
            {
                buffer[i] = '\0';
                append(&head, buffer);
                i = 0;
            }
            if (strchr("+-*/=<>;,(){}", ch))
            {
                char operator[3] = {ch, '\0'};
                append(&head, operator);
            }
        }
    }
    if (i > 0)
    {
        buffer[i] = '\0';
        append(&head, buffer);
    }

    fclose(file);

    Node *temp = head;
    while (temp)
    {

        if (match(keyword_pattern, temp->word))
        {
            printf("KEYWORD: %s\n", temp->word);
        }
        else if (match(identifier_pattern, temp->word))
        {
            printf("IDENTIFIER: %s\n", temp->word);
        }
        else if (match(number_pattern, temp->word))
        {
            printf("NUMBER: %s\n", temp->word);
        }
        else if (match(operator_pattern, temp->word))
        {
            printf("OPERATOR: %s\n", temp->word);
        }
        else if (match(punct_pattern, temp->word))
        {
            printf("PUNCTUATION: %s\n", temp->word);
        }
        else
        {
            printf("UNKNOWN: %s\n", temp->word);
        }
        temp = temp->next;
    }
}