AC_INIT([luacppinterface], [1.0], [bug-report@address])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_AR
AX_CXX_COMPILE_STDCXX_11


AC_ARG_ENABLE([gcov],
  [AS_HELP_STRING([--enable-gcov],
    [use Gcov to test the test suite])],
    [],
    [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])


AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile LuaCppInterface/Makefile tests/Makefile])
AC_OUTPUT
