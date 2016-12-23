/*
 * NAME
 * 	   unana - Unanagram words using a dictionary, usually in O(1) time
 *
 * SYNOPSIS
 *     unana ANAGRAM DICTIONARY
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "key.h"
#include "anagram.h"

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

	puts("Loading dictionary...");
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

		Result *r = malloc(sizeof(Result)); // Owned
		if (!r) {
			puts("Error allocating space");
			goto CLEANUP;
		}
	   
		r->val = strdup(val); // Owned
		r->next = table[tkey];
		table[tkey] = r;

		c = fgetc(f);
		if (c == EOF)
			break;
		ungetc(c, f);
	}

	// TODO: Make interactive, dictionary only loads once

	char* target = strdup(argv[1]);
	size_t keylen;
	char* t_key = dict_key(target, strlen(target), &keylen); // Owned
	size_t tt_key = table_key(t_key);

	printf("Using target '%s' with key '%s' (%u)\n", target, t_key, tt_key);

	Result *r = table[tt_key];
	while (r) {
		if (is_anagram(target, r->val))
			printf("Found result: %s\n", r->val);
		r = r->next;
	}

CLEANUP:
	// TODO: Free all Results and Result.vals
	return EXIT_SUCCESS;
}
