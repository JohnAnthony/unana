#include <stdlib.h>
#include <string.h>

#include "anagram.h"

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
