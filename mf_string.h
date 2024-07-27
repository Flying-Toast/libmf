#ifndef __HAVE_MF_STRING_H
#define __HAVE_MF_STRING_H

#include <stddef.h>
#include <stdbool.h>

#define STR(LIT) (str_t) { .ptr = "" LIT "", .len = sizeof("" LIT "") - 1 }
#define STRING(LIT) str_to_string(STR(LIT))

typedef struct {
	const char *ptr;
	size_t len;
} str_t;

typedef struct {
	char *ptr;
	size_t len;
	size_t cap;
} string_t;

#ifndef __HAVE_MF_OPT_CHAR
	#define __HAVE_MF_OPT_CHAR
	#define MF_OPT_IMPL_TYPE char,
	#include "mf_opt.h"
	#undef MF_OPT_IMPL_TYPE
#endif

string_t string_new(void);
void string_free(string_t s);
void string_push(string_t *s, char ch);
char_opt_t string_pop(string_t *s);
str_t string_as_str(string_t s);
void string_insert(string_t *s, size_t idx, char ch);
void string_remove(string_t *s, size_t idx);
void string_append(string_t *s, str_t other);

bool str_eq(str_t a, str_t b);
string_t str_to_string(str_t s);
str_t cstr_as_str(char *cstr);

#endif
