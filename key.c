#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"

const char* freq = "etaoinshrdlcumwfgypbvkjxqz";

static int
by_rev_freq(const void* a, const void* b) {
	return strchr(freq, *(char*)b) - strchr(freq, *(char*)a);
}

char* // Ownership passes out
dict_key(char* line, size_t len, size_t* keylen) {
	size_t i;
	char* s;
	char* ret = malloc(KEY_SIZE + 1);
	assert(ret);
	char* sorted = malloc(len);
	assert(ret);

	memcpy(sorted, line, len);
	qsort(sorted, len, 1, &by_rev_freq);

	for (i = 0; i < KEY_SIZE && sorted[i]; i++)
		ret[i] = sorted[i];

	*keylen = i;
	return ret;
}

size_t
table_key(char* dict_key) {
	size_t ret = 0;
	char* s = dict_key;

	while (*s != '\0') {
		ret *= 26;
		ret += (strchr(freq, *s) - freq) + 1;
		s++;
	}

	return ret;
}
