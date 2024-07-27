#define VECNAME(MAC) _VECNAME(MAC)
#define _VECNAME(FST, _) FST ## _vec_t
#define SLICENAME(MAC) _SLICENAME(MAC)
#define _SLICENAME(FST, _) FST ## _slice_t
#define TYPENAME(MAC) _TYPENAME(MAC)
#define _TYPENAME(FST, SND) SND FST

#ifdef MF_ARR_IMPL_TYPE
#include <stddef.h>

typedef struct {
	TYPENAME(MF_ARR_IMPL_TYPE) *ptr;
	size_t len;
} SLICENAME(MF_ARR_IMPL_TYPE);

typedef struct {
	TYPENAME(MF_ARR_IMPL_TYPE) *ptr;
	size_t len;
	size_t cap;
} VECNAME(MF_ARR_IMPL_TYPE);
#endif

#undef VECNAME
#undef _VECNAME
#undef SLICENAME
#undef _SLICENAME
#undef TYPENAME
#undef _TYPENAME

#ifndef __MF_ARR_ONETIME
#define __MF_ARR_ONETIME

#include <stdlib.h>

#define VEC_INIT { .ptr = NULL, .cap = 0, .len = 0 }

#define vec_reserve(VEC, NEWCAP) \
	do { \
		typeof(VEC) __reserve_vec = VEC; \
		size_t __reserve_newcap = NEWCAP; \
		/* throw away len to make sure it's really a vec and not a slice */ \
		(void)__reserve_vec->len; \
		if (__reserve_vec->cap == 0) { \
			if (__reserve_newcap > 0) { \
				__reserve_vec->ptr = malloc(__reserve_newcap * sizeof(__reserve_vec->ptr[0])); \
			} \
		} else { \
			if (__reserve_newcap > __reserve_vec->cap) { \
				__reserve_vec->ptr = realloc(__reserve_vec->ptr, __reserve_newcap * sizeof(__reserve_vec->ptr[0])); \
			} \
		} \
		__reserve_vec->cap = __reserve_newcap; \
	} while(0)

#define vec_push(VEC, ITEM) \
	do { \
		typeof(VEC) __push_vec = VEC; \
		typeof(ITEM) __push_item = ITEM; \
		/* throw away len to make sure it's really a vec and not a slice */ \
		(void)__push_vec->len; \
		vec_reserve(__push_vec, __push_vec->cap + 1); \
		__push_vec->ptr[__push_vec->len] = __push_item; \
		__push_vec->len += 1; \
	} while(0)

#endif
