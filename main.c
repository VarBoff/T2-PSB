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

#define PROGRAM_NAME "ig"
#define AUTHORS proper_name("Eduardo d'Alençon, Pedro Machado, Vinícius Boff")

/* The value to return to the calling program.  */
static int exit_status;

int main()
{

      FILE *fp = fopen("poema.txt", "r");
      if (!fp)
      {
            perror("ERROR");
            return EXIT_FAILURE;
      }

      // Read lines from file, allocate memory and build an array of lines
      // -----------------------------------------------------------------
      char *lineBuf = NULL;
      size_t n = 0;
      size_t nLines = 0;
      ssize_t lineLength = 0;
      size_t sizeIncrement = 10;
      char **lines = malloc(sizeIncrement * sizeof(char **));
      size_t i = 0;

      while ((lineLength = getline(&lineBuf, &n, fp)) != -1)
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
                        return EXIT_FAILURE;
                  }
                  lines = tmp;
            }
            // Remove \n from the line.
            lineBuf[strcspn(lineBuf, "\n")] = 0;

            // Allocate space on the heap for the line.
            *(lines + i) = malloc((lineLength + 1) * sizeof(char));

            // Copy the getline buffer into the new string.
            strcpy(*(lines + i), lineBuf);

            i++;

            // Keep track of the number of lines read for later use.
            nLines = i;
      }

      // Do something with the array of strings.
      printf("nLines: %lu\n", nLines);
      for (size_t k = 0; k < nLines; k++)
      {
            printf("%lu\t %s\n", k, *(lines + k));
      }

      // Free the buffer utilised by `getline()`.
      free(lineBuf);

      // Free the array of strings.
      for (size_t i = 0; i < nLines; i++)
            free(*(lines + i));
      free(lines);

      fclose(fp);
      return 0;
}
