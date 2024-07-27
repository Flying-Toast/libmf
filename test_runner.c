#include <assert.h>
#include <stdio.h>
#include "mf_string.h"

#ifndef __HAVE_MF_OPT_INT
	#define __HAVE_MF_OPT_INT
	#define MF_OPT_IMPL_TYPE int,
	#include "mf_opt.h"
	#undef MF_OPT_IMPL_TYPE
#endif

struct foo { int hello; };

#ifndef __HAVE_MF_OPT_FOO
	#define __HAVE_MF_OPT_FOO
	#define MF_OPT_IMPL_TYPE foo,struct
	#include "mf_opt.h"
	#undef MF_OPT_IMPL_TYPE
#endif

void test_opt(void) {
	int_opt_t noint = NONE_INIT;
	foo_opt_t somefoo = SOME_INIT((struct foo) { .hello = 123 });
	assert(!noint.has_val);
	assert(somefoo.has_val);
	assert(UNWRAP(somefoo).hello == 123);
}

#ifndef __HAVE_MF_ARR_INT
	#define __HAVE_MF_ARR_INT
	#define MF_ARR_IMPL_TYPE int,
	#include "mf_arr.h"
	#undef MF_ARR_IMPL_TYPE
#endif

void test_arr(void) {
	int_vec_t ints = VEC_INIT;
	assert(ints.len == 0);
	vec_push(&ints, 123);
	assert(ints.len == 1);
	vec_push(&ints, 456);
	assert(ints.len == 2);
	assert(ints.ptr[0] == 123);
	assert(ints.ptr[1] == 456);
}

void test_string(void) {
	string_t foo = STRING("foo");
	assert(str_eq(string_as_str(foo), STR("foo")));
	string_push(&foo, ',');
	string_append(&foo, cstr_as_str("bar"));
	assert(str_eq(string_as_str(foo), STR("foo,bar")));
}

int main(void) {
	test_string();
	test_opt();
	test_arr();

	puts("All tests passed.");
}
