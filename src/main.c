#include <pthread.h>
#include <stdlib.h>
#include <linux/srcu.h>

#include "bug_on.h"

int x;
int y;

int __unbuffered_tpr_x;
int __unbuffered_tpr_y;

DEFINE_SRCU(ss);

void rcu_reader(void)
{
	int idx;

	idx = srcu_read_lock(&ss);
	__unbuffered_tpr_x = x;
#ifdef FORCE_FAILURE
	srcu_read_unlock(&ss, idx);
	idx = srcu_read_lock(&ss);
#endif
	__unbuffered_tpr_y = y;
	srcu_read_unlock(&ss, idx);
}

void *thread_update(void *arg)
{
	x = 1;
#ifndef FORCE_FAILURE_2
	synchronize_srcu(&ss);
#endif
	y = 1;

	return NULL;
}

void *thread_process_reader(void *arg)
{
	rcu_reader();

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tu;
	pthread_t tpr;

	if (pthread_create(&tu, NULL, thread_update, NULL))
		abort();
	if (pthread_create(&tpr, NULL, thread_process_reader, NULL))
		abort();
	if (pthread_join(tu, NULL))
		abort();
	if (pthread_join(tpr, NULL))
		abort();
	assert(__unbuffered_tpr_y == 0 || __unbuffered_tpr_x == 1);

	return 0;
}
