/* gerarIndicesRemissivos

This program was developed for the Basic 
Software course, taught by Professor 
Marco Aurélio Mangan.

It serves as an academic piece 
for evaluation and therefore 
has no warranty. 

Authors: Eduardo D'alençon, Pedro Semensato, Vinicius Boff
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFile.h"

#define PROGRAM_NAME "ig"
#define AUTHORS "Eduardo dAlencon, Pedro Machado, Vinicius Boff"

#define USAGE_FMT "%s inputFile [--csv] [--html] [--dark] [--help] [--version]\n"
#define VERSION "Program Name: %s\nAuthors: %s \nVersion: 1.0"

#define LINES_IN_A_PAGE 30

void usage()
{
	printf(USAGE_FMT, PROGRAM_NAME);
	fputs("inputfile    file from which the index is generated\n"
		  "[--csv]        generates output in csv format\n"
		  "[--html]       generates output in html format\n"
		  "[--dark]       enables darkmode for html output\n"
		  "[--help]       displays this message\n"
		  "[--version]  displays the program's version",
		  stdout);
}

int main(int argc, char **argv)
{
	size_t totalLines = 0;
	size_t totalWords = 0;
	size_t actualLine;

	int csv = 0;
	int html = 0;
	int dark = 0;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--csv"))
		{
			csv = 1;
		}
		else if (!strcmp(argv[i], "--html"))
		{
			html = 1;
		}
		else if (!strcmp(argv[i], "--dark"))
		{
			dark = 1;
		}
		else if (!strcmp(argv[i], "--help"))
		{
			printf(USAGE_FMT, PROGRAM_NAME);
			fputs("inputfile    file from which the index is generated\n"
				  "--csv        generates output in csv format\n"
				  "--html       generates output in html format\n"
				  "--dark       enables darkmode for html output\n"
				  "--help       displays this message\n"
				  "[--version]  displays the program's version",
				  stdout);
			exit(EXIT_SUCCESS);
		}
		else if (!strcmp(argv[i], "--version"))
		{
			printf(VERSION, PROGRAM_NAME, AUTHORS);
			exit(EXIT_SUCCESS);
		}
	}

	if (argc < 2)
	{
		fprintf(stderr, "Please supply a file path:\n%s <file path>\n", argv[0]);
		return EXIT_FAILURE;
	}
	FILE *fp = fopen(argv[1], "r");

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
		size_t pagina[50];
		int contagem;
	};

	struct word *words = malloc(10000 * sizeof(struct word));

	puts("Vetor de struct words criado");

	// Do something with the array of strings.
	printf("totallines=%lu\n", (unsigned long)totalLines);

	for (actualLine = 1; actualLine < totalLines + 1; actualLine++)
	{
		printf("Actual line=%lu\n", (unsigned long)actualLine);
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
				if (strcmp(wordsPtr->palavra, ptr) == 0)
				{
					printf("Found duplicate in index=%lu\n", (unsigned long)i);

					if (wordsPtr->pagina[wordsPtr->contagem - 1] != (actualLine / LINES_IN_A_PAGE) + 1)
					{
						wordsPtr->pagina[wordsPtr->contagem] = (actualLine / LINES_IN_A_PAGE) + 1;
						wordsPtr->contagem++;
					}
					found = 1;
				}
			}

			if (!found)
			{
				printf("New word! Adding in=%lu\n", (unsigned long)totalWords);
				strcpy(&*(words + totalWords)->palavra, ptr);
				(words + totalWords)->pagina[(words + totalWords)->contagem] = (actualLine / LINES_IN_A_PAGE) + 1;
				(words + totalWords)->contagem++;
				totalWords++;
			}

			ptr = strtok(NULL, delim);
		}
		printf("\n");
	}

	printf("\nnLines: %lu", (unsigned long)totalLines);
	printf("\nnWords: %lu", (unsigned long)totalWords);

	struct word *wordsPtr = words;
	for (int i = 0; i < totalWords; i++, wordsPtr++)
	{
		printf("\nPalavra: %s", wordsPtr->palavra);

		for (int j = 0; j < wordsPtr->contagem; j++)
		{
			printf("\n\tPagina %lu", (unsigned long)wordsPtr->pagina[j]);
		}
	}

	// Free the array of strings.
	for (size_t i = 0; i < totalLines; i++)
		free(*(lines + i));

	if (html)
	{
		FILE *file = NULL;

		file = fopen("textFile.html", "a");

		if (file != NULL)
		{
			if (dark)
			{
				fprintf(file, "<style>h1{color:blue} body{background-color:gray} p{display:inline}</style>");
			}
			else
			{
				fprintf(file, "<style>h1{color:blue} body{background-color:white} p{display:inline}</style>");
			}

			fprintf(file, "<h1>Índice Remissivo</h1>");
			wordsPtr = words;
			for (int i = 0; i < totalWords; i++, wordsPtr++)
			{
				fprintf(file, "\n<h4>Palavra: %s</h4>", wordsPtr->palavra);
				fprintf(file, "<p>   Paginas: </p>");
				for (int j = 0; j < wordsPtr->contagem; j++)
				{
					fprintf(file, "<p> %u</p>", (unsigned int)wordsPtr->pagina[j]);
				}
			}
		}
		fclose(file);
	}

	if (csv)
	{
		FILE *file = NULL;
		file = fopen("arquivoCSV.csv", "a");

		if (file != NULL)
		{
			wordsPtr = words;
			for (int i = 0; i < totalWords; i++, wordsPtr++)
			{
				char resultados[2000] = "";
				for (int j = 0; j < wordsPtr->contagem; j++)
				{
					char palavra[500];
					sprintf(palavra, "%d",(unsigned int) wordsPtr->pagina[j]);
					strcat(resultados, palavra);
					strcat(resultados, ",");
				}
				fprintf(file, "\n%s,%s", wordsPtr->palavra, resultados);
			}
			fclose(file);
		}
	}

	free(lines);
	free(words);

	return 0;
}
