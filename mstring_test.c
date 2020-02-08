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
#define EXPECT_EQ_SIZE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), ((size_t)expect), (actual), "%ld")
#define EXPECT_EQ_CHAR(expect, actual) EXPECT_EQ_BASE((expect) == (actual), (expect), (actual), "%c")
#define EXPECT_EQ_STRING(expect, actual, actual_length) EXPECT_EQ_BASE((memcmp((expect), (actual), ((size_t)actual_length)) == 0), (expect), (actual), "%s")
void test_mstring_init() {
    mstring s;
    mstring_init(&s, "test");
    EXPECT_EQ_SIZE(4ul, s.size);
    EXPECT_EQ_STRING("test", s.base, 4);
    mstring_free(&s);
}

void test_mstring_get() {
    mstring s;
    mstring_init(&s, "test");
    EXPECT_EQ_STRING("test", mstring_get(&s), 4);
    mstring_free(&s);
}

void test_mstring_append() {
    mstring s;
    mstring_init(&s, "");
    mstring_append(&s, "append", 6);
    EXPECT_EQ_STRING("append", mstring_get(&s), 6);
    mstring_free(&s);
}

void test_mstring_append_char() {
    mstring s;
    mstring_init(&s, "");
    mstring_append_char(&s, 'a');
    mstring_append_char(&s, 'o');
    mstring_append_char(&s, 'b');
    mstring_append_char(&s, 'i');
    EXPECT_EQ_SIZE(4, s.size);
    EXPECT_EQ_STRING("aobi", mstring_get(&s), 4);
    mstring_free(&s);
}

void test_mstring_get_size() {
    mstring s;
    mstring_init(&s, "");
    EXPECT_EQ_SIZE(0, mstring_get_size(&s));
    mstring_free(&s);

    mstring_init(&s, "H");
    EXPECT_EQ_SIZE(1, mstring_get_size(&s));
    mstring_free(&s);

    mstring_init(&s, "HELLO");
    EXPECT_EQ_SIZE(5, mstring_get_size(&s));
    mstring_free(&s);
}

void test_mstring_char_at() {
    mstring s;
    mstring_init(&s, "get_char");
    EXPECT_EQ_CHAR('_', mstring_char_at(&s, 3));
    mstring_free(&s);

    mstring_init(&s, "c");
    EXPECT_EQ_CHAR('c', mstring_char_at(&s, 0));
    mstring_free(&s);
}

void test_all() {
    test_mstring_init();
    test_mstring_get();
    test_mstring_append();
    test_mstring_append_char();
    test_mstring_get_size();
    test_mstring_char_at();
}

int main() {
    test_all();
    printf("Test (%d/%d), success rate: %.2f%%\n", test_success, test_total, (float)test_success/test_total * 100.0f);
    return (test_total == test_success) ? 0 : 1;
}
