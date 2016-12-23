#define KEY_SIZE 6
#define KEY_SPACE 30891577 // 26^6

char* dict_key(char* line, size_t len, size_t* keylen);
size_t table_key(char* dict_key);
