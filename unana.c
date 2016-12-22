/*
 * NAME
 * 	   unana - Unanagram words using a dictionary, usually in O(1) time
 *
 * SYNOPSIS
 *     unana ANAGRAM DICTIONARY
 */

#include <stdlib.h>
#include <stdio.h>

// 26^6
#define T_SZ 30891577

typedef struct Result Result;
struct Result {
	char* val;
	Result* next;
};

int
main(void) {
	Result** table = calloc(T_SZ, sizeof(Result*));
	if (!table) {
		puts("Failed to allocate lookup table");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
