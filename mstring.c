#include <stddef.h>     /* size_t */
#include <stdlib.h>     /* malloc(), realloc() */
#include <string.h>     /* strncpy() */
#include "mstring.h"

#define STRING_INITIAL_CAPACITY (32)
void mstring_init(mstring* s, const char* src) {
    char c;
    s->capacity = STRING_INITIAL_CAPACITY;
    s->size = 0;
    s->base = (char*) malloc(s->capacity + 1);
    while ((c = *src++) != '\0') {
        mstring_append_char(s, c);
    }
}

static void mstring_expand(mstring* s) {
    s->capacity += s->capacity >> 1; /* 1.5 times */
    s->base = (char*) realloc(s->base, s->capacity);
}

void mstring_free(mstring* s) {
    free(s->base);
}

void mstring_append_char(mstring* s, char c) {
    if (s->capacity < s->size + sizeof(char) + 1) {
        mstring_expand(s);
    }
    s->base[s->size] = c;
    s->size += 1;
    s->base[s->size] = '\0';
}

void mstring_append(mstring* s, const char* src, size_t len) {
    while (s->capacity < s->size + len + 1) {
        mstring_expand(s);
    }
    strncpy(s->base + s->size, src, len);
    s->size += len;
    s->base[s->size] = '\0';
}

const char* mstring_get(mstring* s) {
    return s->base;
}

size_t mstring_get_size(const mstring* s) {
    return s->size;
}

char mstring_char_at(const mstring* s, size_t index) {
    return s->base[index];
}
