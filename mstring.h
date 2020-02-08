#include <stddef.h>     /* size_t */

typedef struct {
    char* base;
    size_t capacity;
    size_t size;
} mstring;

void mstring_init(mstring* s, const char* src);
void mstring_free(mstring* s);
void mstring_append(mstring* s, const char* src, size_t len);
void mstring_append_char(mstring* s, char c);
size_t mstring_get_size(const mstring* s);
char mstring_char_at(const mstring* s, size_t index);
const char* mstring_get(mstring* s);
