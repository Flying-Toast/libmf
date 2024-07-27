#define OPTNAME(MAC) _OPTNAME(MAC)
#define _OPTNAME(FST, _) FST ## _opt_t
#define TYPENAME(MAC) _TYPENAME(MAC)
#define _TYPENAME(FST, SND) SND FST

#ifdef MF_OPT_IMPL_TYPE
typedef struct {
	bool has_val;
	TYPENAME(MF_OPT_IMPL_TYPE) val;
} OPTNAME(MF_OPT_IMPL_TYPE);
#endif

#undef OPTNAME
#undef _OPTNAME
#undef TYPENAME
#undef _TYPENAME

#ifndef __MF_OPT_ONETIME
#define __MF_OPT_ONETIME

#include <assert.h>

#define NONE_INIT { .has_val = false }
#define SOME_INIT(VAL) { .has_val = true, .val = (VAL) }
#define UNWRAP(OPT) ({ typeof(OPT) __opt = OPT; assert(__opt.has_val); __opt.val; })

#endif
