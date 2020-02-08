#include <stdio.h>              /* fgetc(), fopen() */
#include <stdlib.h>             /* exit() */
#include "mstring.h"

#define ASSERT_EXIT(assertion, message)                                                                                 \
    do {                                                                                                                \
        if (!(assertion)) {                                                                                               \
            fprintf(stderr, "%s:%d ASSERTION_FAILED: %s\n", __FILE__, __LINE__, (message) == NULL ? "" : (message));    \
            exit(1);                                                                                                    \
        }                                                                                                               \
    } while (0) 

mstring read_text(const char* file_path) {
    mstring s;
    char c;
    FILE* file;
    
    mstring_init(&s, "");
    file = fopen(file_path, "r");
    while ((c = fgetc(file)) != EOF) {
        mstring_append_char(&s, c);
    }

    return s;
}

int main(int argc, char* argv[]) {
    ASSERT_EXIT(argc == 2, "argc != 2");
    const char* file_path = argv[1];
    mstring s = read_text(file_path);
    for (size_t i = 0, len = mstring_get_size(&s); i < len; ++i) {
        putchar(mstring_char_at(&s, i));
    }
    mstring_free(&s);
    return 0;      
}
