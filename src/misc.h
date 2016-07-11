#ifndef MISC_H
#define MISC_H

#include "assume.h"
#include "int_typedefs.h"
#include "locks.h"

#include <linux/types.h>

/* Probably won't need to deal with bottom halves. */
static inline void local_bh_disable() {}
static inline void local_bh_enable() {}

#define MODULE_ALIAS(X)
#define module_param(...)
#define EXPORT_SYMBOL_GPL(x)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/* Abuse udelay to make sure that busy loops terminate. */
#define udelay(x) assume(0)
#define trace_rcu_torture_read(rcutorturename, rhp, secs, c_old, c) \
	do { } while (0)

#define notrace

/* Avoid including rcupdate.h */
struct rcu_synchronize {
	struct rcu_head head;
	struct completion completion;
};

void wakeme_after_rcu(struct rcu_head *head);

#define rcu_lock_acquire(a) do { } while (0)
#define rcu_lock_release(a) do { } while (0)
#define RCU_LOCKDEP_WARN(c, s) do { } while (0)

/* Let CBMC non-deterministically choose switch between normal and expedited. */
bool rcu_gp_is_normal(void);
bool rcu_gp_is_expedited(void);

#endif
