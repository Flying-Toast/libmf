#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mf_string.h"

static void string_reserve(string_t *s, size_t cap) {
	assert(cap > 0);

	if (s->cap >= cap)
		return;

	if (s->ptr == NULL) {
		s->ptr = malloc(cap);
	} else {
		s->ptr = realloc(s->ptr, cap);
	}
	s->cap = cap;
}

string_t string_new(void) {
	return (string_t) {
		.cap = 0,
		.ptr = NULL,
		.len = 0,
	};
}

void string_free(string_t s) {
	if (s.cap > 0)
		free(s.ptr);
}

str_t cstr_as_str(char *cstr) {
	return (str_t) { .ptr = cstr, .len = strlen(cstr) };
}

void string_append(string_t *s, str_t other) {
	string_reserve(s, s->len + other.len);
	memcpy(s->ptr + s->len, other.ptr, other.len);
	s->len += other.len;
}

void string_push(string_t *s, char ch) {
	string_reserve(s, s->len + 1);
	s->ptr[s->len++] = ch;
}

char_opt_t string_pop(string_t *s) {
	if (s->len == 0) {
		return (char_opt_t) NONE_INIT;
	} else {
		s->len -= 1;
		return (char_opt_t) SOME_INIT(s->ptr[s->len]);
	}
}

str_t string_as_str(string_t s) {
	return (str_t) {
		.len = s.len,
		.ptr = s.ptr,
	};
}

bool str_eq(str_t a, str_t b) {
	if (a.len != b.len)
		return 0;

	return memcmp(a.ptr, b.ptr, a.len) == 0;
}

string_t str_to_string(str_t s) {
	if (s.len == 0) {
		return string_new();
	} else {
		string_t ret = {
			.ptr = malloc(s.len),
			.len = s.len,
			.cap = s.len,
		};
		memcpy(ret.ptr, s.ptr, s.len);
		return ret;
	}
}

void string_insert(string_t *s, size_t idx, char ch) {
	assert(idx <= s->len);

	string_reserve(s, s->len + 1);

	if (idx == s->len) {
		s->ptr[idx] = ch;
		s->len += 1;
		return;
	}

	memmove(s->ptr + idx + 1, s->ptr + idx, s->len - idx);
	s->len += 1;
	s->ptr[idx] = ch;
}

void string_remove(string_t *s, size_t idx) {
	assert(idx < s->len);

	if (idx == s->len - 1) {
		s->len -= 1;
		return;
	}

	memmove(s->ptr + idx, s->ptr + idx + 1, s->len - idx);
	s->len -= 1;
}
