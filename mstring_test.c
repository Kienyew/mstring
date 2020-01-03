#include <stdio.h> /* printf() */
#include <string.h> /* memcmp */
#include "mstring.h"
unsigned test_total = 0;
unsigned test_success = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                                                            \
do {                                                                                                                \
    test_total++;                                                                                                   \
    if (equality) {                                                                                                 \
        test_success++;                                                                                             \
    } else {                                                                                                        \
        printf("%s:%d: EXPECT: " format ", ACTUAL: " format "\n", __FILE__, __LINE__, (expect), (actual));          \
    }                                                                                                               \
} while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), (expect), (actual), "%d")
#define EXPECT_EQ_SIZE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), (expect), (actual), "%ld")
#define EXPECT_EQ_CHAR(expect, actual) EXPECT_EQ_BASE((expect) == (actual), (expect), (actual), "%c")
#define EXPECT_EQ_STRING(expect, actual, actual_length) EXPECT_EQ_BASE((memcmp((expect), (actual), ((size_t)actual_length)) == 0), (expect), (actual), "%s")
void test_string_init() {
    string s;
    string_init(&s, "test");
    EXPECT_EQ_SIZE(4ul, s.size);
    EXPECT_EQ_STRING("test", s.base, 4);
    string_free(&s);
}

void test_string_get() {
    string s;
    string_init(&s, "test");
    EXPECT_EQ_STRING("test", string_get(&s), 4);
    string_free(&s);
}

void test_string_append() {
    string s;
    string_init(&s, "");
    string_append(&s, "append", 6);
    EXPECT_EQ_STRING("append", string_get(&s), 6);
    string_free(&s);
}

void test_string_append_char() {
    string s;
    string_init(&s, "");
    string_append_char(&s, 'a');
    string_append_char(&s, 'o');
    string_append_char(&s, 'b');
    string_append_char(&s, 'i');
    EXPECT_EQ_SIZE(4ul, s.size);
    EXPECT_EQ_STRING("aobi", string_get(&s), 4);
    string_free(&s);
}

void test_all() {
    test_string_init();
    test_string_get();
    test_string_append();
    test_string_append_char();
}

int main() {
    test_all();
    printf("Test (%d/%d), success rate: %.2f%%\n", test_success, test_total, (float)test_success/test_total);
    return (test_total == test_success) ? 0 : 1;
}
