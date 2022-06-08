#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFile.h"

#define _GNU_SOURCE

#define AUTHORS proper_name("Eduardo d'Alençon, Pedro Machado, Vinícius Boff")

int my_getline(char **restrict line, size_t *restrict len, FILE *restrict fp)
{
    if (line == NULL || len == NULL)
    {
        fputs("Erro", stderr);
        return -1;
    }
    if (fp == NULL)
    {
        fputs("Erro", stderr);
        return -1;
    }

    char chunk[128];

    if (*line == NULL)
    {
        *len = sizeof(chunk);
        if ((*line = malloc(*len)) == NULL)
        {
            perror("Erro de memória");
            return -1;
        }
    }
    (*line)[0] = '\0';

    while (fgets(chunk, sizeof(chunk), fp) != NULL)
    {
        if (*len - strlen(*line) < sizeof(chunk))
        {
            *len *= 2;
            if ((*line = realloc(*line, *len)) == NULL)
            {
                perror("Erro de realocação");
                free(line);
                return -1;
            }
        }

        strcat(*line, chunk);

        if ((*line)[strlen(*line) - 1] == '\n')
        {
            return strlen(*line);
        }
    }
    return -1;
}

char **readFileToArray(FILE *fp, size_t *totalLines)
{
    size_t n = 0;
    ssize_t lineLength = 0;
    size_t i = 0;

    char *lineBuf = NULL;
    size_t sizeIncrement = 10;
    char **lines = malloc(sizeIncrement * sizeof(char **));

    while ((lineLength = my_getline(&lineBuf, &n, fp)) != -1)
    {
        // Memory reallocation is expensive - don't reallocate on every iteration.
        if (i >= sizeIncrement)
        {
            sizeIncrement += sizeIncrement;

            // Don't just overwrite with realloc - the original
            // pointer may be lost if realloc fails.
            char **tmp = realloc(lines, sizeIncrement * sizeof(char **));
            if (!tmp)
            {
                perror("realloc");
                return lines;
            }
            lines = tmp;
        }
        // Remove \n from the line.
        lineBuf[strcspn(lineBuf, "\n")] = 0;

        // Allocate space on the heap for the line.
        *(lines + i) = malloc((lineLength + 1) * sizeof(char));

        // Copy the getline buffer into the new string.
        strcpy(*(lines + i), lineBuf);

        // Keep track of the number of lines read for later use.
        i++;
    }

    // Free the buffer utilised by `getline()`.
    free(lineBuf);

    *totalLines = i;

    return lines;
}
