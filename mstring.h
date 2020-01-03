#include <stddef.h> /* size_t */

typedef struct {
    char* base;
    size_t capacity;
    size_t size;
} string;

void string_init(string* s, const char* src);
void string_free(string* s);
void string_append(string* s, const char* src, size_t len);
void string_append_char(string* s, char c);
const char* string_get(string* s);
