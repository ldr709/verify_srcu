#ifndef PERCPU_H
#define PERCPU_H

#define __percpu

/* Ignore alignment, as CBMC doesn't care about false sharing. */
#define alloc_percpu(type) __alloc_percpu(sizeof(type), 1);

static inline void *__alloc_percpu(size_t size, size_t align)
{
	BUG();
	return NULL;
}

static inline void free_percpu(void *ptr)
{
	BUG();
}

#define per_cpu_ptr(ptr, cpu) (&(ptr)[cpu])

#define __this_cpu_inc(pcp) __this_cpu_add(pcp, 1)
#define __this_cpu_dec(pcp) __this_cpu_dec(pcp, 1)
#define __this_cpu_sub(pcp, n) __this_cpu_add(pcp, -(typeof(pcp)) (n))

#define this_cpu_inc(pcp) this_cpu_add(pcp, 1)
#define this_cpu_dec(pcp) this_cpu_sub(pcp, 1)
#define this_cpu_sub(pcp, n) this_cpu_add(pcp, -(typeof(pcp)) (n))

#define __this_cpu_add(pcp, n) \
	do { \
		BUG_ON(preemptible()); \
		*per_cpu_ptr(&(pcp), thread_cpu_id) += (n); \
	} while (0)

#define this_cpu_add(pcp, n) \
	do { \
		int this_cpu_add_impl_cpu = get_cpu(); \
		*per_cpu_ptr(&(pcp), this_cpu_add_impl_cpu) += (n); \
		put_cpu(); \
	} while (0)

#define DEFINE_PER_CPU(type, name) typeof(type) name[NR_CPUS]

#define for_each_possible_cpu(cpu) \
	for ((cpu) = 0; (cpu) < NR_CPUS; ++(cpu))

#endif
