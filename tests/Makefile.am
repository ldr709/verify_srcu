tests =

include %D%/test_script_tests/Makefile.am
include %D%/valtiny_tests/Makefile.am
include %D%/percpu/Makefile.am

TESTS = $(tests)
extra_dist += %D%/test_script.sh $(TESTS)

# Tests specify the minimum number of cpus they must work on in order to
# pass/fail. Below that quantity of cpus they are assumed to always pass.

TEST_EXTENSIONS = .pass .fail
PASS_LOG_COMPILER = $(srcdir)/%D%/test_script.sh
AM_PASS_LOG_FLAGS = --should-pass
FAIL_LOG_COMPILER = $(srcdir)/%D%/test_script.sh
AM_FAIL_LOG_FLAGS = --should-fail

AM_CBMC_FLAGS = -I. -I$(srcdir) $(include_dirs) -32 --pointer-check

AM_TESTS_ENVIRONMENT = CBMC_FLAGS='$(AM_CBMC_FLAGS) $(CBMC_FLAGS)'; export CBMC_FLAGS;
