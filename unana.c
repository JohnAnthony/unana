/*
 * NAME
 * 	   unana - Unanagram words using a dictionary, usually in O(1) time
 *
 * SYNOPSIS
 *     unana ANAGRAM DICTIONARY
 */

#include <stdlib.h>
#include <stdio.h>

#include "key.h"

typedef struct Result Result;
struct Result {
	char* val;
	Result* next;
};

int
main(int argc, char** argv) {
	if (argc != 3) {
		puts("USAGE:");
		puts("    unana ANAGRAM DICTIONARY");
		return EXIT_FAILURE;
	}

	Result** table = calloc(KEY_SPACE, sizeof(Result*));
	if (!table) {
		puts("Failed to allocate lookup table");
		return EXIT_FAILURE;
	}

	FILE* f = fopen(argv[2], "r");
	if (!f) {
		printf("Unable to open dictionary: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	char key[KEY_SIZE + 1];
	char val[256];
	size_t tkey;
	size_t i;
	char c;

	while (1) {
		i = 0;
		while ((c = fgetc(f)) != '$') {
			key[i++] = c;
		}
		key[i] = '\0';

		i = 0;
		for(c = fgetc(f); c != '\n' && c != EOF; c = fgetc(f)) {
			val[i++] = c;
		}
		val[i] = '\0';

		tkey = table_key(key);

		printf("%s __ %s (%u)\n", key, val, tkey);

		c = fgetc(f);
		if (c == EOF)
			break;
		ungetc(c, f);
	}

	// TODO: Free all this memory!
	return EXIT_SUCCESS;
}
