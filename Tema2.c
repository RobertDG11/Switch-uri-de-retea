/* DELIU Robert-Gabriel - 312CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tema2.h"


int main(int argc, char *argv[])
{
	AQ coada = InitQ();

	FILE *in, *out;
	char *string = malloc(256 * sizeof(char)); /*aloca un pointer pentru 
												citirea din fisier*/
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	fgets(string, 256, in); /*Citeste numarul de stive si il 
							tranforma in integer*/
	int M = atoi(string);
	TVS vector_stive = AlocaVectorStive(M);

	char **line = malloc(8 * sizeof(char*)); /*Aloca memorie pentru o linie
												care contine cel mult 8 cuvinte*/
	int i;
	for(i = 0; i < 8; i++) {
		line[i] = malloc(256 * sizeof(char)); /*Aloca memorie pentru 
												fiecare cuvant*/
	}
	while(fgets(string, 256, in)) {
		int count = 0;
		char *tok, *dup;
		dup = strdup(string);
		tok = strtok(dup, " \n");
		while(tok != NULL) {
			strcpy(line[count], tok);
			count++;
			tok = strtok(NULL, " \n");
		}

		free(dup);
		free(tok);

		if(strcmp(line[0], "add") == 0) {
				if(strcmp(line[4], "STACK") == 0) {
					add_stiva(atoi(line[1]), line[2], line[3], line[4], atoi(line[5]), line[6], vector_stive);
				}
				else {
					add_coada(atoi(line[1]), line[2], line[3], line[4], coada);
				}
		}

		else if(strcmp(line[0], "del") == 0) {
				del_stiva(atoi(line[1]), vector_stive, coada);
		
				del_coada(atoi(line[1]), coada);
			
		}

		else if(strcmp(line[0], "set") == 0) {
			if(strcmp(line[2], "STACK") == 0) {
				set_stiva(atoi(line[1]), "STACK", atoi(line[3]), line[4], vector_stive, coada);
			}
			else {
				set_coada(atoi(line[1]), "SINGLE", vector_stive, coada);
			}
		}

		else if(strcmp(line[0], "ipmin") == 0) {
			ipmin(coada, out);
		}

		else if(strcmp(line[0], "show") == 0) {
			show(vector_stive, coada, out);
		}
		
	}
	for(i = 0; i < 8; i++) {
		free(line[i]);
	}

	free(line);
	free(string);
	fclose(in);
	fclose(out);
	FreeVectorStive(vector_stive);
	FreeCoada(coada);

	return 0;
}