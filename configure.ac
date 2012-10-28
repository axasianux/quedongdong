#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([myupan], [1.0], [dongdong.que@asianux.com])
AC_CONFIG_SRCDIR([src/upan.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O

AC_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES([IUPAN],[dbus-1 gconf-2.0 glib-2.0 gobject-2.0])
AC_SUBST(IUPAN_CFLAGS)
AC_SUBST(IUPAN_LIBS)
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile)
