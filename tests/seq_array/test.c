#ifdef NO_SEQ
/* Use macro black magic to disable srcu_readers_seq_idx */

/* Expand to t if p is 1. Expand to e if p is 0 */
#define MACRO_UTIL_IF(p, t, e) MACRO_UTIL_IF_I(p, t, e)
#define MACRO_UTIL_IF_I(p, t, e) MACRO_UTIL_IF_DEF_##p(t, e)
#define MACRO_UTIL_IF_DEF_0(t, e) e
#define MACRO_UTIL_IF_DEF_1(t, e) t

/*
 * Disable srcu_readers_seq_idx callers while not messing the definition up.
 * Detect the definition by check if the first argument begins with "struct".
 * This assumes that the argument doesn't start with parenthesis. This could be
 * fixed, but it shouldn't matter for now.
 */
#define srcu_readers_seq_idx(sp, idx) \
	MACRO_UTIL_IF(MACRO_UTIL_STARTS_STRUCT(sp), \
		      srcu_readers_seq_idx(sp, idx), \
		      0)

#define MACRO_UTIL_FIRST_ARG(x, ...) x

/* Expand to 1 iff x begins with struct. */
#define MACRO_UTIL_STARTS_STRUCT(...) \
	MACRO_UTIL_IS_EMPTY \
	(MACRO_UTIL_STARTS_STRUCT_H(MACRO_UTIL_STARTS_STRUCT_DEF##__VA_ARGS__))
#define MACRO_UTIL_STARTS_STRUCT_DEFstruct ,
#define MACRO_UTIL_STARTS_STRUCT_DEF(...) MACRO_UTIL_STARTS_STRUCT_NOTSTRUCT
#define MACRO_UTIL_STARTS_STRUCT_H(...) \
	MACRO_UTIL_FIRST_ARG(__VA_ARGS__)

/* Check if x expands to nothing. More or less copied from Boost.Preprocessor */
#define MACRO_UTIL_IS_EMPTY(x) \
	MACRO_UTIL_IS_EMPTY_I(x MACRO_UTIL_IS_EMPTY_HELPER)
#define MACRO_UTIL_IS_EMPTY_I(x) \
	MACRO_UTIL_SECOND_OF_PAIR((MACRO_UTIL_IS_EMPTY_DEF_ ## x()))
#define MACRO_UTIL_IS_EMPTY_DEF_MACRO_UTIL_IS_EMPTY_HELPER 1, MACRO_UTIL_ONE
#define MACRO_UTIL_IS_EMPTY_HELPER() , 0

#define MACRO_UTIL_SECOND(x, y) y
#define MACRO_UTIL_SECOND_OF_PAIR(p) MACRO_UTIL_SECOND p

#define MACRO_UTIL_ONE() 1

#endif

#include <src/combined_source.c>

struct state {
	int x;
	int y;
};

struct state writer;
struct state read0;
struct state read1;

DEFINE_SRCU(ss);

void *thread_update(void *arg)
{
	writer.x = 1;
#ifndef FORCE_FAILURE
	synchronize_srcu(&ss);
#endif
	writer.y = 1;

	return NULL;
}

void *thread_process_reader(void *arg)
{
	int idx;
	struct state *read_state = (struct state *) arg;

	idx = srcu_read_lock(&ss);
	read_state->x = writer.x;
	read_state->y = writer.y;
	srcu_read_unlock(&ss, idx);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t update_thread;
	pthread_t read_thread0;
	pthread_t read_thread1;

	if (pthread_create(&update_thread, NULL, thread_update, NULL))
		abort();
	if (pthread_create(&read_thread0, NULL, thread_process_reader, &read0))
		abort();
#ifndef TWO_THREADS
	if (pthread_create(&read_thread1, NULL, thread_process_reader, &read1))
		abort();
#endif

	if (pthread_join(update_thread, NULL))
		abort();
	if (pthread_join(read_thread0, NULL))
		abort();
#ifndef TWO_THREADS
	if (pthread_join(read_thread1, NULL))
		abort();
#endif
	assert(read0.x == 1 || read0.y == 0);
	assert(read1.x == 1 || read1.y == 0);

#ifdef ASSERT_END
	assert(0);
#endif

	return 0;
}
