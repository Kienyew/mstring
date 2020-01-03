#include <stdlib.h> /* malloc(), realloc() */
#include <string.h> /* strncpy() */
#include "mstring.h"

#define STRING_INITIAL_CAPACITY (32)
void string_init(string* s, const char* src) {
    char c;
    s->capacity = STRING_INITIAL_CAPACITY;
    s->size = 0;
    s->base = (char*) malloc(s->capacity + 1);
    while ((c = *src++) != '\0') {
        string_append_char(s, c);
    }
}

static void string_expand(string* s) {
    s->capacity += s->capacity >> 1; /* 1.5 times */
    s->base = (char*) realloc(s->base, s->capacity);
}

void string_free(string* s) {
    free(s->base);
}

void string_append_char(string* s, char c) {
    if (s->capacity < s->size + sizeof(char) + 1) {
        string_expand(s);
    }
    s->base[s->size] = c;
    s->size += 1;
    s->base[s->size] = '\0';
}

void string_append(string* s, const char* src, size_t len) {
    while (s->capacity < s->size + len + 1) {
        string_expand(s);
    }
    strncpy(s->base + s->size, src, len);
    s->size += len;
    s->base[s->size] = '\0';
}

const char* string_get(string* s) {
    return s->base;
}
