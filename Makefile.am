# Compile source files because GCC has better error messages than CBMC.
test_compile_sources =
headers =

include %D%/include/Makefile.am
include %D%/src/Makefile.am
#include %D%/test/Makefile.am

noinst_LIBRARIES = libtest-compile.a
noinst_HEADERS = $(headers)
libtest_compile_a_SOURCES = $(test_compile_sources)
libtest_compile_a_CPPFLAGS = -DRUN -DNR_CPUS=2 -I$(srcdir)/include/ -I$(srcdir)/empty_includes/ -I$(srcdir)/empty_includes_arch/
