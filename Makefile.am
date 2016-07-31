# Compile source files because GCC has better error messages than CBMC.
test_compile_sources =
headers =
extra_dist =

include_dirs = -I$(srcdir)/include/ -I$(srcdir)/empty_includes/ -I$(srcdir)/empty_includes_arch/

include %D%/include/Makefile.am
include %D%/src/Makefile.am
include %D%/tests/Makefile.am

noinst_LIBRARIES = libtest-compile.a
noinst_HEADERS = $(headers)
libtest_compile_a_SOURCES = $(test_compile_sources)
libtest_compile_a_CPPFLAGS = -DRUN -DNR_CPUS=2 $(include_dirs)

extra_dist += empty_includes

EXTRA_DIST = $(extra_dist)

DISTCLEANFILES = linux_source

# configure needs to know the location of the Linux source code.
AM_DISTCHECK_CONFIGURE_FLAGS = --with-linux=$(abs_builddir)/linux_source
