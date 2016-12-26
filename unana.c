/*
 * NAME
 * 	   unana - Unanagram words using a dictionary, usually in O(1) time
 *
 * SYNOPSIS
 *     unana ANAGRAM DICTIONARY
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "key.h"

typedef struct Result Result;
struct Result {
	char* val;
	Result* next;
};


static int
by_alphabet(const void* a, const void* b) {
	return *(char*)b - *(char*)a;
}

bool is_anagram(char* a, char* b) {
	char* a2 = strdup(a);
	char* b2 = strdup(b);

	qsort(a2, strlen(a2), 1, &by_alphabet);
	qsort(b2, strlen(b2), 1, &by_alphabet);

	return strcmp(a2, b2) == 0;
}

int
main(int argc, char** argv) {
	if (argc != 2) {
		puts("USAGE:");
		puts("    unana DICTIONARY");
		return EXIT_FAILURE;
	}

	Result** table = calloc(KEY_SPACE, sizeof(Result*));
	if (!table) {
		puts("Failed to allocate lookup table");
		return EXIT_FAILURE;
	}

	FILE* f = fopen(argv[1], "r");
	if (!f) {
		printf("Unable to open dictionary: %s\n", argv[1]);
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

	puts("Entering shell... (Type !exit or press ^D to exit)");
	char buf[256];
	while (1) {
		printf(">> ");
		if (fgets(buf, 256, stdin) == NULL)
			break;
		size_t len = strlen(buf);

		if (len == 0)
			continue;
		buf[len-1] = '\0';

		if (strcmp(buf, "!exit") == 0)
			break;

		size_t keylen;
		char* t_key = dict_key(buf, strlen(buf), &keylen); // Owned
		size_t tt_key = table_key(t_key);

		printf("Using target '%s' with key '%s' (%u)\n", buf, t_key, tt_key);

		Result *r = table[tt_key];
		while (r) {
			if (is_anagram(buf, r->val))
				printf("Found result: %s\n", r->val);
			r = r->next;
		}
		free(t_key);
	}

CLEANUP:
	puts("Freeing memory");

	for (i = 0; i < KEY_SPACE; i++) {
		Result* r = table[i];
		while (r) {
			Result *next = r->next;
			free(r->val);
			free(r);
			r = next;
		}
	}
	return EXIT_SUCCESS;
}
