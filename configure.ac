AC_INIT([Verify SRCU], [0.1.0])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

AC_CONFIG_SRCDIR([src/combined_source.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AM_PROG_AR
AC_PROG_RANLIB

AC_DEFINE([__KERNEL__], [], [Make the kernel think that it is getting compiled])
AC_DEFINE([_GNU_SOURCE], [], [Tell the standard headers to include everything])

dnl TODO: Check for more features of the compiler instead of assuming GCC. Some
dnl error checking might be helpful too.

AC_CHECK_HEADERS([inttypes.h limits.h stddef.h stdlib.h string.h])

AC_TYPE_SIZE_T

AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_C_TYPEOF

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
