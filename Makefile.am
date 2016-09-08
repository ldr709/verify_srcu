# Compile source files because GCC has better error messages than CBMC.
test_compile_sources =
headers =
nodist_headers =
extra_dist =

include_dirs = -I$(srcdir)/include/ -I$(srcdir)/empty_includes/ -I$(srcdir)/empty_includes_arch/ -Iinclude/

include %D%/include/Makefile.am
include %D%/src/Makefile.am
include %D%/tests/Makefile.am

# Modified SRCU for testing.
modified_srcu_h = include/linux/srcu.h
modified_srcu_c = srcu.c
modified_srcu_output = $(modified_srcu_h) $(modified_srcu_c)
modified_srcu_input = linux_source/include/linux/srcu.h linux_source/kernel/rcu/srcu.c
modified_srcu_script = $(srcdir)/modify_srcu.awk
nodist_headers += $(modified_srcu_h)
BUILT_SOURCES = $(modified_srcu_output)
MOSTLYCLEANFILES = $(modified_srcu_output)
extra_dist += $(modified_srcu_script)
$(modified_srcu_c) : $(modified_srcu_script) Makefile $(modified_srcu_input)
	$(MKDIR_P) include/linux
	$(AWK) -f $(modified_srcu_script) $(modified_srcu_input) $(modified_srcu_output)
$(modified_srcu_h) : $(modified_srcu_c)

noinst_LIBRARIES = libtest-compile.a
noinst_HEADERS = $(headers)
nodist_noinst_HEADERS = $(nodist_headers)
libtest_compile_a_SOURCES = $(test_compile_sources)
libtest_compile_a_CPPFLAGS = -DRUN -DNR_CPUS=2 $(include_dirs)

extra_dist += empty_includes

EXTRA_DIST = $(extra_dist)

DISTCLEANFILES = linux_source

# configure needs to know the location of the Linux source code.
AM_DISTCHECK_CONFIGURE_FLAGS = --with-linux=$(abs_builddir)/linux_source
