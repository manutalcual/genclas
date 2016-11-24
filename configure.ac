AC_INIT([genclas], [0.1.0], [manuel@sisdetec.es])
AC_CONFIG_SRCDIR([src/main.cc])
AM_INIT_AUTOMAKE([genclas], [0.1.0])
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/types.h sys/socket.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

AC_CONFIG_FILES([Makefile etc/Makefile src/Makefile])
AC_OUTPUT
