#ifndef BARRIERS_H
#define BARRIERS_H

#define barrier() __asm__ __volatile__("": : :"memory")

#ifndef NO_SMP_MB

#ifdef RUN
#define smp_mb() __sync_synchronize()
#else
/* Copied from CBMC's implementation of __sync_synchronize(), which seems to be
   disabled by default. */
#define smp_mb() __CPROVER_fence("WWfence", "RRfence", "RWfence", "WRfence", \
				 "WWcumul", "RRcumul", "RWcumul", "WRcumul")
#endif

#else
#define smp_mb() do {} while (0)

#endif

#define READ_ONCE(x) (*(volatile typeof(x) *) &(x))
#define WRITE_ONCE(x, val) (*(volatile typeof(x) *) &(x) = (val))

#endif
