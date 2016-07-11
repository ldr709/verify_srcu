#ifndef BARRIERS_H
#define BARRIERS_H

#define barrier() __asm__ __volatile__("": : :"memory")
#define smp_mb() __sync_synchronize()

#define READ_ONCE(x) (*(volatile typeof(x) *) &(x))
#define WRITE_ONCE(x, val) (*(volatile typeof(x) *) &(x) = (val))

#endif
