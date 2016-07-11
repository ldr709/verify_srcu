#ifndef ATOMIC_H
#define ATOMIC_H

#include "barriers.h"
#include <linux/types.h>

#define ATOMIC_INIT(x) { .counter = (x) }

static inline int atomic_read(atomic_t *x)
{
	return READ_ONCE(x->counter);
}

static inline void atomic_inc(atomic_t *x)
{
	(void) __sync_add_and_fetch(&x->counter, 1);
}

static inline void atomic_dec(atomic_t *x)
{
	(void) __sync_sub_and_fetch(&x->counter, 1);
}

#endif
