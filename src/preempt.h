#ifndef PREEMPT_H
#define PREEMPT_H

#include <stdbool.h>

#include "bug_on.h"

/* This flag contains garbage if preempt_disable_count is 0. */
extern __thread int thread_cpu_id;

/* Support recursive preemption disabling. */
extern __thread int preempt_disable_count;

void preempt_disable();
void preempt_enable();

static inline void preempt_disable_notrace()
{
	preempt_disable();
}

static inline void preempt_enable_no_resched()
{
	preempt_enable();
}

static inline void preempt_enable_notrace()
{
	preempt_enable();
}

static inline int preempt_count()
{
	return preempt_disable_count;
}

static inline bool preemptible()
{
	return !preempt_count();
}

static inline int get_cpu()
{
	preempt_disable();
	return thread_cpu_id;
}

static inline void put_cpu()
{
	preempt_enable();
}

static void might_sleep()
{
	BUG_ON(preempt_disable_count);
}

#endif
