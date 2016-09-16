#include <src/combined_source.c>

struct test_per_cpu_array {
	unsigned long c[2];
	unsigned long seq[2];
};

DEFINE_PER_CPU(struct test_per_cpu_array, per_cpu_data);

struct test_per_cpu_array __percpu *per_cpu_ref = &per_cpu_data;

void *thread(void *arg)
{
	this_cpu_inc(per_cpu_ref->c[0]);
	smp_mb();
	this_cpu_inc(per_cpu_ref->seq[0]);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t0;
	pthread_t t1;

	if (pthread_create(&t0, NULL, thread, NULL))
		abort();
	if (pthread_create(&t1, NULL, thread, NULL))
		abort();
	if (pthread_join(t0, NULL))
		abort();
	if (pthread_join(t1, NULL))
		abort();

	unsigned long sum_c = 0;
	sum_c += READ_ONCE(per_cpu_ptr(per_cpu_ref, 0)->c[0]);
	sum_c += READ_ONCE(per_cpu_ptr(per_cpu_ref, 1)->c[0]);

	unsigned long sum_seq = 0;
	sum_seq += READ_ONCE(per_cpu_ptr(per_cpu_ref, 0)->seq[0]);
	sum_seq += READ_ONCE(per_cpu_ptr(per_cpu_ref, 1)->seq[0]);

	assert(sum_c == 2 && sum_seq == 2);

	return 0;
}
