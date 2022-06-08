/* gerarIndicesRemissivos

Copyright (C) 1990-2022 Free Software Foundation, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFile.h"

#define PROGRAM_NAME "ig"
#define AUTHORS proper_name("Eduardo d'Alençon, Pedro Machado, Vinícius Boff")

int main()
{
      size_t totalLines = 0;
      size_t totalWords = 0;
      size_t actualLine;

      FILE *fp = fopen("poema.txt", "r");
      if (fp == NULL)
      {
            perror("ERROR");
            return EXIT_FAILURE;
      }

      puts("Arquivo aberto!");

      // chama função de leitura

      char **lines = readFileToArray(fp, &totalLines);

      puts("Arquivo lido e alocado em heap");
      // continua

      struct word
      {
            char palavra[50];
            size_t linha[50];
            int contagem;
      };

      struct word *words = malloc(200 * sizeof(struct word));

      puts("Vetor de struct words criado");

      // Do something with the array of strings.
      printf("totallines=%llu\n", totalLines);

      for (actualLine = 1; actualLine < totalLines + 1; actualLine++)
      {
            printf("Actual line=%llu\n", actualLine);
            char delim[] = " ,:;.\"";
            char *ptr = strtok(*(lines + actualLine - 1), delim);

            while (ptr != NULL)
            {
                  // Aqui dentro, ptr é cada palavra lida
                  printf("Found=%s\n", ptr);

                  int found = 0;
                  struct word *wordsPtr = words;

                  for (size_t i = 0; i < totalWords; i++, wordsPtr++)
                  {
                        if (!strcmp(wordsPtr->palavra, ptr) &&
                            wordsPtr->linha[wordsPtr->contagem - 1] != actualLine)
                        {
                              printf("Found duplicate in index=%llu\n", i);
                              wordsPtr->linha[wordsPtr->contagem] = actualLine;
                              wordsPtr->contagem++;
                              found = 1;
                        }
                  }

                  if (!found)
                  {
                        printf("New word! Adding in=%llu\n", totalWords);
                        strcpy(&*(words + totalWords)->palavra, ptr);
                        (words + totalWords)->linha[(words + totalWords)->contagem] = actualLine;
                        (words + totalWords)->contagem++;
                        totalWords++;
                  }

                  ptr = strtok(NULL, delim);
            }
            printf("\n");
      }

      printf("\nnLines: %llu", totalLines);
      printf("\nnWords: %llu", totalWords);

      struct word *wordsPtr = words;
      for (int i = 0; i < totalWords; i++, wordsPtr++)
      {
            printf("\nPalavra: %s", wordsPtr->palavra);

            for (int j = 0; j < wordsPtr->contagem; j++)
            {
                  printf("\n\tLinha %llu", wordsPtr->linha[j]);
            }
      }

      // Free the array of strings.
      for (size_t i = 0; i < totalLines; i++)
            free(*(lines + i));
      free(lines);

      free(words);
      return 0;
}
