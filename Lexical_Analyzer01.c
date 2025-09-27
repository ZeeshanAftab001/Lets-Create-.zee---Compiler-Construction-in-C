#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <regex.h>
#include "linkedlist.h"

int main()
{

    FILE *file = fopen("file.zee", "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    char buffer[100];
    int ch;
    Node *head = NULL;
    int i = 0;
    regex_t regex;
    char *pattern = "^[a-zA-Z_][a-zA-Z0-9_]*$";

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
        }
    }
    if (i > 0)
    {
        buffer[i] = '\0';
        append(&head, buffer);
    }

    fclose(file);

    Node *temp = head;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        printf("Could not compile regex\n");
        free_list(head);
        return 1;
    }

    while (temp)
    {
        if (regexec(&regex, temp->word, 0, NULL, 0) == 0)
        {
            printf("MATCH: %s\n", temp->word);
        }
        else
        {
            printf("NO MATCH: %s\n", temp->word);
        }
        temp = temp->next;
    }
    regfree(&regex);
    free_list(head);

    return 0;
}
