#include <src/combined_source.c>

int main(int argc, char** argv)
{
#ifdef FAIL
	BUG();
#endif
#ifdef MIN_CPUS_FAIL
#if NR_CPUS >= MIN_CPUS_FAIL
	BUG();
#endif
#endif

	return 0;
}
