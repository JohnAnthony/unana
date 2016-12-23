/*
 * NAME
 * 	   mkdict - Take a word-per-line list of words and pack it in a dictionary
 * 	   to be efficiently read by unana
 *
 * SYNOPSIS
 *     mkdict INPUT OUTPUT
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "key.h"

int
main(int argc, char** argv) {
	if (argc != 3) {
		puts("USAGE:");
		puts("    mkdict INPUT OUTPUT");
		return EXIT_FAILURE;
	}
		
	FILE* fin;
	FILE* fout;
	char* line;
	size_t len = 0;
	ssize_t read;
	unsigned int count = 0;

	fin = fopen(argv[1], "r");
	if (!fin) {
		printf("Unable to open worlist: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fout = fopen(argv[2], "w");
	if (!fin) {
		printf("Unable to open dictionary file for output: %s\n", argv[2]);
		fclose(fin);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fin)) != -1) {
		char* s;
		bool good = true;
		size_t written;
		size_t keylen;
		char* key;

		line[read-1] = '\0';
		s = line;
		while (*s) {
			*s = tolower(*s);

			if (*s < 'a' || *s > 'z') {
				printf("Rejecting word '%s' for special characters\n", line);
				good = false;
				break;
			}

			s++;
		}
		if (!good)
			continue;

		key = dict_key(line, read-1, &keylen);
		written = fwrite(key, 1, keylen, fout);
		free(key);

		written = fwrite(line, 1, read, fout);
		if (written != read) {
			printf("Error writing to dictionary at word: '%s'\n", line);
			goto CLEANUP;
		}

		count++;
	}

	printf("Wrote %u words to dictionary\n", count);

CLEANUP:

	fclose(fin);
	if (line)
		free(line);
	return EXIT_SUCCESS;
}
