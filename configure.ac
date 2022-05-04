#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mcheck], [1.0.0], [chenyanchang1990@162.com])
AC_CONFIG_SRCDIR([mcheck.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])

AC_CANONICAL_HOST

# Checks for programs.
AC_LANG(C)
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([malloc.h stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
                 example/Makefile])
AC_OUTPUT
