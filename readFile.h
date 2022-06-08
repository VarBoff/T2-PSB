#include <stdio.h>

#ifndef READ_FILE /* Include guard */
#define READ_FILE

int my_getline(char **line, size_t *len, FILE *fp);
char **readFileToArray(FILE *fp, size_t *totalLines);

#endif // READ_FILE_